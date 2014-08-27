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
 *     (___)_)   File : testdlog.cpp                        ||--|| *          *
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
 *   Unit Test for DLog                                                       *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "config.h"
#include "testdlog.h"
#include "test.h"
#include "dsqlite.h"
#ifdef DLIBS_HAVE_MYSQL
  #include "dmysql.h"
#endif
#ifdef DLIBS_HAVE_PGSQL
  #include "dpgsql.h"
#endif

#define LOGFILE "testdlog.log"
#define DBLOGFILE "testdlog.db"
#define PORT 12346

void TestDLog::logfile_test()
{
	DLogger * log = 0;
	DLogParams params;
	DLogEngine * filelog = 0;
	bool success = false;
	DString today;

	log = DLogger::getInstance();
	TEST_ASSERT_MSG( log != 0, "Can not get logger instance" )
	params.mode = DLogShared::OPENCLOSE;
	params.minlevel = DLogShared::INFO;
	params.optionnal["dateformat"] = "%Y-%m-%d";
	params.optionnal["pattern"] = "%SYSTEM_ID %DATE - %TYPE - %MESSAGE";
	params.specific["filename"] = LOGFILE;

	log->addUserVar( "%SYSTEM_ID" );
    log->setupUserVar ( "%SYSTEM_ID", "DLog" );

	filelog = log->addLogEngine ( DLogEngine::FILE, params );
	TEST_ASSERT_MSG( filelog != 0, "Can not add log file engine" )

	log->insertMessage ( "Debug message", DLogShared::DEBUG );
	log->insertMessage ( "Info message", DLogShared::INFO );
	today = DString::Now( "%Y-%m-%d" );

	log->removeLogEngine ( filelog );
	log->close();
	DLogger::deleteInstance();

	std::ifstream file;
	DString buffer, content, awaiting;

	for ( int i = 0 ; i < 80 ; i++ )
	{
		awaiting += "-";
	}
	awaiting += "DLog " + today + " - INFOS - Info message";

	file.open ( params.specific["filename"].c_str() );
	while ( getline ( file, buffer ) )
	{
		content += buffer;
	}
	file.close();

	TEST_ASSERT_MSG( content.simplifyWhiteSpace() == awaiting, "Log file content is corrupted" )

	int removed = remove( LOGFILE );
	TEST_ASSERT_MSG( removed == 0, "Can not deleting log file" )
}

void TestDLog::stream_test()
{
	DLogger * log = 0;
	DLogParams params;
	DLogEngine * console = 0;

	log = DLogger::getInstance();
	TEST_ASSERT_MSG( log != 0, "Can not get logger instance" )
	params.minlevel = DLogShared::DEBUG;

	console = log->addLogEngine ( DLogEngine::STDOUT, params );
	TEST_ASSERT_MSG( console != 0, "Can not add stdout engine" )

	log->insertMessage ( "Debug message", DLogShared::DEBUG );
	log->insertMessage ( "Info message", DLogShared::INFO );

	log->debug( "Debug message" );
	log->verbose( "Verbose message" );
	log->info( "Info message" );
	log->signal( "Signal message" );
	log->warning( "Warning message" );
	log->error( "Error message" );
	log->critical( "Critical message" );

	log->removeLogEngine ( console );
	log->close();
	DLogger::deleteInstance();
}

