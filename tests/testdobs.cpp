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
 *     (___)_)   File : testdobs.cpp                        ||--|| *          *
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
 *   Unit Test for DObs                                                       *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "testdobs.h"

void TestDObs::constructor_test()
{
	Barometer barometer;
	Thermometer thermometer;
	std::ostringstream stream;

	{ // To limit WeatherStation range to this block
		WeatherStation station;

		thermometer.addObserver( &station );
		barometer.addObserver( &station );

		thermometer.setValue( 22 );
		TEST_ASSERT_MSG( station.popFirstEvent() == "Temperature = 22 degrees.", "Wrong event (#1)" )
		barometer.setValue( 1024 );
		TEST_ASSERT_MSG( station.popFirstEvent() == "Presure = 1024 mBars.", "Wrong event (#2)" )
	}

	barometer.setValue( 1020 );
}

int main( int argc, char** argv )
{
	std::ofstream file;
	TestDObs ets;

	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );
	/*Test::HtmlOutput html;

	file.open( "dobs.html" );
	ets.run( html );
	html.generate( file, true, "DObs" );
	file.close();*/

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
}