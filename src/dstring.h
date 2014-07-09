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
 *     (___)_)   File : dstring.h                           ||--|| *          *
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
 ******************************************************************************/

#ifndef DSTRING_H
#define DSTRING_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <iterator>
#include <cmath>
#include <list>


/**
 * @relates DString
 * Convert any standard string to a numeric value
 * \param Value a reference to the value
 * \param str the string to convert
 * \param base the numeric base ( octal, decimal, hexa )
 * \return A numeric value
 */
template<class T> T strToValue ( T & Value, const std::string & str, int base = 0 )
{
	Value = 0;
	std::istringstream iss ( str );

	if ( ( base == 0 ) && ( str.length() > 1 ) )
	{
		if ( str.substr ( 0, 2 ) == "0x" )
		{
			base = 16;
		}
		else if ( str.substr ( 0, 1 ) == "0" )
		{
			base = 8;
		}
		else
		{
			base = 10;
		}
	}
	if ( base == 16 )
	{
		iss.setf ( std::ios::hex, std::ios::basefield );
	}
	else if ( base == 8 )
	{
		iss.setf ( std::ios::oct, std::ios::basefield );
	}
	iss >> Value;
	return Value;
}


/**
 * @relates DString
 * Convert any numeric value to a standard string
 * \param Value a reference to the value
 * \param base the numeric base ( octal, decimal, hexa )
 * \param prec precision for floating point value ( float or double ). This parameter is ignored for others values.
 * \return A standard string
 */
template<class T> std::string valueToStr ( T & Value, int base = 10, int prec = 0 )
{
	std::string str;
	std::string::size_type pos;

	// Create output string flux to create str
	std::ostringstream oss;
	if ( base == 16 )
	{
		oss.setf ( std::ios::hex, std::ios::basefield );
	}
	if ( base == 8 )
	{
		oss.setf ( std::ios::oct, std::ios::basefield );
	}
	if ( prec > 0 )
	{
		oss.precision ( prec );
	}
	// Write value in flux
	oss << Value;
	// Return string
	str = oss.str();
	if ( prec >= 0 )
	{
		pos = str.find ( "." );
		if ( pos != std::string::npos )
		{
			if ( ( pos + prec + 1 ) < str.length() )
			{
				str = str.substr ( 0, ( pos + prec + 1 ) );
			}
		}
	}
	return str;
}

/**
 * @relates DString
 * Convert any numeric value (int, unsigned int, float, double, etc...) to a string
 * base 2 (bin).\n
 * For integer values divide by 2, until get down to 1 and concatene the rest
 */
template<class T> std::string decTobin ( T & Value )
{
	std::string str;
	T val = Value;
	T vtmp;

	while ( val > 0 )
	{
		vtmp = val % 2;
		str = valueToStr ( vtmp ) + str;
		val = val / 2;
	}

	return str;
}

/**
 * @relates DString
 * Convert a string base 2 value (bin) to double.\n
 *
 * To convert binary to decimal, we start from the right to the left of the
 * binary chain and at each bit, we associate the value @f$ 2^n @f$ ,
 * the first bit being bit number 0, and it be incremented to 1 for each round.
 */
double binToDec ( const std::string & str );

class DString;
/**
 * @typedef DStringList
 * \ref DString
 * Create a standard list of DString. Iterator can be defined as
 * DStringList::iterator
 */
typedef std::list<DString> DStringList;

/**
 * This is an improvement of standard string, which implement a lot of usefull
 * methods.
 * 100% STL compliant.
 * @short Upgraded standard string
 * @author Didier FABERT <didier.fabert@gmail.com>
 */
class DString
{
	public:

		/**
		 * Make empty string.
		 */
		DString ( void );
		/**
		 * Make string from a standard string.
		 */
		DString ( const std::string & str );
		/**
		 * Make string from c language char table.
		 */
		DString ( const char *str );
		/**
		 * Make string from a single char.
		 */
		DString ( char c );
		/**
		 * Destructor
		 */
		~DString();

		/**
		 * @typedef BaseFlag
		 * Commonly base for numbers
		 */
		typedef enum
		{
			BINARY  = 0x2,
			OCTAL   = 0x8,
			DECIMAL = 0xA,
			HEXA    = 0xF,
		}BaseFlag;

