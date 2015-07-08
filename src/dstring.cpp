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
 *     (___)_)   File : dstring.cpp                         ||--|| *          *
 *                                                                            *
 *   This program is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU General Public License as published by     *
 *   the Free Software Foundation; either version 3 of the License, or        *
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
 ******************************************************************************/


#include "dstring.h"
#include <stdint.h>
#include <utf8.h>
#include <pcrecpp.h>

//The matching interface supports at most 16 arguments per call
#define PCRE_MAX_ARGS 16

DString::DString()
{
	m_str = "";
}

DString::DString ( const std::string & str )
{
	m_str = str;
}

DString::DString ( const char *str )
{
	m_str = str;
}

DString::DString ( char c )
{
	m_str = c;
}

DString::~DString()
{
}

////////////////////////////////////////////////////////////////////////////////
//                             Number operations                              //
////////////////////////////////////////////////////////////////////////////////

short int DString::toShort ( int base ) const
{
	short int Value = 0;

	Value = strToValue ( Value, m_str, base );
	return Value;
}

unsigned short int DString::toUShort ( int base ) const
{
	unsigned short int Value = 0;

	Value = strToValue ( Value, m_str, base );
	return Value;
}

int DString::toInt ( int base ) const
{
	int Value = 0;

	Value = strToValue ( Value, m_str, base );
	return Value;
}

unsigned int DString::toUInt ( int base ) const
{
	unsigned int Value = 0;

	Value = strToValue ( Value, m_str, base );
	return Value;
}

long DString::toLong ( int base ) const
{
	long Value = 0;

	Value = strToValue ( Value, m_str, base );
	return Value;
}

unsigned long DString::toULong ( int base ) const
{
	unsigned long Value = 0;

	Value = strToValue ( Value, m_str, base );
	return Value;
}

long long int DString::toLongLong ( int base ) const
{
	long long int Value = 0;

	Value = strToValue ( Value, m_str, base );
	return Value;
}

unsigned long long int DString::toULongLong ( int base ) const
{
	unsigned long long int Value = 0;

	Value = strToValue ( Value, m_str, base );
	return Value;
}

float DString::toFloat() const
{
	float Value = 0;

	Value = strToValue ( Value, m_str, 10 );
	return Value;
}

double DString::toDouble() const
{
	double Value = 0;

	Value = strToValue ( Value, m_str, 10 );
	return Value;
}

long double DString::toLongDouble() const
{
	long double Value = 0;

	Value = strToValue ( Value, m_str, 10 );
	return Value;
}

DString & DString::setNum ( int number, int base )
{
	m_str = valueToStr ( number, base, -1 );
	return *this;
}

DString & DString::setNum ( unsigned int number, int base )
{
	m_str = valueToStr ( number, base, -1 );
	return *this;
}

DString & DString::setNum ( long int number, int base )
{
	m_str = valueToStr ( number, base, -1 );
	return *this;
}

DString & DString::setNum ( unsigned long int number, int base )
{
	m_str = valueToStr ( number, base, -1 );
	return *this;
}

DString & DString::setNum ( long long int number, int base )
{
	m_str = valueToStr ( number, base, -1 );
	return *this;
}

DString & DString::setNum ( unsigned long long int number, int base )
{
	m_str = valueToStr ( number, base, -1 );
	return *this;
}

DString & DString::setNum ( short int number, int base )
{
	m_str = valueToStr ( number, base, -1 );
	return *this;
}

DString & DString::setNum ( unsigned short int number, int base )
{
	m_str = valueToStr ( number, base, -1 );
	return *this;
}

DString & DString::setNum ( float number, int prec )
{
	this->m_str = valueToStr ( number, 10, prec );
	return *this;
}

DString & DString::setNum ( double number, int prec )
{
	this->m_str = valueToStr ( number, 10, prec );
	return *this;
}

