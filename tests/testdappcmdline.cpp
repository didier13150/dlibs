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
 *     (___)_)   File : testdappcmdline.cpp                 ||--|| *          *
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
 *   Unit Test for DAppCmdLine                                                *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "dappcmdline.h"
#include "testdappcmdline.h"
#include "test.h"

void TestDAppCmdLine::constructor_test()
{
	DAppCmdLine app;
	int argc = 0;
	const char * argv[] = { "/my/path/constructor_test" };
	
	if ( sizeof( argv[0] ) ) argc = sizeof( argv ) / sizeof( argv[0] );

	app.setAppVersion( "1.0.0" );
	app.addOption( "help", "Print this help", 'h' );
	app.addOption( "version", "Show version", 'v' );
	app.addOption( "prefix", "Show the prefix where dlibs are installed" );
	app.addOption( "tarname", "Show package name" );
	app.addOption( "bugreport", "Show address where bug report must be sent" );

	if ( ! app.parse( argc, const_cast<char**>(argv) ) )
	{
		TEST_FAIL( "Error on parsing command line" )
		return;
	}
}

void TestDAppCmdLine::arg_and_opt_test()
{
	DAppCmdLine app;
	int argc = 0;
	const char * argv[] = { "/my/path/constructor_test" };
	
	if ( sizeof( argv[0] ) ) argc = sizeof( argv ) / sizeof( argv[0] );

	app.setAppVersion( "1.0.0" );
	app.addOption( "help", "Print this help", 'h' );
	app.addOption( "version", "Show version", 'v' );
	app.addOption( "verylongversionstring", "Show long version", "PATH", 'l' );
	app.addArgument( "First arg" );
	app.addArgument( "Second arg" );

	if ( ! app.parse( argc, const_cast<char**>(argv) ) )
	{
		TEST_FAIL( "Error on parsing command line" )
		return;
	}
}

void TestDAppCmdLine::show_help_test()
{
	DAppCmdLine app;
	int argc = 0;
	const char * argv[] = { "/my/path/constructor_test" };
	std::streambuf *backup;
	std::ostringstream stream;
	DString buffer;

	if ( sizeof( argv[0] ) ) argc = sizeof( argv ) / sizeof( argv[0] );
	
	app.addArgument( "First arg" );
	app.addOption( "file", "Specify filename", "<FILE>", 'f' );

	if ( ! app.parse( argc, const_cast<char**>(argv) ) )
	{
		TEST_FAIL( "Error on parsing command line" )
		return;
	}
	
	// Redirect stdout to buffer
	backup = std::cout.rdbuf();
	std::cout.rdbuf( stream.rdbuf() );
	app.showHelp();
	std::cout.rdbuf(backup);
	buffer = stream.str();
	//std::cout << std::endl << "\"" << buffer  << "\"" << std::endl;
	TEST_ASSERT_MSG( buffer == "\nconstructor_test [opts] [First arg]\n\n  -f, --file=<FILE> Specify filename\n\n", "Show help is not printed correctly" )
	TEST_ASSERT_MSG( app.getAppName() == "constructor_test", "Bad app name" )
}

void TestDAppCmdLine::show_version_test()
{
	DAppCmdLine app;
	int argc = 0;
	const char * argv[] = { "/my/path/constructor_test" };
	std::streambuf *backup;
	std::ostringstream stream;
	DString buffer;
	
	if ( sizeof( argv[0] ) ) argc = sizeof( argv ) / sizeof( argv[0] );
	
	app.addArgument( "First arg" );
	app.addOption( "help", "Print this help", 'h' );

	if ( ! app.parse( argc, const_cast<char**>(argv) ) )
	{
		TEST_FAIL( "Error on parsing command line" )
		return;
	}
	
	// Redirect stdout to buffer
	backup = std::cout.rdbuf();
	
	std::cout.rdbuf( stream.rdbuf() );
	app.showVersion();
	std::cout.rdbuf(backup);
	buffer = stream.str();
	TEST_ASSERT_MSG( buffer == "constructor_test Version : VERSION_NOT_SET\n", "Show version is not printed correctly" )
	TEST_ASSERT_MSG( app.getAppVersion() == "VERSION_NOT_SET", "Bad version reported when not set" )
	
	// clear stream: clear internal state and set empty data
	stream.clear();
	stream.str("");
	
	app.setAppVersion( "1.2.3" );
	
	std::cout.rdbuf( stream.rdbuf() );
	app.showVersion();
	std::cout.rdbuf(backup);
	buffer = stream.str();
	//std::cout << std::endl << "\"" << buffer  << "\"" << std::endl;
	TEST_ASSERT_MSG( buffer == "constructor_test Version : 1.2.3\n", "Show version is not printed correctly" )
	TEST_ASSERT_MSG( app.getAppVersion() == "1.2.3", "Bad version reported when set" )
}

