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
 *     (___)_)   File : dbase64.cpp                         ||--|| *          *
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

#include "dbase64.h"


const unsigned char base64_offset[256] =
{
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
	64, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
	64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};

const char base64_map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

DBase64::DBase64()
{

}

DBase64::~DBase64()
{

}

const DString & DBase64::encodeFromFile( const DString & filename )
{
	std::ifstream file;
	int filesize;
	char * buffer = 0;
	char * encr = 0;
	
	file.open( filename.c_str(), std::ifstream::ate | std::ifstream::binary );
	filesize = static_cast<int>( file.tellg() );
	file.clear();
	file.seekg( std::ios::beg );
	
	buffer = new char[filesize];
	
	for ( int i = 0 ; i < filesize ; i++ )
	{
		buffer[i] = file.get();
	}
	file.close();
	
	encr = new char[ _base64_length(filesize)+1 ];
	_base64_encode( buffer, filesize, encr);
	
	m_encoded = encr;
	delete [] buffer;
	delete [] encr;
	
	return m_encoded;
}

/*
void DBase64::decodeToFile( const DString & filename )
{
	std::ofstream file;
	int length = _ascii_length( m_encoded.length() );
	char * buffer = 0;
	
	buffer = new char[ length + 1 ];
	_base64_decode( m_encoded.c_str(), length, buffer);
	
	file.open( filename.c_str(), std::ifstream::binary );
	file << buffer;
	file.close();
	delete [] buffer;
}
*/

void DBase64::setEncoded( const DString & str )
{
	m_encoded = str;
}

const DString & DBase64::getEncoded()
{
	return m_encoded;
}

DStringList DBase64::getWrappedEncoded( int wrapping )
{
	DStringList list;
	int i = 0;
	
	if ( ! wrapping )
	{
		list.push_back( m_encoded );
		return list;
	}
	while( i < static_cast<int>( m_encoded.length() ) )
	{
		list.push_back( m_encoded.mid( i, wrapping ) );
		i += wrapping;
	}
	return list;
}

void DBase64::_base64_encode(const char * srcp, int len, char * dstp)
{
	register int i = 0;

	for (i = 0; i < len - 2; i += 3)
	{
		*dstp++ = *( base64_map + ((*(srcp+i)>>2)&0x3f));
		*dstp++ = *( base64_map + (((*(srcp+i)<< 4)&0x30) | ((*(srcp+i+1)>>4)&0x0f)));
		*dstp++ = *( base64_map + (((*(srcp+i+1)<<2)&0x3C) | ((*(srcp+i+2)>>6)&0x03)));
		*dstp++ = *( base64_map + (*(srcp+i+2)&0x3f));
	}
	srcp += i;
	len -= i;

	if(len & 0x02 ) /* (i==2) 2 bytes left,pad one byte of '=' */
	{      
		*dstp++ = *(base64_map + ((*srcp>>2)&0x3f));
		*dstp++ = *(base64_map + (((*srcp<< 4)&0x30) | ((
							*(srcp+1)>>4)&0x0f )));
		*dstp++ = *(base64_map + ((*(srcp+1)<<2)&0x3C) );
		*dstp++ = '=';
	}
	else if(len & 0x01 )  /* (i==1) 1 byte left,pad two bytes of '='  */
	{ 
		*dstp++ = *(base64_map + ((*srcp>>2)&0x3f));
		*dstp++ = *(base64_map + ((*srcp<< 4)&0x30));
		*dstp++ = '=';
		*dstp++ = '=';
	}
	*dstp = '\0';
}

/*
void DBase64::_base64_decode(const char * srcp, int len, char * dstp)
{
	register int i = 0;
	char * dst = dstp;
	
	while(i < len)
	{
		*dstp++ = (base64_offset[*(reinterpret_cast<const unsigned char*>(srcp)+i)] <<2 | 
							base64_offset[*(reinterpret_cast<const unsigned char*>(srcp)+i+1)] >>4);
		*dstp++ = (base64_offset[*(reinterpret_cast<const unsigned char*>(srcp)+i+1)]<<4 | 
							base64_offset[*(reinterpret_cast<const unsigned char*>(srcp)+i+2)]>>2);
		*dstp++ = (base64_offset[*(reinterpret_cast<const unsigned char*>(srcp)+i+2)]<<6 |
							base64_offset[*(reinterpret_cast<const unsigned char*>(srcp)+i+3)] );
		i += 4;
	}
	srcp += i;
	
	if(*(srcp-2) == '=')  // remove 2 bytes of '='  padded while encoding
	{	 
		*(dstp--) = '\0';
		*(dstp--) = '\0';
	}
	else if(*(srcp-1) == '=') // remove 1 byte of '='  padded while encoding
		*(dstp--) = '\0';

	*dstp = '\0';

	return dst;
}
*/
/*
size_t DBase64::_base64_length(char * str)
{
	int len = strlen( str );
	return _base64_length( len );
}
*/
size_t DBase64::_base64_length(int len)
{
	size_t  npad = len % 3;
	// padded for multiple of 3 bytes
	size_t  size = ( npad > 0 )? ( len + 3 - npad ) : len;
	return ( ( size * 8 ) / 6 );
}
/*
size_t DBase64::_ascii_length(size_t len)
{
	return ( ( len * 6 ) / 8 );
}
*/