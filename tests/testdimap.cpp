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
#include <unistd.h>
#include "testdimap.h"
#include "dimap.h"
#include "test.h"
#include "dsettings.h"

TestDIMAP::TestDIMAP()
{
	TEST_ADD( TestDIMAP::setup )
	TEST_ADD( TestDIMAP::basic_test )
	TEST_ADD( TestDIMAP::fetch_some_mails_test )
	TEST_ADD( TestDIMAP::flag_test )
	TEST_ADD( TestDIMAP::list_test )
	TEST_ADD( TestDIMAP::bad_host_test )
	TEST_ADD( TestDIMAP::bad_credential_test )
	TEST_ADD( TestDIMAP::delete_one_test )
	TEST_ADD( TestDIMAP::delete_all_test )
}

void TestDIMAP::setup()
{
	DSettings sets;
	int err;
	
	err = sets.setFileName ( "test-settings.xml" );
	if ( err != DSettings::SUCCESS )
	{
		TEST_FAIL( "Can not specify settings file." )
		_user = "root";
		_passwd = "";
		_host = "localhost";
	}
	
	err = sets.readEntry ( "/settings/imap/user", _user );
	if ( err != DSettings::SUCCESS )
	{
		TEST_FAIL( "Can not read entry for IMAP user." )
		_user = "root";
	}
	
	err = sets.readEntry ( "/settings/imap/password", _passwd );
	if ( err != DSettings::SUCCESS )
	{
		TEST_FAIL( "Can not read entry for IMAP password." )
		_passwd = "";
	}
	
	err = sets.readEntry ( "/settings/imap/host", _host );
	if ( err != DSettings::SUCCESS )
	{
		TEST_FAIL( "Can not read entry for IMAP hostname." )
		_host = "localhost";
	}
	
	err = sets.readEntry ( "/settings/imap/dir", _dir );
	if ( err != DSettings::SUCCESS or _dir.isEmpty() )
	{
		_dir = "INBOX";
	}
}

void TestDIMAP::basic_test()
{
	DIMAP imap;
	DString content;
	
	imap.setHostname( _host );
	imap.setUser( _user );
	imap.setPassword( _passwd );
	TEST_ASSERT_MSG( imap.getDir() == "INBOX", "Wrong default directory" )
	imap.setDir( _dir );
	TEST_ASSERT_MSG( imap.getDir() == _dir, "Wrong current directory" )
	TEST_ASSERT_MSG( imap.getHostname() == _host, "Wrong hostname" )
	TEST_ASSERT_MSG( imap.getUser() == _user, "Wrong user" )
	TEST_ASSERT_MSG( imap.getPassword() == _passwd , "Wrong password" )
	TEST_ASSERT_MSG( imap.getTimeout() == 30 , "Wrong default timeout" )
	imap.setTimeout( 10 );
	TEST_ASSERT_MSG( imap.getTimeout() == 10 , "Wrong current timeout" )
	TEST_ASSERT_MSG( imap.getUid() == 1 , "Wrong UID" )
	content = imap.getMessage();
	TEST_ASSERT_MSG( ! content.isEmpty(), "No message downloaded" )
	imap.next();
	TEST_ASSERT_MSG( imap.getUid() == 2 , "Wrong UID" )
}

void TestDIMAP::bad_host_test()
{
	DIMAP imap;
	DString content;
	
	imap.setHostname( "imap.example.org" );
	imap.setLogin( "toto", "toto" );
	imap.getDirList();
	TEST_ASSERT_MSG( imap.getLastError() == "curl_easy_perform() failed: Couldn't resolve host name", "Wrong error message for unknown host" )
	content = imap.getMessage();
	TEST_ASSERT_MSG( imap.getLastError() == "curl_easy_perform() failed: Couldn't resolve host name", "Wrong error message for unknown host" )
}

void TestDIMAP::bad_credential_test()
{
	DIMAP imap;
	DString content;
	
	imap.setHostname( _host );
	// Wrong login with wrong password
	imap.setLogin( "toto", "toto" );
	imap.getMessage();
	TEST_ASSERT_MSG( imap.getLastError() == "curl_easy_perform() failed: Login denied", "Wrong error message for unknown user: get message" )
	
	imap.erase();
	TEST_ASSERT_MSG( imap.getLastError() == "curl_easy_perform(STORE 1 +Flags \\Deleted) failed: Login denied", "Wrong error message for unknown user: erase" )
	
	imap.expunge();
	TEST_ASSERT_MSG( imap.getLastError() == "curl_easy_perform(EXPUNGE) failed: Login denied", "Wrong error message for unknown user: expunge" )
	
	imap.getDirList();
	TEST_ASSERT_MSG( imap.getLastError() == "curl_easy_perform() failed: Login denied", "Wrong error message for unknown user: dir list" )

	// Allowed login with wrong password
	imap.setLogin( _user, "toto" );
	
	imap.getMessage();
	TEST_ASSERT_MSG( imap.getLastError() == "curl_easy_perform() failed: Login denied", "Wrong error message for allowed user but wrong pasword: get message" )

}

void TestDIMAP::fetch_some_mails_test()
{
	DIMAP imap;
	DString content;
	unsigned int uid = 0;
	
	imap.setHostname( _host );
	imap.setLogin( _user, _passwd );
	imap.setDir( _dir );
	
	content = imap.getMessage();
	while ( ! content.isEmpty() ) {
		uid++;
		imap.next();
		if ( uid > 2 ) break;
		content = imap.getMessage();
	}
	TEST_ASSERT_MSG( uid != 0, "No message downloaded" )
}

void TestDIMAP::delete_one_test()
{
	DIMAP imap;
	DString content;
	
	imap.setHostname( _host );
	imap.setLogin( _user, _passwd );
	imap.setDir( _dir );
	
	content = imap.getMessage();
	TEST_ASSERT_MSG( imap.erase(), "Mail not deleted" )
}

void TestDIMAP::delete_all_test()
{
	DIMAP imap;
	DString content;
	
	imap.setHostname( _host );
	imap.setLogin( _user, _passwd );
	imap.setDir( _dir );
	
	content = imap.getMessage();
	while ( ! content.isEmpty() ) {
		TEST_ASSERT_MSG( imap.erase(), "Mail not deleted" )
		imap.next();
		content = imap.getMessage();
	}
	imap.expunge();
	content = imap.getMessage();
	TEST_ASSERT_MSG( content.isEmpty(), "Message still present" )
	TEST_ASSERT_MSG( imap.getLastError() == "curl_easy_perform() failed: Remote file not found", "Wrong error message for empty dir" )
}

void TestDIMAP::flag_test()
{
	DIMAP imap;
	
	imap.setHostname( _host );
	imap.setLogin( _user, _passwd );
	imap.setDir( _dir );
	
	imap.getMessage();
	TEST_ASSERT_MSG( imap.read(), "Mail not flagged as read" )
	TEST_ASSERT_MSG( imap.answered(), "Mail not flagged as answered" )
	TEST_ASSERT_MSG( imap.setFlag( DIMAP::FLAGGED ), "Mail not flagged as flagged" )
}

void TestDIMAP::list_test()
{
	DIMAP imap;
	
	imap.setHostname( _host );
	imap.setLogin( _user, _passwd );
	TEST_ASSERT_MSG( imap.getDirList().size(), "IMAP Dir list is empty" )
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
