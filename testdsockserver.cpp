/******************************************************************************
 * Unit Test for DSocket class, server part                                   *
 ******************************************************************************/
#include <iostream>
#include <cstdlib>
#include "dlibs.h" // replace it by #include <dlibs/dlibs.h>

using namespace std;

int testdsockserver()
{
	DServerSock server;
	int hSock = -1;
	DString buffer;
	DURL url;
	int port = 0;

	cout << "Port to open ( 0 to quit ) : ";
	cin >> port;

	if ( ( port > 0 ) && ( port < 65535 ) )
	{
		cout << "Launch the client application (dlibstestdsockclient)" << endl;
		cout << "Text must be appear inside this console." << endl;
		server.setTimeout ( 3000 );

		if ( server.openSock ( port ) != DSock::SUCCESS )
		{
			cout << "port " << port << " cannot be opened" << endl;
			cout << server.getLastError() << endl;
			return EXIT_FAILURE;
		}

		if ( server.openConnection ( hSock ) != DSock::SUCCESS )
		{
			cout << "Server cannot accept new client" << endl;
			cout << server.getLastError() << endl;
			server.closeSock();
			return EXIT_FAILURE;
		}
		cout << "Client Address = " << server.getClientAddress() << endl;
		usleep ( 100000 );

		while ( errno != DSock::NO_SOCKET )
		{
			errno = server.readMessage ( hSock, buffer );
			{
				buffer = buffer.simplifyWhiteSpace();
				if ( !buffer.isEmpty() )
				{
					cout << buffer << endl;
				}
				else
				{
					cout << server.getLastError() << endl;
				}
			}
			errno = server.writeMessage( hSock, "123456789012345678901234567890123456789012345678901234567890123456789012345678901" );
		}
		cout << "Close client connection" << endl;
		server.closeConnection ( hSock );

		server.closeSock();
	}
	return EXIT_SUCCESS;
}
