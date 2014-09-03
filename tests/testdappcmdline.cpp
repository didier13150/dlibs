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
#include "testdappcmdline.h"
#include "test.h"

void TestDAppCmdLine::constructor_test()
{
	DAppCmdLine args;
	int argc = 0;
	const char * argv[] = { "/my/path/constructor_test" };

	args.setAppVersion( "1.0.0" );
	args.addOption( "help", "Print this help", 'h' );
	args.addOption( "version", "Show version", 'v' );
	args.addOption( "prefix", "Show the prefix where dlibs are installed" );
	args.addOption( "tarname", "Show package name" );
	args.addOption( "bugreport", "Show address where bug report must be sent" );

	if ( ! args.parse( argc, const_cast<char**>(argv) ) )
	{
		TEST_FAIL( "Error on parsing command line" )
		return;
	}
}

void TestDAppCmdLine::arg_and_opt_test()
{
	DAppCmdLine args;
	int argc = 0;
	const char * argv[] = { "/my/path/constructor_test" };

	args.setAppVersion( "1.0.0" );
	args.addOption( "help", "Print this help", 'h' );
	args.addOption( "version", "Show version", 'v' );
	args.addOption( "verylongversionstring", "Show long version", 'l' );
	args.addArgument( "First arg" );
	args.addArgument( "Second arg" );

	if ( ! args.parse( argc, const_cast<char**>(argv) ) )
	{
		TEST_FAIL( "Error on parsing command line" )
		return;
	}
}

void TestDAppCmdLine::show_help_test()
{
	DAppCmdLine args;
	int argc = 0;
	const char * argv[] = { "/my/path/constructor_test" };
	std::streambuf *backup;
	std::ostringstream stream;
	DString buffer;

	args.addArgument( "First arg" );
	args.addOption( "help", "Print this help", 'h' );

	if ( ! args.parse( argc, const_cast<char**>(argv) ) )
	{
		TEST_FAIL( "Error on parsing command line" )
		return;
	}
	
	// Redirect stdout to buffer
	backup = std::cout.rdbuf();
	std::cout.rdbuf( stream.rdbuf() );
	args.showHelp();
	std::cout.rdbuf(backup);
	buffer = stream.str();
	TEST_ASSERT_MSG( buffer == "\nconstructor_test [opts] [First arg]\n\n  -h, --help Print this help\n\n", "Show help is not printed correctly" )
}

void TestDAppCmdLine::show_version_test()
{
	DAppCmdLine args;
	int argc = 0;
	const char * argv[] = { "/my/path/constructor_test" };
	std::streambuf *backup;
	std::ostringstream stream;
	DString buffer;

	args.addArgument( "First arg" );
	args.addOption( "help", "Print this help", 'h' );

	if ( ! args.parse( argc, const_cast<char**>(argv) ) )
	{
		TEST_FAIL( "Error on parsing command line" )
		return;
	}
	
	// Redirect stdout to buffer
	backup = std::cout.rdbuf();
	
	std::cout.rdbuf( stream.rdbuf() );
	args.showVersion();
	std::cout.rdbuf(backup);
	buffer = stream.str();
	TEST_ASSERT_MSG( buffer == "constructor_test Version : VERSION_NOT_SET\n", "Show version is not printed correctly" )
	
	// clear stream: clear internal state and set empty data
	stream.clear();
	stream.str("");
	
	args.setAppVersion( "1.2.3" );
	
	std::cout.rdbuf( stream.rdbuf() );
	args.showVersion();
	std::cout.rdbuf(backup);
	buffer = stream.str();
	//std::cout << std::endl << "\"" << buffer  << "\"" << std::endl;
	TEST_ASSERT_MSG( buffer == "constructor_test Version : 1.2.3\n", "Show version is not printed correctly" )
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