void TestDAppCmdLine::set_args_test()
{
	DAppCmdLine app;
	DAppArg arg1, arg2, arg3;
	DAppArgList args;
	int argc = 0;
	const char * argv1[] = { "/my/path/set_opts_test",
							 "/var/log/my.log",
							 "/var/run/my.pid"
						   };
	const char * argv2[] = { "/my/path/set_opts_test",
							 "/var/log/my.log",
							 "/var/run/my.pid",
							 "/var/lock/my.lock",
						   };
	
	if ( sizeof( argv1[0] ) ) argc = sizeof( argv1 ) / sizeof( argv1[0] );
	
	arg1.setDescription( "Log file" );
	arg2.setDescription( "PID file" );
	arg3.setDescription( "Lock file" );
	args.push_back( arg1 );
	args.push_back( arg2 );
	args.push_back( arg3 );
	app.setArguments( args );
	
	if ( ! app.parse( argc, const_cast<char**>(argv1) ) )
	{
		TEST_FAIL( "Error on parsing command line" )
		return;
	}
	TEST_ASSERT_MSG( app.getArgumentValue( 0 ) == "/var/log/my.log", "DAppCmdLine doesn't report good argument value" )
	TEST_ASSERT_MSG( app.getArgumentValue( 1 ) == "/var/run/my.pid", "DAppCmdLine doesn't report good argument value" )
	TEST_ASSERT_MSG( app.getArgumentValue( 2 ) == DString::empty(), "DAppCmdLine doesn't report empty value for missing argument" )
	TEST_ASSERT_MSG( app.getArgumentValue( 3 ) == DString::empty(), "DAppCmdLine doesn't report empty value for out of list id" )
	TEST_ASSERT_MSG( app.getNbExpectedArgs() == 3, "DAppCmdLine doesn't report good number of expected arguments" )
	TEST_ASSERT_MSG( app.getNbFoundArgs() == 2, "DAppCmdLine doesn't report good number of found arguments" )
	TEST_ASSERT_MSG( app.haveAllExpectedArgsFound() == false, "DAppCmdLine doesn't report good delta between expected and found arguments" )
	
	if ( sizeof( argv2[0] ) ) argc = sizeof( argv2 ) / sizeof( argv2[0] );
	if ( ! app.parse( argc, const_cast<char**>(argv2) ) )
	{
		TEST_FAIL( "Error on parsing command line" )
		return;
	}
	TEST_ASSERT_MSG( app.getArgumentValue( 0 ) == "/var/log/my.log", "DAppCmdLine doesn't report good argument value" )
	TEST_ASSERT_MSG( app.getArgumentValue( 1 ) == "/var/run/my.pid", "DAppCmdLine doesn't report good argument value" )
	TEST_ASSERT_MSG( app.getArgumentValue( 2 ) == "/var/lock/my.lock", "DAppCmdLine doesn't report good argument value" )
	TEST_ASSERT_MSG( app.getArgumentValue( 3 ) == DString::empty(), "DAppCmdLine doesn't report empty value for out of list id" )
	TEST_ASSERT_MSG( app.getNbExpectedArgs() == 3, "DAppCmdLine doesn't report good number of expected arguments" )
	TEST_ASSERT_MSG( app.getNbFoundArgs() == 3, "DAppCmdLine doesn't report good number of found arguments" )
	TEST_ASSERT_MSG( app.haveAllExpectedArgsFound() == true, "DAppCmdLine doesn't report good delta between expected and found arguments" )
}

