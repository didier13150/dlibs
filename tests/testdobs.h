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
 *     (___)_)   File : testdobs.h                          ||--|| *          *
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

#ifndef _TESTDOBS_H
#define _TESTDOBS_H

#include <cpptest.h>

#include "dobs.h"

class TestDObs : public Test::Suite
{
public:
	TestDObs()
	{
		TEST_ADD( TestDObs::constructor_test )
	}

private:
	void constructor_test();
};

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

#endif // _TESTDOBS_H
