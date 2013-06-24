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


#include "dstring.h"

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
	std::string str;

	if ( len >= m_str.length() )
	{
		str = m_str;
		return str;
	}
	if ( !isEmpty() )
	{
		str = m_str.substr ( 0, len );
	}
	else
	{
		str = "";
	}
	return str;
}

DString DString::right ( unsigned int len ) const
{
	std::string str;

	if ( len >= m_str.length() )
	{
		str = m_str;
		return str;
	}
	if ( !isEmpty() )
	{
		str = m_str.substr ( ( m_str.length() - len ), len );
	}
	else
	{
		str = "";
	}
	return str;
}

DString DString::mid ( unsigned int index, unsigned int len ) const
{
	std::string str;

	if ( ( index + len ) >= m_str.length() )
	{
		if ( index < m_str.length() )
		{
			str = m_str.substr ( index, ( m_str.length() - index ) );
		}
		else
		{
			str = "";
		}
		return str;
	}
	if ( ( !isEmpty() ) && ( index < m_str.length() ) )
	{
		str = m_str.substr ( ( 0 + index ), len );
	}
	else
	{
		str = "";
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

std::list<DString> DString::splitConstantSize ( unsigned int max_size )
{
	std::list<DString> tmplist;
	std::list<DString> returnedlist;
	std::list<DString>::iterator ite;
	DString str;
	DString buffer;
	bool reached = false;

	tmplist = split ( " " );
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

DStringList DString::split ( const DString sep, bool allowNull ) const
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
				liststr.push_back ( buffer );
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
					buffer = m_str.substr ( pos1 + sep.length(), pos2 - pos1 - 1 );
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
						liststr.push_back ( buffer );
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
	for ( unsigned int i = 0 ; i < m_str.length() ; i++ )
	{
		if ( m_str[i] >= 0x41 && m_str[i] <= 0x5A )
		{
			m_str[i] += 0x20;
		}
	}
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
	for ( unsigned int i = 0 ; i < m_str.length() ; i++ )
	{
		if ( m_str[i] >= 0x61 && m_str[i] <= 0x7A )
		{
			m_str[i] -= 0x20;
		}
	}
	return *this;
}

DString DString::upper() const
{
	std::string buffer = m_str;
	
	for ( unsigned int i = 0 ; i < buffer.length() ; i++ )
	{
		if ( buffer[i] >= 0x41 && buffer[i] <= 0x5A )
		{
			buffer[i] -= 0x20;
		}
	}
	return buffer;
}

DString DString::leftJustify ( unsigned int width, char fill )
{
	unsigned int i;

	for ( i = m_str.length() ; i < width ; i++ )
	{
		m_str = m_str + fill;
	}

	return *this;
}

DString DString::rightJustify ( unsigned int width, char fill )
{
	unsigned int i;

	for ( i = m_str.length() ; i < width ; i++ )
	{
		m_str = fill + m_str;
	}

	return *this;
}

void DString::truncate ( unsigned int width )
{
	if ( width < m_str.length() )
	{
		m_str.resize ( width );
	}
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
		buffer.lower();
		occur.lower();
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
	DString buffer ( before );
	int index = 0;

	if ( !cs )
	{
		buffer.lower();
	}

	while ( index >= 0 )
	{
		index = find ( buffer, index, cs );
		if ( index >= 0 )
		{
			replace ( index, buffer.length(), after );
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
		buf1.lower();
		buf2.lower();
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
		buffer.lower();
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
	DString buffer;
	int i = 0;

	liststr = split ( sep );

	// begin on the left
	if ( ( start >= 0 ) && ( end >= start ) )
	{
		ite = liststr.begin();
		if ( ite == liststr.end() )
		{
			buffer = "";
		}
		else
		{
			for ( i = 0 ; i < start ; i++ )
			{
				ite++;
				if ( ite == liststr.end() )
				{
					buffer = "";
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
		if ( rite == liststr.rend() )
		{
			buffer = "";
		}
		else
		{
			for ( i = 1 ; i < std::abs ( ( double ) start ) ; i++ )
			{
				rite++;
				if ( rite == liststr.rend() )
				{
					buffer = "";
					break;
				}
			}
			while ( i <= std::abs ( ( double ) end ) && rite != liststr.rend() )
			{
				buffer.prepend ( *rite );
				rite++;
				i++;
				if ( rite != liststr.rend() && i <= std::abs ( ( double ) end ) )
				{
					buffer.prepend ( sep );
				}
			}
		}
	}
	else
	{
		buffer = "";
	}

	return buffer;
}

DString DString::timeToString ( const time_t & t, const char * format )
{
	char szBuffer[80];
	struct tm *stTm;
	DString buffer;

	// Get local time
	stTm = localtime ( &t );
	//translate format's time and writting on file
	strftime ( szBuffer, sizeof ( szBuffer ), format, stTm );
	buffer = szBuffer;

	return buffer;
}

DString DString::timeToString ( const time_t & t, DateFormat format )
{
	return timeToString ( t, getFormat ( format ) );
}

DString DString::Now ( const char * format )
{
	return timeToString ( time ( NULL ), format );
}

DString DString::Now ( DateFormat format )
{
	return timeToString ( time ( NULL ), getFormat ( format ) );
}

DString & DString::convertTime ( const char * oldformat,
                                 const char * newformat )
{
	//char *strptime(const char *buf, const char *format, struct tm *tm);
	struct tm stTm;
	DString buffer;
	char szBuffer[80];

	// Get local time
	strptime ( m_str.c_str(), oldformat, &stTm );
	strftime ( szBuffer, sizeof ( szBuffer ), newformat, &stTm );
	m_str = szBuffer;

	return *this;
}

DString & DString::convertTime ( DateFormat oldformat,
                                 DateFormat newformat )
{
	convertTime( getFormat ( oldformat ), getFormat ( newformat ) );
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
	short int number;
	binToDec ( m_str, number );
	return number;
}

unsigned short int DString::toUShortBase10()
{
	unsigned short int number;
	binToDec ( m_str, number );
	return number;
}

int DString::toIntBase10()
{
	int number;
	binToDec ( m_str, number );
	return number;
}

unsigned int DString::toUIntBase10()
{
	unsigned int number;
	binToDec ( m_str, number );
	return number;
}

long int DString::toLongBase10()
{
	long int number;
	binToDec ( m_str, number );
	return number;
}


unsigned long int DString::toULongBase10()
{
	unsigned long int number;
	binToDec ( m_str, number );
	return number;
}

long long int DString::toLongLongBase10()
{
	long int number;
	binToDec ( m_str, number );
	return number;
}


long long unsigned int DString::toULongLongBase10()
{
	unsigned long long int number;
	binToDec ( m_str, number );
	return number;
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

bool DString::containsOnlyLegalChar ( std::list<char> & legalChar ) const
{
	unsigned int i;
	bool correct = true;
	bool found;
	std::list<char>::iterator it;

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
	bool legal;

	switch ( base )
	{
		case BINARY:
		{
			legal = containsOnlyLegalChar ( onlyBinary() );
			break;
		}
		case OCTAL:
		{
			legal = containsOnlyLegalChar ( onlyOctal() );
			break;
		}
		case DECIMAL:
		{
			legal = containsOnlyLegalChar ( onlyDecimal() );
			break;
		}
		case HEXA:
		{
			legal = containsOnlyLegalChar ( onlyHexa ( caseflag ) );
			break;
		}
		default:
		{
			return false;
		}
	}
	return legal;
}

///////////////////////////////////////////////////////////////////////////////
std::list<char> & DString::onlyBinary() const
{
	static std::list<char> legalCharDec;

	legalCharDec.push_back ( '0' );
	legalCharDec.push_back ( '1' );

	return legalCharDec;
}

std::list<char> & DString::onlyOctal() const
{
	static std::list<char> legalCharDec;

	legalCharDec.push_back ( '0' );
	legalCharDec.push_back ( '1' );
	legalCharDec.push_back ( '2' );
	legalCharDec.push_back ( '3' );
	legalCharDec.push_back ( '4' );
	legalCharDec.push_back ( '5' );
	legalCharDec.push_back ( '6' );
	legalCharDec.push_back ( '7' );

	return legalCharDec;
}

std::list<char> & DString::onlyDecimal() const
{
	static std::list<char> legalCharDec;

	legalCharDec.push_back ( '0' );
	legalCharDec.push_back ( '1' );
	legalCharDec.push_back ( '2' );
	legalCharDec.push_back ( '3' );
	legalCharDec.push_back ( '4' );
	legalCharDec.push_back ( '5' );
	legalCharDec.push_back ( '6' );
	legalCharDec.push_back ( '7' );
	legalCharDec.push_back ( '8' );
	legalCharDec.push_back ( '9' );

	return legalCharDec;
}

std::list<char> & DString::onlyHexa ( CaseFlag caseflag ) const
{
	static std::list<char> legalCharDec;

	legalCharDec.push_back ( '0' );
	legalCharDec.push_back ( '1' );
	legalCharDec.push_back ( '2' );
	legalCharDec.push_back ( '3' );
	legalCharDec.push_back ( '4' );
	legalCharDec.push_back ( '5' );
	legalCharDec.push_back ( '6' );
	legalCharDec.push_back ( '7' );
	legalCharDec.push_back ( '8' );
	legalCharDec.push_back ( '9' );
	if ( ( caseflag & UPPERCASE ) == UPPERCASE )
	{
		legalCharDec.push_back ( 'A' );
		legalCharDec.push_back ( 'B' );
		legalCharDec.push_back ( 'C' );
		legalCharDec.push_back ( 'D' );
		legalCharDec.push_back ( 'E' );
		legalCharDec.push_back ( 'F' );
	}
	if ( ( caseflag & LOWERCASE ) == LOWERCASE )
	{
		legalCharDec.push_back ( 'a' );
		legalCharDec.push_back ( 'b' );
		legalCharDec.push_back ( 'c' );
		legalCharDec.push_back ( 'd' );
		legalCharDec.push_back ( 'e' );
		legalCharDec.push_back ( 'f' );
	}

	return legalCharDec;
}

const char * DString::getFormat ( DateFormat format )
{
	DString buffer;
	switch ( format )
	{
		case ISO_DATETIME:
		{
			buffer = "%Y-%m-%d %H:%M:%S";
			break;
		}
		case ISO_DATETIME_T:
		{
			buffer = "%Y-%m-%dT%H:%M:%S";
			break;
		}
		case ISO_DATE:
		{
			buffer = "%Y-%m-%d";
			break;
		}
		case ISO_TIME:
		default:
		{
			buffer = "%H:%M:%S";
			break;
		}
	}
	return buffer.c_str();
}

std::istream & getline ( std::istream & stream, DString & content, char delim )
{
	return ( getline ( stream, content.getReference(), delim ) );
}
