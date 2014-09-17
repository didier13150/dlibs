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
 *     (___)_)   File : testdthread.cpp                     ||--|| *          *
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
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                *
 *                                                                            *
 *   Unit Test for DThread                                                    *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdthread.h"
#include "dthread.h"
#include "test.h"

class Foo : public DThread
{
public:
	Foo() : DThread(), nb( 0 ) {}

	void run()
	{
		nb++;
	}
	void clear() { nb = 0; }
	int getNb() { return nb; }
private:
	int nb;
};

void TestDThread::single_loop_test()
{
	Foo foo;

	foo.setRunMode( DThread::SINGLE_LOOP );
	foo.setSleep( 100000 );
	foo.start();
	sleep( 1 );
	TEST_ASSERT_MSG( foo.isRunning() == false, "Single loop thread still running" )
	TEST_ASSERT_MSG( foo.getNb() == 1, "Single loop thread make more than one loop" )
	TEST_ASSERT_MSG( foo.getReturn() == 0, "Single loop thread return none zero value" )
}

void TestDThread::multi_loop_test()
{
	Foo foo;

	foo.setRunMode( DThread::MULTI_LOOP );
	foo.setSleep( 100000 );
	foo.start();
	sleep( 1 );
	TEST_ASSERT_MSG( foo.isRunning() == true, "Multi loop thread not running" )
	TEST_ASSERT_MSG( foo.getNb() >= 1, "Multi loop thread make more than one loop" )
	TEST_ASSERT_MSG( foo.getReturn() == 255, "Multi loop thread return bad status when running" )
	foo.stop();
	TEST_ASSERT_MSG( foo.isRunning() == false, "Multi loop thread still running after stop" )
	TEST_ASSERT_MSG( foo.getReturn() == 0, "Multi loop thread return none zero value" )
}

void TestDThread::multi_stop_test()
{
	Foo foo;

	foo.setRunMode( DThread::MULTI_LOOP );
	foo.setSleep( 100000 );
	foo.start();
	sleep( 1 );
	TEST_ASSERT_MSG( foo.isRunning() == true, "Multi loop thread not running" )
	TEST_ASSERT_MSG( foo.getNb() >= 1, "Multi loop thread make more than one loop" )
	foo.stop();
	TEST_ASSERT_MSG( foo.isRunning() == false, "Multi loop thread still running after stop" )
	TEST_ASSERT_MSG( foo.getReturn() == 0, "Multi loop thread return none zero value" )
	foo.stop();
	foo.stop();
	TEST_ASSERT_MSG( foo.isRunning() == false, "Multi loop thread still running after stop" )
	TEST_ASSERT_MSG( foo.getReturn() == 0, "Multi loop thread return none zero value" )
}

void TestDThread::just_stop_test()
{
	Foo foo;
	foo.stop();
	foo.stop();
}

void TestDThread::force_stop_test()
{
	Foo foo;

	foo.setRunMode( DThread::MULTI_LOOP );
	foo.setSleep( 100000 );
	foo.start();
	sleep( 1 );
	TEST_ASSERT_MSG( foo.isRunning() == true, "Multi loop thread not running" )
	TEST_ASSERT_MSG( foo.getNb() >= 1, "Multi loop thread make more than one loop" )
	foo.stop( true );
	TEST_ASSERT_MSG( foo.isRunning() == false, "Multi loop thread still running after stop" )
	TEST_ASSERT_MSG( foo.getReturn() == 0, "Multi loop thread return none zero value" )
	
	
}

int main()
{
	TestDThread ets;
#ifdef TEST_HTML
	std::ofstream file;
	Test::HtmlOutput html;

	file.open( "dthread.html" );
	ets.run( html );
	html.generate( file, true, "DThread" );
	file.close();
#endif

#ifdef TEST_STDOUT
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
#endif
	return EXIT_SUCCESS;
}
