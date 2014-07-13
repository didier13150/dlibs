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
 *     (___)_)   File : testdenv.cpp                        ||--|| *          *
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
 *   Unit Test for DEnv                                                       *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdenv.h"

void TestDEnv::constructor_test()
{
	DEnv * env = DEnv::getInstance();
	
	TEST_ASSERT_MSG( env->getVar( "HOME" ).left(5) == "/home", "Get HOME env var failed" )
	TEST_ASSERT_MSG( env->getVar( "toto95123" ) == DString::empty(), "Get empty toto env var failed" )
}

void TestDEnv::setenv_test()
{
	DEnv * env = DEnv::getInstance();
	
	TEST_ASSERT_MSG( env->getVar( "toto95123" ) == DString::empty(), "Get toto env var failed" )
	env->setVar( "toto95123", "DLibs test" );
	TEST_ASSERT_MSG( env->getVar( "toto95123" ) == "DLibs test", "Get toto env var failed after set" )
}

void TestDEnv::getenv_test()
{
	DEnv * env = DEnv::getInstance();
	TEST_ASSERT_MSG( env->getVar( "toto95123" ) == "DLibs test", "Get toto env var failed after set" )
	env->setVar( "toto95123", DString::empty() );
	TEST_ASSERT_MSG( env->getVar( "toto95123" ) == DString::empty(), "Set empty env var to toto failed" )
}

int main( int argc, char** argv )
{
	std::ofstream file;
	TestDEnv ets;
	
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );
	Test::HtmlOutput html;
	
	file.open( "denv.html" );
	ets.run( html );
	html.generate( file, true, "DEnv" );
	file.close();
	
	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
}