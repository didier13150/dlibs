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
#include <syslog.h>
#include "config.h"
#include "testdlog.h"
#include "dlog.h"
#include "test.h"
#include "dsqlite.h"
#include "dsettings.h"
#ifdef DLIBS_HAVE_MYSQL
  #include "dmysql.h"
#endif
#ifdef DLIBS_HAVE_PGSQL
  #include "dpgsql.h"
#endif

#define LOGFILE  "testdlog.log"
#define LOGFILE2 "testdlog2.log"
#define LOGFILE3 "/tmp/azerty/testdlog3.log"
#define DBLOGFILE "testdlog.db"
#define PORT 12346

void TestDLog::logfile_test()
{
	DLogger * log = 0;
	DLogParams params;
	DLogEngine * engine = 0;
	bool status = false;
	DString today;

	log = DLogger::getInstance();
	TEST_ASSERT_MSG( log != 0, "Can not get logger instance" )
	params.mode = DLogShared::OPENCLOSE;
	params.minlevel = DLogShared::NONE;
	params.optionnal["dateformat"] = "%Y-%m-%d";
	params.optionnal["pattern"] = "%SYSTEM_ID %DATE - %TYPE - %MESSAGE";
	params.specific["filename"] = LOGFILE;

	log->addUserVar( "%SYSTEM_ID" );
    log->setupUserVar ( "%SYSTEM_ID", "DLog" );

	engine = log->addLogEngine ( DLogEngine::FILE, params );
	TEST_ASSERT_MSG( engine != 0, "Can not add log file engine" )

	log->debug( "Debug message" );
	log->verbose( "Verbose message" );
	log->info( "Info message" );
	log->signal( "Signal message" );
	log->warning( "Warning message" );
	log->error( "Error message" );
	log->critical( "Critical message" );
	log->insertMessage ( "Message without level", DLogShared::NONE );

	today = DString::Now( "%Y-%m-%d" );
	log->removeLogEngine ( engine );
	log->close();
	DLogger::deleteInstance();

	std::ifstream file;
	DString buffer, content, awaiting = "";

	for ( int i = 0 ; i < 80 ; i++ )
	{
		awaiting += "-";
	}
	awaiting += "\n\n";
	awaiting += "DLog " + today + " - DEBUG - Debug message\n";
	awaiting += "DLog " + today + " - INFOS - Verbose message\n";
	awaiting += "DLog " + today + " - INFOS - Info message\n";
	awaiting += "DLog " + today + " - SIGNL - Signal message\n";
	awaiting += "DLog " + today + " - WARNG - Warning message\n";
	awaiting += "DLog " + today + " - ERROR - Error message\n";
	awaiting += "DLog " + today + " - CRITL - Critical message\n";
	awaiting += "Message without level\n";

	file.open ( params.specific["filename"].c_str() );
	while ( getline ( file, buffer ) )
	{
		content += buffer + "\n";
	}
	file.close();

	TEST_ASSERT_MSG( content == awaiting, "Log file content is corrupted" )

	int removed = remove( LOGFILE );
	TEST_ASSERT_MSG( removed == 0, "Can not deleting log file" )
	
	DLogEngineFile * filelog = new DLogEngineFile( LOGFILE2, DLogShared::PERSISTANT );
	status = filelog->open();
	TEST_ASSERT_MSG( status, "Cannot open log file #2" )
	filelog->close();
	
	TEST_ASSERT_MSG( filelog->getFileName() == LOGFILE2, "Can not get log file name" )
	removed = remove( LOGFILE2 );
	TEST_ASSERT_MSG( removed == 0, "Can not deleting log file #2" )
	
	filelog->setFileName( LOGFILE3, DLogShared::PERSISTANT ); 
	status = filelog->open();
	TEST_ASSERT_MSG( ! status, "Can open impossible log file #3" )
	delete filelog;
}

