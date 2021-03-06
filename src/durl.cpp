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
 *     (___)_)   File : durl.cpp                            ||--|| *          *
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

#include "durl.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <utf8.h>

DURL::DURL()
{
	clear();
}

DURL::DURL( DString address )
{
	clear();
	setURL( address );
}

DURL::~DURL()
{
}

int DURL::setURL( const DString & address )
{

	struct hostent *host_addr;
	struct sockaddr_in addr;
	//struct addrinfo hints;
	DString buffer;

	clear();
	m_url.url = address;
	encode();
	
	// if protocol is set
	if ( m_url.url.contains( "://" ) )
	{
		m_url.service = m_url.url.section( "://", 0, 0 );
		
		// extract hostname and port if any
		if ( m_url.url.section( "://", 1 ).contains( ":" ) )
		{
			m_url.hostname = m_url.url.section( "://", 1 ).section( ":", 0, 0 );
			m_url.port = m_url.url.section( "://", 1 ).section( ":", 1, 1 ).section( "/", 0, 0 ).toInt();
			m_url.path = m_url.url.section( "://", 1 ).section( ":", 1, 1 ).section( "/", 1 );
		}
		else
		{
			m_url.hostname = m_url.url.section( "://", 1 ).section( "/", 0, 0 );
			m_url.path = m_url.url.section( "://", 1 ).section( "/", 1 );
		}
	}
	else
	{
		// extract hostname and port if any
		if ( m_url.url.contains( ":" ) )
		{
			m_url.hostname = m_url.url.section( ":", 0, 0 );
			m_url.port = m_url.url.section( ":", 1, 1 ).section( "/", 0, 0 ).toInt();
			m_url.path = m_url.url.section( ":", 1, 1 ).section( "/", 1 );
		}
		else
		{
			m_url.hostname = m_url.url.section( "/", 0, 0 );
			m_url.path = m_url.url.section( "/", 1 );
		}
	}
	m_url.ip = m_url.hostname;
	
	if ( ! m_url.path.isEmpty() )
		m_url.path.prepend( "/" );

	m_error = "";
	m_errno = SUCCESS;
	
	m_type = checkType( m_url.ip );
	if ( m_type == DURL::IPV4_ADDR )
	{
		char host[1024];
		char service[20];
		memset( &addr, 0, sizeof( addr ) );
		addr.sin_family      = AF_INET; //TODO use AF_UNSPEC instead for IPv4 and IPv6, or AF_INET6 to force IPv6
		addr.sin_addr.s_addr = inet_addr( m_url.ip.c_str() );
		int failure = 1;
		for ( int i = 0 ; i < 10 ; i++ )
		{
			failure = getnameinfo( reinterpret_cast<sockaddr*> ( &addr ), sizeof( addr ), host, sizeof( host ), service, sizeof( service ), 0 );
			if ( failure != EAI_AGAIN ) break;
			usleep( 100000 );
		}
		
		buffer = host;
		if ( ( ! failure ) && ( buffer != m_url.ip ) ) {
			m_url.hostname = host;
		}
		else {
			m_url.hostname = m_url.ip;
			m_error = "Cannot get hostname by address";
			m_errno = NO_HOST_BY_ADDR;
		}
	}
	else if ( m_type == DURL::IPV6_ADDR )
	{
		//TODO IPv6 part is not implemented yet
	}
	else
	{
		m_url.ip.clear();
		host_addr = gethostbyname( m_url.hostname.c_str() );

		if ( ! host_addr )
		{
			m_error = "Cannot get address by hostname";
			m_errno = NO_HOST_BY_NAME;
		}
		else
		{
			addr.sin_addr.s_addr = reinterpret_cast<struct in_addr*> ( host_addr->h_addr )->s_addr;
			m_url.ip = inet_ntoa( addr.sin_addr );
			if ( checkType( m_url.ip ) == DURL::HOSTNAME )
			{
				m_error = "IP Address is out of range";
				m_errno = IP_OUT_OF_RANGE;
				m_url.ip.clear();
			}
		}
	}

	// If port is already set, no need to search it
	if ( ! m_url.service.isEmpty() && ! m_url.port )
	{
		m_url.port = getPortByService( m_url.service );
		if ( ! m_url.port )
		{
			m_error = "Cannot get port by service name";
			if ( m_errno == SUCCESS ) m_errno = NO_SERVICE;
		}
	}
	if ( m_url.service.isEmpty() && m_url.port )
	{
		m_url.service = getServiceByPort( m_url.port );
		if ( m_url.service.isEmpty() )
		{
			m_error = "Cannot get service by port name";
			if ( m_errno == SUCCESS ) m_errno = NO_SERVICE;
		}
	}
	
	return m_errno;
}

