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

void TestDSettings::open_test()
{
	DSettings sets;
	int err;

	err = sets.setFileName ( CONF_FILE );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not specify settings file" )
	TEST_ASSERT_MSG( sets.getRootNode() == "settings", "Wrong root node name" )
}

void TestDSettings::get_test()
{
	DSettings sets;
	DString buffer;
	DStringList list;
	DStringList::iterator it;
	int err;

	err = sets.setFileName ( CONF_FILE );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not specify settings file." )

	err = sets.readEntry ( "/settings/user1/name", buffer );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not read entry." )
	TEST_ASSERT_MSG( buffer == "doe", "Wrong name for user1." )

	list = sets.getEntries( "/settings/user1/firstname" );
	err = sets.getLastErrno();
	TEST_ASSERT_MSG( list.size() == 2, "Wrong number of rows. Must be 2." )
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not get entries." )
	for ( it = list.begin() ; it != list.end() ; ++it )
	{
		TEST_ASSERT_MSG( ( *it == "john" || *it == "joe" ), "Wrong firstname for user1." )
	}
}

void TestDSettings::set_test()
{
	DSettings sets;
	DString buffer;
	int err;

	err = sets.setFileName ( CONF_FILE );
	err = sets.writeEntry ( "/settings/user2/name", "Bud" );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not update entry." )

	err = sets.writeEntry ( "/settings/user3", "" );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not write new empty entry." )

	err = sets.writeEntry ( "/settings/user3/name", "Patoche" );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not write new entry." )

	err = sets.writeEntry ( "/settings/user3/firstname", "Sébastien" );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not write new entry." )

	err = sets.writeEntry ( "/settings/user3/firstname", "Seb", false );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not write duplicate entry." )

	err = sets.writeEntry ( "/settings/user3/surname", "Quand il pète, il troue son slip" );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not write new entry." )
}

void TestDSettings::afterset_test()
{
	DSettings sets;
	DString buffer;
	int err;
	DStringList list;
	DStringList::iterator it;

	err = sets.setFileName ( CONF_FILE );
	err = sets.readEntry ( "/settings/user2/name", buffer );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not read entry." )
	TEST_ASSERT_MSG( buffer == "Bud", "Entry not updated." )

	err = sets.readEntry ( "/settings/user3/name", buffer );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not read entry." )
	TEST_ASSERT_MSG( buffer == "Patoche", "Entry not updated." )

	list = sets.getEntries( "/settings/user3/firstname" );
	err = sets.getLastErrno();
	TEST_ASSERT_MSG( list.size() == 2, "Wrong number of rows. Must be 2." )
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not get entries." )
	for ( it = list.begin() ; it != list.end() ; ++it )
	{
		TEST_ASSERT_MSG( ( *it == "Sébastien" || *it == "Seb" ), "Wrong firstname for user3." )
	}

	err = sets.readEntry ( "/settings/user3/surname", buffer );
	TEST_ASSERT_MSG( err == DSettings::SUCCESS, "Can not read entry." )
	TEST_ASSERT_MSG( buffer == "Quand il pète, il troue son slip", "Entry not updated." )
}

void TestDSettings::write_config()
{
	std::ofstream file;
	DString buffer;

	buffer = "<settings>\n\t<user1>\n\t\t<name>doe</name>\n\t\t<firstname>john"
			 "</firstname>\n\t\t<firstname>joe</firstname>\n\t</user1>\n\t<user2>"
			 "\n\t\t<name>bud</name>\n\t\t<firstname>weiser</firstname>\n\t</user2>"
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
	/*Test::HtmlOutput html;

	file.open( "dsettings.html" );
	ets.run( html );
	html.generate( file, true, "DSettings" );
	file.close();*/

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
}