		/**
		 * @typedef CaseFlag
		 * Text case
		 */
		typedef enum
		{
			LOWERCASE  = 0x01,
			UPPERCASE  = 0x02,
			BOTHCASE   = LOWERCASE | UPPERCASE,
		}CaseFlag;

		/**
		 * @typedef DateFormat
		 * Date-time common format ( ISO )
		 */
		typedef enum
		{
			ISO_DATETIME   = 0x00,
			ISO_DATETIME_T = 0x01,
			ISO_DATE       = 0x02,
			ISO_TIME       = 0x03,
		}DateFormat;

		/**
		 * Return a reference to the internal standard string
		 */
		std::string & getReference();

		/**
		 * Sets the string to contain the DString str
		 */
		DString & operator = ( const DString & str );
		/**
		 * Sets the string to contain the standard string str.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & operator = ( const std::string & str );
		/**
		 * Sets the string to contain the string str.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & operator = ( const char *str );
		/**
		 * Sets the string to contain the char c.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & operator = ( char c );
		/**
		 * Appends the string str to the string and returns a reference to the
		 * string.
		 */
		const DString & operator += ( const DString & str );
		/**
		 * Appends the string str to the string and returns a reference to the
		 * string.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		const DString & operator += ( const std::string & str );
		/**
		 * Appends the string str to the string and returns a reference to the
		 * string.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		const DString & operator += ( const char * str );
		/**
		 * Appends the char c to the string and returns a reference to the string..\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		const DString & operator += ( char c );

		/**
		 * Returns a string which is the result of concatenating the string s1
		 * and the string s2.
		 */
		friend const DString operator + ( const DString & str1, const DString & str2 );

		/**
		 * Returns a string which is the result of concatenating the string s1
		 * and the string s2.
		 */
		friend const DString operator + ( const DString & str1,
		                                  const std::string & str2 );
		/**
		 * Returns a string which is the result of concatenating the string s1
		 * and the string s2.
		 */
		friend const DString operator + ( const DString & str1, const char * str2 );

		/**
		 * Returns a string which is the result of concatenating the string s1
		 * and the char c.
		 */
		friend const DString operator + ( const DString & str1, char c );

		/**
		 * Returns a string which is the result of concatenating the string s1
		 * and the string s2.
		 */
		friend const DString operator + ( const std::string & str1,
		                                  const DString & str2 );

		/**
		 * Returns a string which is the result of concatenating the string s1
		 * and the string s2.
		 */
		friend const DString operator + ( const char * str1, const DString & str2 );

		/**
		 * Returns a string which is the result of concatenating the char c
		 * and the string s1.
		 */
		friend const DString operator + ( char c, const DString & str1 );

		/**
		 * Returns TRUE if str1 is equal to str2; otherwise returns FALSE.
		 */
		friend bool operator == ( const DString & str1, const DString & str2 );

		/**
		 * Returns TRUE if str1 is equal to str2; otherwise returns FALSE.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		friend bool operator == ( const DString & str1, const std::string & str2 );

		/**
		 * Returns TRUE if str1 is equal to str2; otherwise returns FALSE.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		friend bool operator == ( const DString & str1, const char * str2 );

		/**
		 * Returns TRUE if str1 is equal to str2; otherwise returns FALSE.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		friend bool operator == ( const std::string & str1, const DString & str2 );

		/**
		 * Returns TRUE if str1 is equal to str2; otherwise returns FALSE.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		friend bool operator == ( const char * str1, const DString & str2 );

		/**
		 * Returns TRUE if str1 is not equal to str2; otherwise returns FALSE.
		 */
		friend bool operator != ( const DString & str1, const DString & str2 );

		/**
		 * Returns TRUE if str1 is not equal to str2; otherwise returns FALSE.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		friend bool operator!= ( const DString & str1, const std::string & str2 );

		/**
		 * Returns TRUE if str1 is not equal to str2; otherwise returns FALSE.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		friend bool operator != ( const DString & str1, const char * str2 );

		/**
		 * Returns TRUE if str1 is not equal to str2; otherwise returns FALSE.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		friend bool operator != ( const std::string & str1, const DString & str2 );

		/**
		 * Returns TRUE if str1 is not equal to str2; otherwise returns FALSE.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		friend bool operator != ( const char * str1, const DString & str2 );

		/**
		 * Returns TRUE if str1 is lesser than str2; otherwise returns FALSE.\n
		 * This friendly method is necessary to define standart key-value pair
		 * container ( ex std::map ) with a DString key.
		 */
		friend bool operator < ( const DString & str1, const DString & str2 );