void TestDAppCmdLine::set_opts_test()
{
	DAppCmdLine app;
	DAppOption opt1, opt2, opt3, opt4, opt5, opt6;
	DAppOptionList opts;
	int argc = 0;
	const char * argv[] = { "/my/path/set_opts_test",
							"--logfile",
							"/var/log/my.log",
							"-v",
							"-p=/var/run/my.pid",
							"--lockfile=/var/lock/my.lock",
							"--name",
							"toto"
	};
	
	if ( sizeof( argv[0] ) ) argc = sizeof( argv ) / sizeof( argv[0] );
	
	opt1.set( "help", "Print this help", DString::empty(), 'h' );
	opt2.setName( "logfile" );
	opt2.setAlias( 'l' );
	opt2.setExample( "<FILE>" );
	opt2.setDescription( "Specify log file" );
	opt3.set( "socket", "Specify socket file", "<FILE>", 's');
	opt4.set( "verbose", "Make application more talkative", DString::empty(), 'v');
	opt5.set( "pidfile", "Specify pid file", "<FILE>", 'p');
	opt6.set( "lockfile", "Specify lock file", "<FILE>", 'L');
	opts.push_back( opt1 );
	opts.push_back( opt2 );
	opts.push_back( opt3 );
	opts.push_back( opt4 );
	opts.push_back( opt5 );
	opts.push_back( opt6 );
	
	app.setOptions( opts );
	app.addOption( "name", "Specify name", "<NAME>", 'n' );

	if ( ! app.parse( argc, const_cast<char**>(argv) ) )
	{
		TEST_FAIL( "Error on parsing command line" )
		return;
	}
	TEST_ASSERT_MSG( app.getOptionValue( "logfile" ) == "/var/log/my.log", "DAppCmdLine doesn't report good value with name" )
	TEST_ASSERT_MSG( app.getOptionValue( "l" ) == "/var/log/my.log", "DAppCmdLine doesn't report good value with alias" )
	TEST_ASSERT_MSG( app.haveOption( "logfile" ), "DAppCmdLine doesn't have value" )
	TEST_ASSERT_MSG( app.haveOption( "l" ) , "DAppCmdLine doesn't have value with alias" )
	TEST_ASSERT_MSG( app.getOptionValue( "socket" ) == DString::empty(), "DAppCmdLine doesn't report empty value" )
	TEST_ASSERT_MSG( app.getOptionValue( "s" ) == DString::empty(), "DAppCmdLine doesn't report empty value with alias" )
	TEST_ASSERT_MSG( app.haveOption( "socket" ) == false, "DAppCmdLine have default value" )
	TEST_ASSERT_MSG( app.haveOption( "s" ) == false, "DAppCmdLine have default value with alias" )
	TEST_ASSERT_MSG( app.haveOption( "verbose" ), "DAppCmdLine option without value isn't set" )
	TEST_ASSERT_MSG( app.haveOption( "v" ), "DAppCmdLine option without value isn't set with alias" )
	TEST_ASSERT_MSG( app.getOptionValue( "lockfile" ) == "/var/lock/my.lock", "DAppCmdLine doesn't report good value with name" )
	TEST_ASSERT_MSG( app.getOptionValue( "L" ) == "/var/lock/my.lock", "DAppCmdLine doesn't report good value with alias" )
	TEST_ASSERT_MSG( app.haveOption( "lockfile" ), "DAppCmdLine doesn't have value" )
	TEST_ASSERT_MSG( app.haveOption( "L" ) , "DAppCmdLine doesn't have value with alias" )
	TEST_ASSERT_MSG( app.getOptionValue( "pidfile" ) == "/var/run/my.pid", "DAppCmdLine doesn't report good value with name" )
	TEST_ASSERT_MSG( app.getOptionValue( "p" ) == "/var/run/my.pid", "DAppCmdLine doesn't report good value with alias" )
	TEST_ASSERT_MSG( app.haveOption( "pidfile" ), "DAppCmdLine doesn't have value" )
	TEST_ASSERT_MSG( app.haveOption( "p" ) , "DAppCmdLine doesn't have value with alias" )
	TEST_ASSERT_MSG( app.haveOption( "name" ), "DAppCmdLine doesn't have value" )
	TEST_ASSERT_MSG( app.getOptionValue( "name" ) == "toto", "DAppCmdLine doesn't report good value with name" )
	TEST_ASSERT_MSG( app.getOptionValue( "n" ) == "toto", "DAppCmdLine doesn't report good value with alias" )
}