DString & DString::setNum ( long double number, int prec )
{
	this->m_str = valueToStr ( number, 10, prec );
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
//                             Others operations                              //
////////////////////////////////////////////////////////////////////////////////

bool DString::isEmpty() const
{
	if ( m_str.length() == 0 )
	{
		return true;
	}
	return false;
}

void DString::clear()
{
	this->m_str.clear();
}

unsigned int DString::length() const
{
	return m_str.length();
}

////////////////////////////////////////////////////////////////////////////////
//                                Operators                                   //
////////////////////////////////////////////////////////////////////////////////
DString & DString::operator = ( const DString & str )
{
	m_str = str.m_str;
	return *this;
}

DString & DString::operator = ( const std::string & str )
{
	m_str = str;
	return *this;
}

DString & DString::operator = ( const char *str )
{
	m_str = str;
	return *this;
}

DString & DString::operator = ( char c )
{
	m_str = c;
	return *this;
}

const DString & DString::operator += ( const DString & str )
{
	m_str += str.m_str;
	return *this;
}

const DString & DString::operator += ( const std::string & str )
{
	m_str += str;
	return *this;
}

const DString & DString::operator += ( const char * str )
{
	m_str += str;
	return *this;
}

const DString & DString::operator += ( char c )
{
	m_str += c;
	return *this;
}

const DString operator + ( const DString & str1, const DString & str2 )
{
	DString str;

	str.m_str = str1.m_str + str2.m_str;

	return str;
}

const DString operator + ( const DString & str1, const std::string & str2 )
{
	DString str;
	DString buffer ( str2 );

	str.m_str = str1.m_str + buffer.m_str;

	return str;
}

const DString operator + ( const DString & str1, const char * str2 )
{
	DString str;
	DString buffer ( str2 );

	str.m_str = str1.m_str + buffer.m_str;

	return str;
}

const DString operator + ( const DString & str1, char c )
{
	DString str;
	DString buffer ( c );

	str.m_str = str1.m_str + buffer.m_str;

	return str;
}

const DString operator + ( const std::string & str1, const DString & str2 )
{
	DString str;
	DString buffer ( str1 );

	str.m_str = buffer.m_str + str2.m_str;

	return str;
}

const DString operator + ( const char * str1, const DString & str2 )
{
	DString str;
	DString buffer ( str1 );

	str.m_str = buffer.m_str + str2.m_str;

	return str;
}

const DString operator + ( char c, const DString & str1 )
{
	DString str;
	DString buffer ( c );

	str.m_str = buffer.m_str + str1.m_str;

	return str;
}

bool operator == ( const DString & str1, const DString & str2 )
{
	if ( str1.m_str == str2.m_str )
	{
		return true;
	}
	return false;
}

bool operator == ( const DString & str1, const std::string & str2 )
{
	if ( str1.m_str == str2 )
	{
		return true;
	}
	return false;
}

bool operator == ( const DString & str1, const char * str2 )
{
	if ( str1.m_str == str2 )
	{
		return true;
	}
	return false;
}

bool operator == ( const std::string & str1, const DString & str2 )
{
	if ( str1 == str2.m_str )
	{
		return true;
	}
	return false;
}

bool operator == ( const char * str1, const DString & str2 )
{
	if ( str1 == str2.m_str )
	{
		return true;
	}
	return false;
}

bool operator != ( const DString & str1, const DString & str2 )
{
	if ( str1.m_str != str2.m_str )
	{
		return true;
	}
	return false;
}

bool operator != ( const DString & str1, const std::string & str2 )
{
	if ( str1.m_str != str2 )
	{
		return true;
	}
	return false;
}

bool operator != ( const DString & str1, const char * str2 )
{
	if ( str1.m_str != str2 )
	{
		return true;
	}
	return false;
}

bool operator != ( const std::string & str1, const DString & str2 )
{
	if ( str1 != str2.m_str )
	{
		return true;
	}
	return false;
}

bool operator != ( const char * str1, const DString & str2 )
{
	if ( str1 != str2.m_str )
	{
		return true;
	}
	return false;
}

bool operator < ( const DString & str1, const DString & str2 )
{
	return str1.m_str < str2.m_str;
}

bool operator > ( const DString & str1, const DString & str2 )
{
	return str1.m_str > str2.m_str;
}

bool operator <= ( const DString & str1, const DString & str2 )
{
	return str1.m_str <= str2.m_str;
}

bool operator >= ( const DString & str1, const DString & str2 )
{
	return str1.m_str >= str2.m_str;
}

std::ostream& operator << ( std::ostream& s, const DString & str )
{
	s << str.m_str;
	return s;
}

std::istream& operator >> ( std::istream& s, DString & str )
{
	s >> str.m_str;
	return s;
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

DString DString::left ( unsigned int len ) const
{
	std::string str = "";

	if ( len >= m_str.length() )
	{
		str = m_str;
		return str;
	}
	if ( !isEmpty() )
	{
		str = m_str.substr ( 0, len );
	}
	return str;
}

DString DString::right ( unsigned int len ) const
{
	std::string str = "";

	if ( len >= m_str.length() )
	{
		str = m_str;
		return str;
	}
	if ( ! isEmpty() )
	{
		str = m_str.substr ( ( m_str.length() - len ), len );
	}
	return str;
}

DString DString::mid ( unsigned int index, unsigned int len ) const
{
	std::string str = "";

	if ( ( index + len ) >= m_str.length() )
	{
		if ( index < m_str.length() )
		{
			str = m_str.substr ( index, ( m_str.length() - index ) );
		}
		return str;
	}
	if ( ( ! isEmpty() ) && ( index < m_str.length() ) )
	{
		str = m_str.substr ( ( 0 + index ), len );
	}
	return str;
}

std::string DString::toString() const
{
	return m_str;
}

const char* DString::c_str() const
{
	return m_str.c_str();
}

DString DString::at ( unsigned int index ) const
{
	DString str;

	if ( index < m_str.length() )
	{
		str = m_str.substr ( index, 1 );
	}
	else
	{
		str = "";
	}
	return str;
}

char DString::operator [] ( unsigned int index ) const
{
	char c;

	if ( index < m_str.length() )
	{
		c = m_str[index];
	}
	else
	{
		c = 0;
	}
	return c;
}

DString DString::stripWhiteSpace() const
{
	unsigned int uiIte1, uiIte2;
	std::string str;

	// remove spaces at the beginning
	uiIte1=0;
	while ( m_str[uiIte1] <= 0x20 && uiIte1 < m_str.length() )
	{
		uiIte1++;
	}
	// remove spaces at the end
	uiIte2 = m_str.length();
	while ( ( m_str[uiIte2] <= 0x20 ) && ( uiIte2 > uiIte1 ) )
	{
		uiIte2--;
	}
	str = m_str.substr ( uiIte1, ( ( uiIte2 + 1 )- uiIte1 ) );
	return DString ( str );
}

DString DString::simplifyWhiteSpace() const
{
	std::string str, buffer;
	unsigned int uiIte1;
	bool first;

	str = "";
	first = true;
	buffer = stripWhiteSpace().toString();
	// Let only one space in the middle, but remove \t and so on
	for ( uiIte1 = 0 ; uiIte1 < buffer.length() ; uiIte1++ )
	{
		if ( buffer[uiIte1] <= 0x20 )
		{
			if ( first )
			{
				str += " ";
			}
			first = false;
		}
		else
		{
			str += buffer[uiIte1];
			first = true;
		}
	}
	return DString ( str );
}

DString DString::removeWhiteSpace ( void ) const
{
	DString buffer ( m_str );

	buffer = buffer.simplifyWhiteSpace();
	buffer.remove ( " " );
	return buffer;
}

std::list<DString> DString::splitConstantSize ( const DString & sep, unsigned int max_size )
{
	std::list<DString> tmplist;
	std::list<DString> returnedlist;
	std::list<DString>::iterator ite;
	DString str;
	DString buffer;
	bool reached = false;

	tmplist = split ( sep );
	ite = tmplist.begin();
	while ( ite != tmplist.end() )
	{
		str = *ite;
		ite++;
		buffer.clear();
		if ( str.length() > max_size )
		{
			reached = true;
		}
		else
		{
			reached = false;
		}
		while ( !reached && ite != tmplist.end() )
		{
			buffer = " ";
			buffer += *ite;
			if ( ( str.length() + buffer.length() ) <= max_size )
			{
				str += buffer;
				ite++;
			}
			else
			{
				reached = true;
			}
		}
		returnedlist.push_back ( str );
	}
	return returnedlist;
}

DStringList DString::split ( const DString & sep, bool allowNull ) const
{
	DString buffer;
	std::list<DString> liststr;
	std::string::size_type pos1 = 0, pos2 = 0;

	pos1 = m_str.find ( sep.c_str(), pos1 );
	if ( pos1 != std::string::npos )
	{
		buffer = m_str.substr ( 0, pos1 );
		if ( buffer.isEmpty() )
		{
			if ( allowNull )
			{
				liststr.push_back ( "" );
			}
		}
		else
		{
			liststr.push_back ( buffer );
		}
		while ( pos1 != std::string::npos )
		{
			pos1 = m_str.find ( sep.c_str(), pos1 );
			pos2 = m_str.find ( sep.c_str(), pos1 + 1 );
			if ( pos1 != std::string::npos )
			{
				if ( pos2 != std::string::npos )
				{
					buffer = m_str.substr ( pos1 + sep.length(), pos2 - pos1 - sep.length() );
				}
				else
				{
					buffer =
					    m_str.substr ( pos1 + sep.length(), m_str.length() - pos1 );
				}
				pos1 = pos2;
				if ( buffer.isEmpty() )
				{
					if ( allowNull )
					{
						liststr.push_back ( "" );
					}
				}
				else
				{
					liststr.push_back ( buffer );
				}
			}
		}
	}
	else
	{
		buffer = m_str;
		liststr.push_back ( buffer );
	}
	return liststr;
}

DString & DString::toLower()
{
	*this = this->lower();
	return *this;
}

DString DString::lower() const
{
	std::string buffer = m_str;
	
	for ( unsigned int i = 0 ; i < buffer.length() ; i++ )
	{
		if ( buffer[i] >= 0x41 && buffer[i] <= 0x5A )
		{
			buffer[i] += 0x20;
		}
	}
	return buffer;
}

DString & DString::toUpper()
{
	*this = this->upper();
	return *this;
}

DString DString::upper() const
{
	std::string buffer = m_str;
	
	for ( unsigned int i = 0 ; i < buffer.length() ; i++ )
	{
		if ( buffer[i] >= 0x61 && buffer[i] <= 0x7A )
		{
			buffer[i] -= 0x20;
		}
	}
	return buffer;
}

DString & DString::leftJustify ( unsigned int width, char fill )
{
	unsigned int i;

	for ( i = m_str.length() ; i < width ; i++ )
	{
		m_str = m_str + fill;
	}

	return *this;
}

DString & DString::rightJustify ( unsigned int width, char fill )
{
	unsigned int i = m_str.length();

	for ( ; i < width ; i++ )
	{
		m_str = fill + m_str;
	}

	return *this;
}

DString & DString::truncate ( unsigned int width )
{
	if ( width < m_str.length() )
	{
		m_str.resize ( width );
	}
	return *this;
}

DString & DString::fill ( char c, unsigned int length )
{
	for ( unsigned int i = 0 ; i < length ; i++ )
	{
		m_str += c;
	}
	return *this;
}

int DString::contains ( char c, bool cs ) const
{
	DString buffer ( c );

	return contains ( buffer, cs );
}

int DString::contains ( const std::string &str, bool cs ) const
{
	DString buffer ( str );

	return contains ( buffer, cs );
}

int DString::contains ( const char *str, bool cs ) const
{
	DString buffer ( str );

	return contains ( buffer, cs );
}

int DString::contains ( const DString &str, bool cs ) const
{
	std::string::size_type pos1 = 0, pos2 = 1;
	int nb = 0;
	DString buffer = this->m_str;
	DString occur = str;

	if ( this->m_str.length() == 0 )
	{
		return 0;
	}

	if ( !cs )
	{
		buffer.toLower();
		occur.toLower();
	}

	if ( buffer.left( occur.length() ) == occur )
	{
		nb++;
	}

	while ( pos1 != std::string::npos )
	{
		pos2 = buffer.toString().find ( occur.toString(), pos1 + 1 );
		pos1 = pos2;
		if ( pos2 != std::string::npos )
		{
			nb++;
		}
	}
	return nb;
}

DString & DString::append ( const DString & str )
{
	this->m_str += str.m_str;
	return *this;
}

DString & DString::append ( const char *str )
{
	DString buffer ( str );

	append ( buffer );
	return *this;
}

DString & DString::append ( const std::string &str )
{
	DString buffer ( str );

	append ( buffer );
	return *this;
}

DString & DString::append ( const char c )
{
	DString buffer ( c );

	append ( buffer );
	return *this;
}

DString & DString::prepend ( const DString & str )
{
	this->m_str = str.m_str + this->m_str;
	return *this;
}

DString & DString::prepend ( const char *str )
{
	DString buffer ( str );

	prepend ( buffer );
	return *this;
}

DString & DString::prepend ( const std::string &str )
{
	DString buffer ( str );

	prepend ( buffer );
	return *this;
}

DString & DString::prepend ( const char c )
{
	DString buffer ( c );

	prepend ( buffer );
	return *this;
}

DString & DString::insert ( unsigned int index, const DString & str )
{
	DString buffer = str;

	while ( index > m_str.length() )
	{
		m_str += " ";
	}
	m_str.insert ( index, buffer.toString() );
	return *this;
}

DString & DString::insert ( unsigned int index, const std::string & str )
{
	DString buffer ( str );
	insert ( index, buffer );
	return *this;
}

DString & DString::insert ( unsigned int index, const char * str )
{
	DString buffer ( str );
	insert ( index, buffer );
	return *this;
}

DString & DString::insert ( unsigned int index, char c )
{
	DString buffer ( c );
	insert ( index, buffer );
	return *this;
}

DString & DString::replace ( unsigned int index, unsigned int len, const DString & str )
{
	while ( index > m_str.length() )
	{
		m_str += " ";
	}
	m_str.replace ( index, len, str.toString() );
	return *this;
}

DString & DString::replace ( unsigned int index, unsigned int len, const std::string & str )
{
	DString buffer ( str );
	replace ( index, len, buffer );
	return *this;
}

DString & DString::replace ( unsigned int index, unsigned int len, const char * str )
{
	DString buffer ( str );
	replace ( index, len, buffer );
	return *this;
}

DString & DString::replace ( unsigned int index, unsigned int len, char c )
{
	DString buffer ( c );
	replace ( index, len, buffer );
	return *this;
}

DString & DString::replace ( const DString & before,
                             const DString & after,
                             bool cs )
{
	DString buffer ( m_str );
	DString target ( before );
	int index = 0;

	if ( !cs )
	{
		buffer.toLower();
		target.toLower();
	}

	while ( index >= 0 )
	{
		index = buffer.find ( target, index, cs );
		if ( index >= 0 )
		{
			replace ( index, target.length(), after );
			index += after.length();
		}
	}

	return *this;
}

int DString::find ( const DString & str, int index, bool cs ) const
{
	DString buf1 ( m_str );
	DString buf2 ( str );
	std::string::size_type pos;
	int occur = 0;

	if ( !cs )
	{
		buf1.toLower();
		buf2.toLower();
	}

	if ( index < 0 )
	{
		pos = buf1.toString().rfind ( buf2.toString(), index );
	}
	else
	{
		pos = buf1.toString().find ( buf2.toString(), index );
	}
	if ( pos == std::string::npos )
	{
		occur = -1;
	}
	else
	{
		occur = pos;
	}
	return occur;
}

int DString::find ( const std::string & str, int index, bool cs ) const
{
	DString buffer ( str );

	return ( find ( buffer, index, cs ) );
}

int DString::find ( const char * str, int index, bool cs ) const
{
	DString buffer ( str );

	return ( find ( buffer, index, cs ) );
}

int DString::find ( char c, int index, bool cs ) const
{
	DString buffer ( c );

	return ( find ( buffer, index, cs ) );
}

DString & DString::remove ( unsigned int index, unsigned int len )
{
	if ( index >= m_str.length() )
	{
		return *this;
	}
	while ( m_str.length() < ( index + len ) )
	{
		m_str += ' ';
	}
	m_str.erase ( index, len );
	return *this;
}

DString & DString::remove ( const DString & str, bool cs )
{
	DString buffer ( str );
	int index = 0;

	if ( !cs )
	{
		buffer.toLower();
	}

	do
	{
		index = find ( buffer, 0, cs );
		if ( index >= 0 )
		{
			remove ( index, buffer.toString().length() );
		}
	}
	while ( index >= 0 );

	return *this;
}
DString & DString::remove ( const std::string & str, bool cs )
{
	DString buffer ( str );
	remove ( buffer, cs );
	return *this;
}

DString & DString::remove ( const char * str, bool cs )
{
	DString buffer ( str );
	remove ( buffer, cs );
	return *this;
}

DString & DString::remove ( char c )
{
	DString buffer ( c );
	remove ( buffer, true );
	return *this;
}

DString DString::section ( const DString sep, int start, int end ) const
{
	DStringList liststr;
	DStringList::iterator ite;
	std::list<DString>::reverse_iterator rite;
	DString buffer = "";
	int i = 0;

	liststr = split ( sep );

	// begin on the left
	if ( ( start >= 0 ) && ( end >= start ) )
	{
		ite = liststr.begin();
		if ( ite != liststr.end() )
		{
			for ( i = 0 ; i < start ; i++ )
			{
				ite++;
				if ( ite == liststr.end() )
				{
					break;
				}
			}
			while ( i <= end && ite != liststr.end() )
			{
				buffer += *ite;
				ite++;
				i++;
				if ( ite != liststr.end() && i <= end )
				{
					buffer += sep;
				}
			}
		}
	}
	// begin on the right
	else if ( ( start < 0 ) && ( ( end <= start ) || ( end == 0xFFFFFFF ) ) )
	{
		rite = liststr.rbegin();
		if ( rite != liststr.rend() )
		{
			for ( i = 1 ; i < static_cast<int> ( std::abs ( static_cast<double> ( start ) ) ) ; i++ )
			{
				rite++;
				if ( rite == liststr.rend() )
				{
					break;
				}
			}
			while ( i <= static_cast<int> ( std::abs ( static_cast<double> ( end ) ) ) && rite != liststr.rend() )
			{
				buffer.prepend ( *rite );
				rite++;
				i++;
				if ( rite != liststr.rend() && i <= static_cast<int> ( std::abs ( static_cast<double> ( end ) ) ) )
				{
					buffer.prepend ( sep );
				}
			}
		}
	}

	return buffer;
}

DString & DString::assign( const std::istreambuf_iterator<char> & first, const std::istreambuf_iterator<char> & last )
{
	m_str.assign( first, last );
	return *this;
}

DString DString::timeToString ( const time_t & t, DString format )
{
	char buffer[80];
	DString date;
	struct tm *stm = 0;
	
	// Get local time
	stm = localtime ( &t );
	if ( ! stm ) return date;
	mktime( stm );
	//translate format's time and writting on buffer
	strftime ( buffer, sizeof( buffer ), format.c_str(), stm );
	date = buffer;
	
	return date;
}

DString DString::timeToString ( const time_t & t, DateFormat format )
{
	return timeToString ( t, getFormat ( format ) );
}

DString DString::Now ( const DString & format )
{
	return timeToString ( time ( NULL ), format.c_str() );
}

DString DString::Now ( DateFormat format )
{
	return timeToString ( time ( NULL ), getFormat ( format ) );
}

DString & DString::convertTime ( const DString & oldformat,
                                 const DString & newformat )
{
	//char *strptime(const char *buf, const char *format, struct tm *tm);
	struct tm stm;
	char buffer[80];

	// Get local time
	strptime ( m_str.c_str(), oldformat.c_str(), &stm );
	size_t t = strftime ( buffer, sizeof ( buffer ), newformat.c_str(), &stm );
	if ( t )
	{
		m_str = buffer;
	}

	return *this;
}

DString DString::empty()
{
	DString buffer ( "" );
	return buffer;
}

DString & DString::toBase2 ( int number )
{
	m_str = decTobin ( number );
	return *this;
}

DString & DString::toBase2 ( unsigned int number )
{
	m_str = decTobin ( number );
	return *this;
}


DString & DString::toBase2 ( short int number )
{
	m_str = decTobin ( number );
	return *this;
}


DString & DString::toBase2 ( unsigned short int number )
{
	m_str = decTobin ( number );
	return *this;
}

DString & DString::toBase2 ( long int number )
{
	m_str = decTobin ( number );
	return *this;
}

DString & DString::toBase2 ( unsigned long int number )
{
	m_str = decTobin ( number );
	return *this;
}

DString & DString::toBase2 ( long long int number )
{
	m_str = decTobin ( number );
	return *this;
}

DString & DString::toBase2 ( unsigned long long int number )
{
	m_str = decTobin ( number );
	return *this;
}

short int DString::toShortBase10()
{
	return static_cast<short int> ( binToDec ( m_str ) );
}

unsigned short int DString::toUShortBase10()
{
	return static_cast<unsigned short int> ( binToDec ( m_str ) );
}

int DString::toIntBase10()
{
	return static_cast<int> ( binToDec ( m_str ) );
}

unsigned int DString::toUIntBase10()
{
	return static_cast<unsigned int> ( binToDec ( m_str ) );
}

long int DString::toLongBase10()
{
	return static_cast<long int> ( binToDec ( m_str ) );
}


unsigned long int DString::toULongBase10()
{
	return static_cast<unsigned long int> ( binToDec ( m_str ) );
}

long long int DString::toLongLongBase10()
{
	return static_cast<long long int> ( binToDec ( m_str ) );
}


long long unsigned int DString::toULongLongBase10()
{
	return static_cast<unsigned long long int> ( binToDec ( m_str ) );
}

DString DString::removeEscapeSequence() const
{
	unsigned int i;
	DString withoutEscape;

	for ( i=0 ; i < m_str.length() ; i++ )
	{
		if ( m_str[i] == 0x0A )
		{
			withoutEscape += "\n";
		}
		if ( m_str[i] == 0x0D )
		{
			withoutEscape += "\n";
		}
		if ( m_str[i] >= 0x20 )
		{
			withoutEscape += m_str[i];
		}
	}
	return withoutEscape;
}

std::string & DString::getReference()
{
	return m_str;
}

DString DString::toHTML() const
{
	DString quoted;
	DString buffer;
	
	char * str = const_cast<char *>( m_str.c_str() ); // utf-8 string
    char * str_i = str;                               // string iterator
    char * end = str + strlen( str ) + 1;             // end iterator

	do
	{
		uint32_t code = utf8::next( str_i, end ); // get 32 bit code of a utf-8 symbol
		if ( ( code == 0 ) || ( code >= 0x7F && code <= 0x9F ) )
		{
			continue;
		}
		if ( ( code == 0x20 ) ||
			 ( code >= 0x30 && code <= 0x39 ) ||
			 ( code >= 0x41 && code <= 0x5a ) ||
			 ( code >= 0x61 && code <= 0x7a ) )
		{
			quoted += code;
			continue;
		}
		buffer.setNum( static_cast<int>( code ) );
		buffer.prepend( "&#" );
		buffer.append( ";" );
		quoted += buffer;
	}
	while ( str_i < end );
	
	return quoted;
}

DString DString::toQuotedPrintable() const
{
	DString quoted;
	DString buffer;
	
	char * str = const_cast<char *>( m_str.c_str() ); // utf-8 string
    char * str_i = str;                               // string iterator
    char * end = str + strlen( str ) + 1;             // end iterator

	do
	{
		uint32_t code = utf8::next( str_i, end ); // get 32 bit code of a utf-8 symbol
		if ( code == 0 )
		{
			continue;
		}
		// ISO 8859-15 additions ( modify from ISO 8859-1 )
		if ( code == 0x20AC )
		{
			quoted += "=E2=82=AC";
			continue;
		}
		if ( code == 0x160 )
		{
			quoted += "=C5=A0";
			continue;
		}
		if ( code == 0x161 )
		{
			quoted += "=C5=A1";
			continue;
		}
		if ( code == 0x17d )
		{
			quoted += "=C5=BD";
			continue;
		}
		if ( code == 0x17e )
		{
			quoted += "=C5=BE";
			continue;
		}
		if ( code == 0x152 )
		{
			quoted += "=C5=92";
			continue;
		}
		if ( code == 0x153 )
		{
			quoted += "=C5=93";
			continue;
		}
		if ( code == 0x178 )
		{
			quoted += "=C5=B8";
			continue;
		}
		if ( code >= 0xa0 && code < 0xc0 )
		{
			buffer.setNum( static_cast<int>( code ), 16 ).toUpper();
			buffer.prepend( "=C2=" );
			quoted += buffer;
			continue;
		}
		if ( code >= 0xc0 )
		{
			uint32_t code2 = code & 0xBF;
			buffer.setNum( static_cast<int>( code2 ), 16 ).toUpper();
			buffer.prepend( "=C3=" );
			quoted += buffer;
			continue;
		}
		quoted += code;
	}
	while ( str_i < end );
	
	return quoted;
}

void DString::fromQuotedPrintable( const DString & str )
{
	// TODO implement utf-8 and iso8859-1*
	unsigned int i = 0;
	DString buffer;
	uint32_t value;
	
	m_str.clear();
	while ( i < str.length() ) {
		buffer.clear();
		if ( str[i] == '=' ) {
			while ( str[i] == '=' ) {
				buffer += str.mid( i, 3 );
				i = i + 3;
			}
			buffer = buffer.toUpper().remove( "=" );
			if ( buffer.length() == 2 ) {
				value = static_cast<uint32_t>( buffer.toUInt( 16 ) );
				//value += 0xC340;
			}
			else if ( buffer == "E282AC" ) {
				value = 0x20AC;
			}
			else if ( buffer == "C5A0" ) {
				value = 0x160;
			}
			else if ( buffer == "C5A1" ) {
				value = 0x161;
			}
			else if ( buffer == "C5BD" ) {
				value = 0x17d;
			}
			else if ( buffer == "C5BE" ) {
				value = 0x17e;
			}
			else if ( buffer == "C592" ) {
				value = 0x152;
			}
			else if ( buffer == "C593" ) {
				value = 0x153;
			}
			else if ( buffer == "C5B8" ) {
				value = 0x178;
			}
			else if ( buffer.left( 2 ) == "C2" ) {
				std::cout << buffer << std::endl;
				value = static_cast<uint32_t>( buffer.right(2).toUInt( 16 ) );
			}
			else if ( buffer.left( 2 ) == "C3" ) {
				value = static_cast<uint32_t>( buffer.right(2).toUInt( 16 ) );
				value += 0x40;
			}
			
			if (value <= 0x7f)
			{
				m_str.append(1, static_cast<char>(value));
			}
			else if (value <= 0x7ff)
			{
				m_str.append(1, static_cast<char>(0xc0 | ((value >> 6) & 0x1f)));
				m_str.append(1, static_cast<char>(0x80 | (value & 0x3f)));
			}
			else if (value <= 0xffff)
			{
				m_str.append(1, static_cast<char>(0xe0 | ((value >> 12) & 0x0f)));
				m_str.append(1, static_cast<char>(0x80 | ((value >> 6) & 0x3f)));
				m_str.append(1, static_cast<char>(0x80 | (value & 0x3f)));
			}
			else
			{
				m_str.append(1, static_cast<char>(0xf0 | ((value >> 18) & 0x07)));
				m_str.append(1, static_cast<char>(0x80 | ((value >> 12) & 0x3f)));
				m_str.append(1, static_cast<char>(0x80 | ((value >> 6) & 0x3f)));
				m_str.append(1, static_cast<char>(0x80 | (value & 0x3f)));
			}
		}
		else {
			m_str += str[i];
			i++;
		}
	}
}

DString DString::replaceEscapeSequence ( const DString & begin,
										 const DString & end ) const
{
	unsigned int i;
	DString withoutEscape;

	for ( i=0 ; i < m_str.length() ; i++ )
	{
		if ( m_str[i] < 0x20 )
		{
			withoutEscape += begin;
		}
		if ( m_str[i] == 0x00 )
		{
			withoutEscape += "NUL";
		}
		if ( m_str[i] == 0x01 )
		{
			withoutEscape += "SOH";
		}
		if ( m_str[i] == 0x02 )
		{
			withoutEscape += "STX";
		}
		if ( m_str[i] == 0x03 )
		{
			withoutEscape += "ETX";
		}
		if ( m_str[i] == 0x04 )
		{
			withoutEscape += "EOT";
		}
		if ( m_str[i] == 0x05 )
		{
			withoutEscape += "ENQ";
		}
		if ( m_str[i] == 0x06 )
		{
			withoutEscape += "ACK";
		}
		if ( m_str[i] == 0x07 )
		{
			withoutEscape += "BEL";
		}
		if ( m_str[i] == 0x08 )
		{
			withoutEscape += "BS";
		}
		if ( m_str[i] == 0x09 )
		{
			withoutEscape += "HT";
		}
		if ( m_str[i] == 0x0A )
		{
			withoutEscape += "LF";
		}
		if ( m_str[i] == 0x0B )
		{
			withoutEscape += "VT";
		}
		if ( m_str[i] == 0x0C )
		{
			withoutEscape += "FF";
		}
		if ( m_str[i] == 0x0D )
		{
			withoutEscape += "CR";
		}
		if ( m_str[i] == 0x0E )
		{
			withoutEscape += "SO";
		}
		if ( m_str[i] == 0x0F )
		{
			withoutEscape += "SI";
		}
		if ( m_str[i] == 0x10 )
		{
			withoutEscape += "DLE";
		}
		if ( m_str[i] == 0x11 )
		{
			withoutEscape += "DC1";
		}
		if ( m_str[i] == 0x12 )
		{
			withoutEscape += "DC2";
		}
		if ( m_str[i] == 0x13 )
		{
			withoutEscape += "DC3";
		}
		if ( m_str[i] == 0x14 )
		{
			withoutEscape += "DC4";
		}
		if ( m_str[i] == 0x15 )
		{
			withoutEscape += "NAK";
		}
		if ( m_str[i] == 0x16 )
		{
			withoutEscape += "SYN";
		}
		if ( m_str[i] == 0x17 )
		{
			withoutEscape += "ETB";
		}
		if ( m_str[i] == 0x18 )
		{
			withoutEscape += "CAN";
		}
		if ( m_str[i] == 0x19 )
		{
			withoutEscape += "EM";
		}
		if ( m_str[i] == 0x1A )
		{
			withoutEscape += "SUB";
		}
		if ( m_str[i] == 0x1B )
		{
			withoutEscape += "ESC";
		}
		if ( m_str[i] == 0x1C )
		{
			withoutEscape += "FS";
		}
		if ( m_str[i] == 0x1D )
		{
			withoutEscape += "GS";
		}
		if ( m_str[i] == 0x1E )
		{
			withoutEscape += "RS";
		}
		if ( m_str[i] == 0x1F )
		{
			withoutEscape += "US";
		}
		if ( m_str[i] < 0x20 )
		{
			withoutEscape += end;
		}
		if ( m_str[i] >= 0x20 )
		{
			withoutEscape += m_str[i];
		}
	}
	return withoutEscape;
}

bool DString::containsOnlyLegalChar ( const std::list<char> & legalChar ) const
{
	unsigned int i;
	bool correct = true;
	bool found;
	std::list<char>::const_iterator it;

	i = 0;
	while ( correct && i < m_str.length() )
	{
		found = false;
		it = legalChar.begin();
		while ( !found && it != legalChar.end() )
		{
			if ( ( *it ) == m_str.at ( i ) )
			{
				found = true;
			}
			it++;
		}
		if ( !found )
		{
			correct = false;
		}
		i++;
	}
	return correct;
}

bool DString::containsOnlyLegalChar ( BaseFlag base, CaseFlag caseflag ) const
{
	bool legal = false;

	switch ( base )
	{
		case DString::BINARY:
		{
			legal = containsOnlyLegalChar ( onlyBinary() );
			break;
		}
		case DString::OCTAL:
		{
			legal = containsOnlyLegalChar ( onlyOctal() );
			break;
		}
		case DString::DECIMAL:
		{
			legal = containsOnlyLegalChar ( onlyDecimal() );
			break;
		}
		case DString::HEXA:
		{
			legal = containsOnlyLegalChar ( onlyHexa ( caseflag ) );
			break;
		}
	}
	return legal;
}

bool DString::match ( const DString & pattern, bool cs, bool fullmatch ) const
{
	pcrecpp::RE_Options opt;
	
	if ( ! cs ) {
		opt.set_caseless( true );
	}
	pcrecpp::RE re( pattern.c_str(), opt );
	if ( fullmatch ) {
		return re.FullMatch( m_str.c_str() );
	}
	return re.PartialMatch( m_str.c_str() );
}

int DString::haveMatches ( const DString & pattern ) const
{
	pcrecpp::RE_Options opt;
	
	pcrecpp::RE re( pattern.c_str(), opt );
	return re.NumberOfCapturingGroups();
}

DStringList DString::getMatches ( const DString & pattern, bool cs ) const
{
	DStringList matches;
	pcrecpp::RE_Options opt;
	
	if ( ! cs ) {
		opt.set_caseless( true );
	}
	pcrecpp::RE re( pattern.c_str(), opt );
	
	int  n = re.NumberOfCapturingGroups();
	if ( n < 0 )
		return matches;

	else if( n > PCRE_MAX_ARGS ) {
		// Overflow: There are too many capturing groups
		return matches;
	}

	std::string str[PCRE_MAX_ARGS];
	const pcrecpp::Arg *args[PCRE_MAX_ARGS];

	for ( int i = 0 ; i < PCRE_MAX_ARGS ; i++ ) {
		
		args[i] = new pcrecpp::Arg( &str[i] );
	}

	pcrecpp::StringPiece input( m_str );

	int consumed;
	if ( re.DoMatch( input, pcrecpp::RE::UNANCHORED, &consumed, args, n ) ) {
		input.remove_prefix(consumed);
		for ( int i = 0 ; i < n ; i++ ) {
			matches.push_back( str[i] );
		}
	}
	
	for ( int i = 0 ; i < PCRE_MAX_ARGS ; i++ ) {
		delete args[i];
	}
	
	return matches;
}
///////////////////////////////////////////////////////////////////////////////
std::list<char> & DString::onlyBinary() const
{
	static std::list<char> legalCharDec;

	legalCharDec.clear();
	// '0', '1'
	for ( char c = 0x30 ; c <= 0x31 ; c++ ) {
		legalCharDec.push_back ( c );
	}

	return legalCharDec;
}

std::list<char> & DString::onlyOctal() const
{
	static std::list<char> legalCharDec;

	legalCharDec.clear();
	for ( char c = 0x30 ; c <= 0x37 ; c++ ) {
		legalCharDec.push_back ( c );
	}

	return legalCharDec;
}

std::list<char> & DString::onlyDecimal() const
{
	static std::list<char> legalCharDec;

	legalCharDec.clear();
	for ( char c = 0x30 ; c <= 0x39 ; c++ ) {
		legalCharDec.push_back ( c );
	}

	return legalCharDec;
}

std::list<char> & DString::onlyHexa ( DString::CaseFlag caseflag ) const
{
	static std::list<char> legalCharDec;

	legalCharDec.clear();
	for ( char c = 0x30 ; c <= 0x39 ; c++ ) {
		legalCharDec.push_back ( c );
	}
	if ( ( caseflag & DString::UPPERCASE ) == DString::UPPERCASE )
	{
		for ( char c = 0x41 ; c <= 0x46 ; c++ ) {
			legalCharDec.push_back ( c );
		}
	}
	if ( ( caseflag & DString::LOWERCASE ) == DString::LOWERCASE )
	{
		for ( char c = 0x61 ; c <= 0x66 ; c++ ) {
			legalCharDec.push_back ( c );
		}
	}

	return legalCharDec;
}

DString DString::getFormat ( DateFormat format )
{
	static DString buffer;
	switch ( format )
	{
		case DString::ISO_DATETIME:
		{
			buffer = "%Y-%m-%d %H:%M:%S";
			break;
		}
		case DString::ISO_DATETIME_T:
		{
			buffer = "%Y-%m-%dT%H:%M:%S";
			break;
		}
		case DString::ISO_DATE:
		{
			buffer = "%Y-%m-%d";
			break;
		}
		case DString::ISO_TIME:
		default:
		{
			buffer = "%H:%M:%S";
			break;
		}
	}
	return buffer;
}

double binToDec ( const std::string & str )
{
	unsigned int i;
	std::string number;

	double Value = 0;
	for ( i = 0 ; i < str.length() ; i++ )
	{
		number = str.substr ( str.length()-1-i, 1 );
		if ( number == "1" ) {
			Value += pow ( 2.0, static_cast<double>(i) );
		}
	}
	return Value;
}

std::istream & getline ( std::istream & stream, DString & content, char delim )
{
	return ( getline ( stream, content.getReference(), delim ) );
}