		/**
		 * Returns TRUE if str1 is lesser or equal than str2; otherwise returns FALSE.\n
		 * This friendly method is necessary to define standart key-value pair
		 * container ( ex std::map ) with a DString key.
		 */
		friend bool operator <= ( const DString & str1, const DString & str2 );

		/**
		 * Returns TRUE if str1 is greater than str2; otherwise returns FALSE.\n
		 * This friendly method is necessary to define standart key-value pair
		 * container ( ex std::map ) with a DString key.
		 */
		friend bool operator > ( const DString & str1, const DString & str2 );

		/**
		 * Returns TRUE if str1 is greater or equal than str2; otherwise returns FALSE.\n
		 * This friendly method is necessary to define standart key-value pair
		 * container ( ex std::map ) with a DString key.
		 */
		friend bool operator >= ( const DString & str1, const DString & str2 );

		/**
		* Writes DString to the stream s and returns a reference to the stream.
		*/
		friend std::ostream& operator << ( std::ostream& s, const DString & str );

		/**
		* Reads DString from the stream s and returns a reference to the stream.
		*/
		friend std::istream& operator >> ( std::istream& s, DString & str );

		/**
		 * Returns the string converted to a short int using base base,
		 * which is 10 by default and must be 8 (octal), 10 (decimal) or 16 (hexa).\n
		 * Returns 0 if conversion fails.
		 */
		short int toShort ( int base = 10 ) const ;

		/**
		 * Returns the string converted to an unsigned short int using base base,
		 * which is 10 by default and must be 8 (octal), 10 (decimal) or 16 (hexa).
		 */
		unsigned short int toUShort ( int base = 10 ) const ;

		/**
		 * Returns the string converted to an int using base base,
		 * which is 10 by default and must be 8 (octal), 10 (decimal) or 16 (hexa).
		 */
		int toInt ( int base = 10 ) const ;

		/**
		 * Returns the string converted to an unsigned int using base base,
		 * which is 10 by default and must be 8 (octal), 10 (decimal) or 16 (hexa).
		 */
		unsigned int toUInt ( int base = 10 ) const ;

		/**
		 * Returns the string converted to a long int using base base,
		 * which is 10 by default and must be 8 (octal), 10 (decimal) or 16 (hexa).
		 */
		long int toLong ( int base = 10 ) const ;

		/**
		 * Returns the string converted to an unsigned long int using base base,
		 * which is 10 by default and must be 8 (octal), 10 (decimal) or 16 (hexa).
		 */
		unsigned long toULong ( int base = 10 ) const ;

		/**
		 * Returns the string converted to a long int using base base,
		 * which is 10 by default and must be 8 (octal), 10 (decimal) or 16 (hexa).
		 */
		long long int toLongLong ( int base = 10 ) const ;

		/**
		 * Returns the string converted to an unsigned long int using base base,
		 * which is 10 by default and must be 8 (octal), 10 (decimal) or 16 (hexa).
		 */
		unsigned long long int toULongLong ( int base = 10 ) const ;

		/**
		 * Returns the string converted to a float.
		 */
		float toFloat ( void ) const ;

		/**
		 * Returns the string converted to a double.
		 */
		double toDouble ( void ) const ;

		/**
		 * Returns the string converted to a long double.
		 */
		long double toLongDouble ( void ) const ;

		/**
		 * Convert integer to string using base base
		 * which is 10 by default and must be 8 (octal), 10 (decimal) or 16 (hexa).
		 */
		DString & setNum ( int number, int base = 10 );

		/**
		 * Convert unsigned integer to string using base base
		 * which is 10 by default and must be 8 (octal), 10 (decimal) or 16 (hexa).\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 * @return a reference to the string
		 */
		DString & setNum ( unsigned int number, int base = 10 );

		/**
		 * Convert long integer to string using base base
		 * which is 10 by default and must be 8 (octal), 10 (decimal) or 16 (hexa).\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 * @return a reference to the string
		 */
		DString & setNum ( long int number, int base = 10 );

