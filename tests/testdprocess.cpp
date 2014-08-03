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
 *     (___)_)   File : testdprocess.cpp                    ||--|| *          *
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
 *   Unit Test for DProcess                                                   *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdprocess.h"

void TestDProcess::simple_test()
{
	DProcess process;

	process.setExecutable( "ls" );
	process << "/proc/cpuinfo";
	process.setComMode( DProcess::READ_ONLY );
	process.setExeMode( DProcess::BLOCK );

	process.start();
	TEST_ASSERT_MSG( process.getOutput().stripWhiteSpace() == "/proc/cpuinfo", "Wrong output for DProcess" )
	process.stop();
}

void TestDProcess::block_test()
{
	DProcess process;

	process.setExecutable( "for i in $(seq 1 2) ; do sleep 1 ; done ; echo \"Done\"" );
	process.setComMode( DProcess::READ_ONLY );
	process.setExeMode( DProcess::BLOCK );
	process.start();
	
	TEST_ASSERT_MSG( process.getOutput().stripWhiteSpace() == "Done", "Wrong output for DProcess" )
	process.stop();
}

void TestDProcess::nonblock_test()
{
	DProcess process;
	unsigned int loop = 0;

	process.setExecutable( "for i in $(seq 1 2) ; do sleep 1 ; done ; echo \"Done\"" );
	process.setComMode( DProcess::READ_ONLY );
	process.setExeMode( DProcess::NOBLOCK );
	process.start();

	while ( process.isRunning() )
	{
		loop++;
		usleep( 100000 );
	}
	
	TEST_ASSERT_MSG( loop >= 4, "Wrong loop number for DProcess" )
	TEST_ASSERT_MSG( process.getOutput().stripWhiteSpace() == "Done", "Wrong output for DProcess" )
	process.stop();
}

int main( int argc, char** argv )
{
	std::ofstream file;
	TestDProcess ets;

	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );
	/*Test::HtmlOutput html;

	file.open( "dprocess.html" );
	ets.run( html );
	html.generate( file, true, "DProcess" );
	file.close();*/

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
}