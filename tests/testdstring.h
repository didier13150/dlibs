#include <stdio.h>
#include <cpptest.h>

#include "dstring.h"

class TestDString : public Test::Suite
{
public:
	TestDString()
	{
		TEST_ADD( TestDString::constructor_test )
		TEST_ADD( TestDString::add_test )
		TEST_ADD( TestDString::compare_test )
		TEST_ADD( TestDString::others_operators_test )
		TEST_ADD( TestDString::number_test )
		TEST_ADD( TestDString::binary_test )
		TEST_ADD( TestDString::length_test )
		TEST_ADD( TestDString::substr_test )
		TEST_ADD( TestDString::legal_char_test )
		TEST_ADD( TestDString::split_test )
		TEST_ADD( TestDString::time_test )
		TEST_ADD( TestDString::map_key_test )
		TEST_ADD( TestDString::space_test )
		TEST_ADD( TestDString::case_test )
		TEST_ADD( TestDString::justify_test )
		TEST_ADD( TestDString::contains_test )
	}
    
private:
	void constructor_test();
	void add_test();
	void compare_test();
	void others_operators_test();
	void number_test();
	void binary_test();
	void length_test();
	void substr_test();
	void legal_char_test();
	void split_test();
	void time_test();
	void map_key_test();
	void space_test();
	void case_test();
	void justify_test();
	void contains_test();
};