		/**
		 * Convert unsigned long integer to string using base base
		 * which is 10 by default and must be 8 (octal), 10 (decimal) or 16 (hexa).\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 * @return a reference to the string
		 */
		DString & setNum ( unsigned long int number, int base = 10 );

		/**
		 * Convert long long integer to string using base base
		 * which is 10 by default and must be 8 (octal), 10 (decimal) or 16 (hexa).\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 * @return a reference to the string
		 */
		DString & setNum ( long long int number, int base = 10 );

		/**
		 * Convert unsigned long long integer to string using base base
		 * which is 10 by default and must be 8 (octal), 10 (decimal) or 16 (hexa).\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 * @return a reference to the string
		 */
		DString & setNum ( unsigned long long int number, int base = 10 );

		/**
		 * Convert short integer to string using base base
		 * which is 10 by default and must be 8 (octal), 10 (decimal) or 16 (hexa).\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 * @return a reference to the string
		 */
		DString & setNum ( short int number, int base = 10 );

		/**
		 * Convert unsigned short integer to string using base base
		 * which is 10 by default and must be 8 (octal), 10 (decimal) or 16 (hexa).\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 * @return a reference to the string
		 */
		DString & setNum ( unsigned short int number, int base = 10 );

		/**
		 * Convert float number to string with precision prec.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 * @return a reference to the string
		 */
		DString & setNum ( float number, int prec );

		/**
		 * Convert double number to string with precision prec.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 * @return a reference to the string
		 */
		DString & setNum ( double number, int prec );

		/**
		 * Convert long double number to string with precision prec.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 * @return a reference to the string
		 */

		DString & setNum ( long double number, int prec );
		/**
		 * Convert short integer value to binary.
		 */
		DString & toBase2 ( short int number );

		/**
		 * Convert unsigned short integer value to binary.
		 */
		DString & toBase2 ( unsigned short int number );

		/**
		 * Convert integer value to binary.
		 */
		DString & toBase2 ( int number );

		/**
		 * Convert unsigned integer value to binary.
		 */
		DString & toBase2 ( unsigned int number );

		/**
		 * Convert long integer value to binary.
		 */
		DString & toBase2 ( long int number );

		/**
		 * Convert unsigned long integer value to binary.
		 */
		DString & toBase2 ( unsigned long int number );

		/**
		 * Convert long integer value to binary.
		 */
		DString & toBase2 ( long long int number );

		/**
		 * Convert unsigned long integer value to binary.
		 */
		DString & toBase2 ( unsigned long long int number );

		/**
		 * Convert binary to a short integer value
		 */
		short int toShortBase10();

		/**
		 * Convert binary to an unsigned short integer value
		 */
		unsigned short int toUShortBase10();

		/**
		 * Convert binary to an integer value
		 */
		int toIntBase10();

		/**
		 * Convert binary to an unsigned integer value
		 */
		unsigned int toUIntBase10();

		/**
		 * Convert binary to a long integer value
		 */
		long int toLongBase10();

		/**
		 * Convert binary to an unsigned long integer value
		 */
		unsigned long int toULongBase10();

		/**
		 * Convert binary to a long integer value
		 */
		long long int toLongLongBase10();

		/**
		 * Convert binary to an unsigned long integer value
		 */
		unsigned long long int toULongLongBase10();

		/**
		 * Returns TRUE if the string is empty
		 * (which mean that length is equal to 0), false otherwise
		 */
		bool isEmpty ( void ) const;

		/**
		 * Returns the length of the string.
		 */
		unsigned int length ( void ) const;

		/**
		 * Clear the DString.
		 */
		void clear ( void );

		/**
		* Returns a substring that contains the len leftmost characters of the
		* string.\n
		* The whole string is returned if len exceeds the length of the string.
		*/
		DString left ( unsigned int len ) const;
		/**
		* Returns a substring that contains the len rightmost characters of the
		* string.
		* The whole string is returned if len exceeds the length of the string.
		*/
		DString right ( unsigned int len ) const;
		/**
		 * Returns a string that contains the len characters of this string,
		 * starting at position index.\n
		 * Returns an empty string if the string is empty or index is out of range.\n
		 * Returns the whole string from index if index + len exceeds the length
		 * of the string.
		 */
		DString mid ( unsigned int index, unsigned int len ) const;

		/**
		 * Return a standard string
		 */
		std::string toString ( void ) const;