void TestDLog::socket_test()
{
	DLogger * log = 0;
	DLogParams params;
	DLogEngine * sockclient = 0;
	DServerSock server;
	int h = -1;
	DString buffer;
	int err;

	server.setTimeout ( 1500 );
	err = server.openSock ( PORT );
	TEST_ASSERT_MSG( err == DSock::SUCCESS, "Can not open socket on server side" )
	if ( err != DSock::SUCCESS ) return;

	log = DLogger::getInstance();
	TEST_ASSERT_MSG( log != 0, "Can not get logger instance" )
	params.mode = DLogShared::PERSISTANT;
	params.minlevel = DLogShared::DEBUG;
	params.optionnal["dateformat"] = "%Y-%m-%d";
	params.optionnal["pattern"] = "%TYPE - %MESSAGE";
	buffer.setNum( PORT );
	buffer.prepend( "localhost:" );
	params.specific["sockhost"] = buffer;

	sockclient = log->addLogEngine ( DLogEngine::SOCKET, params );
	TEST_ASSERT_MSG( sockclient != 0, "Can not add socket engine" )
	TEST_ASSERT_MSG( sockclient->isValid() == true, "Log socket is not valid" )
	if ( ! sockclient->isValid() )
	{
		sockclient->close();
		log->removeLogEngine( sockclient );
		log->close();
		server.closeSock();
		return;
	}

	err = server.openConnection ( h );
	TEST_ASSERT_MSG( err == DSock::SUCCESS, "Can not open new connection on server side" )
	if ( err != DSock::SUCCESS )
	{
		sockclient->close();
		log->removeLogEngine( sockclient );
		log->close();
		server.closeSock();
		return;
	}

	log->insertMessage ( "Info message", DLogShared::INFO );
	err = server.readMessage ( h, buffer );
	TEST_ASSERT_MSG( err == DSock::SUCCESS, "Server can not read message" )
	TEST_ASSERT_MSG( buffer.simplifyWhiteSpace() == "INFOS - Info message", "Server receive wrong message" )

	sockclient->close();
	server.closeConnection ( h );
	server.closeSock();
	log->removeLogEngine ( sockclient );
	log->close();
	DLogger::deleteInstance();
}

void TestDLog::syslog_test()
{
	DLogger * log = 0;
	DLogParams params;
	DLogEngine * syslog = 0;

	log = DLogger::getInstance();
	TEST_ASSERT_MSG( log != 0, "Can not get logger instance" )
	params.specific["appname"] = "DLog Syslog Test";
	params.minlevel = DLogShared::INFO;

	syslog = log->addLogEngine ( DLogEngine::SYSLOG, params );
	TEST_ASSERT_MSG( syslog != 0, "Can not add syslog engine" )

	log->insertMessage ( "Debug message", DLogShared::DEBUG );
	log->insertMessage ( "Info message", DLogShared::INFO );

	log->removeLogEngine ( syslog );
	log->close();
	DLogger::deleteInstance();
}

void TestDLog::unintialized_test()
{
	DLogger * log = DLogger::getInstance();
	// unintialized engine ( test for unintialized engine pointer )
	DLogEngine * uninitializedlog;
	// gcc complains about var which may be used unitialized
	// it's just a test with an unitialized pointer to be sure this
	// class is safe.
	log->removeLogEngine ( uninitializedlog );
	DLogger::deleteInstance();
}

void TestDLog::sqlite_test()
{
	DLogger * log = DLogger::getInstance();
	DLogParams params;

	// specific to dsqlite
	params.specific["dbtype"] = "dsqlite";
	params.specific["dbbase"] = DBLOGFILE;
	params.specific["dbcreate"] = "CREATE TABLE applog (date, level, message);";

	// params for stdout log engine
	params.minlevel = DLogShared::INFO;
	params.optionnal["dateformat"] = DString::getFormat ( DString::ISO_DATE );
	params.optionnal["pattern"] = "INSERT INTO applog(date, level, message) VALUES(\"%DATE\", \"%TYPE\", \"%MESSAGE\");";

	// create database log engine
	DLogEngine * dblog = log->addLogEngine ( DLogEngine::DATABASE, params );

	log->insertMessage ( "Debug message", DLogShared::DEBUG );
	log->insertMessage ( "Info message", DLogShared::INFO );

	log->removeLogEngine ( dblog );
	log->close();
	DLogger::deleteInstance();

    DFactory<DDatabase> factory;
    DDatabaseParams dbparams;
    DDatabaseResult results;
	DDatabaseRows::const_iterator it;

#ifdef WITH_EXCEPTIONS
    DFactory<DDatabase>::Register ( "dsqlite", new DSQLite ( true ) );
#else
	DFactory<DDatabase>::Register ( "dsqlite", new DSQLite () );
#endif
    DDatabase * db = factory.create ( "dsqlite" );
    dbparams.base = params.specific["dbbase"];

	db->setParams ( dbparams );
	results = db->open();
	TEST_ASSERT_MSG( results.errnb == 0, "Database not opened" )
	results = db->exec ( "SELECT * FROM applog;" );
	TEST_ASSERT_MSG( results.errnb == 0, "Query not executed successfully" )
	db->close();
    delete db;

	TEST_ASSERT_MSG( results.rows.size() == 1, "Wrong number of row in database sqlite" )
	it = results.rows.begin();
	TEST_ASSERT_MSG( it != results.rows.end(), "Wrong number of row in database sqlite" )
	TEST_ASSERT_MSG( it->at("level") == "INFOS", "Wrong level on database sqlite" )
	TEST_ASSERT_MSG( it->at("message") == "Info message", "Wrong message on database sqlite" )


	int removed = remove( DBLOGFILE );
	TEST_ASSERT_MSG( removed == 0, "Can not deleting database file" )
}

