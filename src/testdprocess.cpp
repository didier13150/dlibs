/******************************************************************************
 * Unit Test for DProcess class                                               *
 ******************************************************************************/

#include <iostream>
#include <cstdlib>

#include "dlibs.h" // replace it by #include <dlibs/dlibs.h>

using namespace std;

int testdprocess( bool fileauto )
{
	DProcess process;
	DStringList args, rargs;

	process.setExecutable( "ls" );
	process << "-la" << "/tmp";
	//args.push_back( "-l" );
	//args.push_back( "/tmp" );
	//process.setArgs( args );
	process.setComMode( DProcess::READ_ONLY );
	process.setExeMode( DProcess::NOBLOCK );

	process.start();

	while ( process.isRunning() )
	{
		cout << "alive" << endl;
		usleep(100000);
	}

	cout << process.getOutput() << endl;
	process.stop();
	
	return 0;
}
