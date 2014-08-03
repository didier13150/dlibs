/******************************************************************************
 *      ____              ____    _       _   _                               *
 *     /# /_\_           |  _ \  (_)   __| | (_)   ___   _ __                 *
 *    |  |/o\o\          | | | | | |  / _` | | |  / _ \ | '__|                *
 *    |  \\_/_/          | |_| | | | | (_| | | | |  __/ | |                   *
 *   / |_   |            |____/  |_|  \__,_| |_|  \___| |_|                   *
 *  |  ||\_ ~|                                                                *
 *  |  ||| \/                                                                 *
 *  |  |||       Project : DLibs : usefull tools for C++ programming          *
 *  \//  |                                                                    *
 *   ||  |       Developper : Didier FABERT <didier.fabert@gmail.com>         *
 *   ||_  \      Date : 2009, April                                           *
 *   \_|  o|                                             ,__,                 *
 *    \___/      Copyright (C) 2009 by didier fabert     (oo)____             *
 *     ||||__                                            (__)    )\           *
 *     (___)_)   File : testdstring.cpp                     ||--|| *          *
 *                                                                            *
 *   This program is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU General Public License as published by     *
 *   the Free Software Foundation; either version 2 of the License, or        *
 *   (at your option) any later version.                                      *
 *                                                                            *
 *   This program is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *   GNU General Public License for more details.                             *
 *                                                                            *
 *   You should have received a copy of the GNU General Public License        *
 *   along with this program; if not, write to the                            *
 *   Free Software Foundation, Inc.,                                          *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.             *
 *                                                                            *
 *   Unit Test for DString                                                    *
 *                                                                            *
 ******************************************************************************/
#include <cstdlib>
#include <iostream>
#include <map>
#include "testdstring.h"

void TestDString::constructor_test()
{
	DString str = "UTF-8 &éèêàâç";

	std::string sstr = "UTF-8 &éèêàâç";
	const char * cchar = "UTF-8 &éèêàâç";
	DString strStr ( sstr );
	DString strConstChar ( cchar );
	DString strDStr ( str );

	TEST_ASSERT_MSG( str == strStr, "Allocation from standard string failed" )
	TEST_ASSERT_MSG( str == strConstChar, "Allocation from const char* failed" )
	TEST_ASSERT_MSG( str == strDStr, "Allocation from DString failed" )

	char c = 'c';
	DString strChar ( c );
	str = "c";
    TEST_ASSERT_MSG( str == strChar, "Allocation from char failed" )
}

void TestDString::add_test()
{
	DString str = "UTF-8 &éèêàâç";
	std::string str2 = "Add";

	str += str2;
	TEST_ASSERT_MSG( str == "UTF-8 &éèêàâçAdd", "Add 2 DStrings failed" )
	char c = 0x41; // A
	str += c;
	TEST_ASSERT_MSG( str == "UTF-8 &éèêàâçAddA", "Add char failed (operator +=)" )
	str = str + 0x24; // $
	TEST_ASSERT_MSG( str == "UTF-8 &éèêàâçAddA$", "Add char failed (operator +)" )
}

void TestDString::compare_test()
{
	DString str = "U";
	TEST_ASSERT_MSG( str == "U", "Compare DString with const char * failed" )
	TEST_ASSERT_MSG( str == std::string("U"), "Compare DString with std string failed" )
	TEST_ASSERT_MSG( str == 'U', "Compare DString with char failed" )
	TEST_ASSERT_MSG( str != "u", "Compare DString with const char * failed" )
	TEST_ASSERT_MSG( str != std::string("u"), "Compare DString with std string failed" )
	TEST_ASSERT_MSG( str != 'u', "Compare DString with char failed" )
}