void TestDLog::mysql_test()
{
#ifdef DLIBS_HAVE_MYSQL
	DLogger * log = DLogger::getInstance();
	DLogParams params;

	// specific to dmysql
	params.specific["dbtype"] = "dmysql";
	params.specific["dbuser"] = "dlibs";
	params.specific["dbpassword"] = "dlibspw";
	params.specific["dbhost"] = "localhost";
	params.specific["dbbase"] = "dlibs";
	params.specific["dbcreate"] = "CREATE TABLE applog (date, level, message);";
	// params for stdout log engine
	params.minlevel = DLogShared::INFO;
	params.optionnal["dateformat"] = DString::getFormat ( DString::ISO_DATE );
	params.optionnal["pattern"] = "INSERT INTO applog(date, level, message) VALUES(\"%DATE\", \"%TYPE\", \"%MESSAGE\");";

	// create database log engine
	DLogEngine * dblog = log->addLogEngine ( DLogEngine::DATABASE, params );

	log->insertMessage ( "Debug message", DLogShared::DEBUG );
	log->insertMessage ( "Info message", DLogShared::INFO );

	log->removeLogEngine ( dblog );
	log->close();
	DLogger::deleteInstance();

    DFactory<DDatabase> factory;
    DDatabaseParams dbparams;
    DDatabaseResult results;
	DDatabaseRows::const_iterator it;

#ifdef WITH_EXCEPTIONS
    DFactory<DDatabase>::Register ( "mysql", new DMySQL ( false ) );
#else
	DFactory<DDatabase>::Register ( "mysql", new DMySQL () );
#endif
    DDatabase * db = factory.create ( "mysql" );
    dbparams.host = params.specific["dbhost"];
    dbparams.user = params.specific["dbuser"];
    dbparams.password = params.specific["dbpassword"];
    dbparams.base = params.specific["dbbase"];

	db->setParams ( dbparams );
	results = db->open();
	if ( results.errnb != 0 )
	{
		db->close();
		delete db;
		TEST_FAIL( "Database not opened" )
		return;
	}
	
	results = db->exec ( "SELECT * FROM applog;" );
	if ( results.errnb != 0 )
	{
		db->close();
		delete db;
		TEST_FAIL( "Database not opened" )
		return;
	}
	TEST_ASSERT_MSG( results.errnb == 0, "Query not executed successfully" )

	TEST_ASSERT_MSG( results.rows.size() == 1, "Wrong number of row in database sqlite" )
	it = results.rows.begin();
	TEST_ASSERT_MSG( it != results.rows.end(), "Wrong number of row in database sqlite" )
	TEST_ASSERT_MSG( it->at("level") == "INFOS", "Wrong level on database sqlite" )
	TEST_ASSERT_MSG( it->at("message") == "Info message", "Wrong message on database sqlite" )
	db->close();
	delete db;
#endif
}


void TestDLog::pgsql_test()
{
#ifdef DLIBS_HAVE_PGSQL
#endif
}

int main( int argc, char** argv )
{
	TestDLog ets;
#ifdef TEST_HTML
	std::ofstream file;
	Test::HtmlOutput html;

	file.open( "dlog.html" );
	ets.run( html );
	html.generate( file, true, "DLog" );
	file.close();
#endif

#ifdef TEST_STDOUT
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
#endif
	return EXIT_SUCCESS;
}

