/******************************************************************************
 * Unit Test for DURL class                                                   *
 ******************************************************************************/

#include <iostream>
#include <cstdlib>

#include "dlibs.h" // replace it by #include <dlibs/dlibs.h>

using namespace std;

int testdurl()
{
	DURL url;
	DStringList hosts;
	DStringList::iterator it;

	hosts.push_back( "localhost/var/www/dlibs/" );
	hosts.push_back( "127.0.0.1" );
	hosts.push_back( "http://www.google.fr:8080/ig" );
	hosts.push_back( "smtp://localhost" );
	hosts.push_back( "ssh://localhost:2222/svn/dlibs/" );
	hosts.push_back( "toto://localhost" );
	
	for ( it = hosts.begin() ; it != hosts.end() ; ++it )
	{
		url.setURL ( *it );
		cout << "URL = " << *it << endl;
		if ( url.getLastErrno() != DURL::SUCCESS )
		{
			cout << url.getLastError() << endl;
		}
		cout << url << endl;
		url.clear();
		cout << "-----------------------------------------------------" << endl;
	}
	
	return 0;
}