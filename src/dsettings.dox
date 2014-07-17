/******************************************************************************
 * Unit Test for DSettings                                                    *
 ******************************************************************************/

#include <iostream>
#include <cstdlib>
#include "dlibs.h"   // replace it by #include <dlibs/dlibs.h>

using namespace std;

int testdsettings()
{
	DSettings sets;
	DString filename = "/tmp/dsettings.xml";
	DString rootnode = "settings";
	std::ofstream file;
	DString buffer;

	
	//cout << "Enter the settings file name to read : ";
	//cin >> filename;
	
	buffer = "<settings>\n\t<user1>\n\t\t<name>doe</name>\n\t\t<surname>john"
			 "</surname>\n\t</user1>\n\t<user2>\n\t\t<name>bud</name>\n"
			 "\t\t<surname>weiser</surname>\n\t</user2>\n</settings>\n";

	cout << "Write a simple config file : /tmp/dsettings.xml" << endl;
	file.open ( filename.c_str() );
	file << buffer;
	file.close();
	
	// Open settings file
	//sets.setRootNodeName ( rootnode );
	if ( sets.setFileName ( filename ) != DSettings::SUCCESS )
	{
		cout << "Error on setFileName process : " << sets.getLastError() << endl;
		return -1;
	}

	// Get log config
	if ( sets.setGroup ( "user1", false ) != DSettings::SUCCESS )
	{
		cout << "Error on setGroup process : " << sets.getLastError() << endl;
		return -1;
	}
	if ( sets.readEntry ( "name", buffer ) != DSettings::SUCCESS )
	{
		cout << "Error on readEntry process : " << sets.getLastError() << endl;
		return -1;
	}


	cout << "user1 name is " << buffer << endl;
	cout << "user1 surname is "
			<< DSettings::getSettings( sets, "user1", "surname", &buffer ) << endl;
	
	if ( !buffer.isEmpty() )
	{
		cout << buffer << endl;
	}
	
	cout << "user2 addresss is "
			<< DSettings::getSettings( sets, "user2", "address", &buffer ) << endl;

	if ( !buffer.isEmpty() )
	{
		cout << buffer << endl;
	}
	
	cout << "user3 surname is "
			<< DSettings::getSettings( sets, "user3", "surname", &buffer ) << endl;

	if ( !buffer.isEmpty() )
	{
		cout << buffer << endl;
	}

	return 0;
}
