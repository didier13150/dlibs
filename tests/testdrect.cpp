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
 *     (___)_)   File : testdrect.cpp                       ||--|| *          *
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
 *   Unit Test for DRect                                                      *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdrect.h"
#include "test.h"
#include "dpoint.h"

typedef DPoint<int> Point;
typedef DRect<int> Rect;
typedef DRect<int>::Apex Apex;

void TestDRect::constructor_test()
{
	Rect rect1( -2, -2, 2, 2 );
	Rect rect2( 2, 2, -2, -2 );
	TEST_ASSERT_MSG( rect1 == rect2, "formatRect failed" )
	Rect rect3( -2, 2, 2, -2);
	Rect rect4( 2, -2, -2, 2);
	TEST_ASSERT_MSG( rect3 == rect4, "formatRect failed" )
}

void TestDRect::constructor_dpoint_test()
{
	Point pt1(2,2);
	Point pt2(-2,-2);
	Rect rect1( pt2, pt1 );
	Rect rect2( -2, -2, 2, 2 );
	TEST_ASSERT_MSG( rect1 == rect2, "Construct from DPoint failed" )
}

void TestDRect::apex_test()
{
	Apex apex1, apex2( -2, -2, 2, 2 ) ;
	Rect rect1( -2, -2, 2, 2 ), rect2;
	
	apex1 = rect1.getApex();
	TEST_ASSERT_MSG( apex1 == apex2, "Getting Apex failed" )
	
	rect2.setApex( Apex( -2, -2, 2, 2 ) );
	TEST_ASSERT_MSG( rect1 == rect2, "Setting rect from apex failed" )
}

void TestDRect::inside_test()
{
	Point pt1( 1, 1 );
	Point pt2( 2, 2 );
	Point pt3( 3, 3 );
	Rect rect( -2, -2, 2, 2 );
	TEST_ASSERT_MSG( rect.isInside( pt1 ) == true, "Check if a point is inside a rect failed" )
	TEST_ASSERT_MSG( rect.isInside( pt2 ) == true, "Check if a point is inside a rect failed" )
	TEST_ASSERT_MSG( rect.isInside( pt3 ) == false, "Check if a point is inside a rect failed" )
	TEST_ASSERT_MSG( rect.isInside( pt1, false ) == true, "Check if a point is inside a rect failed" )
	TEST_ASSERT_MSG( rect.isInside( pt2, false ) == false, "Check if a point is inside a rect failed" )
	TEST_ASSERT_MSG( rect.isInside( pt3, false ) == false, "Check if a point is inside a rect failed" )
}

int main()
{
	TestDRect ets;
#ifdef TEST_HTML
	std::ofstream file;
	Test::HtmlOutput html;

	file.open( "drect.html" );
	ets.run( html );
	html.generate( file, true, "DRect" );
	file.close();
#endif

#ifdef TEST_STDOUT
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
#endif
	return EXIT_SUCCESS;
}
