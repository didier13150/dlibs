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
 *     (___)_)   File : testdpoint.cpp                      ||--|| *          *
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
 *   Unit Test for DPoint                                                     *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdpoint.h"
#include "dpoint.h"
#include "test.h"

typedef DPoint<unsigned int> UPoint;
typedef DPoint<int> Point;
typedef DPoint<float> FPoint;

void TestDPoint::constructor_test()
{
	UPoint pt;
	TEST_ASSERT_MSG( pt.getX() == 0, "Get initial X var failed" )
	TEST_ASSERT_MSG( pt.getY() == 0, "Get initial Y var failed" )
	TEST_ASSERT_MSG( pt.isNull() == true, "Initial vars are not null" )
	UPoint pt2(2,2);
	TEST_ASSERT_MSG( pt2.getX() == 2, "Get initial X var failed" )
	TEST_ASSERT_MSG( pt2.getY() == 2, "Get initial Y var failed" )
	TEST_ASSERT_MSG( pt2.isNull() == false, "Initial vars are null" )
	FPoint pt3( 3.2, 5.4);
	TEST_ASSERT_DELTA_MSG( pt3.getX(), 3.2, 0.0001, "Get initial X float var failed" )
	TEST_ASSERT_DELTA_MSG( pt3.getY(), 5.4, 0.0001, "Get initial Y float var failed" )
	pt3.clear();
	TEST_ASSERT_MSG( pt3.getX() == 0.0, "Get X float var after clear failed" )
	TEST_ASSERT_MSG( pt3.getY() == 0.0, "Get Y float var after clear failed" )
}

void TestDPoint::reference_test()
{
	UPoint pt(2,8);
	pt.refX()++;
	pt.refY()++;
	TEST_ASSERT_MSG( pt.getX() == 3, "Get initial X var failed" )
	TEST_ASSERT_MSG( pt.getY() == 9, "Get initial Y var failed" )
	unsigned int x, y;
	pt.getPoint(x, y);
	TEST_ASSERT_MSG( x == 3, "Get x var failed" )
	TEST_ASSERT_MSG( y == 9, "Get y var failed" )
}

void TestDPoint::comparator_test()
{
	Point pt1(2,3), pt2(4,6);
	TEST_ASSERT_MSG( pt2 != pt1, "DPoint pt2 is not different to pt1" )
	TEST_ASSERT_MSG( pt2 > pt1, "DPoint pt2 is not superior to pt1" )
	TEST_ASSERT_MSG( pt1 < pt2, "DPoint pt1 is not inferior to pt2" )
	TEST_ASSERT_MSG( pt1 <= pt2, "DPoint pt1 is not inferior or equal to pt2" )
	TEST_ASSERT_MSG( pt2 > pt1, "DPoint pt2 is not superior to pt1" )
	TEST_ASSERT_MSG( pt2 >= pt1, "DPoint pt2 is not superior or equal to pt1" )
	pt2 /= 2;
	TEST_ASSERT_MSG( pt1 == pt2, "DPoint are not equals after operator/" )
	TEST_ASSERT_MSG( pt2 >= pt1, "DPoint pt2 is not superior or equal to pt1" )
	TEST_ASSERT_MSG( pt1 >= pt2, "DPoint pt1 is not superior or equal to pt2" )
}

void TestDPoint::operator_test()
{
	Point pt1(2,3), pt2(4,6), pt3;
	pt3 = pt1 + pt2;
	TEST_ASSERT_MSG( pt3.getX() == 6, "Get X var after operator+ failed" )
	TEST_ASSERT_MSG( pt3.getY() == 9, "Get Y var after operator+ failed" )
	pt3 = pt1 - pt2;
	TEST_ASSERT_MSG( pt3.getX() == -2, "Get X var after operator- failed" )
	TEST_ASSERT_MSG( pt3.getY() == -3, "Get Y var after operator- failed" )
	pt3 = pt1 * pt2;
	TEST_ASSERT_MSG( pt3.getX() == 8, "Get X var after operator* failed" )
	TEST_ASSERT_MSG( pt3.getY() == 18, "Get Y var after operator* failed" )
	pt3 = pt2 / pt1;
	TEST_ASSERT_MSG( pt3.getX() == 2, "Get X var after operator/ failed" )
	TEST_ASSERT_MSG( pt3.getY() == 2, "Get Y var after operator/ failed" )

	FPoint fpt1(3.0,3.5), fpt2(4.5,5.25), fpt3;
	fpt3 = fpt1 + fpt2;
	TEST_ASSERT_MSG( fpt3.getX() == 7.5, "Get X var after operator+ failed (float)" )
	TEST_ASSERT_MSG( fpt3.getY() == 8.75, "Get Y var after operator+ failed (float)" )
	fpt3 = fpt1 - fpt2;
	TEST_ASSERT_MSG( fpt3.getX() == -1.5, "Get X var after operator- failed (float)" )
	TEST_ASSERT_MSG( fpt3.getY() == -1.75, "Get Y var after operator- failed (float)" )
	fpt3 = fpt1 * fpt2;
	TEST_ASSERT_MSG( fpt3.getX() == 13.5, "Get X var after operator* failed" )
	TEST_ASSERT_MSG( fpt3.getY() == 18.375, "Get Y var after operator* failed" )
	fpt3 = fpt2 / fpt1;
	TEST_ASSERT_MSG( fpt3.getX() == 1.5, "Get X var after operator/ failed" )
	TEST_ASSERT_MSG( fpt3.getY() == 1.5, "Get Y var after operator/ failed" )

}

void TestDPoint::stream_test()
{
	FPoint pt( 3.2, 5.4);
	TEST_ASSERT_MSG( pt.toString() == "{3.2,5.4}", "Get string dump failed" )
	std::istringstream iss;
	std::ostringstream oss;

	iss.str( "{8.6,7.1}" );
	iss >> pt;
	TEST_ASSERT_DELTA_MSG( pt.getX(), 8.6, 0.0001, "Get X float var after stream push failed" )
	TEST_ASSERT_DELTA_MSG( pt.getY(), 7.1, 0.0001, "Get Y float var after stream push failed" )
	TEST_ASSERT_MSG( pt.toString() == "{8.6,7.1}", "Get string dump failed after stream push" )
	oss << pt;
	TEST_ASSERT_MSG( oss.str() == "{8.6,7.1}", "Get string dump failed after stream push" )

}

int main()
{
	TestDPoint ets;
#ifdef TEST_HTML
	std::ofstream file;
	Test::HtmlOutput html;

	file.open( "dpoint.html" );
	ets.run( html );
	html.generate( file, true, "DPoint" );
	file.close();
#endif

#ifdef TEST_STDOUT
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
#endif
	return EXIT_SUCCESS;
}