void TestDString::others_operators_test()
{
	DString str1 = "a";
	DString str2 = "b";
	TEST_ASSERT_MSG( str1 < str2, "Compare DStrings (lesser than) failed" )
	TEST_ASSERT_MSG( str1 <= str2, "Compare DStrings (lesser or equal than) failed" )
	TEST_ASSERT_MSG( str2 > str1, "Compare DStrings (greater than) failed" )
	TEST_ASSERT_MSG( str2 >= str1, "Compare DStrings (greater or equal than) failed" )
	str1 = "aaaaa";
	str2 = "bb";
	TEST_ASSERT_MSG( str1 < str2, "Compare DStrings (lesser than) failed" )

	str1 = "bcdef";
	str1.getReference().insert( 0, "a" );
	TEST_ASSERT_MSG( str1 == "abcdef", "get reference failed" )
	TEST_ASSERT_MSG( str1.at(0) == "a", "extracts char (dstring) failed" )
	TEST_ASSERT_MSG( str1[2] == 'c', "extracts char failed" )

}

void TestDString::number_test()
{
	DString str;

	str = "-123456789";
	int i = str.toInt();
	TEST_ASSERT_MSG( i == -123456789, "Convert DString to int failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.setNum( i );
	TEST_ASSERT_MSG( str == "-123456789", "Convert int to DString failed" )

	str = "123456789";
	unsigned int ui = str.toUInt();
	TEST_ASSERT_MSG( ui == 123456789, "Convert DString to unsigned int failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.setNum( ui );
	TEST_ASSERT_MSG( str == "123456789", "Convert unsigned int to DString failed" )

	str = "-12345";
	short int si = str.toShort();
	TEST_ASSERT_MSG( si == -12345, "Convert DString to short int failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.setNum( si );
	TEST_ASSERT_MSG( str == "-12345", "Convert short int to DString failed" )

	str = "12345";
	unsigned short int usi = str.toUShort();
	TEST_ASSERT_MSG( usi == 12345, "Convert DString to unsigned short int  failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.setNum( usi );
	TEST_ASSERT_MSG( str == "12345", "Convert unsigned short int  to DString failed" )

	str = "-123456789";
	long int li = str.toLong();
	TEST_ASSERT_MSG( li == -123456789, "Convert DString to long int li failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.setNum( li );
	TEST_ASSERT_MSG( str == "-123456789", "Convert long int li to DString failed" )

	str = "123456789";
	unsigned long int uli = str.toULong();
	TEST_ASSERT_MSG( uli == 123456789, "Convert DString to unsigned long int  failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.setNum( uli );
	TEST_ASSERT_MSG( str == "123456789", "Convert unsigned long int  to DString failed" )

	str = "-123456789";
	long long int lli = str.toLongLong();
	TEST_ASSERT_MSG( lli == -123456789, "Convert DString to long long int  failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.setNum( lli );
	TEST_ASSERT_MSG( str == "-123456789", "Convert long long int  to DString failed" )

	str = "123456789";
	unsigned long long int ulli = str.toULongLong();
	TEST_ASSERT_MSG( ulli == 123456789, "Convert DString to unsigned long long int  failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.setNum( ulli );
	TEST_ASSERT_MSG( str == "123456789", "Convert unsigned long long int  to DString failed" )

	str = "3.1415927";
	float f = str.toFloat();
	TEST_ASSERT_DELTA_MSG( f, 3.1415927, 0.0000001, "Convert DString to float failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.setNum( f, 6 );
	TEST_ASSERT_MSG( str == "3.14159", "Convert float to DString failed" )

	str = "3.1415927";
	double d = str.toDouble();
	TEST_ASSERT_DELTA_MSG( d, 3.1415927, 0.0000001, "Convert DString to double failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.setNum( d, 6 );
	TEST_ASSERT_MSG( str == "3.14159", "Convert double to DString failed" )

	str = "-3.1415927";
	long double ld = str.toLongDouble();
	TEST_ASSERT_DELTA_MSG( ld, -3.1415927, 0.0000001, "Convert DString to long double failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.setNum( ld, 6 );
	TEST_ASSERT_MSG( str == "-3.14159", "Convert long double to DString failed" )
}

void TestDString::binary_test()
{
	DString str;

	str.toBase2 ( 0x7FFFFFFF );
	//str = "10010100";
	TEST_ASSERT_MSG( str == "1111111111111111111111111111111", "Convert binary to DString failed" )
	str.toBase2 ( 0xFFFFFFFF );
	TEST_ASSERT_MSG( str == "11111111111111111111111111111111", "Convert binary to DString failed (2)" )

	str = "10010100";
	int i = str.toIntBase10();
	TEST_ASSERT_MSG( i == 148, "Convert DString binary to int failed" )
		str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.toBase2 ( i );
	TEST_ASSERT_MSG( str == "10010100", "Convert int to DString binary failed" )

	str = "10010100";
	unsigned int ui = str.toUIntBase10();
	TEST_ASSERT_MSG( ui == 148, "Convert DString binary to int failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.toBase2 ( ui );
	TEST_ASSERT_MSG( str == "10010100", "Convert unsigned int to DString binary failed" )

	str = "10010100";
	short int si = str.toShortBase10();
	TEST_ASSERT_MSG( si == 148, "Convert DString binary to int failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.toBase2 ( si );
	TEST_ASSERT_MSG( str == "10010100", "Convert short int to DString binary failed" )

	str = "10010100";
	unsigned short int usi = str.toUShortBase10();
	TEST_ASSERT_MSG( usi == 148, "Convert DString binary to int failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.toBase2 ( usi );
	TEST_ASSERT_MSG( str == "10010100", "Convert unsigned short int to DString binary failed" )

	str = "10010100";
	long int li = str.toLongBase10();
	TEST_ASSERT_MSG( li == 148, "Convert DString binary to int failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.toBase2 ( li );
	TEST_ASSERT_MSG( str == "10010100", "Convert long int to DString binary failed" )

	str = "10010100";
	unsigned long int uli = str.toULongBase10();
	TEST_ASSERT_MSG( uli == 148, "Convert DString binary to int failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.toBase2 ( uli );
	TEST_ASSERT_MSG( str == "10010100", "Convert unsigned long int to DString binary failed" )

	str = "10010100";
	long long int lli = str.toLongLongBase10();
	TEST_ASSERT_MSG( lli == 148, "Convert DString binary to int failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.toBase2 ( lli );
	TEST_ASSERT_MSG( str == "10010100", "Convert long long int to DString binary failed" )

	str = "10010100";
	unsigned long long int ulli = str.toULongLongBase10();
	TEST_ASSERT_MSG( ulli == 148, "Convert DString binary to int failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.toBase2 ( ulli );
	TEST_ASSERT_MSG( str == "10010100", "Convert  to DString binary failed" )
}

void TestDString::length_test()
{
	DString str = "10010100";

	TEST_ASSERT_MSG( str.length() == 8, "Calculate length failed" )
	TEST_ASSERT_MSG( str.isEmpty() == false, "Check if not empty failed" )
	str.clear();
	TEST_ASSERT_MSG( str.length() == 0, "Calculate length about empty DString failed" )
	TEST_ASSERT_MSG( str == DString::empty(), "Check if DString is equal to an empty DString failed" )
	TEST_ASSERT_MSG( str.isEmpty() == true, "Check if empty failed" )
}

void TestDString::substr_test()
{
	DString str = "abcdefghijklmnopqrstuvwxyz0123456789";
	TEST_ASSERT_MSG( str.left( 26 ) == "abcdefghijklmnopqrstuvwxyz", "Extract substring from the left failed" )
	TEST_ASSERT_MSG( str.right( 10 ) == "0123456789", "Extract substring from the right failed" )
	TEST_ASSERT_MSG( str.mid ( 26, 5 ) == "01234", "Extract substring from the middle failed" )
	TEST_ASSERT_MSG( str.mid ( 0, 50 ) == str, "Extract substring from the middle failed" )
	TEST_ASSERT_MSG( str.at( 3 ) == DString('d'), "Extract char from the middle failed" )
	TEST_ASSERT_MSG( str.at( 173 ) == DString::empty(), "Extract char from the middle failed" )
	TEST_ASSERT_MSG( str[3] == 'd', "Extract char from the middle failed" )
	TEST_ASSERT_MSG( str[173] == 0, "Extract char from the middle failed" )

	str = "ABC;DEF 01234;56789 abc;def";
	TEST_ASSERT_MSG( str.section( " ", 1, 1 ) == "01234;56789", "Extract section failed" )
	TEST_ASSERT_MSG( str.section( " ", 1, 2 ) == "01234;56789 abc;def", "Extract section from beginning failed" )
	TEST_ASSERT_MSG( str.section( ";", -1, -2 ) == "56789 abc;def", "Extract section from end failed" )
	str = "ABC;DEF 01234;56789 abc;def";
	TEST_ASSERT_MSG( str.remove( ";" ).remove( ' ' ) == "ABCDEF0123456789abcdef", "Remove string or char failed" )
	str = "ABCDEF0123456789abcdef";
	str.remove( 16, 4 );
	TEST_ASSERT_MSG( str == "ABCDEF0123456789ef", "Remove by place failed" )
	str = "ABCDEF0123456789abcdef";
	str.replace( "a", ",", false );
	TEST_ASSERT_MSG( str == ",BCDEF0123456789,bcdef", "Replace string or char failed" )
	str = "ABCDEF0123456789abcdef";
	str.replace( "a", ",", true );
	TEST_ASSERT_MSG( str == "ABCDEF0123456789,bcdef", "Replace string or char failed" )
	str = "ABCDEF0123456789abcdef";
	str.replace( 6, 10, "--" );
	TEST_ASSERT_MSG( str == "ABCDEF--abcdef", "Replace by place failed" )
	str = "ABCDEFabcdef";
	str.insert( 6, "0123456789" );
	TEST_ASSERT_MSG( str == "ABCDEF0123456789abcdef", "Insert by place failed" )
	str = "ABCDEF0123456789abcdef";
	TEST_ASSERT_MSG( str.find( "abc" ) == 16, "Find substring failed (case sensitive)" )
	TEST_ASSERT_MSG( str.find( "abc", -1 ) == 16, "Find substring failed (case sensitive)" )
	TEST_ASSERT_MSG( str.find( "ABC" ) == 0, "Find substring failed (case sensitive)" )
	TEST_ASSERT_MSG( str.find( "ABC", 0 ) == 0, "Find substring failed (case sensitive)" )
	TEST_ASSERT_MSG( str.find( "abc", -1, false ) == 16, "Reverse find substring failed (case insensitive)" )
	TEST_ASSERT_MSG( str.find( "ABC", -1, false ) == 16, "Reverse find substring failed (case insensitive)" )
	TEST_ASSERT_MSG( str.find( "abc", 0, false ) == 0, "Find substring failed (case insensitive)" )
	TEST_ASSERT_MSG( str.find( "ABC", 0, false ) == 0, "Find substring failed (case insensitive)" )
}

void TestDString::legal_char_test()
{
	DString str = "abcdefghijklmnopqrstuvwxyz0123456789";
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA, DString::BOTHCASE ) == false,
					 "Check legal char failed for not hexa char" )

	str = "abcdef0123456789";
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA, DString::BOTHCASE ) == true,
					 "Check legal char failed for both case (string on lower case)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA, DString::LOWERCASE ) == true,
					 "Check legal char failed for lower case (string on lower case)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA, DString::UPPERCASE ) == false,
					 "Check legal char failed for upper case (string on lower case)" )

	str = "ABCDEF0123456789";
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA, DString::BOTHCASE ) == true,
					 "Check legal char failed for both case (string on upper case)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA, DString::UPPERCASE ) == true,
					 "Check legal char failed for upper case (string on upper case)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA, DString::LOWERCASE ) == false,
					 "Check legal char failed for lower case (string on upper case)" )

	str = "ABCdef0123456789";
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA, DString::BOTHCASE ) == true,
					 "Check legal char failed for both case (string on both case)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA, DString::UPPERCASE ) == false,
					 "Check legal char failed for upper case (string on both case)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA, DString::LOWERCASE ) == false,
					 "Check legal char failed for lower case (string on both case)" )

	str = "0123456789";
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA, DString::BOTHCASE ) == true,
					 "Check legal char failed for both case (decimal string)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA, DString::UPPERCASE ) == true,
					 "Check legal char failed for upper case (decimal )" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA, DString::LOWERCASE ) == true,
					 "Check legal char failed for lower case (decimal )" )

	str = "1010101110";
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::BINARY ) == true,
					 "Check legal char failed for binary (binary string)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::OCTAL ) == true,
					 "Check legal char failed for octal (binary string)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::DECIMAL ) == true,
					 "Check legal char failed for decimal (binary string)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA ) == true,
					 "Check legal char failed for hexa (binary string)" )

	str = "1012501710";
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::BINARY ) == false,
					 "Check legal char failed for binary (octal string)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::OCTAL ) == true,
					 "Check legal char failed for octal (octal string)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::DECIMAL ) == true,
					 "Check legal char failed for decimal (octal string)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA ) == true,
					 "Check legal char failed for hexa (binary string)" )

	str = "1812591710";
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::BINARY ) == false,
					 "Check legal char failed for binary (decimal string)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::OCTAL ) == false,
					 "Check legal char failed for octal (decimal string)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::DECIMAL ) == true,
					 "Check legal char failed for decimal (decimal string)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA ) == true,
					 "Check legal char failed for hexa (decimal string)" )

	str = "181A59F7c0";
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::BINARY ) == false,
					 "Check legal char failed for binary (hexa string)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::OCTAL ) == false,
					 "Check legal char failed for octal (hexa string)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::DECIMAL ) == false,
					 "Check legal char failed for decimal (hexa string)" )
	TEST_ASSERT_MSG( str.containsOnlyLegalChar ( DString::HEXA ) == true,
					 "Check legal char failed for hexa (hexa string)" )

}
void TestDString::split_test()
{
	DString str = "\ntext1\ntext2\ntext3\ntext4\n";
	DString sub;
	DStringList strl = str.split ( "\n" );
	TEST_ASSERT_MSG( strl.size() == 4, "Split with wrong number of substr" )

	DStringList::iterator it = strl.begin();
	TEST_ASSERT_MSG( it != strl.end(), "Split with wrong number of substr" )
	unsigned short int i = 1;
	while ( it != strl.end() ) {
		sub.clear();
		sub.setNum( i );
		sub.prepend( "text" );
		TEST_ASSERT_MSG( *it == sub, "Substr is wrong" )
		++it;
		i++;
	}
	// Must be separated by space
	str = " text1 text2 text3 text4 ";
	strl.clear();
	strl = str.splitConstantSize( " ", 6 );
	TEST_ASSERT_MSG( strl.size() == 4, "Split with wrong number of substr" )

	it = strl.begin();
	TEST_ASSERT_MSG( it != strl.end(), "Split with wrong number of substr" )
	i = 1;
	while ( it != strl.end() ) {
		sub.clear();
		sub.setNum( i );
		sub.prepend( "text" );
		TEST_ASSERT_MSG( *it == sub, "Substr is wrong" )
		++it;
		i++;
	}
}

