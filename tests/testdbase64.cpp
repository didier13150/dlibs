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
 *     (___)_)   File : testdbase64.cpp                     ||--|| *          *
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
 *   Unit Test for DBase64                                                    *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "dstring.h"
#include "testdbase64.h"
#include "test.h"

#define TESTFILE CMAKE_SOURCE_DIR"/tux.png"
#define WRAPPING 76

static const char * imgdata = 
	"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"
	"AAAElFTkSuQmCC";

void TestDBase64::encode_test()
{
	DBase64 base;
	DString encoded;
	
	encoded = base.encodeFromFile( TESTFILE );
	
	TEST_ASSERT_MSG( encoded == imgdata, "Wrong image encoding" )
}

void TestDBase64::encode_wrapped_test()
{
	DBase64 base;
	DString encoded;
	DStringList lines;
	
	encoded = base.encodeFromFile( TESTFILE );
	lines = base.getWrappedEncoded( 76 );
	TEST_ASSERT_MSG( lines.size() == 249, "Wrong image encoding" )
	/*for ( DStringList::iterator it = lines.begin() ; it != lines.end() ; ++it )
	{
		std::cout << *it << std::endl;
	}*/
}

void TestDBase64::decode_test()
{
	/*DBase64 base;
	
	base.setEncoded( imgdata );
	base.decodeToFile( "/tmp/tux.png" );*/
}

int main( int argc, char** argv )
{
	TestDBase64 ets;
#ifdef TEST_HTML
	std::ofstream file;
	Test::HtmlOutput html;

	file.open( "dbase64.html" );
	ets.run( html );
	html.generate( file, true, "DBase64" );
	file.close();
#endif

#ifdef TEST_STDOUT
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout << std::endl );

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
#endif
	return EXIT_SUCCESS;
}