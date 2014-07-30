/******************************************************************************
 *      ____              ____    _       _   _                               *
 *     /# /_\_           |  _ \  (_)   __| | (_)   ___   _ __                 *
 *    |  |/o\o\          | | | | | |  / _` | | |  / _ \ | '__|                *
 *    |  \\_/_/          | |_| | | | | (_| | | | |  __/ | |                   *
 *   / |_   |            |____/  |_|  \__,_| |_|  \___| |_|                   *
 *  |  ||\_ ~|                                                                *
 *  |  ||| \/                                                                 *
 *  |  |||       Project : DLibs : usefull tools for C++ programming          *
 *  \//  |                                                                    *
 *   ||  |       Developper : Didier FABERT <didier.fabert@gmail.com>         *
 *   ||_  \      Date : 2009, April                                           *
 *   \_|  o|                                             ,__,                 *
 *    \___/      Copyright (C) 2009 by didier fabert     (oo)____             *
 *     ||||__                                            (__)    )\           *
 *     (___)_)   File : testdmysql.cpp                      ||--|| *          *
 *                                                                            *
 *   This program is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU General Public License as published by     *
 *   the Free Software Foundation; either version 3 of the License, or        *
 *   (at your option) any later version.                                      *
 *                                                                            *
 *   This program is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *   GNU General Public License for more details.                             *
 *                                                                            *
 *   You should have received a copy of the GNU General Public License        *
 *   along with this program; if not, write to the                            *
 *   Free Software Foundation, Inc.,                                          *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.             *
 *                                                                            *
 *   Unit Test for DMySQL                                                     *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdmysql.h"
#include "config.h"

#ifndef WITH_EXCEPTIONS
  #define COMPILE_WITH_EXCEPTIONS 0
#else
  #define COMPILE_WITH_EXCEPTIONS 1
  #include "dexception.h"
#endif
#ifndef DBUSER
#define DBUSER "root"
#endif
#ifndef DBPASSWD
#define DBPASSWD "obione"
#endif
#ifndef DBBASE
#define DBBASE "test"
#endif
void TestDMySQL::exception_enabled()
{
#if COMPILE_WITH_EXCEPTIONS
    std::cout << std::endl << "Exception enabled" << std::endl;
#else
    std::cout << std::endl << "Exception disabled" << std::endl;
#endif
}

void TestDMySQL::socket_connect_test()
{
	DMySQL * db = 0;
	DDatabaseParams params;
	DDatabaseResult results;
	DDatabaseRows::const_iterator it;

	params.host = "localhost";
	params.user = DBUSER;
	params.password = DBPASSWD;
	params.base = DBBASE;
	
#if COMPILE_WITH_EXCEPTIONS
    db = new DMySQL ( true );
#else
	db = new DMySQL ();
#endif
	db->setParams ( params );
	
	results = db->open();
	if ( results.errnb != 0 )
	{
		db->close();
		delete db;
		return;
	}
	
	TEST_ASSERT_MSG( results.errnb == 0, "Database not opened" )
	// Clean up
	db->close();
    delete db;
}
void TestDMySQL::network_connect_test()
{
	DMySQL * db = 0;
	DDatabaseParams params;
	DDatabaseResult results;
	DDatabaseRows::const_iterator it;

	params.host = "127.0.0.1";
	params.user = DBUSER;
	params.password = DBPASSWD;
	params.base = DBBASE;
	
#if COMPILE_WITH_EXCEPTIONS
    db = new DMySQL ( true );
#else
	db = new DMySQL ();
#endif
	db->setParams ( params );
	
	results = db->open();
	if ( results.errnb != 0 )
	{
		db->close();
		delete db;
		return;
	}
	
	TEST_ASSERT_MSG( results.errnb == 0, "Database not opened" )
	// Clean up
	db->close();
    delete db;
}

void TestDMySQL::insert_test()
{
	DMySQL * db = 0;
	DDatabaseParams params;
	DDatabaseResult results;
	DDatabaseRows::const_iterator it;

	params.host = "localhost";
	params.user = DBUSER;
	params.password = DBPASSWD;
	params.base = DBBASE;
	
#if COMPILE_WITH_EXCEPTIONS
    db = new DMySQL ( true );
#else
	db = new DMySQL ();
#endif
	db->setParams ( params );
	
	results = db->open();
	if ( results.errnb != 0 )
	{
		db->close();
		delete db;
		return;
	}
	
	results = db->exec ( "CREATE TABLE mytable (field1 INT(8), field2 INT(8) );" );
	if ( results.errnb != 0 )
	{
		db->close();
		delete db;
		TEST_ASSERT_MSG( results.errnb == 0, "Query not executed successfully (create table)" )
		return;
	}
	
	results = db->exec ( "INSERT INTO mytable(field1, field2) VALUES(1, 2);" );
	if ( results.errnb != 0 )
	{
		db->close();
		delete db;
		TEST_ASSERT_MSG( results.errnb == 0, "Query not executed successfully (insert 1)" )
		return;
	}
	
	results = db->exec ( "INSERT INTO mytable(field1, field2) VALUES(2, NULL);" );
	if ( results.errnb != 0 )
	{
		db->close();
		delete db;
		TEST_ASSERT_MSG( results.errnb == 0, "Query not executed successfully (insert 2)" )
		return;
	}
	
	results = db->exec ( "SELECT * FROM mytable WHERE field1 = 1;" );
	if ( results.errnb != 0 )
	{
		db->close();
		delete db;
		TEST_ASSERT_MSG( results.errnb == 0, "Query not executed successfully (select 1)" )
		return;
	}
	
	TEST_ASSERT_MSG( results.rows.size() == 1, "Wrong number of row in database" )
	it = results.rows.begin();
	TEST_ASSERT_MSG( it != results.rows.end(), "Wrong number of row in database" )
	TEST_ASSERT_MSG( it->at("field1") == "1", "Wrong first record on database" )
	TEST_ASSERT_MSG( it->at("field2") == "2", "Wrong second record on database" )
	
	results = db->exec ( "SELECT * FROM mytable WHERE field1 = 2;" );
	if ( results.errnb != 0 )
	{
		db->close();
		delete db;
		TEST_ASSERT_MSG( results.errnb == 0, "Query not executed successfully (select 2)" )
		return;
	}
	
	TEST_ASSERT_MSG( results.rows.size() == 1, "Wrong number of row in database" )
	it = results.rows.begin();
	TEST_ASSERT_MSG( it != results.rows.end(), "Wrong number of row in database" )
	TEST_ASSERT_MSG( it->at("field1") == "2", "Wrong first record on database" )
	TEST_ASSERT_MSG( it->at("field2") == "NULL", "Wrong second record on database" )
	
	
	results = db->exec ( "DROP TABLE mytable;" );
	if ( results.errnb != 0 )
	{
		db->close();
		delete db;
		TEST_ASSERT_MSG( results.errnb == 0, "Query not executed successfully (create table)" )
		return;
	}
	
	// Clean up
	db->close();
    delete db;
}

int main( int argc, char** argv )
{
	std::ofstream file;
	TestDMySQL ets;
	
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );
	Test::HtmlOutput html;
	
	file.open( "dmysql.html" );
	ets.run( html );
	html.generate( file, true, "DMySQL" );
	file.close();
	
	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
}
/*
#include <mysql.h>
int main( int argc, char** argv )
{
	MYSQL mysql, *connect;
	if (mysql_library_init(0, NULL, NULL)) {
		fprintf(stderr, "could not initialize MySQL library\n");
		exit(1);
	}
	
	connect = mysql_init( &mysql );
	if( connect == NULL )
	{
		printf("\nFailed to initate MySQL connection");
		exit(1);
	}
	//now you can call any MySQL API function you like
	if ( ! mysql_real_connect(&mysql,"localhost","root","obione","test",0,NULL,0))
	{ 
		printf( "Failed to connect to MySQL: Error: %s\n",
		mysql_error(&mysql)); 
		exit(1);
	}
	printf("Logged on to database sucessfully\n");
	printf( "Mysql: %ld, Connect: %ld\n", &mysql, connect );
	mysql_close(&mysql);
	
	mysql_library_end();
}*/