void TestDLog::stream_test()
{
	DLogger * log = 0;
	DLogParams params;
	DLogEngine * console = 0, * console2 = 0, * console3 = 0;
	std::streambuf *backup;
	std::ostringstream stream;
	DString buffer, reference;
	bool status = false;

	log = DLogger::getInstance();
	TEST_ASSERT_MSG( log != 0, "Can not get logger instance" )
	params.minlevel = DLogShared::DEBUG;

	console = log->addLogEngine ( DLogEngine::STDOUT, params );
	console2 = log->addLogEngine ( DLogEngine::STDOUT, params );
	console3 = new DLogEngineStdout();
	status = console3->open();
	TEST_ASSERT_MSG( status, "Can not open stdout" )
	log->addLogEngine( console3 );
	TEST_ASSERT_MSG( console != 0, "Can not add stdout engine" )
	TEST_ASSERT_MSG( console == console2, "Get none sigleton stdout " )
	log->removeLogEngine( console3 );
	delete( console3 );

	// Redirect stdout to buffer
	backup = std::cout.rdbuf();
	std::cout.rdbuf( stream.rdbuf() );
	
	log->debug( "Debug message" );
	reference = "Debug message\n";
	log->verbose( "Verbose message" );
	reference += "Verbose message\n";
	log->info( "Info message" );
	reference += "Info message\n";
	log->signal( "Signal message" );
	reference += "Signal message\n";
	log->warning( "Warning message" );
	reference += "Warning message\n";
	log->error( "Error message" );
	reference += "Error message\n";
	log->critical( "Critical message" );
	reference += "Critical message\n";
	
	// Get stream and restore stdout
	std::cout.rdbuf(backup);
	buffer = stream.str();
	
	TEST_ASSERT_MSG( buffer == reference, "Wrong stream output" )

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
	params.specific["sockbufsize"] = "256";

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

void TestDLog::socket2_test()
{
	DLogger * log = 0;
	DLogParams params;
	DLogEngine * sockclient = 0;
	DString buffer;
	int err;

	log = DLogger::getInstance();
	TEST_ASSERT_MSG( log != 0, "Can not get logger instance" )
	params.mode = DLogShared::OPENCLOSE;
	params.minlevel = DLogShared::DEBUG;
	params.optionnal["dateformat"] = "%Y-%m-%d";
	params.optionnal["pattern"] = "%TYPE - %MESSAGE";
	buffer.setNum( PORT );
	buffer.prepend( "localhost2222aa:33333" );
	params.specific["sockhost"] = buffer;

	sockclient = log->addLogEngine ( DLogEngine::SOCKET, params );
	TEST_ASSERT_MSG( sockclient != 0, "Can not add socket engine" )
	TEST_ASSERT_MSG( sockclient->open() == false, "Bad hostname make valid Log socket" )
	TEST_ASSERT_MSG( sockclient->isValid() == false, "Bad hostname make valid Log socket" )
	sockclient->close();
	log->close();
	DLogger::deleteInstance();
}

void TestDLog::syslog_test()
{
	DLogger * log = 0;
	DLogParams params;
	DLogEngine * syslog = 0;
	DString buffer;

	log = DLogger::getInstance();
	TEST_ASSERT_MSG( log != 0, "Can not get logger instance" )
	params.mode = DLogShared::PERSISTANT;
	params.specific["appname"] = "DLog Syslog Test";
	buffer.setNum( LOG_USER );
	params.specific["facility"] = buffer;
	params.minlevel = DLogShared::DEBUG;

	syslog = log->addLogEngine ( DLogEngine::SYSLOG, params );
	TEST_ASSERT_MSG( syslog != 0, "Can not add syslog engine" )
	
	log->debug( "Debug message" );
	log->verbose( "Verbose message" );
	log->info( "Info message" );
	log->signal( "Signal message" );
	log->warning( "Warning message" );
	log->error( "Error message" );
	log->critical( "Critical message" );
	
	log->insertMessage ( "None level message", DLogShared::NONE );

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

void TestDLog::sqlite2_test()
{
	DLogger * log = DLogger::getInstance();
	DLogParams params;

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
    dbparams.base = "/tmp/dlibs.db";

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


	int removed = remove( "/tmp/dlibs.db" );
	TEST_ASSERT_MSG( removed == 0, "Can not deleting database file" )
}

void TestDLog::mysql_test()
{
#ifdef DLIBS_HAVE_MYSQL
	DLogger * log = DLogger::getInstance();
	DLogParams params;
	DSettings sets;
	DString dbbase, dbuser, dbpasswd, dbhost, dbport;
	int err;
	
	err = sets.setFileName ( "test-settings.xml" );
	if ( err != DSettings::SUCCESS )
	{
		TEST_FAIL( "Can not specify settings file." )
		dbbase = "test";
		dbuser = "root";
		dbpasswd = "";
	}
	
	err = sets.readEntry ( "/settings/mysql/base", dbbase );
	if ( err != DSettings::SUCCESS )
	{
		TEST_FAIL( "Can not read entry for database name." )
		dbbase = "test";
	}
	
	err = sets.readEntry ( "/settings/mysql/user", dbuser );
	if ( err != DSettings::SUCCESS )
	{
		TEST_FAIL( "Can not read entry for database user." )
		dbuser = "root";
	}
	
	err = sets.readEntry ( "/settings/mysql/password", dbpasswd );
	if ( err != DSettings::SUCCESS )
	{
		TEST_FAIL( "Can not read entry for database password." )
		dbpasswd = "";
	}
	
	err = sets.readEntry ( "/settings/mysql/host", dbhost );
	if ( err != DSettings::SUCCESS )
	{
		TEST_FAIL( "Can not read entry for database hostname." )
		dbhost = "localhost";
	}
	
	err = sets.readEntry ( "/settings/mysql/port", dbport );
	if ( err != DSettings::SUCCESS )
	{
		dbport = "3306";
	}

	// specific to dmysql
	params.specific["dbtype"] = "dmysql";
	params.specific["dbuser"] = dbuser;
	params.specific["dbpassword"] = dbpasswd;
	params.specific["dbhost"] = dbhost;
	params.specific["dbbase"] = dbbase;
	params.specific["dbport"] = dbport;
	params.specific["dbcreate"] = "CREATE TABLE applog (date VARCHAR(20), level VARCHAR(5), message TEXT);";
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
		TEST_FAIL( "Select all rows from table failed" )
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

void TestDLog::params_test()
{
	DLogParams params;
	DString buffer, ref;
	std::ostringstream stream;
	
	TEST_ASSERT_MSG( params.toString( DLogShared::NONE ) == "NONE", "Bad export to string (level)" )
	TEST_ASSERT_MSG( params.toString( DLogShared::DEBUG ) == "DEBUG", "Bad export to string (level)" )
	TEST_ASSERT_MSG( params.toString( DLogShared::VERBOSE ) == "VERBOSE", "Bad export to string (level)" )
	TEST_ASSERT_MSG( params.toString( DLogShared::INFO ) == "INFO", "Bad export to string (level)" )
	TEST_ASSERT_MSG( params.toString( DLogShared::SIGNALS ) == "SIGNALS", "Bad export to string (level)" )
	TEST_ASSERT_MSG( params.toString( DLogShared::WARNING ) == "WARNING", "Bad export to string (level)" )
	TEST_ASSERT_MSG( params.toString( DLogShared::ERROR ) == "ERROR", "Bad export to string (level)" )
	TEST_ASSERT_MSG( params.toString( DLogShared::CRITICAL ) == "CRITICAL", "Bad export to string (level)" )
	TEST_ASSERT_MSG( params.toString( DLogShared::PERSISTANT ) == "PERSISTANT", "Bad export to string (mode)" )
	TEST_ASSERT_MSG( params.toString( DLogShared::OPENCLOSE ) == "OPENCLOSE", "Bad export to string (mode)" )
	params.specific["dbtype"] = "dsqlite";
	params.minlevel = DLogShared::INFO;
	params.optionnal["dateformat"] = DString::getFormat ( DString::ISO_DATE );
	
	ref = "DLogParams:\n\toptionnal[dateformat] = %Y-%m-%d\n\toptionnal[pattern] = %DATE %TYPE %MESSAGE\n";
	ref += "\tspecific[dbtype] = dsqlite\n\tMinimum log level = INFO\n\tMode = OPENCLOSE\n";
	
	stream << params;
	TEST_ASSERT_MSG( stream.str() == ref, "Wrong stream output" )
}

void TestDLog::no_close_test()
{
	DLogger * log = 0;
	DLogParams params;
	DLogEngineSyslog * syslog = new DLogEngineSyslog( "DLog Syslog Test" );
	DString buffer;

	log = DLogger::getInstance();
	TEST_ASSERT_MSG( log != 0, "Can not get logger instance" )
	params.mode = DLogShared::PERSISTANT;
	buffer.setNum( LOG_USER );
	params.specific["facility"] = buffer;
	params.minlevel = DLogShared::INFO;

	log->addLogEngine ( syslog );
	TEST_ASSERT_MSG( syslog != 0, "Can not add syslog engine" )
	
	log->debug( "Debug message" );
	log->verbose( "Verbose message" );
	log->info( "Info message" );
	log->signal( "Signal message" );
	log->warning( "Warning message" );
	log->error( "Error message" );
	log->critical( "Critical message" );

	log->close();
	DLogger::deleteInstance();
}

void TestDLog::logger_test()
{
	DLogger * log = 0;
	log = DLogger::getInstance();
	
	TEST_ASSERT_MSG( log->addAndSetupUserVar( "%PARENT", "this" ), "Cannot setup custom variable" )
	TEST_ASSERT_MSG( ! log->addAndSetupUserVar( "%PARENT", "other" ), "Can redefine custom variable" )
	log->addAndSetupUserVar( "%BROTHER", "this" );
	log->removeUserVar( "%BROTHER" );
	TEST_ASSERT_MSG( log->addAndSetupUserVar( "%BROTHER", "this" ), "Cannot setup custom variable after deletion" )
	
	DLogger::deleteInstance();
}

void TestDLog::engine_test()
{
	DLogEngine * engine;
	DLogParams params;
	
	engine = new DLogEngineSyslog();
	
	TEST_ASSERT_MSG( engine->getDateFormat() == "%Y-%m-%d %H:%M:%S", "Engine report bad default date format" )
	TEST_ASSERT_MSG( engine->getMinLogLevel() == DLogShared::INFO, "Engine report bad default min log level" )
	TEST_ASSERT_MSG( engine->getLogPattern() == "%DATE %TYPE %MESSAGE", "Engine report bad default log pattern" )
	TEST_ASSERT_MSG( engine->getMode() == DLogShared::PERSISTANT, "Engine report bad default mode" )
	
	params.mode = DLogShared::OPENCLOSE;
	params.optionnal["dateformat"] = "%Y-%m-%d";
	params.optionnal["pattern"] = "%TYPE - %MESSAGE";
	params.minlevel = DLogShared::WARNING;
	engine->setParam( params );
	
	TEST_ASSERT_MSG( engine->getDateFormat() == "%Y-%m-%d", "Engine report bad date format" )
	TEST_ASSERT_MSG( engine->getMinLogLevel() == DLogShared::WARNING, "Engine report bad min log level" )
	TEST_ASSERT_MSG( engine->getLogPattern() == "%TYPE - %MESSAGE", "Engine report bad log pattern" )
	TEST_ASSERT_MSG( engine->getMode() == DLogShared::OPENCLOSE, "Engine report bad mode" )
	
	delete engine;
}

int main()
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

