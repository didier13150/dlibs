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
 *     (___)_)   File : testdsingleton.cpp                  ||--|| *          *
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
 *   Unit Test for DSingleton                                                 *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdsingleton.h"
#include "dsingleton.h"
#include "test.h"

class Foo : public DSingleton<Foo>
{
	// To let DSingleton have access to Foo protected constructor
	friend class DSingleton<Foo>;
	
protected:
	// Protected constructor
	Foo() : nb( 0 ) {}
	
public:
	int getVal()
	{
		return nb;
	}
	void increment()
	{
		nb++;
	}
	void reset()
	{
		nb = 0;
	}
private:
	int nb;
};

void TestDSingleton::singleton_test()
{
	int i;

	Foo::getInstance()->reset();
	i = Foo::getInstance()->getVal();
	TEST_ASSERT_MSG( i == 0, "Initialisation failed" )
	Foo::getInstance()->increment();
	i = Foo::getInstance()->getVal();
	TEST_ASSERT_MSG( i == 1, "First Increment failed" )
	Foo::getInstance()->increment();
	i = Foo::getInstance()->getVal();
	TEST_ASSERT_MSG( i == 2, "Second Increment failed" )
	Foo::getInstance()->reset();
	i = Foo::getInstance()->getVal();
	TEST_ASSERT_MSG( i == 0, "Reset failed" )
	Foo::deleteInstance();
}

void TestDSingleton::killonly_test()
{
	Foo::deleteInstance();
}

int main()
{
	TestDSingleton ets;
#ifdef TEST_HTML
	std::ofstream file;
	Test::HtmlOutput html;

	file.open( "dsingleton.html" );
	ets.run( html );
	html.generate( file, true, "DSingleton" );
	file.close();
#endif

#ifdef TEST_STDOUT
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
#endif
	return EXIT_SUCCESS;
}
