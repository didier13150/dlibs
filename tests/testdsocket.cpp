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
 *     (___)_)   File : testdsocket.cpp                     ||--|| *          *
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
 *   Unit Test for DSocket                                                    *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdsocket.h"

#define PORT 12345

void TestDSocket::basic_com_test()
{
	DServerSock server;
	DClientSock client;
	int h = -1;
	DString buffer;
	int err;
	
	server.setTimeout ( 1500 );
	client.setTimeout ( 1500 );
	err = server.openSock ( PORT );
	TEST_ASSERT_MSG( err == DSock::SUCCESS, "Can not open socket on server side" )
	
	err = client.openSock ( "localhost", PORT );
	TEST_ASSERT_MSG( err == DSock::SUCCESS, "Can not open socket on client side" )
	if ( err != DSock::SUCCESS )
	{
		server.closeSock();
		return;
	}
	
	err = server.openConnection ( h );
	TEST_ASSERT_MSG( err == DSock::SUCCESS, "Can not open new connection on server side" )
	if ( err != DSock::SUCCESS )
	{
		server.closeSock();
		return;
	}
	
	err = client.writeMessage ( "Hello Server !" );
	TEST_ASSERT_MSG( err == DSock::SUCCESS, "Client can not write message" )
	
	err = server.readMessage ( h, buffer );
	TEST_ASSERT_MSG( err == DSock::SUCCESS, "Server can not read message" )
	TEST_ASSERT_MSG( buffer.simplifyWhiteSpace() == "Hello Server !", "Server receive wrong message" )
	
	err = server.writeMessage ( h, "Hello Client !" );
	TEST_ASSERT_MSG( err == DSock::SUCCESS, "Server can not write message" )
	
	err = client.readMessage ( buffer );
	TEST_ASSERT_MSG( err == DSock::SUCCESS, "Client can not read message" )
	TEST_ASSERT_MSG( buffer.simplifyWhiteSpace() == "Hello Client !", "Client receive wrong message" )
	
	client.closeSock();
	
	server.closeConnection ( h );
	server.closeSock();
}

int main( int argc, char** argv )
{
	std::ofstream file;
	TestDSocket ets;
	
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );
	Test::HtmlOutput html;
	
	file.open( "dsocket.html" );
	ets.run( html );
	html.generate( file, true, "DSocket" );
	file.close();
	
	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
}