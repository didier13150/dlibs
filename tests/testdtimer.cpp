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
 *     (___)_)   File : testdtimer.cpp                      ||--|| *          *
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
 *   Unit Test for DTimer                                                     *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdtimer.h"

void TestDTimer::start_precision_test()
{
	DTimer timer;
	timer.start(1500);
	sleep( 1 );
	TEST_ASSERT_MSG( timer.timeToTimeout() >= 0, "No timeout" )
	TEST_ASSERT_MSG( timer.isStarted() == true, "Timer not started" )
	sleep( 1 );
	TEST_ASSERT_MSG( timer.timeToTimeout() == 0, "Timeout not reached" )
	TEST_ASSERT_MSG( timer.isStarted() == false, "Timer not stopped" )
}
void TestDTimer::start_rounded_test()
{
	DTimer timer;
	timer.start(2800);
	sleep( 1 );
	TEST_ASSERT_MSG( timer.timeToTimeout() >= 0, "No timeout" )
	TEST_ASSERT_MSG( timer.isStarted() == true, "Timer not started" )
	sleep( 2 );
	TEST_ASSERT_MSG( timer.timeToTimeout() == 0, "Timeout not reached" )
	TEST_ASSERT_MSG( timer.isStarted() == false, "Timer not stopped" )
}

int main( int argc, char** argv )
{
	std::ofstream file;
	TestDTimer ets;

	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );
	/*Test::HtmlOutput html;

	file.open( "dtimer.html" );
	ets.run( html );
	html.generate( file, true, "DTimer" );
	file.close();*/

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
}