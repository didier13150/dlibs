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
#include <stdio.h>
#include <iostream>
#include <map>
#include "testdstring.h"
#include "dstring.h"
#include "test.h"

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
	char c = 0x41; // A

	TEST_ASSERT_MSG( str + str2 == "UTF-8 &éèêàâçAdd", "Add std::string to DStrings failed (operator +)" )
	TEST_ASSERT_MSG( str2 + str == "AddUTF-8 &éèêàâç", "Add DStrings to std::string failed (operator +)" )
	TEST_ASSERT_MSG( str + c == "UTF-8 &éèêàâçA", "Add char to DStrings failed (operator +)" )
	TEST_ASSERT_MSG( c + str == "AUTF-8 &éèêàâç", "Add DStrings to char failed (operator +)" )
	str += str2;
	TEST_ASSERT_MSG( str == "UTF-8 &éèêàâçAdd", "Add std::string to DStrings failed (operator +=)" )
	str += c;
	TEST_ASSERT_MSG( str == "UTF-8 &éèêàâçAddA", "Add char failed (operator +=)" )
	str = str + 0x24; // $
	TEST_ASSERT_MSG( str == "UTF-8 &éèêàâçAddA$", "Add char failed (operator +)" )
	
	str = "UTF-8 &éèêàâç";
	str2 = "Add";
	c = 0x41; // A
	TEST_ASSERT_MSG( str.append( str2 ) == "UTF-8 &éèêàâçAdd", "Append std::string to DStrings failed" )
	str = "UTF-8 &éèêàâç";
	TEST_ASSERT_MSG( str.append( c ) == "UTF-8 &éèêàâçA", "Append std::string to DStrings failed" )
	str = "UTF-8 &éèêàâç";
	TEST_ASSERT_MSG( str.prepend( str2 ) == "AddUTF-8 &éèêàâç", "Prepend std::string to DStrings failed" )
	str = "UTF-8 &éèêàâç";
	TEST_ASSERT_MSG( str.prepend( c ) == "AUTF-8 &éèêàâç", "Prepend std::string to DStrings failed" )
}

