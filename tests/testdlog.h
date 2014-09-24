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
 *     (___)_)   File : testdlog.h                          ||--|| *          *
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
 *   Unit Test for DLog                                                       *
 *                                                                            *
 ******************************************************************************/

#ifndef _TESTDLOG_H
#define _TESTDLOG_H

#include <cpptest.h>

class TestDLog : public Test::Suite
{
public:
	TestDLog()
	{
		TEST_ADD( TestDLog::socket_test )
		TEST_ADD( TestDLog::socket2_test )
		TEST_ADD( TestDLog::logfile_test )
		TEST_ADD( TestDLog::stream_test )
		TEST_ADD( TestDLog::syslog_test )
		TEST_ADD( TestDLog::sqlite_test )
		TEST_ADD( TestDLog::sqlite2_test )
		TEST_ADD( TestDLog::mysql_test )
		TEST_ADD( TestDLog::pgsql_test )
		TEST_ADD( TestDLog::unintialized_test )
		TEST_ADD( TestDLog::params_test )
		TEST_ADD( TestDLog::no_close_test )
		TEST_ADD( TestDLog::logger_test )
		TEST_ADD( TestDLog::engine_test )
	}

private:
	void logfile_test();
	void stream_test();
	void socket_test();
	void socket2_test();
	void syslog_test();
	void sqlite_test();
	void sqlite2_test();
	void mysql_test();
	void pgsql_test();
	void unintialized_test();
	void params_test();
	void no_close_test();
	void logger_test();
	void engine_test();
};

#endif // _TESTDLOG_H
