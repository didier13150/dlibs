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
#include "dbase64.h"
#include "testdbase64.h"
#include "test.h"

#define TESTFILE0 CMAKE_SOURCE_DIR"/tests/testdbase64.0.txt"
#define TESTFILE1 CMAKE_SOURCE_DIR"/tests/testdbase64.1.txt"
#define TESTFILE2 CMAKE_SOURCE_DIR"/tests/testdbase64.2.txt"

#define WRAPPING 76

static const char * test0 = "YWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXow";
static const char * test1 = "YWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXo=";
static const char * test2 = "YWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXowMTIzNDU2Nzg5YWJjZGVmZ2hpamtsbW5vcHFyc3R1"
							"dnd4eXowMTIzNDU2Nzg5YWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXowMTIzNDU2Nzg5YWJjZGVm"
							"Z2hpamtsbW5vcHFyc3R1dnd4eXowMQ==";

void TestDBase64::encode_test()
{
	DBase64 base;
	DString encoded;
	
	encoded = base.encodeFromFile( TESTFILE0 );
	TEST_ASSERT_MSG( encoded == test0, "Wrong base64 encoding" )
	encoded = base.encodeFromFile( TESTFILE1 );
	TEST_ASSERT_MSG( encoded == test1, "Wrong base64 encoding" )
	encoded = base.encodeFromFile( TESTFILE2 );
	TEST_ASSERT_MSG( encoded == test2, "Wrong base64 encoding" )
}

void TestDBase64::encode_wrapped_test()
{
	DBase64 base;
	DString encoded;
	DStringList lines;
	
	encoded = base.encodeFromFile( TESTFILE2 );
	lines = base.getWrappedEncoded( 76 );
	TEST_ASSERT_MSG( lines.size() == 3, "Wrong wrapped base64 encoding" )
	lines.clear();
	lines = base.getWrappedEncoded( 0 );
	TEST_ASSERT_MSG( lines.size() == 1, "Wrong no-wrapped base64 encoding" )
}

void TestDBase64::decode_test()
{
	DBase64 base;
	DString ref, buffer;
	
	ref = test0;
	base.setEncoded( ref );
	buffer = base.getEncoded();
	TEST_ASSERT_MSG( ref == buffer, "Get encoded failed" )
	//base.decodeToFile( "/tmp/testdbase64.0.txt" );
}

int main()
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