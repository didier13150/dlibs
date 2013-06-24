/******************************************************************************
 * Unit Test for DException class                                                   *
 ******************************************************************************/

#include <iostream>
#include <cstdlib>

#include "dlibs.h" // replace it by #include <dlibs/dlibs.h>

using namespace std;

void make_exception();
void make_exception_db();

int testdexceptions()
{
	try
	{
		make_exception();
		make_exception_db();
	}
	// Catch DExceptions
	catch ( const DException& e )
	{
		cout << e.what() << endl;
	}
	// Catch all others exceptions
	catch ( ... )
	{
		cout << "Another unknow exception encoured" << endl;
	}
	return 1;
}

void make_exception()
{
	// Get a random number between 0 and 1024
	static int nb = rand() % 1024;
	static DString what("A simple exception for test, with a random error code");
	// Throw an exception
	throw DEXCEPTION( what, nb );
}

void make_exception_db()
{
	// Get a random number between 0 and 1024
	static int nb = rand() % 1024;
	static DString what("A simple database exception for test, with a random error code");
	// Throw an exception
	throw DEXCEPTION_DB( what, nb );
}
