#include <stdio.h>
#include <cpptest.h>

#include "dstring.h"

class TestDString : public Test::Suite
{
public:
    TestDString()
    {
        TEST_ADD(TestDString::constructor_test)
        TEST_ADD(TestDString::add_test)
        TEST_ADD(TestDString::number_test)
        TEST_ADD(TestDString::binary_test)
    }
    
private:
    void constructor_test();
    void add_test();
    void number_test();
    void binary_test();
};