void TestDAppCmdLine::app_opt_stream_test()
{
	DAppOption opt;
	std::ostringstream stream;
	DString buffer, ref;
	
	stream << opt;
	buffer = stream.str();
	
    ref = "opt[][] = \"\" [Example=] [Is set=0] [Must have value=0] ()";
	TEST_ASSERT_MSG( buffer == ref, "Empty DAppArg doesn't print on stream correctly" )
	
	// Before first allocation
	TEST_ASSERT_MSG( opt.getDescription().isEmpty(), "DAppArg doesn't report empty description" )
	TEST_ASSERT_MSG( opt.getAlias() == 0, "DAppArg doesn't report zero alias" )
	TEST_ASSERT_MSG( opt.getExample().isEmpty(), "DAppArg doesn't report empty example" )
	TEST_ASSERT_MSG( opt.getName().isEmpty(), "DAppArg doesn't report empty name" )
	TEST_ASSERT_MSG( opt.getValue().isEmpty(), "DAppArg doesn't report empty value" )
	
	opt.set( "help", "Print this help", DString::empty(), 'h' );
	TEST_ASSERT_MSG( opt.getDescription() == "Print this help", "DAppArg doesn't report good description" )
	TEST_ASSERT_MSG( opt.getAlias() == 'h', "DAppArg doesn't report good alias" )
	TEST_ASSERT_MSG( opt.getExample().isEmpty(), "DAppArg doesn't report empty example" )
	TEST_ASSERT_MSG( opt.getName() == "help", "DAppArg doesn't report good name" )
	TEST_ASSERT_MSG( opt.getValue().isEmpty(), "DAppArg doesn't report empty value" )
	
	// clear stream: clear internal state and set empty data
	stream.clear();
	stream.str("");
	
	stream << opt;
	buffer = stream.str();
    ref = "opt[help][h] = \"\" [Example=] [Is set=0] [Must have value=0] (Print this help)";
	TEST_ASSERT_MSG( buffer == ref, "DAppArg doesn't print on stream correctly" )
	
	// clear stream: clear internal state and set empty data
	stream.clear();
	stream.str("");
	
	// After clear
	opt.clear();
	stream << opt;
	buffer = stream.str();
    ref = "opt[][] = \"\" [Example=] [Is set=0] [Must have value=0] ()";
	TEST_ASSERT_MSG( buffer == ref, "Empty DAppArg doesn't print on stream correctly" )
	// Before assignation
	TEST_ASSERT_MSG( opt.getDescription().isEmpty(), "DAppArg doesn't report empty description" )
	TEST_ASSERT_MSG( opt.getAlias() == 0, "DAppArg doesn't report zero alias" )
	TEST_ASSERT_MSG( opt.getExample().isEmpty(), "DAppArg doesn't report empty example" )
	TEST_ASSERT_MSG( opt.getName().isEmpty(), "DAppArg doesn't report empty name" )
	TEST_ASSERT_MSG( opt.getValue().isEmpty(), "DAppArg doesn't report empty value" )
	
	stream.clear();
	stream.str("");
	// Second allocation
	opt.clear();
	opt.setName( "logfile" );
	opt.setAlias( 'f' );
	opt.setExample( "<FILE>" );
	opt.setDescription( "Specify log file" );
	TEST_ASSERT_MSG( opt.getDescription() == "Specify log file", "DAppArg doesn't report good description" )
	TEST_ASSERT_MSG( opt.getAlias() == 'f', "DAppArg doesn't report good alias" )
	TEST_ASSERT_MSG( opt.getExample() == "<FILE>", "DAppArg doesn't report empty example" )
	TEST_ASSERT_MSG( opt.getName() == "logfile", "DAppArg doesn't report good name" )
	TEST_ASSERT_MSG( opt.getValue().isEmpty(), "DAppArg doesn't report empty value" )
	TEST_ASSERT_MSG( opt.isMandatory() == true, "DAppArg doesn't report good mandatory status" )
	TEST_ASSERT_MSG( opt.isSet() == false, "DAppArg doesn't report good status" )
	opt.setMandatoryState( true );
	TEST_ASSERT_MSG( opt.isMandatory() == true, "DAppArg doesn't report good mandatory status" )
	TEST_ASSERT_MSG( opt.getValue().isEmpty(), "DAppArg doesn't report empty value" )
	TEST_ASSERT_MSG( opt.isSet() == false, "DAppArg doesn't report good status" )
	stream << opt;
	buffer = stream.str();
    ref = "opt[logfile][f] = \"NO-VALUE\" [Example=<FILE>] [Is set=0] [Must have value=1] (Specify log file)";
	//std::cout << std::endl << "\"" << buffer  << "\"" << std::endl << "\"" << ref << "\"" << std::endl;
	TEST_ASSERT_MSG( buffer == ref, "DAppArg doesn't print on stream correctly" )
	opt.setValue( "/var/log/dlibs.log" );
	TEST_ASSERT_MSG( opt.getValue() == "/var/log/dlibs.log", "DAppArg doesn't report empty value" )
	opt.setState( true );
	TEST_ASSERT_MSG( opt.isSet() == true, "DAppArg doesn't report good status" )
	
	stream.clear();
	stream.str("");
	stream << opt;
	buffer = stream.str();
    ref = "opt[logfile][f] = \"/var/log/dlibs.log\" [Example=<FILE>] [Is set=1] [Must have value=1] (Specify log file)";
	//std::cout << std::endl << "\"" << buffer  << "\"" << std::endl << "\"" << ref << "\"" << std::endl;
	TEST_ASSERT_MSG( buffer == ref, "DAppArg doesn't print on stream correctly" )
	
}

