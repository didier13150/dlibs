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
 *     (___)_)   File : testdfactory.cpp                    ||--|| *          *
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
 *   Unit Test for DFactory                                                   *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "config.h"
#include "testdfactory.h"
#include "test.h"

#ifdef DLIBS_HAVE_MYSQL
  #include "dmysql.h"
#endif
#ifdef DLIBS_HAVE_PGSQL
  #include "dpgsql.h"
#endif
#include "dsqlite.h"


void TestDFactory::basic_test()
{
	DFactory<Object> factory;

	DFactory<Object>::Register ( "round", new Round () );
	DFactory<Object>::Register ( "square", new Square () );

	Object * obj = factory.create ( "round" );
	TEST_ASSERT_MSG( obj->what() == "Round", "Wrong object created" )
	delete( obj );

	obj = factory.create ( "square" );
	TEST_ASSERT_MSG( obj->what() == "Square", "Wrong object created" )
	delete( obj );
}

void TestDFactory::ddatabase_test()
{
	DFactory<DDatabase> factory;
#ifdef DLIBS_HAVE_MYSQL
#ifdef WITH_EXCEPTIONS
	DFactory<DDatabase>::Register ( "dmysql", new DMySQL( true ) );
#else
	DFactory<DDatabase>::Register ( "dmysql", new DMySQL() );
#endif
#endif
#ifdef DLIBS_HAVE_PGSQL
#ifdef WITH_EXCEPTIONS
	DFactory<DDatabase>::Register ( "dpgsql", new DPgSQL( true ) );
#else
	DFactory<DDatabase>::Register ( "dpgsql", new DPgSQL() );
#endif
#endif
#ifdef WITH_EXCEPTIONS
	DFactory<DDatabase>::Register ( "dsqlite", new DSQLite( true ) );
#else
	DFactory<DDatabase>::Register ( "dsqlite", new DSQLite() );
#endif

	DDatabase * db = factory.create( "dsqlite" );
	delete( db );

#ifdef DLIBS_HAVE_MYSQL
	db = factory.create( "dsqlite" );
	delete( db );
#endif

#ifdef DLIBS_HAVE_PGSQL
	db = factory.create( "dpgsql" );
	delete( db );
#endif
}

int main()
{
	TestDFactory ets;
#ifdef TEST_HTML
	std::ofstream file;
	Test::HtmlOutput html;

	file.open( "dfactory.html" );
	ets.run( html );
	html.generate( file, true, "DFactory" );
	file.close();
#endif

#ifdef TEST_STDOUT
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
#endif
	return EXIT_SUCCESS;
}
