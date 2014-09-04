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
 *     (___)_)   File : testdstring.h                       ||--|| *          *
 *                                                                            *
 *   This program is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU General Public License as published by     *
 *   the Free Software Foundation; either version 2 of the License, or        *
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
 *   Unit Test for DString                                                    *
 *                                                                            *
 ******************************************************************************/

#ifndef _TESTDSTRING_H
#define _TESTDSTRING_H

#include <cpptest.h>

class TestDString : public Test::Suite
{
public:
	TestDString()
	{
		TEST_ADD( TestDString::constructor_test )
		TEST_ADD( TestDString::add_test )
		TEST_ADD( TestDString::compare_test )
		TEST_ADD( TestDString::others_operators_test )
		TEST_ADD( TestDString::number_test )
		TEST_ADD( TestDString::binary_test )
		TEST_ADD( TestDString::length_test )
		TEST_ADD( TestDString::substr_test )
		TEST_ADD( TestDString::legal_char_test )
		TEST_ADD( TestDString::split_test )
		TEST_ADD( TestDString::time_test )
		TEST_ADD( TestDString::map_key_test )
		TEST_ADD( TestDString::space_test )
		TEST_ADD( TestDString::case_test )
		TEST_ADD( TestDString::justify_test )
		TEST_ADD( TestDString::contains_test )
		TEST_ADD( TestDString::stream_test )
		TEST_ADD( TestDString::quoted_printable_test )
		TEST_ADD( TestDString::html_test )
	}
    
private:
	void constructor_test();
	void add_test();
	void compare_test();
	void others_operators_test();
	void number_test();
	void binary_test();
	void length_test();
	void substr_test();
	void legal_char_test();
	void split_test();
	void time_test();
	void map_key_test();
	void space_test();
	void case_test();
	void justify_test();
	void contains_test();
	void stream_test();
	void quoted_printable_test();
	void html_test();
};

#endif // _TESTDSTRING_H