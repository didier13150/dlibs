/******************************************************************************
 * Unit Test for DSocket class, client part                                   *
 ******************************************************************************/
#include <iostream>
#include <cstdlib>
#include "dlibs.h" // replace it by #include <dlibs/dlibs.h>

using namespace std;

int testdsockclient ( int port, size_t bufsize )
{
	DClientSock client;
	DStringList messages;
	DStringList::iterator it;
	DString message;

	if ( bufsize )
	{
		client.setBufferSize( bufsize );
	}

	messages.push_back( "Wake up, Neo." );
	messages.push_back( "The matrix has you..." );
	messages.push_back( "Follow the white rabbit." );
	messages.push_back( "Knock, knock, Neo." );

	if ( ( port > 0 ) && ( port < 65535 ) )
	{
		if ( client.openSock ( "localhost", port ) != DSock::SUCCESS )
		{
			cout << client.getLastError() << endl;
			return EXIT_FAILURE;
		}
		client.setTimeout ( 2000 ); // time out = 2 seconds
		for ( it = messages.begin() ; it != messages.end() ; ++it )
		{
			if ( client.writeMessage ( *it ) != DSock::SUCCESS )
			{
				cout << client.getLastError() << endl;
			}
			client.readMessage( message );
			if ( message.length() )
			{
				cout << message.stripWhiteSpace() << endl;
				message.clear();
			}
			sleep ( 2 );
		}
		client.closeSock();
	}
	return EXIT_SUCCESS;
}
