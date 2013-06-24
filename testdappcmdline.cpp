/******************************************************************************
 * Unit Test for DArgs                                                      *
 ******************************************************************************/

#include <iostream>
#include <cstdlib>
#include "dlibs.h"    // replace it by #include <dlibs/dlibs.h>

using namespace std;

int testdappcmdline( bool fileauto, int argc, char ** argv )
{
	DAppCmdLine args;

	for (int nb = 0 ; nb < argc ; ++nb )
	{
		cout << argv[nb] << " ";
	}
	cout << endl;

	args.addOption( "help", "Show help", 'h', false );
	args.addOption( "debug", "Set debug mode", 'd', false );
	args.addOption( "version", "Show version number", 'v', false );
	args.addOption( "testing", "Test only one library", 't', true );
	args.addOption( "nul", "Nul entry", 'n', true );
	args.addArgument( "loop number" );

	if ( args.parse( argc, argv ) )
	{
		cout << args.getLastError() << endl;
	}

	cout << "have option -d : " << args.haveOption( "d" ) << endl;
	cout << "have option --debug : " << args.haveOption( "debug" ) << endl;
	cout << "have option -v : " << args.haveOption( "v" ) << endl;
	cout << "have option --version : " << args.haveOption( "version" ) << endl;
	cout << "have option -t : " << args.haveOption( "t" ) << endl;
	cout << "have option --testing : " << args.haveOption( "testing" ) << endl;
	cout << "option --testing = " << args.getOption( "testing" ) << endl;
	cout << "option -t = " << args.getOption( "t" ) << endl;
	cout << "option --nul = " << args.getOption( "nul" ) << endl;
	cout << "option -n = " << args.getOption( "n" ) << endl;

	cout << endl << "Show help :" << endl;
	args.showHelp();
	return 0;
}
