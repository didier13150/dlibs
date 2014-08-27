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
 *     (___)_)   File : testdsmtp.cpp                       ||--|| *          *
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
 *   Unit Test for DSMTP                                                      *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdsmtp.h"
#include "test.h"

#define TESTFILE CMAKE_SOURCE_DIR"/tux.png"
#define WRAPPING 76

void TestDSMTP::simple_test()
{
	DSMTP mail;
	DSMTP::ERRNO code;
	DURL server;
	DStringList transaction;
	DStringList::const_iterator it;

	server.setURL( "smtp://localhost.localdomain:25" );

	mail.setHost ( server );
	mail.setSender ( "root@localhost" );
	mail.addReceiver ( "root@localhost" );
	mail.setEmail ( "DLibs test", "This is just a simple DLibs test, SMTP part" );
	code = mail.send();
	
	TEST_ASSERT_MSG( mail.getLastError() == DString::empty(), "Error reported when sending email" )
	if ( code != DSMTP::SUCCESS )
	{
		transaction = mail.getTransactionLog();
		for ( it = transaction.begin() ; it != transaction.end() ; it++ )
		{
			std::cout << *it << std::endl;
		}
		TEST_FAIL( "Email not sent" )
	}
}

void TestDSMTP::with_attach_test()
{
	DSMTP mail;
	DSMTP::ERRNO code;
	DURL server;
	DStringList transaction;
	DStringList::const_iterator it;

	server.setURL( "smtp://localhost.localdomain:25" );

	mail.setHost ( server );
	mail.setSender ( "root@localhost" );
	mail.addReceiver ( "root@localhost" );
	mail.addAttach( TESTFILE );
	mail.setEmail ( "DLibs test", "This is just a simple DLibs test, SMTP part", "test" );
	code = mail.send();
	
	TEST_ASSERT_MSG( mail.getLastError() == DString::empty(), "Error reported when sending email" )
	if ( code != DSMTP::SUCCESS )
	{
		transaction = mail.getTransactionLog();
		for ( it = transaction.begin() ; it != transaction.end() ; it++ )
		{
			std::cout << *it << std::endl;
		}
		TEST_FAIL( "Email not sent" )
	}
}
void TestDSMTP::get_mime_type()
{
	TEST_ASSERT_MSG( getMimeType( CMAKE_SOURCE_DIR"/tux.png" ) == "image/png", "Bad format reported for tux PNG image" )
	TEST_ASSERT_MSG( getMimeType( CMAKE_SOURCE_DIR"/logo.svg" ) == "image/svg+xml", "Bad format reported for tux SVG image" )
	TEST_ASSERT_MSG( getMimeType( CMAKE_SOURCE_DIR"/AUTHORS" ) == "text/plain", "Bad format reported for tux PNG image" ) 
}

int main( int argc, char** argv )
{
	TestDSMTP ets;
#ifdef TEST_HTML
	std::ofstream file;
	Test::HtmlOutput html;

	file.open( "dsmtp.html" );
	ets.run( html );
	html.generate( file, true, "DSMTP" );
	file.close();
#endif

#ifdef TEST_STDOUT
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout << std::endl );

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
#endif
	return EXIT_SUCCESS;
}
