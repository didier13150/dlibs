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
 *     (___)_)   File : testdurl.cpp                        ||--|| *          *
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
 *   Unit Test for DURL                                                       *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdurl.h"

void TestDURL::constructor_test()
{
	DURL url( "127.0.0.1" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url constructor failed" )
}

void TestDURL::url_test()
{
	DURL url;

	url.setURL( "127.0.0.1" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url set failed" )
	TEST_ASSERT_MSG( url.getIPAddress() == "127.0.0.1", "Url doesn't report good IP" )
	TEST_ASSERT_MSG( url.getHost().section( '.', 0, 0 ) == "localhost", "Url doesn't report good hostname" )
	TEST_ASSERT_MSG( url.getPort() == 0, "Url doesn't report good port" )
	TEST_ASSERT_MSG( url.getServiceName() == DString::empty(), "Url doesn't report good service" )
	TEST_ASSERT_MSG( url.getPath() == DString::empty(), "Url doesn't report good path" )
	TEST_ASSERT_MSG( url.isIPAddress() == true, "Url not reported as an IP address" )
	TEST_ASSERT_MSG( url.isHostname() == false, "Url reported as a hostname" )

	url.setURL( "localhost/var/www/dlibs/" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url with path set failed" )
	TEST_ASSERT_MSG( url.getIPAddress() == "127.0.0.1", "Url doesn't report good IP" )
	TEST_ASSERT_MSG( url.getHost().section( '.', 0, 0 ) == "localhost", "Url doesn't report good hostname" )
	TEST_ASSERT_MSG( url.getPort() == 0, "Url doesn't report good port" )
	TEST_ASSERT_MSG( url.getServiceName() == DString::empty(), "Url doesn't report good service" )
	TEST_ASSERT_MSG( url.getPath() == "/var/www/dlibs", "Url doesn't report good path" )
	TEST_ASSERT_MSG( url.isIPAddress() == false, "Url reported as an IP address" )
	TEST_ASSERT_MSG( url.isHostname() == true, "Url not reported as a hostname" )

	url.setURL( "http://www.google.fr" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url with path and protocol set failed" )
	TEST_ASSERT_MSG( url.getHost() == "www.google.fr", "Url doesn't report good hostname" )
	TEST_ASSERT_MSG( url.getPort() == 80, "Url doesn't report good port" )
	TEST_ASSERT_MSG( url.getServiceName() == "http", "Url doesn't report good service" )
	TEST_ASSERT_MSG( url.getPath() == DString::empty(), "Url doesn't report good path" )
	TEST_ASSERT_MSG( url.isIPAddress() == false, "Url reported as an IP address" )
	TEST_ASSERT_MSG( url.isHostname() == true, "Url not reported as a hostname" )

	url.setURL( "ssh://localhost/svn" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url with path and protocol set failed" )
	TEST_ASSERT_MSG( url.getIPAddress() == "127.0.0.1", "Url doesn't report good IP" )
	TEST_ASSERT_MSG( url.getHost().section( '.', 0, 0 ) == "localhost", "Url doesn't report good hostname" )
	TEST_ASSERT_MSG( url.getPort() == 22, "Url doesn't report good port" )
	TEST_ASSERT_MSG( url.getServiceName() == "ssh", "Url doesn't report good service" )
	TEST_ASSERT_MSG( url.getPath() == "/svn", "Url doesn't report good path" )
	TEST_ASSERT_MSG( url.isIPAddress() == false, "Url reported as an IP address" )
	TEST_ASSERT_MSG( url.isHostname() == true, "Url not reported as a hostname" )

	url.setURL( "ssh://localhost:2222/svn/dlibs/" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url with path,port and protocol set failed" )
	TEST_ASSERT_MSG( url.getIPAddress() == "127.0.0.1", "Url doesn't report good IP" )
	TEST_ASSERT_MSG( url.getHost().section( '.', 0, 0 ) == "localhost", "Url doesn't report good hostname" )
	TEST_ASSERT_MSG( url.getPort() == 2222, "Url doesn't report good port" )
	TEST_ASSERT_MSG( url.getServiceName() == "ssh", "Url doesn't report good service" )
	TEST_ASSERT_MSG( url.getPath() == "/svn/dlibs", "Url doesn't report good path" )
	TEST_ASSERT_MSG( url.isIPAddress() == false, "Url reported as an IP address" )
	TEST_ASSERT_MSG( url.isHostname() == true, "Url not reported as a hostname" )

	url.setURL( "toto://localhost:12345/svn/dlibs" );
	TEST_ASSERT_MSG( url.getLastErrno() == 0, "Url with port and protocol set failed" )
	TEST_ASSERT_MSG( url.getIPAddress() == "127.0.0.1", "Url doesn't report good IP" )
	TEST_ASSERT_MSG( url.getHost().section( '.', 0, 0 ) == "localhost", "Url doesn't report good hostname" )
	TEST_ASSERT_MSG( url.getPort() == 12345, "Url doesn't report good port" )
	TEST_ASSERT_MSG( url.getServiceName() == "toto", "Url doesn't report good service" )
	TEST_ASSERT_MSG( url.getPath() == "/svn/dlibs", "Url doesn't report good path" )
	TEST_ASSERT_MSG( url.isIPAddress() == false, "Url reported as an IP address" )
	TEST_ASSERT_MSG( url.isHostname() == true, "Url not reported as a hostname" )

	url.setURL( "toto://localhost/ip" );
	TEST_ASSERT_MSG( url.getLastErrno() == DURL::NO_SERVICE, "Url with wrong protocol set successfully" )
	TEST_ASSERT_MSG( url.getIPAddress() == "127.0.0.1", "Url doesn't report good IP" )
	TEST_ASSERT_MSG( url.getHost().section( '.', 0, 0 ) == "localhost", "Url doesn't report good hostname" )
	TEST_ASSERT_MSG( url.getPort() == 0, "Url doesn't report good port" )
	TEST_ASSERT_MSG( url.getServiceName() == "toto", "Url doesn't report good service" )
	TEST_ASSERT_MSG( url.getPath() == "/ip", "Url doesn't report good path" )
	TEST_ASSERT_MSG( url.isIPAddress() == false, "Url reported as an IP address" )
	TEST_ASSERT_MSG( url.isHostname() == true, "Url not reported as a hostname" )

	url.setURL( "http://1.1.1.1:8080/ip" );
	TEST_ASSERT_MSG( url.getLastErrno() == DURL::NO_HOST_BY_ADDR, "Url with IP address set successfully" )
	TEST_ASSERT_MSG( url.getIPAddress() == "1.1.1.1", "Url doesn't report good IP" )
	TEST_ASSERT_MSG( url.getHost() == DString::empty(), "Url report wrong hostname" )
	TEST_ASSERT_MSG( url.getPort() == 8080, "Url doesn't report good port" )
	TEST_ASSERT_MSG( url.getServiceName() == "http", "Url doesn't report good service" )
	TEST_ASSERT_MSG( url.getPath() == "/ip", "Url doesn't report good path" )
	TEST_ASSERT_MSG( url.isIPAddress() == true, "Url reported as an IP address" )
	TEST_ASSERT_MSG( url.isHostname() == false, "Url not reported as a hostname" )
}

int main( int argc, char** argv )
{
	std::ofstream file;
	TestDURL ets;

	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );
	/*Test::HtmlOutput html;

	file.open( "durl.html" );
	ets.run( html );
	html.generate( file, true, "DURL" );
	file.close();*/

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
}