		/**
		 * Return a C language string (const char*).
		 */
		const char* c_str ( void ) const;

		/**
		 * Returns a Dstring that contains the character at index i, or an
		 * empty string if index is beyond the length of the string.
		 */
		DString at ( unsigned int index ) const;
		/**
		 * Returns the character at index i, or 0 if i is beyond the length of the
		 * string.
		 */
		char operator [] ( unsigned int index ) const;

		/**
		 * Returns a string that has whitespace removed from the start and the end.
		 * @see #simplifyWhiteSpace
		 * @see #removeWhiteSpace
		 */
		DString stripWhiteSpace ( void ) const;

		/**
		 * Returns a string that has whitespace removed from the start and the end,
		 * and which has each sequence of internal whitespace replaced with a
		 * single space.
		 * @see #stripWhiteSpace
		 * @see #removeWhiteSpace
		 */
		DString simplifyWhiteSpace ( void ) const;

		/**
		 * Returns a string that has all whitespace removed
		 * @see #stripWhiteSpace
		 * @see #simplifyWhiteSpace
		 */
		DString removeWhiteSpace ( void ) const;

		/**
		 * Splits the string into strings standard list wherever the regular
		 * expression sep occurs, and returns the list of those strings.\n
		 * If \p allowNull is false (the default), an empty string is not pushed
		 * into the DStringList, otherwise, an empty string can be pushed into the
		 * DStringList if two separators are found without string in the middle of
		 * them.
		 */
		DStringList split ( const DString & sep, bool allowNull = false ) const;

		/**
		 * Splits the string into strings standard list wherever the \em max_size
		 * occurs (entire word only), and returns the list of those strings.\n
		 * Each size's element is equal or lower than the value of \em max_size. \n
		 */
		DStringList splitConstantSize ( const DString & sep,  unsigned int max_size );

		/**
		 * Returns a uppercase copy of the string.
		 * @see #upper
		 */
		DString upper ( void ) const;

		/**
		 * Convert string to uppercase.
		 * @see #toLower
		 */
		DString & toUpper ( void );
		
		/**
		* Returns a lowercase copy of the string.
		* @see #upper
		*/
		DString lower ( void ) const;
		
		/**
		* Convert string to string.
		* @see #toUpper
		*/
		DString & toLower ( void );

		/**
		 * Returns a string of length width that contains this string padded by the
		 * fill character.\n
		 * If the length of the string is more than width, then the returned string
		 * is a copy of the string.
		 */
		DString & leftJustify ( unsigned int width, char fill = ' ' );

		/**
		 * Returns a string of length width that contains the fill character
		 * followed by the string.\n
		 * If the length of the string is more than width, then the returned string
		 * is a copy of the string.
		 */
		DString & rightJustify ( unsigned int width, char fill = ' ' );

		/**
		 * Fill the string with length \em length c character
		 */
		DString & fill ( char c, unsigned int length );

		/**
		 * If newLen is less than the length of the string, then the string is
		 * truncated at position newLen. Otherwise nothing happens.
		 */
		DString & truncate ( unsigned int width );

		/**
		 * Returns the number of times the string \em str occurs in the string.\n
		 * If \em cs is TRUE (the default), the search is case sensitive; otherwise
		 * the search is case insensitive.
		 */
		int contains ( const DString &str, bool cs = true ) const;

		/**
		 * Returns the number of times the string str occurs in the string.\n
		 * If cs is TRUE (the default), the search is case sensitive; otherwise
		 * the search is case insensitive.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		int contains ( const char *str, bool cs = true ) const;

		/**
		 * Returns the number of times the character c occurs in the string.\n
		 * If cs is TRUE (the default), the search is case sensitive; otherwise
		 * the search is case insensitive.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		int contains ( char c, bool cs = true ) const;

		/**
		 * Returns the number of times the string str occurs in the string.\n
		 * If cs is TRUE (the default), the search is case sensitive; otherwise
		 * the search is case insensitive.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		int contains ( const std::string &str, bool cs = true ) const;

		/**
		 * Appends str to the string and returns a reference to the result.
		 */
		DString & append ( const DString &str );

		/**
		 * Appends str to the string and returns a reference to the result.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & append ( const char *str );

		/**
		 * Appends str to the string and returns a reference to the result.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & append ( const std::string &str );

		/**
		 * Appends the character c to the string and returns a reference to the
		 * string.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 * result.
		 */
		DString & append ( const char c );