void TestDAppCmdLine::app_arg_stream_test()
{
	DAppArg arg;
	std::ostringstream stream;
	DString buffer;
	
	// Before allocation
	TEST_ASSERT_MSG( arg.getDescription().isEmpty(), "DAppArg doesn't report empty description" )
	TEST_ASSERT_MSG( arg.getValue().isEmpty(), "DAppArg doesn't report empty value" )
	
	// After allocation
	arg.setDescription( "First Arg" );
	TEST_ASSERT_MSG( arg.getDescription() == "First Arg", "DAppArg doesn't report good description" )
	TEST_ASSERT_MSG( arg.getValue().isEmpty(), "DAppArg doesn't report empty value" )
	arg.setValue( "OK" );
	TEST_ASSERT_MSG( arg.getValue() == "OK", "DAppArg doesn't report good value" )
	
	stream << arg;
	buffer = stream.str();
	TEST_ASSERT_MSG( buffer == "arg[First Arg] = \"OK\"", "DAppArg doesn't print on stream correctly" )
	
	// clear stream: clear internal state and set empty data
	stream.clear();
	stream.str("");
	
	// After clear
	arg.clear();
	stream << arg;
	buffer = stream.str();
	TEST_ASSERT_MSG( arg.getDescription().isEmpty(), "DAppArg doesn't report empty description" )
	TEST_ASSERT_MSG( arg.getValue().isEmpty(), "DAppArg doesn't report empty value" )
	TEST_ASSERT_MSG( buffer == "arg[] = \"\"", "Cleared DAppArg doesn't print on stream correctly" )
}

