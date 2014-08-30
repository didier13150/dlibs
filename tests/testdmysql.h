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
 *     (___)_)   File : testdmysql.h                        ||--|| *          *
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
 *   Unit Test for DMySQL                                                     *
 *                                                                            *
 ******************************************************************************/

#ifndef _TESTDMYSQL_H
#define _TESTDMYSQL_H

#include <cpptest.h>

#include "dmysql.h"
#include "dfactory.h"

class TestDMySQL : public Test::Suite
{
public:
	TestDMySQL()
	{
		TEST_ADD( TestDMySQL::setup )
		TEST_ADD( TestDMySQL::exception_enabled )
		TEST_ADD( TestDMySQL::socket_connect_test )
		TEST_ADD( TestDMySQL::network_connect_test )
		TEST_ADD( TestDMySQL::insert_test )
		TEST_ADD( TestDMySQL::insert_exception_test )
		TEST_ADD( TestDMySQL::factory_test )
	}

private:
	void setup();
	void exception_enabled();
	void socket_connect_test();
	void network_connect_test();
	void insert_test();
	void insert_exception_test();
	void factory_test();
	
	DString _dbhost;
	DString _dbip;
	DString _dbbase;
	DString _dbuser;
	DString _dbpasswd;
};

#endif // _TESTDMYSQL_H
