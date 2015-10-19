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
 *     (___)_)   File : testdappcmdline.h                   ||--|| *          *
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
 *   Unit Test for DAppCmdLine                                                *
 *                                                                            *
 ******************************************************************************/

#ifndef _TESTDAPPCMDLINE_H
#define _TESTDAPPCMDLINE_H

#include <cpptest.h>

class TestDAppCmdLine : public Test::Suite
{
public:
	TestDAppCmdLine()
	{
		TEST_ADD( TestDAppCmdLine::constructor_test )
		TEST_ADD( TestDAppCmdLine::arg_and_opt_test )
		TEST_ADD( TestDAppCmdLine::show_help_test )
		TEST_ADD( TestDAppCmdLine::show_version_test )
		TEST_ADD( TestDAppCmdLine::app_opt_stream_test )
		TEST_ADD( TestDAppCmdLine::app_arg_stream_test )
		TEST_ADD( TestDAppCmdLine::set_args_test )
		TEST_ADD( TestDAppCmdLine::set_opts_test )
		TEST_ADD( TestDAppCmdLine::print_app_test )
		TEST_ADD( TestDAppCmdLine::bad_opts_test )
		TEST_ADD( TestDAppCmdLine::help_with_lot_of_opts_test )
		TEST_ADD( TestDAppCmdLine::arg_with_dash_test )
	}

private:
	void constructor_test();
	void show_help_test();
	void show_version_test();
	void arg_and_opt_test();
	void app_opt_stream_test();
	void app_arg_stream_test();
	void set_args_test();
	void set_opts_test();
	void print_app_test();
	void bad_opts_test();
	void help_with_lot_of_opts_test();
	void arg_with_dash_test();
};

#endif // _TESTDAPPCMDLINE_H
