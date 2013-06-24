/******************************************************************************
 * Unit Test for DTimer class                                                 *
 ******************************************************************************/

#include <iostream>
#include <cstdlib>

#include "dlibs.h" // replace it by #include <dlibs/dlibs.h>

using namespace std;

int testdtimer()
{
    DTimer timer;

	timer.start(5000);
	cout << "Timer started" << endl;
	cout << "Timeout not reached,  " << timer.timeToTimeout() << " ms to wait" << endl;
	
	sleep(1);
	
	cout << "Timeout not reached,  " << timer.timeToTimeout() << " ms to wait" << endl;
	timer.restart();
	cout << "Timer reset" << endl;
	cout << "Timeout not reached,  " << timer.timeToTimeout() << " ms to wait" << endl;
	
	sleep(1);
	
	cout << "Timeout not reached,  " << timer.timeToTimeout() << " ms to wait" << endl;
	timer.restart();
	cout << "Timer reset" << endl;
	cout << "Timeout not reached,  " << timer.timeToTimeout() << " ms to wait" << endl;
	
	do
	{
		cout << "Timeout not reached,  " << timer.timeToTimeout() << " ms to wait" << endl;
		usleep(500000);
		
	} while ( timer.timeToTimeout() );
	
	cout << "Timer stopped" << endl;
	
	sleep(1);
	
	timer.start(1500);
	cout << "Timer started" << endl;
	
	do
	{
		cout << "Timeout not reached,  " << timer.timeToTimeout() << " ms to wait" << endl;
		usleep(100000);
	} while ( timer.timeToTimeout() );
	
	cout << "Timer stopped" << endl;
	return 0;
}