void TestDString::time_test()
{
	DString str;
	str = DString::timeToString ( 1404831621, "%Y-%m-%d %H-%M-%S" );
	TEST_ASSERT_MSG( str == "2014-07-08 17-00-21", "Get Date-Time failed" )
	str = DString::timeToString ( 1404831621, DString::ISO_DATETIME_T );
	TEST_ASSERT_MSG( str == "2014-07-08T17:00:21", "Get Date-Time failed" )
	str.convertTime ( "%Y-%m-%dT%H-%M-%S", "%Y-%m-%d" );
	TEST_ASSERT_MSG( str == "2014-07-08", "Convert Date-Time to Date failed" )
	str = DString::timeToString ( 1404831621, "%Y-%m-%dT%H-%M-%S" );
	str.convertTime ( "%Y-%m-%dT%H-%M-%S", "%H:%M:%S" );
	TEST_ASSERT_MSG( str == "17:00:21", "Convert Date-Time to Time failed" )
}

void TestDString::map_key_test()
{
	std::map<DString, DString> mp;
	DString str;

	str = "1";
	mp[str] = "123456789";
	str = "2";
	mp[str] = "987654321";
	str = "1";
	TEST_ASSERT_MSG( mp[str] == "123456789", "MAp Key failed" )
	str = "2";
	TEST_ASSERT_MSG( mp[str] == "987654321", "MAp Key failed" )
}