void TestDAppCmdLine::print_app_test()
{
	DAppCmdLine app;
	DAppOption opt1, opt2;
	DAppOptionList opts;
	DAppArg arg1, arg2, arg3;
	DAppArgList args;
	int argc = 0;
	const char * argv[] = { "/my/path/set_opts_test",
							"--logfile", "/var/log/my.log",
							"/var/run/my.pid",
							"/var/lock/my.lock"
						  };
	std::ostringstream stream;
	DString ref;
	
	if ( sizeof( argv[0] ) ) argc = sizeof( argv ) / sizeof( argv[0] );
	
	opt1.set( "help", "Print this help", DString::empty(), 'h' );
	opts.push_back( opt1 );
	opt2.setName( "logfile" );
	opt2.setAlias( 'l' );
	opt2.setExample( "<FILE>" );
	opt2.setDescription( "Specify log file" );
	opts.push_back( opt2 );
	app.setOptions( opts );
	
	arg1.setDescription( "PID file" );
	arg2.setDescription( "Lock file" );
	arg3.setDescription( "runtime PATH" );
	args.push_back( arg1 );
	args.push_back( arg2 );
	args.push_back( arg3 );
	app.setArguments( args );

	if ( ! app.parse( argc, const_cast<char**>(argv) ) )
	{
		TEST_FAIL( "Error on parsing command line" )
		return;
	}
	
	stream << app;
	ref = "DAppCmdLine\n";
	ref += "{0} arg[PID file] = \"/var/run/my.pid\"\n";
	ref += "{1} arg[Lock file] = \"/var/lock/my.lock\"\n";
	ref += "{2} arg[runtime PATH] = \"\"\n";
	ref += "{help} opt[help][h] = \"\" [Example=] [Is set=0] [Must have value=0] (Print this help)\n";
	ref += "{logfile} opt[logfile][l] = \"/var/log/my.log\" [Example=<FILE>] [Is set=1] [Must have value=1] (Specify log file)\n";
	ref += "{h} alias help\n";
	ref += "{l} alias logfile\n";
	TEST_ASSERT_MSG( stream.str() == ref, "DAppCmdLine doesn't print on stream correctly after parse process" )
}

void TestDAppCmdLine::bad_opts_test()
{
	DAppCmdLine app;
	int argc = 0;
	const char * argv1[] = { "/my/path/set_opts_test", "--logfile", "/var/log/my.log" };
	
	if ( sizeof( argv1[0] ) ) argc = sizeof( argv1 ) / sizeof( argv1[0] );
	
	app.addOption( "help", "Print this help", 'h' );
	app.addOption( "logfile", "Specify log file", "<FILE>", 'l' );
	argc--;
	
	if ( ! app.parse( argc, const_cast<char**>(argv1) ) )
	{
		TEST_ASSERT_MSG( app.getLastError() == "No argument found for option logfile",
						 "Bad Last error when arg was not followed by value" )
	}
	else
	{
		TEST_FAIL( "Error on parsing command line. Error must be reported at this point" )
	}
	
	argc = 0;
	const char * argv2[] = { "/my/path/set_opts_test", "--logfile", "-h" };
	if ( sizeof( argv2[0] ) ) argc = sizeof( argv2 ) / sizeof( argv2[0] );
	
	if ( ! app.parse( argc, const_cast<char**>(argv2) ) )
	{
		TEST_ASSERT_MSG( app.getLastError() == "No argument found for option logfile",
						 "Bad Last error when arg was not followed by value" )
	}
	else
	{
		TEST_FAIL( "Error on parsing command line. Error must be reported at this point" )
	}
	
	argc = 0;
	const char * argv3[] = { "/my/path/set_opts_test", "-k" };
	if ( sizeof( argv3[0] ) ) argc = sizeof( argv3 ) / sizeof( argv3[0] );
	
	if ( ! app.parse( argc, const_cast<char**>(argv3) ) )
	{
		TEST_ASSERT_MSG( app.getLastError() == "Unknow option found : -k",
						 "Bad Last error when arg was not known" )
	}
	else
	{
		TEST_FAIL( "Error on parsing command line. Error must be reported at this point" )
	}
	TEST_ASSERT_MSG( app.getOptionValue( "k" ).isEmpty(), "DAppCmdLine doesn't report empty value for unknown option" )
}

