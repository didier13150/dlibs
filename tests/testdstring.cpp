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
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                *
 *                                                                            *
 *   Unit Test for DString                                                    *
 *                                                                            *
 ******************************************************************************/
#include <cstdlib>
#include <iostream>
#include <map>
#include "testdstring.h"

using namespace std;

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
	string str2 = "Add";
	
	str += str2;
	char c = 0x41; // A
	str += c;
	TEST_ASSERT_MSG( str == "UTF-8 &éèêàâçAddA", "Add 2 DStrings failed" )
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

	str = "-123456789.258";
	long double ld = str.toLongDouble();
	TEST_ASSERT_DELTA_MSG( ld, -123456789.258, 0.001, "Convert DString to long double failed" )
	str.clear();
	TEST_ASSERT_MSG( str == DString::empty(), "clear failed" )
	str.setNum( ld, 6 );
	TEST_ASSERT_MSG( str == "-123456789.258", "Convert long double to DString failed" )
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
/*
	cout << "#########################################################" << endl;
	str = "Chaine pleine";
	if ( str.isEmpty() )
	{
		cout << "La chaine est vide" << endl;
		cout << "Longueur = " << str.length() << endl;
	}
	else
	{
		cout << "La chaine n'est pas vide" << endl;
		cout << "Longueur = " << str.length() << endl;
	}
	cout << "str.clear()" << endl;
	str.clear();
	if ( str.isEmpty() )
	{
		cout << "La chaine est vide" << endl;
		cout << "Longueur = " << str.length() << endl;
	}
	else
	{
		cout << "La chaine n'est pas vide" << endl;
		cout << "Longueur = " << str.length() << endl;
	}

	cout << "#########################################################" << endl;
	str = "abcdefghijklmnopqrstuvwxyz0123456789";
	cout << "27 first char (from the left) : " << str.left ( 27 ) << endl;
	cout << "50 first char (from the left) : " << str.left ( 50 ) << endl;
	cout << "10 first char (from the right) : " << str.right ( 10 ) << endl;
	cout << "50 first char (from the right) : " << str.right ( 50 ) << endl;
	cout << "01234 are 5 char (begin at position 26) : " << str.mid ( 26, 5 ) << endl;
	cout << "the 50 first char (begin at position 0) : " << str.mid ( 0, 50 ) << endl;

	cout << "#########################################################" << endl;
	cout << "la dstring de base = \"" << str << "\"" << endl;
	cout << "str length = " << str.length() << endl;
	str = str.at ( 3 );
	cout << "un DString qui est le caractère n 3 =" << str << endl;
	str = str.at ( 73 );
	cout << "un DString qui est le caractère n 73 =" << str << endl;
	str = str.at ( 173 );
	cout << "un DString qui est le caractère n 173 =" << str << endl;
	sstr = str[3];
	cout << "un standard string qui est le caractère n 3 =" << sstr << endl;
	sstr = str[73];
	cout << "un standard string qui est le caractère n 73 =" << sstr << endl;
	sstr = str[173];
	cout << "un standard string qui est le caractère n 173 =" << sstr << endl;

	cout << "#########################################################" << endl;
	str = "abcdefghijklmnopqrstuvwxyz0123456789";
	cout << str << endl;
	if ( str.containsOnlyLegalChar ( DString::HEXA, DString::LOWERCASE ) )
	{
		cout << "La chaine est valide (hexa in lowercase)" << endl;
	}
	else
	{
		cout << "La chaine n'est pas valide (hexa in lowercase)" << endl;
	}
	str = "abcdef0123456789";
	cout << str << endl;
	if ( str.containsOnlyLegalChar ( DString::HEXA, DString::LOWERCASE ) )
	{
		cout << "La chaine est valide (hexa in lowercase)" << endl;
	}
	else
	{
		cout << "La chaine n'est pas valide (hexa in lowercase)" << endl;
	}
	str = "ABCDEF0123456789";
	cout << str << endl;
	if ( str.containsOnlyLegalChar ( DString::HEXA, DString::LOWERCASE ) )
	{
		cout << "La chaine est valide (hexa in lowercase)" << endl;
	}
	else
	{
		cout << "La chaine n'est pas valide (hexa in lowercase)" << endl;
	}
	str = "ABCDEF0123456789";
	cout << str << endl;
	if ( str.containsOnlyLegalChar ( DString::HEXA, DString::UPPERCASE ) )
	{
		cout << "La chaine est valide (hexa in uppercase)" << endl;
	}
	else
	{
		cout << "La chaine n'est pas valide (hexa in uppercase)" << endl;
	}
	str = "ABCDEF0123456789abcdef";
	cout << str << endl;
	if ( str.containsOnlyLegalChar ( DString::HEXA, DString::BOTHCASE ) )
	{
		cout << "La chaine est valide (hexa, case insensitive)" << endl;
	}
	else
	{
		cout << "La chaine n'est pas valide (hexa, case insensitive)" << endl;
	}

	cout << "#########################################################" << endl;

	cout << "split" << endl;
	str = "text1\ntext2\ntext3\ntext4";
	DStringList strl = str.split ( "\n" );
	DStringList::iterator it;
	for ( it = strl.begin() ; it != strl.end() ; ++it )
	{
		cout << *it << endl;
	}
	cout << "#########################################################" << endl;

	cout << "Time" << endl;
	cout << "static now : " << DString::Now ( "%Y-%m-%dT%H-%M-%S" ) << endl;
	cout << "static now : " << DString::Now ( DString::ISO_DATETIME ) << endl;
	str = DString::timeToString ( time ( NULL ), DString::ISO_DATETIME );
	cout << str << endl;
	str.convertTime ( DString::ISO_DATETIME, DString::ISO_DATE );
	cout << "convert datetime to date : " << str << endl;

	cout << "#########################################################" << endl;

	cout << "std::map" << endl;

	std::map<DString, DString> mp;

	str = "1";
	mp[str] = "123456789";
	str = "2";
	mp[str] = "987654321";

	str = "1";
	cout << "good if '123456789' is displayed : " << mp[str] << endl;
	str = "2";
	cout << "good if '987654321' is displayed : " << mp[str] << endl;
	
	cout << "#########################################################" << endl;
	
	cout << "section test" << endl;
	
	str = "ABC;DEF 01234;56789 abc;def";
	cout << "la dstring de base = \"" << str << "\"" << endl;
	cout << "Section ( \" \", 1, 1 ) = \"" << str.section( " ", 1, 1 ) << "\"" << endl;
	cout << "Section ( \";\", 1, 2 ) = \"" << str.section( ";", 1, 2 ) << "\"" << endl;
	cout << "Section ( \";\", 1, 3 ) = \"" << str.section( ";", 1, 3 ) << "\"" << endl;
	cout << "Section ( \";\", 1, 30 ) = \"" << str.section( ";", 1, 30 ) << "\"" << endl;
	cout << "Section ( \";\", -1, -1 ) = \"" << str.section( ";", -1, -1 ) << "\"" << endl;
	
	
#if 0
	cout << "getline test" << endl;
	ifstream iss;
	bool finished = false;
	while ( !finished )
	{
		cout << endl << "Enter file name to read : ";
		cin >> str;
		if ( str == "quit" || str == "exit" )
		{
			finished = true;
		}
		else
		{
			iss.open ( str.c_str() );
			if ( iss )
			{
				while ( getline ( iss, strDStr ) )
				{
					cout << strDStr << endl;
				}
				finished = true;
			}
			else
			{
				cout << "Cannot open file " << str << endl;
			}
		}
	}

	iss.close();
#endif
	cout << endl << "End of DString test" << endl;
	return 0;
}
*/


int main( int argc, char** argv )
{
	Test::TextOutput output(Test::TextOutput::Verbose);
	TestDString ets;
	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
}