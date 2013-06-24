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
 *     (___)_)   File : dlibstest.cpp                       ||--|| *          *
 *                                                                            *
 *   This program is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU General Public License as published by     *
 *   the Free Software Foundation; either version 2 of the License, or        *
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
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                *
 ******************************************************************************/


#include "dlibs.h" // replace it by #include <dlibs/dlibs.h>

#include <pthread.h>
#include <cstdlib>
#include <getopt.h>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

extern int testdstring();
extern int testdlog( bool );
extern int testdsmtp( bool );
extern int testdsockserver();
extern int testdtimer();
extern int testdurl();
extern int testdsettings();
extern int testdexceptions();
extern int testdsingleton();
extern int testdthread();
extern int testdsqlite();
extern int testdfactory();
extern int testdobs();
extern int testdappcmdline( bool, int, char ** );
extern int testdpoint();
extern int testdrect();
extern int testdenv();
extern int testdprocess( bool );

#ifdef DLIBS_HAVE_MYSQL
	extern int testdmysql();
#else
	int testdmysql()
	{
		std::cout << "DMysql not built" << std::endl;
		return 0;
	}
#endif
	
#ifdef DLIBS_HAVE_PGSQL
	extern int testdpgsql( bool );
#else
	int testdpgsql( bool )
	{
		std::cout << "DPgSQL not built" << std::endl;
		return 0;
	}
#endif

int main ( int argc, char *argv[] )
{
	DAppCmdLine args;
	bool debug = false;
	DString library, file;
	
	args.setAppVersion( DLIBS_VERSION );
	args.addOption( "help", "Show help", 'h', false );
	args.addOption( "version", "Show version number", 'v', false );
	args.addOption( "debug", "Set debug mode", 'd', false );
	args.addOption( "testing", "Test only one library", 't', true );
	//args.addArgument( "FILE" );

	if ( !args.parse( argc, argv ) )
	{
		cout << "Error on parsing command line : " << args.getLastError() << endl;
		exit( EXIT_FAILURE );
	}
	
	if ( args.haveOption( "version" ) )
	{
		args.showVersion();
		exit ( EXIT_SUCCESS );
	}
	
	if ( args.haveOption( "help" ) )
	{
		args.showHelp();
		exit ( EXIT_SUCCESS );
	}
	
	if ( !args.haveAllExpectedArgsFound() )
	{
		cout << "Not found exact number of required arguments in command line" << endl;
		cout << "expected = " << args.getNbExpectedArgs() << endl;
		cout << "found = " << args.getNbFoundArgs() << endl;
		args.showHelp();
		exit ( EXIT_FAILURE );
	}
	
	debug = args.haveOption( "debug" );
	library = args.getOption( "testing" );
	
	bool one_loop = true;

	do
	{
		if ( library.isEmpty() )
		{
			cout << "#########################################################";
			cout << "####################" << endl;
			cout << "Enter \"quit\" to exit" << endl;
			cout << "Available libraries are : " << endl;
			cout << "dstring, dsettings, dlog, dtimer, dsocket, dpoint, ";
			cout << "drect, dmysql, dsqlite, durl, dexceptions, dsingleton, ";
			cout << ", dthread, dfactory, dobs, dargs, denv, dprocess" << endl;
			cout << "Library to test : ";
			cin >> library;
			one_loop = false;
		}

		if ( library == "dstring" )
		{
			cout << "DString Test" << endl;
			testdstring();
		}

		else if ( library == "dsettings" )
		{
			cout << "DSettings Test" << endl;
			testdsettings();
		}

		else if ( library == "dlog" )
		{
			cout << "DLog Test" << endl;
			testdlog( !library.isEmpty() );
		}

		else if ( library == "dtimer" )
		{
			cout << "DTimer Test" << endl;
			testdtimer();
		}

		else if ( library == "dsocket" )
		{
			cout << "DSocket Test" << endl;
			testdsockserver();
		}

		else if ( library == "dpoint" )
		{
			cout << "DPoint Test" << endl;
			testdpoint();
		}

		else if ( library == "drect" )
		{
			cout << "DRect Test" << endl;
			testdrect();
		}

		else if ( library == "dmysql" )
		{
			cout << "DMySQL Test" << endl;
			testdmysql ();
		}

		else if ( library == "dsqlite" )
		{
			cout << "DSQLite Test" << endl;
			testdsqlite ();
		}

		else if ( library == "durl" )
		{
			cout << "DURL Test" << endl;
			testdurl();
		}

		else if ( library == "dsmtp" )
		{
			cout << "DSMTP Test" << endl;
			testdsmtp( !library.isEmpty() );
		}

		else if ( library == "dexceptions" )
		{
			cout << "DException Test" << endl;
			testdexceptions();
		}

		else if ( library == "dsingleton" )
		{
			cout << "DSingleton Test" << endl;
			testdsingleton();
		}

		else if ( library == "dthread" )
		{
			cout << "DThread Test" << endl;
			testdthread();
		}

		else if ( library == "dfactory" )
		{
			cout << "DFactory Test" << endl;
			testdfactory();
		}

		else if ( library == "dobs" )
		{
			cout << "DObservable - DObserver Test" << endl;
			testdobs();
		}

		else if ( library == "dpgsql" )
		{
			cout << "DPgSQL Test" << endl;
			testdpgsql( !library.isEmpty() );
		}

		else if ( library == "dappcmdline" )
		{
			cout << "DAppCmdLine Test" << endl;
			testdappcmdline( !library.isEmpty(), argc, argv );
		}

		else if ( library == "denv" )
		{
			cout << "DEnv Test" << endl;
			testdenv();
		}

		else if ( library == "dprocess" )
		{
			cout << "DProcess Test" << endl;
			testdprocess( !library.isEmpty() );
		}
		
		else
		{
			if ( library == "quit" || library == "exit" )
			{
				break;
			}
			cout << library << " is not a part of dlibs !" << endl;
		}
		if ( one_loop )
		{
			break;
		}
		else
		{
			library.clear();
		}

	}
	while ( library != "quit" && library != "exit" );

	return EXIT_SUCCESS;
}