void TestDString::compare_test()
{
	DString str = "U";
	TEST_ASSERT_MSG( str == "U", "Compare DString with const char * failed" )
	TEST_ASSERT_MSG( str == std::string("U"), "Compare DString with std string failed" )
	TEST_ASSERT_MSG( str == 'U', "Compare DString with char failed" )
	TEST_ASSERT_MSG( "U" == str, "Compare DString with const char * failed" )
	TEST_ASSERT_MSG( std::string("U") == str, "Compare DString with std string failed" )
	TEST_ASSERT_MSG( 'U' == str, "Compare DString with char failed" )
	
	TEST_ASSERT_MSG( ! ( str == "V" ), "Compare DString with const char * failed" )
	TEST_ASSERT_MSG( ! ( str == std::string("V") ), "Compare DString with std string failed" )
	TEST_ASSERT_MSG( ! ( str == 'V' ), "Compare DString with char failed" )
	TEST_ASSERT_MSG( ! ( "V" == str ), "Compare DString with const char * failed" )
	TEST_ASSERT_MSG( ! ( std::string("V") == str ), "Compare DString with std string failed" )
	TEST_ASSERT_MSG( ! ( 'V' == str ), "Compare DString with char failed" )
	
	TEST_ASSERT_MSG( str != "u", "Compare DString with const char * failed" )
	TEST_ASSERT_MSG( str != std::string("u"), "Compare DString with std string failed" )
	TEST_ASSERT_MSG( str != 'u', "Compare DString with char failed" )
	TEST_ASSERT_MSG( "u" != str, "Compare DString with const char * failed" )
	TEST_ASSERT_MSG( std::string("u") != str, "Compare DString with std string failed" )
	TEST_ASSERT_MSG( 'u' != str, "Compare DString with char failed" )
	
	TEST_ASSERT_MSG( ! ( str != "U" ), "Compare DString with const char * failed" )
	TEST_ASSERT_MSG( ! ( str != std::string("U") ), "Compare DString with std string failed" )
	TEST_ASSERT_MSG( ! ( str != 'U' ), "Compare DString with char failed" )
	TEST_ASSERT_MSG( ! ( "U" != str ), "Compare DString with const char * failed" )
	TEST_ASSERT_MSG( ! ( std::string("U") != str ), "Compare DString with std string failed" )
	TEST_ASSERT_MSG( ! ( 'U' != str ), "Compare DString with char failed" )
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
	TEST_ASSERT_MSG( str == "3.141593", "Convert float to DString failed" )

	str = "3.1415927";
	double d = str.toDouble();
	TEST_ASSERT_DELTA_MSG( d, 3.1415927, 0.0000001, "Convert DString to double failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.setNum( d, 6 );
	TEST_ASSERT_MSG( str == "3.141593", "Convert double to DString failed" )

	str = "-3.1415927";
	long double ld = str.toLongDouble();
	TEST_ASSERT_DELTA_MSG( ld, -3.1415927, 0.0000001, "Convert DString to long double failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.setNum( ld, 6 );
	TEST_ASSERT_MSG( str == "-3.141593", "Convert long double to DString failed" )
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
	TEST_ASSERT_MSG( str.left( 50 ) == str, "Extract substring from the left failed" )
	TEST_ASSERT_MSG( str.right( 10 ) == "0123456789", "Extract substring from the right failed" )
	TEST_ASSERT_MSG( str.right( 50 ) == str, "Extract substring from the right failed" )
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
	TEST_ASSERT_MSG( str.section( ";", -4, -6 ) == "ABC", "Extract section from end failed" )
	TEST_ASSERT_MSG( str.section( ";", -5, -6 ) == DString::empty(), "Extract section from end failed" )
	
	str = "ABC;DEF 012*34;56789 abc;def*";
	TEST_ASSERT_MSG( str.remove( ";" ).remove( ' ' ).remove( std::string( "*" ) ) == "ABCDEF0123456789abcdef", "Remove string or char failed" )
	str = "ABCDEF0123456789abcdef";
	TEST_ASSERT_MSG( str.remove( "ABC", false ) == "DEF0123456789def", "Remove string or char failed" )
	str = "ABCDEF0123456789abcdef";
	str.remove( 16, 4 );
	TEST_ASSERT_MSG( str == "ABCDEF0123456789ef", "Remove by place failed" )
	str = "ABCDEFabcdef";
	str.remove( 16, 4 );
	TEST_ASSERT_MSG( str == "ABCDEFabcdef", "Remove by place failed" )
	str.remove( 10, 8 );
	TEST_ASSERT_MSG( str == "ABCDEFabcd", "Remove by place failed" )
	
	str = "ABCDEF0123456789abcdef";
	str.replace( "a", ",", false );
	TEST_ASSERT_MSG( str == ",BCDEF0123456789,bcdef", "Replace string or char failed" )
	str = "ABCDEF0123456789abcdef";
	str.replace( "a", ",", true );
	TEST_ASSERT_MSG( str == "ABCDEF0123456789,bcdef", "Replace string or char failed" )
	str = "ABCDEF0123456789abcdef";
	str.replace( 6, 10, "--" );
	TEST_ASSERT_MSG( str == "ABCDEF--abcdef", "Replace by place failed (const char*)" )
	str = "ABCDEF0123456789abcdef";
	str.replace( 6, 10, std::string( "--" ) );
	TEST_ASSERT_MSG( str == "ABCDEF--abcdef", "Replace by place failed (std::string)" )
	str = "ABCDEF0123456789abcdef";
	str.replace( 6, 10, '-' );
	TEST_ASSERT_MSG( str == "ABCDEF-abcdef", "Replace by place failed (char)" )
	str = "ABCDEF";
	str.replace( 8, 10, '-' );
	TEST_ASSERT_MSG( str == "ABCDEF  -", "Replace by place failed (char)" )
	str = "ABCDEF";
	str.replace( 8, 2, '-' );
	TEST_ASSERT_MSG( str == "ABCDEF  -", "Replace by place failed (char)" )
	
	str = "ABCDEFabcdef";
	str.insert( 6, "0123456789" );
	TEST_ASSERT_MSG( str == "ABCDEF0123456789abcdef", "Insert by place failed" )
	str = "ABCDEFabcdef";
	str.insert( 14, "0123456789" );
	TEST_ASSERT_MSG( str == "ABCDEFabcdef  0123456789", "Insert by place failed" )
	str = "ABCDEFabcdef";
	str.insert( 6, std::string( "0123456789" ) );
	TEST_ASSERT_MSG( str == "ABCDEF0123456789abcdef", "Insert by place failed" )
	str = "ABCDEFabcdef";
	str.insert( 6, '0' );
	TEST_ASSERT_MSG( str == "ABCDEF0abcdef", "Insert by place failed" )
	
	str = "ABCDEF0123456789abcdef";
	TEST_ASSERT_MSG( str.find( "abc" ) == 16, "Find substring failed (case sensitive)" )
	TEST_ASSERT_MSG( str.find( "abc", -1 ) == 16, "Find substring failed (case sensitive)" )
	TEST_ASSERT_MSG( str.find( "ABC" ) == 0, "Find substring failed (case sensitive)" )
	TEST_ASSERT_MSG( str.find( "ABC", 0 ) == 0, "Find substring failed (case sensitive)" )
	TEST_ASSERT_MSG( str.find( "abc", -1, false ) == 16, "Reverse find substring failed (case insensitive)" )
	TEST_ASSERT_MSG( str.find( "ABC", -1, false ) == 16, "Reverse find substring failed (case insensitive)" )
	TEST_ASSERT_MSG( str.find( "abc", 0, false ) == 0, "Find substring failed (case insensitive)" )
	TEST_ASSERT_MSG( str.find( "ABC", 0, false ) == 0, "Find substring failed (case insensitive)" )
	
	TEST_ASSERT_MSG( str.find( std::string( "abc" ) ) == 16, "Find substring failed (case sensitive)" )
	TEST_ASSERT_MSG( str.find( std::string( "abc" ), -1 ) == 16, "Find substring failed (case sensitive)" )
	TEST_ASSERT_MSG( str.find( std::string( "ABC" ) ) == 0, "Find substring failed (case sensitive)" )
	TEST_ASSERT_MSG( str.find( std::string( "ABC" ), 0 ) == 0, "Find substring failed (case sensitive)" )
	TEST_ASSERT_MSG( str.find( std::string( "abc" ), -1, false ) == 16, "Reverse find substring failed (case insensitive)" )
	TEST_ASSERT_MSG( str.find( std::string( "ABC" ), -1, false ) == 16, "Reverse find substring failed (case insensitive)" )
	TEST_ASSERT_MSG( str.find( std::string( "abc" ), 0, false ) == 0, "Find substring failed (case insensitive)" )
	TEST_ASSERT_MSG( str.find( std::string( "ABC" ), 0, false ) == 0, "Find substring failed (case insensitive)" )
	
	TEST_ASSERT_MSG( str.find( 'a' ) == 16, "Find substring failed (case sensitive)" )
	TEST_ASSERT_MSG( str.find( 'a', -1 ) == 16, "Find substring failed (case sensitive)" )
	TEST_ASSERT_MSG( str.find( 'A' ) == 0, "Find substring failed (case sensitive)" )
	TEST_ASSERT_MSG( str.find( 'A', 0 ) == 0, "Find substring failed (case sensitive)" )
	TEST_ASSERT_MSG( str.find( 'a', -1, false ) == 16, "Reverse find substring failed (case insensitive)" )
	TEST_ASSERT_MSG( str.find( 'A', -1, false ) == 16, "Reverse find substring failed (case insensitive)" )
	TEST_ASSERT_MSG( str.find( 'a', 0, false ) == 0, "Find substring failed (case insensitive)" )
	TEST_ASSERT_MSG( str.find( 'A', 0, false ) == 0, "Find substring failed (case insensitive)" )
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
	
	strl.clear();
	strl = str.split ( "\n", true );
	TEST_ASSERT_MSG( strl.size() == 6, "Split with wrong number of substr" )
	it = strl.begin();
	TEST_ASSERT_MSG( it != strl.end(), "Split with wrong number of substr" )
	i = 0;
	while ( it != strl.end() ) {
		sub.clear();
		sub.setNum( i );
		sub.prepend( "text" );
		if ( ! i || i == 5 ) sub.clear();
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
	
	strl.clear();
	strl = str.splitConstantSize( " ", 3 );
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
	
	str = DString::timeToString ( 1404831621, DString::ISO_DATETIME );
	TEST_ASSERT_MSG( str == "2014-07-08 17:00:21", "Get Date-Time failed" )
	
	str = DString::timeToString ( 1404831621, DString::ISO_DATE );
	TEST_ASSERT_MSG( str == "2014-07-08", "Get Date failed" )
	
	str = DString::timeToString ( 1404831621,  DString::ISO_TIME );
	TEST_ASSERT_MSG( str == "17:00:21", "Get Time failed" )
	
	str = DString::Now( DString::ISO_DATETIME_T );
	TEST_ASSERT_MSG( str == DString::timeToString ( time( 0 ), DString::ISO_DATETIME_T ), "Now is not current date-time" )
	
	str = DString::Now( "%Y-%m-%d %H-%M-%S" );
	TEST_ASSERT_MSG( str == DString::timeToString ( time( 0 ), "%Y-%m-%d %H-%M-%S" ), "Now is not current date-time" )
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
	TEST_ASSERT_MSG( str.contains( 'A', false ) == 13, "Contains char failed, case insensitive" )
	TEST_ASSERT_MSG( str.contains( "AA", false ) == 10, "Contains string failed" )
	TEST_ASSERT_MSG( str.contains( std::string( "AAA" ), false ) == 7, "Contains string failed" )
	//std::cout << std::endl << str.contains( 'A', false ) << std::endl;
	str.clear();
	TEST_ASSERT_MSG( str.contains( 'a' ) == 0, "Empty string contains char" )
	

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

void TestDString::quoted_printable_test()
{
	DString str;
	
	str = "UTF-8 ¡ ¢ £ € ¥ Š § š © ª « ¬ ® ¯";
	TEST_ASSERT_MSG( str.toQuotedPrintable() == "UTF-8 =C2=A1 =C2=A2 =C2=A3 =E2=82=AC =C2=A5 =C5=A0 =C2=A7 =C5=A1 =C2=A9 =C2=AA =C2=AB =C2=AC =C2=AE =C2=AF", "Bad encodage" )
	str = "UTF-8 ° ± ² ³ Ž µ ¶ · ž ¹ º » Œ œ Ÿ ¿";
	TEST_ASSERT_MSG( str.toQuotedPrintable() == "UTF-8 =C2=B0 =C2=B1 =C2=B2 =C2=B3 =C5=BD =C2=B5 =C2=B6 =C2=B7 =C5=BE =C2=B9 =C2=BA =C2=BB =C5=92 =C5=93 =C5=B8 =C2=BF", "Bad encodage" )
	str = "UTF-8 À Á Â Ã Ä Å Æ Ç È É Ê Ë Ì Í Î Ï";
	TEST_ASSERT_MSG( str.toQuotedPrintable() == "UTF-8 =C3=80 =C3=81 =C3=82 =C3=83 =C3=84 =C3=85 =C3=86 =C3=87 =C3=88 =C3=89 =C3=8A =C3=8B =C3=8C =C3=8D =C3=8E =C3=8F", "Bad encodage" )
	str = "UTF-8 Ð Ñ Ò Ó Ô Õ Ö × Ø Ù Ú Û Ü Ý Þ ß";
	TEST_ASSERT_MSG( str.toQuotedPrintable() == "UTF-8 =C3=90 =C3=91 =C3=92 =C3=93 =C3=94 =C3=95 =C3=96 =C3=97 =C3=98 =C3=99 =C3=9A =C3=9B =C3=9C =C3=9D =C3=9E =C3=9F", "Bad encodage" )
	str = "UTF-8 à á â ã ä å æ ç è é ê ë ì í î ï";
	TEST_ASSERT_MSG( str.toQuotedPrintable() == "UTF-8 =C3=A0 =C3=A1 =C3=A2 =C3=A3 =C3=A4 =C3=A5 =C3=A6 =C3=A7 =C3=A8 =C3=A9 =C3=AA =C3=AB =C3=AC =C3=AD =C3=AE =C3=AF", "Bad encodage" )
	str = "UTF-8 ð ñ ò ó ô õ ö ÷ ø ù ú û ü ý þ ÿ";
	TEST_ASSERT_MSG( str.toQuotedPrintable() == "UTF-8 =C3=B0 =C3=B1 =C3=B2 =C3=B3 =C3=B4 =C3=B5 =C3=B6 =C3=B7 =C3=B8 =C3=B9 =C3=BA =C3=BB =C3=BC =C3=BD =C3=BE =C3=BF", "Bad encodage" )
}

void TestDString::html_test()
{
	DString str;
	
	str = "UTF-8 ¡ ¢ £ € ¥ Š § š © ª « ¬ ® ¯";
	TEST_ASSERT_MSG( str.toHTML() == "UTF&#45;8 &#161; &#162; &#163; &#8364; &#165; &#352; &#167; &#353; &#169; &#170; &#171; &#172; &#174; &#175;", "Bad encodage" )
}

void TestDString::replace_escape_test()
{
	DString str, ref;
	
	str = static_cast<char> ( 0x00 );
	ref = "<NUL>";

	str += 0x01;
	ref += "<SOH>";

	str += 0x02;
	ref += "<STX>";

	str += 0x03;
	ref += "<ETX>";

	str += 0x04;
	ref += "<EOT>";

	str += 0x05;
	ref += "<ENQ>";

	str += 0x06;
	ref += "<ACK>";

	str += 0x07;
	ref += "<BEL>";

	str += 0x08;
	ref += "<BS>";

	str += 0x09;
	ref += "<HT>";

	str += 0x0A;
	ref += "<LF>";

	str += 0x0B;
	ref += "<VT>";

	str += 0x0C;
	ref += "<FF>";

	str += 0x0D;
	ref += "<CR>";

	str += 0x0E;
	ref += "<SO>";

	str += 0x0F;
	ref += "<SI>";

	str += 0x10;
	ref += "<DLE>";

	str += 0x11;
	ref += "<DC1>";

	str += 0x12;
	ref += "<DC2>";

	str += 0x13;
	ref += "<DC3>";

	str += 0x14;
	ref += "<DC4>";

	str += 0x15;
	ref += "<NAK>";

	str += 0x16;
	ref += "<SYN>";

	str += 0x17;
	ref += "<ETB>";

	str += 0x18;
	ref += "<CAN>";

	str += 0x19;
	ref += "<EM>";

	str += 0x1A;
	ref += "<SUB>";

	str += 0x1B;
	ref += "<ESC>";

	str += 0x1C;
	ref += "<FS>";

	str += 0x1D;
	ref += "<GS>";

	str += 0x1E;
	ref += "<RS>";

	str += 0x1F;
	ref += "<US>";
	
	TEST_ASSERT_MSG( str.replaceEscapeSequence() == ref, "Escape sequences are not replaced correctly" )
}

void TestDString::related_function_test()
{
	int i = 0;

	//Decimal
	strToValue( i, "123456789", 10 );
	TEST_ASSERT_MSG( i == 123456789, "String to value failed (base 10)" )
	
	i = 0;
	strToValue( i, "123456789" );
	TEST_ASSERT_MSG( i == 123456789, "String to value failed (base 10)" )
	
	// Hexa
	i = 0;
	strToValue( i, "75bcd15", 16 );
	TEST_ASSERT_MSG( i == 123456789, "String to value failed (base 16)" )
	i = 0;
	strToValue( i, "0x75bcd15" );
	TEST_ASSERT_MSG( i == 123456789, "String to value failed (base 16)" )
	
	// Octal
	i = 0;
	strToValue( i, "361100", 8 );
	TEST_ASSERT_MSG( i == 123456, "String to value failed (base 8)" )
	i = 0;
	strToValue( i, "0361100" );
	TEST_ASSERT_MSG( i == 123456, "String to value failed (base 8)" )
	
	i = 123456789;
	TEST_ASSERT_MSG( valueToStr( i ) == std::string( "123456789" ), "Value to string failed (base 10)" )
	TEST_ASSERT_MSG( valueToStr( i, 16 ) == std::string( "75bcd15" ), "Value to string failed (base 16)" )
	i = 123456;
	TEST_ASSERT_MSG( valueToStr( i, 8 ) == std::string( "361100" ), "Value to string failed (base 8)" )
	
	double d = 3.14159265359;
	TEST_ASSERT_MSG( valueToStr( d, 10, 11 ) == std::string( "3.14159265359" ), "float to string failed (base 10)" )
	TEST_ASSERT_MSG( valueToStr( d, 10, 2 ) == std::string( "3.14" ), "float to string failed (base 10)" )
	
}

int main()
{
	TestDString ets;
#ifdef TEST_HTML
	std::ofstream file;
	Test::HtmlOutput html;

	file.open( "dstring.html" );
	ets.run( html );
	html.generate( file, true, "DString" );
	file.close();
#endif

#ifdef TEST_STDOUT
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );

	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
#endif
	return EXIT_SUCCESS;
}