void TestDString::space_test()
{
	DString str = "\n\t a b    c\n d\te\t ";

	TEST_ASSERT_MSG( str.stripWhiteSpace() == "a b    c\n d\te", "Strip white space failed" )
	TEST_ASSERT_MSG( str.simplifyWhiteSpace() == "a b c d e", "Simplify white space failed" )
	TEST_ASSERT_MSG( str.removeWhiteSpace() == "abcde", "Remove white space failed" )

	str = "toto";
	str += 0x14;
	str += 0x17;
	str += '\r';
	str += '\n';
	TEST_ASSERT_MSG( str.removeEscapeSequence() == "toto\n\n", "Remove escape failed" )
	TEST_ASSERT_MSG( str.replaceEscapeSequence() == "toto<DC4><ETB><CR><LF>", "Replace escape failed" )
	TEST_ASSERT_MSG( str.replaceEscapeSequence( "<@", "@>" ) == "toto<@DC4@><@ETB@><@CR@><@LF@>", "Replace escape failed" )
}

void TestDString::case_test()
{
	DString str = "abcdef";
	TEST_ASSERT_MSG( str.upper() == "ABCDEF", "Convert to upper case failed" )
	str.toUpper();
	TEST_ASSERT_MSG( str == "ABCDEF", "Switch to upper case failed" )

	str = "ABCDEF018";
	TEST_ASSERT_MSG( str.lower() == "abcdef018", "Convert to lower case failed" )
	str.toLower();
	TEST_ASSERT_MSG( str == "abcdef018", "Switch to lower case failed" )
}

