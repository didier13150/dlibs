/******************************************************************************
 * Unit Test for DSingleton class                                             *
 ******************************************************************************/




#include <iostream>
#include <cstdlib>

#include "dlibs.h" // replace it by #include <dlibs/dlibs.h>

using namespace std;

class Foo : public DSingleton<Foo>
{
	// To let DSingleton have access to Foo protected constructor
	friend class DSingleton<Foo>;
	
protected:
	// Protected constructor
	Foo() : nb( 0 ) {}
	
public:
	void show()
	{
		std::cout << nb << std::endl;
	}
	void increment()
	{
		nb++;
	}
private:
	int nb;
};

int testdsingleton()
{
	Foo::getInstance()->show();
	Foo::getInstance()->increment();
	Foo::getInstance()->show();

	std::cout << "Good if 1 is displayed" << std::endl;
	return 0;
}