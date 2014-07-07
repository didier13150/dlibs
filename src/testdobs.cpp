/******************************************************************************
 * Unit Test for DObs class                                                 *
 ******************************************************************************/

#include <iostream>
#include <cstdlib>

#include "dlibs.h" // replace it by #include <dlibs/dlibs.h>

using namespace std;

class Barometer : public DObservable
{
private:
	int presure;

public:
	void setValue( int value )
	{
		presure = value;
		notify();
	}
	
	DBasicEvent & getEvent( void )
	{
		static DBasicEvent event;
		DString buffer;

		buffer.setNum( presure );
		buffer.prepend( "Presure = " );
		buffer.append( " mBars." );
		event.setEventDescription( buffer );
		return event;
	}
};

class Thermometer : public DObservable
{
private:
	int temperature;

public:
	void setValue( int value )
	{
		temperature = value;
		notify();
	}
	
	DBasicEvent & getEvent( void )
	{
		static DBasicEvent event;
		DString buffer;

		buffer.setNum( temperature );
		buffer.prepend( "Temperature = " );
		buffer.append( " degrees." );
		event.setEventDescription( buffer );
		return event;
	}
};

class WeatherStation : public DObserver
{
public:
	WeatherStation() : DObserver() {}
	~WeatherStation() {}
	
	void onEvent( DObservable * observable )
	{
		cout << observable->getEvent().what() << endl;
	}
};

int testdobs()
{
	Barometer barometer;
	Thermometer thermometer;

	{ // To limit WeatherStation range to this block
		WeatherStation station;

		thermometer.addObserver( &station );
		barometer.addObserver( &station );

		thermometer.setValue( 22 );
		barometer.setValue( 1024 );
	}

	barometer.setValue( 1026 );
	
    return 0;
}