		/**
		 * Inserts str at the beginning of the string and returns a reference to the
		 * string.\n
		 */
		DString & prepend ( const DString &str );

		/**
		 * Inserts str at the beginning of the string and returns a reference to the
		 * string.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & prepend ( const char *str );

		/**
		 * Inserts str at the beginning of the string and returns a reference to the
		 * string.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & prepend ( const std::string &str );

		/**
		 * Inserts the character c at the beginning of the string and returns a
		 * reference to the string.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & prepend ( const char c );

		/**
		 *Inserts the string str into the string at position index.\n
		 * If index is beyond the end of the string, the string is extended with
		 * spaces to length index and s is then appended and returns a reference to
		 * the string.
		 */
		DString & insert ( unsigned int index, const DString & str );

		/**
		 *Inserts the string str into the string at position index.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & insert ( unsigned int index, const std::string & str );

		/**
		 *Inserts the string str into the string at position index.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & insert ( unsigned int index, const char * str );

		/**
		 * Inserts the character c into the string at position index.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & insert ( unsigned int index, char c );

		/**
		 * Replaces len characters from the string with s, starting at position
		 * index, and returns a reference to the string.\n
		 * If index is beyond the length of the string, nothing is deleted and s is
		 * appended at the end of the string. If index is valid, but index + len is
		 * beyond the end of the string, the string is truncated at position index,
		 * then s is appended at the end.
		 */
		DString & replace ( unsigned int index, unsigned int len, const DString & str );

		/**
		 * Replaces len characters from the string with s, starting at position
		 * index, and returns a reference to the string.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & replace ( unsigned int index, unsigned int len, const std::string & str );

		/**
		 * Replaces len characters from the string with s, starting at position
		 * index, and returns a reference to the string.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & replace ( unsigned int index, unsigned int len, const char * str );

		/**
		 * Replaces len characters from the string with s, starting at position
		 * index, and returns a reference to the string.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & replace ( unsigned int index, unsigned int len, char c );

		/**
		 * Replaces every occurrence of the string before in the string with after.
		 * Returns a reference to the string.\n
		 * If cs is TRUE (the default), the search is case sensitive; otherwise the
		 * search is case insensitive.
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & replace ( const DString & before,
		                    const DString & after,
		                    bool cs = true );


		/**
		 * Removes len characters from the string starting at position index, and
		 * returns a reference to the string.\n
		 * If index is beyond the length of the string, nothing happens. If index
		 * is within the string, but index + len is beyond the end of the string,
		 * the string is truncated at position index.
		 */
		DString & remove ( unsigned int index, unsigned int len );

		/**
		 * Removes every occurrence of str in the string. Returns a reference to
		 * the string.\n
		 * If cs is TRUE (the default), the search is case sensitive; otherwise the
		 * search is case insensitive.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & remove ( const DString & str, bool cs = true );

		/**
		 * Removes every occurrence of str in the string. Returns a reference to
		 * the string.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & remove ( const std::string & str, bool cs = true );

		/**
		 * Removes every occurrence of str in the string. Returns a reference to
		 * the string.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & remove ( const char * str, bool cs = true );

		/**
		 * Removes every occurrence of c in the string. Returns a reference to
		 * the string.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & remove ( char c );

		/**
		 * This function returns a section of the string.\n
		 * This string is treated as a sequence of fields separated by the
		 * character, \em sep. The returned string consists of the fields from
		 * position \em start to position \em end inclusive.\n \n
		 * Fields are numbered 0, 1, 2, etc., counting from the left.\n
		 * In that case \em end must be equal or greater than \em begin. \n
		 * If \em end is not specified, all fields from position \em start to the
		 * end of the string are included.\n \n
		 * Fields are numbered -1, -2, etc., counting from right to left.\n
		 * In that case \em end must be equal or lower than \em begin. \n
		 * If \em end is not specified, all fields from the beginning  of the string
		 * to the position \em start are included.\n
		 */
		DString section ( const DString sep, int start, int end = 0xFFFFFFF ) const;