void TestDString::justify_test()
{
	DString str = "abcdef";

	str.leftJustify( 10, '-');
	TEST_ASSERT_MSG( str == "abcdef----", "Left justify failed" )
	str.rightJustify( 14, '-');
	TEST_ASSERT_MSG( str == "----abcdef----", "Right justify failed" )
	str.clear();
	str.fill( '-', 10 );
	TEST_ASSERT_MSG( str == "----------", "Fill failed" )
	str.truncate( 6 );
	TEST_ASSERT_MSG( str == "------", "Truncate failed" )
}

void TestDString::contains_test()
{
	DString str = "aaabbbcccdddeeefffaaaabbaaaaaa";
	TEST_ASSERT_MSG( str.contains( 'a' ) == 13, "Contains char failed" )
	TEST_ASSERT_MSG( str.contains( "aa" ) == 10, "Contains string failed" )
	TEST_ASSERT_MSG( str.contains( std::string( "aaa" ) ) == 7, "Contains string failed" )

}

void TestDString::stream_test()
{
	std::istringstream iss;
	std::ostringstream oss;
	DString str;

	iss.str( "abcdef" );
	iss >> str;
	TEST_ASSERT_MSG( str == "abcdef", "Inputting stream failed" )
	str += "123456789";
	oss << str;
	TEST_ASSERT_MSG( oss.str() == "abcdef123456789", "Outputting stream failed" )
}

int main( int argc, char** argv )
{
	std::ofstream file;
	TestDString ets;

	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );
	/*Test::HtmlOutput html;

	file.open( "dstring.html" );
	ets.run( html );
	html.generate( file, true, "DString" );
	file.close();*/

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
}