void TestDAppCmdLine::help_with_lot_of_opts_test()
{
	DAppCmdLine app;
	std::streambuf *backup;
	std::ostringstream stream;
	DString buffer, ref;
	
	int argc = 0;
	const char * argv[] = { "/my/path/test" };

	if ( sizeof( argv[0] ) ) argc = sizeof( argv ) / sizeof( argv[0] );
	
	app.addOption( "help", "display usage", 'h' );
	app.addOption( "file", "use file as input stream", "{file}", 'f' );
	app.addOption( "url", "server hostname and optional port. must use admin port with -z/-a", "http[s]://{host}[:{port}]", 'u' );
	app.addOption( "admin", "admin account name to auth as", "{name}", 'a' );
	app.addOption( "zadmin", "use zimbra admin name/password from localconfig for admin/password", 'z' );
	app.addOption( "authtoken", "use auth token string (has to be in JSON format) from command line", "{authtoken}", 'y' );
	app.addOption( "authtokenfile", "read auth token (has to be in JSON format) from a file", "{authtoken file}", 'Y' );
	app.addOption( "mailbox", "mailbox to open", "{name}", 'm' );
	app.addOption( "auth", "account name to auth as; defaults to -m unless -A is used", "{name}" );
	app.addOption( "admin-priv", "execute requests with admin privileges\n                                           requires -z or -a, and -m", 'A' );
	app.addOption( "password", "password for account", "{pass}", 'p' );
	app.addOption( "passfile", "read password from file", "{file}", 'P' );
	app.addOption( "timeout", "timeout (in seconds)", 't' );
	app.addOption( "verbose", "verbose mode (dumps full exception stack trace)", 'v' );
	app.addOption( "debug", "debug mode (dumps SOAP messages)", 'd' );
	
	app.addArgument( "cmd" );
	app.addArgument( "cmd-args ..." );
	
	if ( ! app.parse( argc, const_cast<char**>(argv) ) )
	{
		TEST_FAIL( "Error on parsing command line" )
		return;
	}
	
	// Redirect stdout to buffer
	backup = std::cout.rdbuf();
	
	std::cout.rdbuf( stream.rdbuf() );
	app.showHelp();
	std::cout.rdbuf(backup);
	buffer = stream.str();
	
	ref  = "\ntest [opts] [cmd] [cmd-args ...]\n\n";
	ref += "  -a, --admin={name}                   admin account name to auth as\n";
	ref += "  -A, --admin-priv                     execute requests with admin privileges\n";
	ref += "                                           requires -z or -a, and -m\n";
	ref += "  --auth={name}                        account name to auth as; defaults to -m unless -A is used\n";
	ref += "  -y, --authtoken={authtoken}          use auth token string (has to be in JSON format) from command line\n";
	ref += "  -Y, --authtokenfile={authtoken file} read auth token (has to be in JSON format) from a file\n";
	ref += "  -d, --debug                          debug mode (dumps SOAP messages)\n";
	ref += "  -f, --file={file}                    use file as input stream\n";
	ref += "  -h, --help                           display usage\n";
	ref += "  -m, --mailbox={name}                 mailbox to open\n";
	ref += "  -P, --passfile={file}                read password from file\n";
	ref += "  -p, --password={pass}                password for account\n";
	ref += "  -t, --timeout                        timeout (in seconds)\n";
	ref += "  -u, --url=http[s]://{host}[:{port}]  server hostname and optional port. must use admin port with -z/-a\n";
	ref += "  -v, --verbose                        verbose mode (dumps full exception stack trace)\n";
	ref += "  -z, --zadmin                         use zimbra admin name/password from localconfig for admin/password\n\n";

	TEST_ASSERT_MSG( buffer == ref, "Show version with a lot of options is not printed correctly" )
}

int main()
{
	TestDAppCmdLine ets;
#ifdef TEST_HTML
	std::ofstream file;
	Test::HtmlOutput html;

	file.open( "dappcmdline.html" );
	ets.run( html );
	html.generate( file, true, "DAppCmdLine" );
	file.close();
#endif

#ifdef TEST_STDOUT
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
#endif
	return EXIT_SUCCESS;
}