		/**
		 * Finds the first match of the string str, starting from
		 * position index.\n If index is -1, the search starts at the last character;
		 * if -2, at the next to last character and so on.\n
		 * If cs is TRUE (the default), the search is case sensitive; otherwise the
		 * search is case insensitive.
		 */
		int find ( const DString & str, int index = 0, bool cs = true ) const;

		/**
		 * Finds the first match of the string str, starting from
		 * position index.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		int find ( const std::string & str, int index = 0, bool cs = true ) const;

		/**
		 * Finds the first match of the string str, starting from
		 * position index.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		int find ( const char * str, int index = 0, bool cs = true ) const;

		/**
		 * Finds the first match of the character c, starting from
		 * position index.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		int find ( char c, int index = 0, bool cs = true ) const;

		/**
		 * Replace escape sequence char (ASCII code < 0x20) by a human readable
		 * string.\n
		 * The human readable string of an escape sequence char begin by the string
		 * \em begin and end by the string \em end.
		 */
		DString replaceEscapeSequence ( const DString & begin = "<",
										const DString & end = ">" ) const;

		/**
		 * Remove any escape sequence char (ASCII code < 0x20)
		 */
		DString removeEscapeSequence() const;

		/**
		 * Check if string contains only legal characters, defined in the list
		 * \p legalChar. \n
		 * return true if no illegal character was found, false otherwise.
		 *
		 */
		bool containsOnlyLegalChar ( const std::list<char> & legalChar ) const;

		/**
		 * Check if string contains only characters which are allowed for value
		 * on base \p base. \n
		 * The case is sensitive and can be set by the \p caseflag flag.
		 */
		bool containsOnlyLegalChar ( BaseFlag base, CaseFlag caseflag = BOTHCASE ) const;

		/**
		* Convert timestamp (time_t) t to a human readable string formated as
		* desired.\n
		* The default is database format (%Y-%m-%d %H-%M-%S).\n
		* Get the current date in string is easy because it's a static method, so no
		* object must be constructed, just type :\n
		* DString::timeToStr(time(NULL), "%d/%m/%Y %H-%M-%S")\n \n
		* Here is the complete list of available parameters :
		* - \%a The abbreviated weekday name according to the current locale.
		* - \%A The full weekday name according to the current locale.
		* - \%b The abbreviated month name according to the current locale.
		* - \%B The full month name according to the current locale.
		* - \%c The preferred date and time representation for the current locale.
		* - \%C The century number (year/100) as a 2-digit integer. (SU)
		* - \%d The day of the month as a decimal number (range 01 to 31).
		* - \%D Equivalent to %m/%d/%y. (Yecch -- for Americans only. Americans
		* should note that in other countries %d/%m/%y is rather common. This means
		* that in international context this format is ambiguous and should not be
		* used.) (SU)
		* - \%e Like %d, the day of the month as a decimal number, but a leading
		* zero is replaced by a space. (SU)
		* - \%E Modifier: use alternative format, see below. (SU)
		* - \%F Equivalent to %Y-%m-%d (the ISO 8601 date format). (C99)
		* - \%G The ISO 8601 year with century as a decimal number. The 4-digit year
		* corresponding to the ISO week number (see %V). This has the same format
		* and value as %y, except that if the ISO week number belongs to the
		* previous or next year, that year is used instead. (TZ)
		* - \%g Like %G, but without century, i.e., with a 2-digit year (00-99).(TZ)
		* - \%h Equivalent to %b. (SU)
		* - \%H The hour as a decimal number using a 24-hour clock (range 00 to 23).
		* - \%I The hour as a decimal number using a 12-hour clock (range 01 to 12).
		* - \%j The day of the year as a decimal number (range 001 to 366).
		* - \%k The hour (24-hour clock) as a decimal number (range 0 to 23); single
		* digits are preceded by a blank. (See also %H.) (TZ)
		* - \%l The hour (12-hour clock) as a decimal number (range 1 to 12); single
		* digits are preceded by a blank. (See also %I.) (TZ)
		* - \%m The month as a decimal number (range 01 to 12).
		* - \%M The minute as a decimal number (range 00 to 59).
		* - \%n A newline character. (SU)
		* - \%O Modifier: use alternative format, see below. (SU)
		* - \%p Either 'AM' or 'PM' according to the given time value, or the
		* corresponding strings for the current locale. Noon is treated as 'pm' and
		* midnight as 'am'.
		* - \%P Like %p but in lowercase: 'am' or 'pm' or a corresponding string for
		* the current locale. (GNU)
		* - \%r The time in a.m. or p.m. notation. In the POSIX locale this is
		* equivalent to '%I:%M:%S %p'. (SU)
		* - \%R The time in 24-hour notation (%H:%M). (SU) For a version including
		* the seconds, see %T below.
		* - \%s The number of seconds since the Epoch, i.e.,
		* since 1970-01-01 00:00:00 UTC. (TZ)
		* - \%S The second as a decimal number (range 00 to 60). (The range is up to
		* 60 to allow for occasional leap seconds.)
		* - \%t A tab character. (SU)
		* - \%T The time in 24-hour notation (%H:%M:%S). (SU)
		* - \%u The day of the week as a decimal, range 1 to 7, Monday being 1.
		* See also %w. (SU)
		* - \%U The week number of the current year as a decimal number,
		* range 00 to 53, starting with the first Sunday as the first day of week 01.
		* See also %V and %W.
		* - \%V The ISO 8601:1988 week number of the current year as a decimal
		* number, range 01 to 53, where week 1 is the first week that has at least
		* 4 days in the current year, and with Monday as the first day of the week.
		* See also %U and %W. (SU)
		* - \%w The day of the week as a decimal, range 0 to 6, Sunday being 0.
		* See also %u.
		* - \%W The week number of the current year as a decimal number,
		* range 00 to 53,
		* starting with the first Monday as the first day of week 01.
		* - \%x The preferred date representation for the current locale without
		* the time.
		* - \%X The preferred time representation for the current locale without the
		* date.
		* - \%y The year as a decimal number without a century (range 00 to 99).
		* - \%Y The year as a decimal number including the century.
		* - \%z The time-zone as hour offset from GMT. Required to emit RFC
		* 822-conformant dates (using "%a, %d %b %Y %H:%M:%S %z"). (GNU)
		* - \%Z The time zone or name or abbreviation.
		* - \%+ The date and time in date(1) format. (TZ) (Not supported in glibc2.)
		* - \%% A literal '%' character.
		*/
		static DString timeToString ( const time_t & t,
		                              DString format = DString( "%Y-%m-%d %H:%M:%S" ) );

