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

using namespace std;

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
	DString buffer;

	m_url.url = address;
	
	// if protocol is set
	if ( address.contains( "://" ) )
	{
		m_url.service = address.section( "://", 0, 0 );
		
		// extract hostname and port if any
		if ( address.section( "://", 1 ).contains( ":" ) )
		{
			m_url.hostname = address.section( "://", 1 ).section( ":", 0, 0 );
			m_url.port = address.section( "://", 1 ).section( ":", 1, 1 ).section( "/", 0, 0 ).toInt();
			m_url.path = address.section( "://", 1 ).section( ":", 1, 1 ).section( "/", 1 );
		}
		else
		{
			m_url.hostname = address.section( "://", 1 ).section( "/", 0, 0 );
			m_url.path = address.section( "://", 1 ).section( "/", 1 );
		}
	}
	else
	{
		// extract hostname and port if any
		if ( address.contains( ":" ) )
		{
			m_url.hostname = address.section( ":", 0, 0 );
			m_url.port = address.section( ":", 1, 1 ).section( "/", 0, 0 ).toInt();
			m_url.path = address.section( ":", 1, 1 ).section( "/", 1 );
		}
		else
		{
			m_url.hostname = address.section( "/", 0, 0 );
			m_url.path = address.section( "/", 1 );
		}
	}
	m_url.ip = m_url.hostname;
	if ( !m_url.path.isEmpty() )
	{
		m_url.path.prepend( "/" );
	}

	if ( isIP( m_url.ip ) )
	{
		m_isIPAddress = true;
				
		host_addr = gethostbyaddr( m_url.ip.c_str(), m_url.ip.length(), AF_INET );

		if ( !host_addr )
		{
			m_error = "Cannot get hostname by address";
			m_errno = NO_HOST_BY_ADDR;
			m_url.hostname.clear();
		}
		else
		{
			m_url.hostname = host_addr->h_name;
		}
	}

	else
	{
		m_isIPAddress = false;
		
		host_addr = gethostbyname( m_url.hostname.c_str() );

		if ( !host_addr )
		{
			m_error = "Cannot get address by hostname";
			m_errno = NO_HOST_BY_NAME;
			m_url.ip.clear();
			return m_errno;
		}
		else
		{
			addr.sin_addr.s_addr = (( struct in_addr* ) host_addr->h_addr )->s_addr;
			m_url.ip = inet_ntoa( addr.sin_addr );
		}
	}

	// If port is already set, no need to search it
	if ( !m_url.service.isEmpty() && !m_url.port )
	{
		m_url.port = getPortByService( m_url.service );
		if ( !m_url.port )
		{
			m_error = "Cannot get port by service name";
			m_errno = NO_SERVICE;
			return m_errno;
		}
	}
	
	if ( m_errno != NO_HOST_BY_ADDR )
	{
		m_error = "";
		m_errno = SUCCESS;
	}

	return m_errno;
}

bool DURL::isIP( const DString & address )
{
	unsigned short int seg, place = 0;
	DString segment;
	bool isIP = false;
	DStringList segments;
	DStringList::iterator it;
	
	// Check if it's an IP address
	if ( address.contains( "." ) == 3 )
	{
		isIP = true;
		segments = address.split( "." );
		place = 0;
		for ( it = segments.begin() ; it != segments.end() ; ++it )
		{
			seg = it->toUShort();
			// if segment is greater than 255, it's not an valid IPv4 address

			if ( seg > 255 )
			{
				isIP = false;
				break;
			}

			// if segment is null and not provided by a 0 char
			// it's not an IP address
			if ( ( seg == 0 ) && ( ( ( *it ) != "0" ) || ( ( *it ) != "00" ) || ( ( *it ) != "000" ) ) )
			{
				isIP = false;
				break;
			}

			// First or last segment cannot be null
			if ((( place == 0 ) || ( place == 3 ) ) && ( seg == 0 ) )
			{
				isIP = false;
				break;
			}

			place++;
		}
	}
	return isIP;
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

const int DURL::getPort() const
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

bool DURL::isIPAddress() const
{
	return m_isIPAddress;
}

bool DURL::isHostname() const
{
	return ( not m_isIPAddress );
}

const DString & DURL::getLastError() const
{
	return m_error;
}

int DURL::getLastErrno()
{
	return m_errno;
}

void DURL::clear()
{
	m_isIPAddress = false;
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

const DString & DURL::DURLData::toString() const
{	
	return url;
}

int DURL::getPortByService( const DString & servicename, const DString & protocol )
{
	std::ifstream servfile;
	DStringList items;
	DStringList::iterator it;
	DString buffer;
	int port = 0;
	
	
	servfile.open( "/etc/services" );
	while( getline( servfile, buffer, '\n' ) )
	{
		if (buffer.contains( servicename ) )
		{
			items = buffer.simplifyWhiteSpace().split( " " );
			it = items.begin();
			if ( it == items.end() )
			{
				return 0;
			}
			if ( *it == servicename )
			{
				++it;
				// no more data on this line
				if ( it == items.end() )
				{
					return 0;
				}
				buffer = it->section( "/", 1 );
				if ( buffer == protocol )
				{
					port = it->section( "/", 0, 0 ).toInt();
					return port;
				}
			}
		}
	}
	
	servfile.close();
	return 0;
}

