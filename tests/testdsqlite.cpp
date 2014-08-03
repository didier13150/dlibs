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
 *     (___)_)   File : testdsqlite.cpp                     ||--|| *          *
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
 *   Unit Test for DSqlite                                                    *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdsqlite.h"
#include "test.h"

#define DBFILE "testdsqlite.db"

#ifndef WITH_EXCEPTIONS
  #define COMPILE_WITH_EXCEPTIONS 0
#else
  #define COMPILE_WITH_EXCEPTIONS 1
  #include "dexception.h"
#endif

void TestDSqlite::constructor_test()
{
	DSQLite * db = 0;
	DDatabaseParams params;
	DDatabaseResult results;
	DDatabaseRows::const_iterator it;

	params.base = DBFILE;

#if COMPILE_WITH_EXCEPTIONS
    db = new DSQLite ( true );
#else
	db = new DSQLite ();
#endif
	db->setParams ( params );

	results = db->open();
	TEST_ASSERT_MSG( results.errnb == 0, "Database not opened" )

	results = db->exec ( "CREATE TABLE mytable (field1, field2);" );
	TEST_ASSERT_MSG( results.errnb == 0, "Query not executed successfully (create table)" )

	results = db->exec ( "INSERT INTO mytable(field1, field2) VALUES(1, 2);" );
	TEST_ASSERT_MSG( results.errnb == 0, "Query not executed successfully (insert 1)" )

	results = db->exec ( "INSERT INTO mytable(field1, field2) VALUES(2, NULL);" );
	TEST_ASSERT_MSG( results.errnb == 0, "Query not executed successfully (insert 2)" )

	results = db->exec ( "SELECT * FROM mytable WHERE field1 = 1;" );
	TEST_ASSERT_MSG( results.errnb == 0, "Query not executed successfully (select 1)" )

	TEST_ASSERT_MSG( results.rows.size() == 1, "Wrong number of row in database sqlite" )
	it = results.rows.begin();
	TEST_ASSERT_MSG( it != results.rows.end(), "Wrong number of row in database sqlite" )
	TEST_ASSERT_MSG( it->at("field1") == "1", "Wrong first record on database sqlite" )
	TEST_ASSERT_MSG( it->at("field2") == "2", "Wrong second record on database sqlite" )

	results = db->exec ( "SELECT * FROM mytable WHERE field1 = 2;" );
	TEST_ASSERT_MSG( results.errnb == 0, "Query not executed successfully (select 2)" )

	TEST_ASSERT_MSG( results.rows.size() == 1, "Wrong number of row in database sqlite" )
	it = results.rows.begin();
	TEST_ASSERT_MSG( it != results.rows.end(), "Wrong number of row in database sqlite" )
	TEST_ASSERT_MSG( it->at("field1") == "2", "Wrong first record on database sqlite" )
	TEST_ASSERT_MSG( it->at("field2") == "NULL", "Wrong second record on database sqlite" )

	// Clean up
	db->close();
    delete db;

	int removed = remove( DBFILE );
	TEST_ASSERT_MSG( removed == 0, "Can not deleting database file" )
}

int main( int argc, char** argv )
{
	TestDSqlite ets;
#ifdef TEST_HTML
	std::ofstream file;
	Test::HtmlOutput html;

	file.open( "dsqlite.html" );
	ets.run( html );
	html.generate( file, true, "DSqlite" );
	file.close();
#endif

#ifdef TEST_STDOUT
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
#endif
	return EXIT_SUCCESS;
}
