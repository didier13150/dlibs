
#include "dlibs.h" // replace it by #include <dlibs/dlibs.h>

#include <cstdlib>
#include <iostream>

using namespace std;

extern int testdsockclient ( int port = 0, size_t bufsize = 80 );

int main ( int argc, char *argv[] )
{
	DString buffer;
	int i = 1;
	long int bufsize = 0;
	int port = 0;

	// Get app arg
	while ( i <  argc)
	{
		buffer = argv[i];
		if (buffer.left(2) == "-b")
		{
			if ( buffer.contains("=") )
			{
				bufsize = buffer.right( buffer.length() - 3 ).toULong();
			}
			else
			{
				++i;
				buffer = argv[i];
				bufsize = buffer.toULong();
			}
		}
		else if (buffer.left(2) == "-p" )
		{
			if ( buffer.contains("=") )
			{
				port = buffer.right( buffer.length() - 3 ).toInt();
			}
			else
			{
				++i;
				buffer = argv[i];
				port = buffer.toInt();
			}
		}
		++i;
	}

	if ( !port )
	{
		cout << "Port to open ( 0 to quit ) : ";
		cin >> port;
	}
	if ( !port )
	{
		return EXIT_SUCCESS;
	}
		
	testdsockclient( port, bufsize );
	return EXIT_SUCCESS;
}