		/**
		 * Convert timestamp (time_t) t to a human readable string in ISO 8601
		 * extended format.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		static DString timeToString ( const time_t & t, DateFormat format );

		/**
		 * Convert current time to a human readable string formated as
		 * desired.\n
		 */
		static DString Now ( const char * format = "%Y-%m-%d %H-%M-%S" );
		/**
		 * Convert current time to a human readable string in ISO 8601
		 * extended format.\n
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		static DString Now ( DateFormat format );

		/**
		 * Convert time in a human readable string formated with \p oldformat to
		 * another string formated with \p newformat.
		 * \see #timeToString for format string.
		 */
		DString & convertTime ( const char * oldformat,
		                        const char * newformat = "%Y-%m-%d %H-%M-%S" );


		/**
		 * Convert time in a human readable string formated with \p oldformat to
		 * another string formated with \p newformat.
		 * This is an overloaded member function, provided for convenience.
		 * It behaves essentially like the above function.
		 */
		DString & convertTime ( DateFormat oldformat, DateFormat newformat );

		/**
		 * Return an empty string
		 */
		static DString empty();

		/**
		 * Get string format from \p format
		 */
		static const char * getFormat ( DateFormat format );

	private:
		std::string m_str;
		/**
		 * Return a list of char allowed in a binary string
		 */
		std::list<char> & onlyBinary() const;

		/**
		 * Return a list of char allowed in a binary string
		 */
		std::list<char> & onlyOctal() const;

		/**
		 * Return a list of  char allowed in a decimal string
		 */
		std::list<char> & onlyDecimal() const;

		/**
		 * Return a list of char allowed in a hexa string
		 */
		std::list<char> & onlyHexa ( CaseFlag caseflag = BOTHCASE ) const;
};

/**
 * @relates DString
 * Extracts characters from \p stream and stores them into \p content
 * until a delimitation character is found. The extraction also stops if
 * the end of file is reached in \p stream or if some other error occurs during
 * the input operation.
 */
std::istream & getline ( std::istream & stream, DString & content, char delim = '\n' );

#endif // DSTRING_H
