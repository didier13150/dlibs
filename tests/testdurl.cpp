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
 *     (___)_)   File : testdurl.cpp                  ||--|| *          *
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
 *   Unit Test for DURL                                                 *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdurl.h"

void TestDURL::constructor_test()
{
	DURL url( "127.0.0.1" );
	std::cout << std::endl << url.getLastError() << std::endl;
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url constructor failed" )
}

void TestDURL::setUrl_test()
{
	DURL url;
	
	url.setURL( "127.0.0.1" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url set failed" )
	url.setURL( "localhost/var/www/dlibs/" );
	std::cout << std::endl << url.getLastError() << std::endl;
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url with path set failed" )
	url.setURL( "http://www.google.fr/ig" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url with path and protocol set failed" )
	url.setURL( "smtp://localhost" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url with protocol set failed" )
	url.setURL( "ssh://localhost:2222/svn/dlibs/" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url with path,port and protocol set failed" )
	url.setURL( "toto://localhost:12345" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url with port and protocol set failed" )
}

void TestDURL::getUrl_test()
{
	DURL url;
	
	url.setURL( "127.0.0.1" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url set failed" )
	TEST_ASSERT_MSG( url.isIPAddress() == true, "Url don't reported as an IP address" )
	url.setURL( "localhost/var/www/dlibs/" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url with path set failed" )
	TEST_ASSERT_MSG( url.isIPAddress() == false, "Url reported as an IP address" )
	url.setURL( "http://www.google.fr/ig" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url with path and protocol set failed" )
	TEST_ASSERT_MSG( url.isIPAddress() == false, "Url reported as an IP address" )
	url.setURL( "smtp://localhost" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url with protocol set failed" )
	TEST_ASSERT_MSG( url.isIPAddress() == false, "Url reported as an IP address" )
	url.setURL( "ssh://localhost:2222/svn/dlibs/" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url with path,port and protocol set failed" )
	TEST_ASSERT_MSG( url.isIPAddress() == false, "Url reported as an IP address" )
	url.setURL( "toto://localhost:12345" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url with port and protocol set failed" )
	TEST_ASSERT_MSG( url.isIPAddress() == false, "Url reported as an IP address" )
	
}

int main( int argc, char** argv )
{
	std::ofstream file;
	TestDURL ets;
	
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );
	Test::HtmlOutput html;
	
	file.open( "durl.html" );
	ets.run( html );
	html.generate( file, true, "DURL" );
	file.close();
	
	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
}