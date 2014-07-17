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
 *     (___)_)   File : testdsettings.cpp                   ||--|| *          *
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
 *   Unit Test for DSettings                                                  *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdsettings.h"

#define CONF_FILE "dsettings.xml"

using namespace std;

void TestDSettings::get_test()
{
	DSettings sets;
	DString buffer;
	DStringList list;
	DStringList::iterator it;
	int err;
	
	err = sets.setFileName ( CONF_FILE );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not specify settings file" )

	err = sets.setGroup ( "user1", false );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not specify group (nocreate)" )
	err = sets.readEntry ( "name", buffer );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not get entry" )
	TEST_ASSERT_MSG( buffer == "doe", "Wrong name for user1" )
	TEST_ASSERT_MSG( sets.getEntry( "name" ) == "doe", "Wrong name for user1 (direct)" )
	list = sets.getEntries( "surname" );
	err = sets.getLastErrno();
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not get entries" )
	for ( it = list.begin() ; it != list.end() ; ++it )
	{
		TEST_ASSERT_MSG( ( *it == "john" || *it == "joe" ), "Wrong surname for user1" )
	}
	
	err = sets.setGroup ( "user2", false );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not specify group (nocreate)" )
	err = sets.readEntry ( "name", buffer );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not get entry" )
	TEST_ASSERT_MSG( buffer == "bud", "Wrong settings for user2" )
	err = sets.readEntry ( "address", buffer );
	TEST_ASSERT_MSG( err == DSettings::NO_ENTRY, "Can get shadow entry (address) on existing group" )
	
	err = sets.setGroup ( "user3", false );
	TEST_ASSERT_MSG( err == DSettings::GROUP_NOT_EXISTS, "Can specify group which doesn't exists (nocreate)" )
	err = sets.readEntry ( "name", buffer );
	TEST_ASSERT_MSG( err == DSettings::NO_ENTRY, "Can get shadow entry (name) on shadow group (user3)" )
}

void TestDSettings::set_test()
{
	DSettings sets;
	DString buffer;
	int err;
	
	err = sets.setGroup ( "user3", true );
	TEST_ASSERT_MSG( err == DSettings::NO_FILE, "Can create group without file" )
	
	err = sets.setFileName ( CONF_FILE );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not specify settings file" )
	
	err = sets.setGroup ( "user3", true );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not create group" )
	
	err = sets.writeEntry ( "name", "toto" );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not create entry" )
}

void TestDSettings::write_config()
{
	std::ofstream file;
	DString buffer;
	
	buffer = "<settings>\n\t<user1>\n\t\t<name>doe</name>\n\t\t<surname>john"
			 "</surname>\n\t\t<surname>joe</surname>\n\t</user1>\n\t<user2>"
			 "\n\t\t<name>bud</name>\n\t\t<surname>weiser</surname>\n\t</user2>"
			 "\n</settings>\n";

	file.open ( CONF_FILE, std::fstream::out | std::fstream::trunc );
	TEST_ASSERT_MSG( file.is_open() == true, "Can not write settings file" )
	file << buffer;
	file.close();
}

void TestDSettings::delete_config()
{
	int success = remove( CONF_FILE );
	TEST_ASSERT_MSG( success == 0, "Can not deleting settings file" )
}

int main( int argc, char** argv )
{
	std::ofstream file;
	TestDSettings ets;
	
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );
	Test::HtmlOutput html;
	
	file.open( "dsettings.html" );
	ets.run( html );
	html.generate( file, true, "DSettings" );
	file.close();
	
	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
}