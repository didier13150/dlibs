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
 *     (___)_)   File : dlibspath.cpp                       ||--|| *          *
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
 ******************************************************************************/

#include <cstdlib>
#include <iostream>

#include "dlibs.h"
#include "config.h"

int main (int argc, char *argv[])
{
	DAppCmdLine args;
	
	args.setAppVersion( DLIBS_VERSION );
	args.addOption( "help", "Print this help", 'h' );
	args.addOption( "version", "Show version", 'v' );
	args.addOption( "prefix", "Show the prefix where dlibs are installed" );
	args.addOption( "tarname", "Show package name" );
	args.addOption( "bugreport", "Show address where bug report must be sent" );

	if ( !args.parse( argc, argv ) )
	{
		std::cout << "Error on parsing command line : " << args.getLastError() << std::endl;
		exit( EXIT_FAILURE );
	}
	
	if ( args.haveOption( "version" ) )
	{
		args.showVersion();
		exit ( EXIT_SUCCESS );
	}
	
	else if ( args.haveOption( "help" ) )
	{
		args.showHelp();
		exit ( EXIT_SUCCESS );
	}
	
	else if ( args.haveOption( "prefix" ) )
	{
		std::cout << DLIBS_PREFIX_PATH << std::endl;
		exit ( EXIT_SUCCESS );
	}
	
	else if ( args.haveOption( "tarname" ) )
	{
		std::cout << DLIBS_PACKAGE_NAME << "-" << DLIBS_VERSION << std::endl;
		exit ( EXIT_SUCCESS );
	}
	
	else if ( args.haveOption( "bugreport" ) )
	{
		std::cout << DLIBS_BUG_REPORT << std::endl;
		exit ( EXIT_SUCCESS );
	}
	args.showHelp();
	exit( EXIT_FAILURE );
}
