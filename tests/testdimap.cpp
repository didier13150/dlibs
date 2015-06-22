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
 *     (___)_)   File : testdimap.cpp                       ||--|| *          *
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
 *   Unit Test for DIMAP                                                      *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdimap.h"
#include "dimap.h"
#include "test.h"

void TestDIMAP::basic_test()
{
	DIMAP imap;
	DString content;
	
	imap.setHostname( IMAP_HOST );
	imap.setLogin( IMAP_USER, IMAP_PASSWD );
	imap.setDir( "INBOX" );
	
	content = imap.getMessage();	
	TEST_ASSERT_MSG( ! content.isEmpty(), "No message downloaded" )
}

void TestDIMAP::fetch_some_mails_test()
{
	DIMAP imap;
	DString content;
	unsigned int uid = 0;
	
	imap.setHostname( IMAP_HOST );
	imap.setLogin( IMAP_USER, IMAP_PASSWD );
	imap.setDir( "INBOX" );
	
	content = imap.getMessage();
	while ( ! content.isEmpty() ) {
		uid++;
		imap.next();
		if ( uid > 2 ) break;
		content = imap.getMessage();
	}
	TEST_ASSERT_MSG( uid != 0, "No message downloaded" )
}

int main()
{
	TestDIMAP ets;
#ifdef TEST_HTML
	std::ofstream file;
	Test::HtmlOutput html;

	file.open( "dimap.html" );
	ets.run( html );
	html.generate( file, true, "DIMAP" );
	file.close();
#endif

#ifdef TEST_STDOUT
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
#endif
	return EXIT_SUCCESS;
}
