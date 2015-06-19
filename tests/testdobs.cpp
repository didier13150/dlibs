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
#include "dobs.h"
#include "test.h"

class Barometer : public DObservable
{
private:
	int presure;

public:
	void setValue( int value )
	{
		presure = value;
		notify();
	}
	
	const DBasicEvent & getEvent( void )
	{
		static DBasicEvent event;
		DString buffer;

		buffer.setNum( presure );
		buffer.prepend( "Presure = " );
		buffer.append( " mBars." );
		event.setEvent( buffer );
		return event;
	}
};

class Thermometer : public DObservable
{
private:
	int temperature;

public:
	void setValue( int value )
	{
		temperature = value;
		notify();
	}
	
	const DBasicEvent & getEvent( void )
	{
		static DBasicEvent event;
		DString buffer;

		buffer.setNum( temperature );
		buffer.prepend( "Temperature = " );
		buffer.append( " degrees." );
		event.setEvent( buffer );
		return event;
	}
};

class WeatherStation : public DObserver
{
public:
	WeatherStation() : DObserver() {}
	~WeatherStation() {}
	
	const std::list<DString> & getEventList() const
	{
		return eventlist;
	}
	
	DString popFirstEvent()
	{
		DString event;
		std::list<DString>::const_iterator it;
		it = eventlist.begin();
		if ( it != eventlist.end() ) {
			event = *it;
			eventlist.pop_back();
		}
		return event;
	}
	
	void onEvent( DObservable * observable )
	{
		eventlist.push_back( observable->getEvent().what() );
	}
	
	void clearEvent()
	{
		eventlist.clear();
	}
private:
	std::list<DString> eventlist;
};

class MinimalStation : public DObserver
{
public:
	MinimalStation() : DObserver() {}
	~MinimalStation() {}
	
	void onEvent( DObservable * observable )
	{
		std::cout << observable->getEvent().what() << std::endl;
	}
};

TestDObs::TestDObs()
{
	TEST_ADD( TestDObs::basic_test )
	TEST_ADD( TestDObs::remove_observer_test )
	TEST_ADD( TestDObs::remove_observable_test )
	TEST_ADD( TestDObs::minimal_observer_test )
}

void TestDObs::basic_test()
{
	Barometer barometer;
	Thermometer thermometer;

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

void TestDObs::remove_observer_test()
{
	Barometer barometer;
	Thermometer thermometer;

	{ // To limit WeatherStation range to this block
		WeatherStation station;

		thermometer.addObserver( &station );
		barometer.addObserver( &station );

		thermometer.setValue( 22 );
		TEST_ASSERT_MSG( station.popFirstEvent() == "Temperature = 22 degrees.", "Wrong event (#1)" )
		barometer.setValue( 1024 );
		TEST_ASSERT_MSG( station.popFirstEvent() == "Presure = 1024 mBars.", "Wrong event (#2)" )
		
		thermometer.removeObserver( &station );
	}

	barometer.setValue( 1020 );
}

void TestDObs::remove_observable_test()
{
	WeatherStation station;
	std::ostringstream stream;

	{ // To limit class range to this block
		Barometer barometer;
		Thermometer thermometer;

		station.addObservable( &barometer );
		station.addObservable( &thermometer );

		thermometer.setValue( 22 );
		TEST_ASSERT_MSG( station.popFirstEvent() == "Temperature = 22 degrees.", "Wrong event (#1)" )
		barometer.setValue( 1024 );
		TEST_ASSERT_MSG( station.popFirstEvent() == "Presure = 1024 mBars.", "Wrong event (#2)" )
		
		station.removeObservable( &barometer );
	}
}

void TestDObs::minimal_observer_test()
{
	MinimalStation station;
	Barometer barometer;
	Thermometer thermometer;
	std::ostringstream stream;
	std::streambuf *backup;
	
	// Redirect stdout to buffer
	backup = std::cout.rdbuf();
	std::cout.rdbuf( stream.rdbuf() );

	thermometer.addObserver( &station );
	barometer.addObserver( &station );
	thermometer.setValue( 22 );
	barometer.setValue( 1024 );
	
	// Get stream and restore stdout
	std::cout.rdbuf(backup);
	TEST_ASSERT_MSG( stream.str() == "Temperature = 22 degrees.\nPresure = 1024 mBars.\n",
					 "Wrong events reported by parent function" )
}

int main()
{
	TestDObs ets;
#ifdef TEST_HTML
	std::ofstream file;
	Test::HtmlOutput html;

	file.open( "dobs.html" );
	ets.run( html );
	html.generate( file, true, "DObs" );
	file.close();
#endif

#ifdef TEST_STDOUT
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
#endif
	return EXIT_SUCCESS;
}
