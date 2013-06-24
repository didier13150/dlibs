/******************************************************************************
 * Unit Test for DEnv class                                                   *
 ******************************************************************************/

#include <iostream>
#include <cstdlib>

#include "dlibs.h" // replace it by #include <dlibs/dlibs.h>

using namespace std;

int testdenv()
{
	DEnv * env;
	
	env = DEnv::getInstance();

	// Print some environment variables
	cout << "home = \"" << env->getVar( "home" ) << "\"" << endl;
	cout << "HOME = \"" << env->getVar( "HOME" ) << "\"" << endl;
	cout << "TOTO = \"" << env->getVar( "TOTO" ) << "\"" << endl;
	cout << "PATH = \"" << env->getVar( "PATH" ) << "\"" << endl;

	// Set ( but not overwrite ) TOTO var to /opt:/usr
	env->setVar( "TOTO", "/opt:/usr", false );
	cout << "TOTO = \"" << env->getVar( "TOTO" ) << "\"" << endl;

	// Set ( and overwrite if needed) TOTO var to /home
	env->setVar( "TOTO", "/home", true );
	cout << "TOTO = \"" << env->getVar( "TOTO" ) << "\"" << endl;

	// Set ( but not overwrite ) TOTO var
	env->setVar( "TOTO", "/tmp", false );
	cout << "TOTO = \"" << env->getVar( "TOTO" ) << "\"" << endl;

	// Print all fetched environment variables
	cout << "Env var : " << endl << *env << endl;
	return 0;
}