DURL::Type DURL::checkType( const DString & address )
{
	unsigned short int val, place = 0;
	DString segment;
	DURL::Type type = DURL::HOSTNAME;
	DStringList segments;
	DStringList::iterator it;
	
	// Check if it's an IPv4 address
	if ( address.contains( "." ) == 3 )
	{
		type = DURL::IPV4_ADDR;
		segments = address.split( "." );
		place = 0;
		for ( it = segments.begin() ; it != segments.end() ; ++it )
		{
			segment = *it;
			val = segment.toUShort();
			
			// if segment is greater than 255, it's not an valid IPv4 address
			if ( val > 255 )
			{
				type = DURL::HOSTNAME;
				break;
			}

			// if segment is null and not provided by a 0 char
			// it's not an IP address
			if ( ( val == 0 ) && ! ( segment == "0" || segment == "00" || segment == "000" ) )
			{
				type = DURL::HOSTNAME;
				break;
			}

			// First or last segment cannot be null
			if ((( place == 0 ) || ( place == 3 ) ) && ( val == 0 ) )
			{
				type = DURL::HOSTNAME;
				break;
			}

			place++;
		}
	}
	// Check if it's an IPv6 address
	else if ( address.contains( ":" ) >= 2 )
	{
		//TODO not implemented yet
		//type = DURL::IPV6_ADDR;
	}
	return type;
}

DString DURL::getHexaCharString( uint32_t code )
{
	DString buffer;
	buffer.setNum( static_cast<int>( code ), 16 ).toUpper();
	buffer.prepend( "%" );
	return buffer;
}

void DURL::encode()
{
	DString buffer;
	
	char * str = const_cast<char *>( m_url.url.c_str() ); // utf-8 string
    char * str_i = str;                                   // string iterator
    char * end = str + strlen( str ) + 1;                 // end iterator

    m_url.url.clear();
	do
	{
		uint32_t code = utf8::next( str_i, end ); // get 32 bit code of a utf-8 symbol
		// enhanced ascii char are not allowed on URL
		if ( code < 20 || code >= 0x7f )
		{
			continue;
		}
		if ( ( code == 0x20 ) ||
			 ( code == 0x22 ) ||
			 ( code == 0x25 ) ||
			 ( code == 0x3c ) ||
			 ( code == 0x3e ) ||
			 ( code == 0x5c ) ||
			 ( code == 0x5e ) ||
			 ( code == 0x60 ) ||
			 ( code == 0x7b ) ||
			 ( code == 0x7c ) ||
			 ( code == 0x7d ) )
		{
			m_url.url += getHexaCharString( code );
			continue;
		}
		m_url.url += code;
	}
	while ( str_i < end );
}

const DString & DURL::getURL() const
{
	return m_url.url;
}

const DString &  DURL::getHost() const
{
	return m_url.hostname;
}

const DString &  DURL::getIPAddress() const
{
	return m_url.ip;
}

int DURL::getPort() const
{
	return m_url.port;
}

const DString & DURL::getServiceName() const
{
	return m_url.service;
}

const DString & DURL::getPath() const
{
	return m_url.path;
}

const DString & DURL::getLastError() const
{
	return m_error;
}

int DURL::getLastErrno()
{
	return m_errno;
}

const DURL::Type & DURL::getType() const
{
	return m_type;
}

void DURL::clear()
{
	m_type = DURL::HOSTNAME;
	m_url.clear();
	m_error.clear();
}


const DString & DURL::toString() const
{
	static DString url;
	DString buffer;
	
	url = "( hostname = \"";
	url += getHost();
	url += "\", IP address = \"";
	url += getIPAddress();
	url += "\", Service = \"";
	url += getServiceName();
	url += "\", Port = \"";
	buffer.setNum( getPort() );
	url += buffer;
	url += "\", Path = \"";
	url += getPath();
	url += "\")";
	return url;
}

std::ostream& operator << ( std::ostream& s, const DURL & url )
{
	s << url.toString();
	return s;
}

DURL::DURLData::DURLData()
{
	clear();
}

DURL::DURLData::~DURLData()
{
}

void DURL::DURLData::clear()
{
	service.clear();
	hostname.clear();
	ip.clear();
	path.clear();
	url.clear();
	port = 0;
}

int DURL::getPortByService( const DString & servicename, const DString & protocol )
{
	int port = 0;
	struct servent *serv = 0;
	
	serv = getservbyname( servicename.c_str(), protocol.c_str() );
	if ( serv )
	{
		port = ntohs( serv->s_port );
	}
	endservent();
	return port;
}

const DString & DURL::getServiceByPort( const int port, const DString & protocol )
{
	static DString service;
	struct servent *serv = 0;
	
	serv = getservbyport( htons( port ), protocol.c_str() );
	if ( serv )
	{
		service = serv->s_name;
	}
	endservent();
	return service;
}