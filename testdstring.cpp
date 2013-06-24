/******************************************************************************
 * Unit Test for DString                                                      *
 ******************************************************************************/

#include <iostream>
#include <cstdlib>
#include <map>
#include "dlibs.h" // replace it by #include <dlibs/dlibs.h>

using namespace std;

int testdstring()
{
	std::string sstr = "This is a standart string";
	const char * cchar = "This is a const char";
	char c = 'c';

	DString strStr ( sstr );
	DString strChar ( c );
	DString strConstChar ( cchar );
	DString strDStr ( strStr );
	DString str;

	cout << "#########################################################" << endl;

	// Constructor
	cout << "Constructor" << endl;
	cout << "DString(std::string) " << "DString from a standart string : " << strStr << endl;
	cout << "DString(char) " << "DString from a single character : " << strChar << endl;
	cout << "DString(const char *) " << "DString from a const char* : " << strConstChar << endl;
	cout << "DString(DString) " << "DString from another DString: " << strDStr << endl;

	cout << "#########################################################" << endl;
	cout << "operator=" << endl;
	// operator=
	str = strDStr; // DString = DString
	cout << "DString=DString : " << str << endl;
	str = strStr; // DString = std::string
	cout << "DString=std::string : " << str << endl;
	str = cchar; // DString = char
	cout << "DString=char : " << str << endl;

	cout << "#########################################################" << endl;
	cout << "operator+=" << endl;
	// operator+=
	str = strDStr;
	str += strDStr;
	cout << "" << str <<endl;
	str = strDStr;
	str += strStr;
	cout << str <<endl;
	str = strDStr;
	c = 0x41;
	str += c;
	cout << str <<endl;

	cout << "#########################################################" << endl;
	cout << "number operations" << endl;
	// number operations
	int i;
	short int si;
	long int li;
	long long int lli;
	unsigned int ui;
	unsigned short int usi;
	unsigned long int uli;
	unsigned long long int ulli;
	float f;
	double d;
	long double ld;

	str = "-123456789";
	i = str.toInt();
	cout << "i = " << i << endl;
	str = "";
	str.setNum ( i );
	cout << "str = " << str << endl;

	str = "123456789";
	ui = str.toUInt();
	cout << "ui = " << ui << endl;
	str = "";
	str.setNum ( ui );
	cout << "str = " << str << endl;

	str = "-12345";
	si = str.toShort();
	cout << "si = " << si << endl;
	str = "";
	str.setNum ( si );
	cout << "str = " << str << endl;

	str = "12345";
	usi = str.toUShort();
	cout << "usi = " << usi << endl;
	str = "";
	str.setNum ( usi );
	cout << "str = " << str << endl;

	str = "-123456789";
	li = str.toLong();
	cout << "li = " << li << endl;
	str = "";
	str.setNum ( li );
	cout << "str = " << str << endl;

	str = "123456789";
	uli = str.toULong();
	cout << "uli = " << uli << endl;
	str = "";
	str.setNum ( uli );
	cout << "str = " << str << endl;

	str = "-123456789";
	lli = str.toLongLong();
	cout << "lli = " << lli << endl;
	str = "";
	str.setNum ( lli );
	cout << "str = " << str << endl;

	str = "123456789";
	ulli = str.toULongLong();
	cout << "ulli = " << ulli << endl;
	str = "";
	str.setNum ( ulli );
	cout << "str = " << str << endl;

	str = "3.1415927";
	f = str.toFloat();
	cout << "f = " << f << endl;
	str = "";
	str.setNum ( f, 7 );
	cout << "str = " << str << endl;

	str = "3.1415927";
	d = str.toDouble();
	cout << "d = " << d << endl;
	str = "";
	str.setNum ( d, 7 );
	cout << "str = " << str << endl;

	str = "123456789.258";
	ld = str.toLongDouble();
	cout << "ld = " << ld << endl;
	str = "";
	str.setNum ( ld, 10 );
	cout << "str = " << str << endl;

	str.toBase2 ( 0x7FFFFFFF );
	//str = "10010100";
	i = str.toIntBase10();
	cout << "i = " << i << endl;
	str = "";
	str.toBase2 ( i );
	cout << "str = " << str << endl;

	str.toBase2 ( 0xFFFFFFFF );
	//str = "10010100";
	ui = str.toUIntBase10();
	cout << "ui = " << ui << endl;
	str = "";
	str.toBase2 ( ui );
	cout << "str = " << str << endl;

	str = "10010100";
	si = str.toShortBase10();
	cout << "si = " << si << endl;
	str = "";
	str.toBase2 ( si );
	cout << "str = " << str << endl;

	str = "10010100";
	usi = str.toUShortBase10();
	cout << "usi = " << usi << endl;
	str = "";
	str.toBase2 ( usi );
	cout << "str = " << str << endl;

	str = "10010100";
	li = str.toLongBase10();
	cout << "li = " << li << endl;
	str = "";
	str.toBase2 ( li );
	cout << "str = " << str << endl;

	str = "10010100";
	uli = str.toULongBase10();
	cout << "uli = " << uli << endl;
	str = "";
	str.toBase2 ( uli );
	cout << "str = " << str << endl;

	str = "10010100";
	lli = str.toLongLongBase10();
	cout << "lli = " << lli << endl;
	str = "";
	str.toBase2 ( lli );
	cout << "str = " << str << endl;

	str = "10010100";
	ulli = str.toULongLongBase10();
	cout << "ulli = " << ulli << endl;
	str = "";
	str.toBase2 ( ulli );
	cout << "str = " << str << endl;

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
	cout << endl << "End of DString test" << endl;
	return 0;
}

