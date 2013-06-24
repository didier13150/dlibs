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
 *     (___)_)   File : dsocket.cpp                         ||--|| *          *
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

#include "dsocket.h"
#include "dtimer.h"
#include <unistd.h>
#include <fcntl.h>
#include <fstream>

using namespace std;

DSock::DSock()
{
	m_buffSize = 80;
}

DSock::~DSock()
{
	this->closeSock();
}

void DSock::closeSock()
{
	// Close socket if any
	if ( m_hSocket >= 0 )
	{
		close ( m_hSocket );
	}
	m_hSocket = -1;
}

void DSock::setTimeout ( unsigned long int timeout )
{
	m_timeout = timeout;
}

void DSock::setBufferSize ( size_t size )
{
	m_buffSize = size * sizeof( char );
}

const DString & DSock::getLastError() const
{
	return m_lastError;
}

int DSock::getStatus()
{
	return m_status;
}

void DSock::setDebug ( int mode )
{
	m_debug = mode;
}

void DSock::setDebugFile ( DString filename )
{
	m_debugfile = filename;
}

void DSock::printMessage(DString message)
{
	DString buffer;
	std::ofstream file;
	
	if (m_debug)
	{
		buffer = message.replaceEscapeSequence();
	}
	if ( ( m_debug & DEBUG_STDOUT ) == DEBUG_STDOUT )
	{
		std::cout << buffer << std::endl;
	}
	if ( ( m_debug & DEBUG_FILE ) == DEBUG_FILE )
	{
		if (!m_debugfile.isEmpty())
		{
			file.open(m_debugfile.c_str(), std::ios::out |  std::ios::app);
			if (file)
			{
				file << buffer << std::endl;
				file.close();
			}
		}
	}
}

/******************************************************************************/
/*                                   Client                                   */
/******************************************************************************/
DClientSock::DClientSock()
	: DSock()
{
	m_timeout = 1;
	m_hSocket = -1;
	m_status = NO_SOCKET;
	m_debug = NO_DEBUG;
}

DClientSock::~DClientSock()
{
	this->closeSock();
}

int DClientSock::openSock ( const DString & host, int port )
{
	string buffer;
	struct sockaddr_in serv_addr;
	struct hostent *host_addr;

	// Open the socket
	m_hSocket = socket ( AF_INET, SOCK_STREAM, 0 );
	if ( m_hSocket < 0 )
	{
		m_lastError = "Cannot open the socket, ";
		m_lastError += strerror ( errno );
		m_status = NO_SOCKET;
		return m_status;
	}

	// Connect socket to host
	memset ( ( char * ) &serv_addr, 0x00, sizeof ( struct sockaddr_in ) );
	serv_addr.sin_family = AF_INET;

	host_addr = gethostbyname(host.c_str());
	if (!host_addr)
	{
		//m_lastError = "Cannot get address by hostname";
		m_lastError = "Cannot get address of hostname " + host + ", ";
		m_lastError += strerror ( errno );
		return NO_HOST;
	}
	serv_addr.sin_addr.s_addr = ((struct in_addr*) host_addr->h_addr)->s_addr;
	//serv_addr.sin_addr.s_addr =  inet_addr ( host.c_str() );
	serv_addr.sin_port = htons ( port );

	if ( connect ( m_hSocket, ( struct sockaddr * ) &serv_addr,
	               sizeof ( serv_addr ) ) < 0 )
	{
		m_lastError = "Cannot connect to host " + host + ", ";
		m_lastError += strerror ( errno );
		m_status = NO_HOST;
		this->closeSock();
		return m_status;
	}
	m_lastError = "";
	m_status = SUCCESS;

	// to have an non-blocked socket
	fcntl ( m_hSocket, F_SETFL, O_NONBLOCK );

	return m_status;
}

int DClientSock::openSock ( const DString & host, const DString & port )
{
	return ( openSock ( host, port.toInt() ) );
}

int DClientSock::openSock ( const DURL & url )
{
	return ( openSock ( url.getIPAddress(), url.getPort() ) );
}

int DClientSock::writeMessage ( const DString & message,
                                unsigned short int retry,
                                bool checkSock )
{
	unsigned short int i = 0;

	m_status = NO_SEND;
	while ( i < retry &&  m_status != SUCCESS )
	{
		writeMessage ( message, checkSock );
		if ( m_status == NO_SOCKET ) break;
		usleep ( 10000 );
		i++;
	}
	return m_status;
}

int DClientSock::writeMessage ( const DString & message, bool checkSock )
{
	DString buffer;

	buffer = message;
	buffer += "\r\n";

	return ( sendPacket( buffer, checkSock ) );
}

int DClientSock::sendPacket ( const DString & packet, bool checkSock )
{
	int numberChar;
	fd_set stFdSet;
	struct timeval stTime;
	DString buffer;
	int timeout;

	if ( checkSock )
	{
		// check if socket is opened
		timeout = m_timeout;
		setTimeout ( 10 );
		m_status = readMessage ( buffer );
		setTimeout ( timeout );
	}

	if ( m_hSocket < 0 || m_status == NO_SOCKET )
	{
		m_status = NO_SOCKET;
		m_lastError = "No opened socket found";
		return m_status;
	}
	FD_ZERO ( &stFdSet );
	FD_SET ( m_hSocket, &stFdSet );
	stTime.tv_sec = m_timeout;
	stTime.tv_usec = 0;

	if (m_debug)
	{
		printMessage(packet);
	}
	// Check if data can be sent without any blocking
	if ( ( select ( m_hSocket+1, NULL, &stFdSet, NULL, &stTime ) != -1 ) &&
	        ( FD_ISSET ( m_hSocket, &stFdSet ) ) )
	{
		numberChar = send ( m_hSocket, packet.c_str(), packet.length(), 0 );
		if ( numberChar > 0 )
		{
			m_lastError = "";
			m_status = SUCCESS;
		}
		else
		{
			m_lastError = "No data sent, ";
			m_lastError =  + strerror ( errno );
			m_status = NO_SEND;
		}
	}
	else
	{
		m_lastError = "No data sent, ";
		m_lastError =  + strerror ( errno );
		m_status = NO_SEND;
	}
	return m_status;
}

int DClientSock::readMessage ( DString & message, unsigned short int retry )
{
	unsigned short int i = 0;

	m_status = NO_SEND;
	while ( i < retry &&  m_status != SUCCESS )
	{
		readMessage ( message );
		i++;
	}
	return m_status;
}

int DClientSock::readMessage ( DString & message )
{
	int numberChar;
	char *buffer;
	DTimer timer;

	// clear line
	message.clear();
	
	if ( m_hSocket < 0 || m_status == NO_SOCKET )
	{
		m_status = NO_SOCKET;
		m_lastError = "No opened socket found";
		return m_status;
	}

	buffer = new char[ m_buffSize + 1 ];

	// Start timer
	timer.start ( m_timeout );

	while ( message.length() == 0 && timer.timeToTimeout() )
	{
		memset ( buffer, 0x0, m_buffSize );
		numberChar = recv ( m_hSocket, buffer, m_buffSize, 0 );
		if ( numberChar < 0 )
		{
			m_lastError = "No data, ";
			m_lastError += strerror ( errno );
			m_status = RECV_NOTHING;
		}
		else if ( numberChar == 0 )
		{
			m_lastError = "Socket disconnected, ";
			m_lastError += strerror ( errno );
			m_status = NO_SOCKET;
			closeSock();
			break;
		}
		else
		{
			message = buffer;
			message.truncate ( numberChar );
			if ( message.length() > 0 )
			{
				if (m_debug)
				{
					printMessage(message);
				}
				m_status = SUCCESS;
				m_lastError = "";
			}
			else
			{
				m_status = RECV_EMPTY;
				m_lastError = "Receive an empty message";
			}
		}
		usleep ( 10000 );
	}

	if ( timer.isStarted() )
	{
		timer.stop();
	}

	delete[]( buffer );

	return m_status;
}

/******************************************************************************/
/*                                   Server                                   */
/******************************************************************************/
DServerSock::DServerSock()
	: DSock()
{
	m_timeout = 1;
	m_hSocket = -1;
	m_status = NO_SOCKET;
	m_debug = NO_DEBUG;
}

DServerSock::~DServerSock()
{
	this->closeSock();
}

int DServerSock::openSock ( int port )
{
	string strBuffer;
	struct sockaddr_in serv_addr;

	// Open the socket
	m_hSocket = socket ( AF_INET, SOCK_STREAM, 0 );
	if ( m_hSocket < 0 )
	{
		m_lastError = "Cannot open the socket, ";
		m_lastError += strerror ( errno );
		m_status = NO_SOCKET;
		return m_status;
	}

	// Connect socket to host
	memset ( ( char * ) &serv_addr, 0x00, sizeof ( struct sockaddr_in ) );
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr =  htonl ( INADDR_ANY );
	serv_addr.sin_port = htons ( port );


	// bind the socket
	if ( bind ( m_hSocket, ( struct sockaddr* ) &serv_addr, sizeof ( serv_addr ) ) < 0 )
	{
		close ( m_hSocket );
		m_lastError = "Cannot bind the socket, ";
		m_lastError += strerror ( errno );
		m_status = ERROR_BINDSOCK;
		return m_status;
	}

	// little init
	if ( listen ( m_hSocket, 1 ) != 0 )
	{
		close ( m_hSocket );
		m_lastError = "Cannot listen new client, ";
		m_lastError += strerror ( errno );
		m_status = ERROR_LISTEN;
		return m_status;
	}

	m_lastError = "";
	m_status = SUCCESS;

	return m_status;
}

int DServerSock::openSock ( const DString & port )
{
	return ( openSock ( port.toInt() ) );
}

int DServerSock::dupSock ()
{
	m_hSocket = dup(1);
	if ( m_hSocket <= 0 )
	{
		m_lastError = "Cannot get the socket, ";
		m_lastError += strerror ( errno );
		m_status = NO_SOCKET;
		return m_status;
	}

	m_lastError = "";
	m_status = SUCCESS;

	return m_status;
}

void DServerSock::closeConnection ( int & hSock )
{
	if ( hSock >= 0 )
	{
		close ( hSock );
		hSock = -1;
	}
}

int DServerSock::openConnection ( int & hSock )
{
	struct sockaddr_in cli_addr;
	int clilen;

	// waiting for client connection
	clilen = sizeof ( cli_addr );
	hSock = accept ( m_hSocket,
	                 ( struct sockaddr* ) &cli_addr,
	                 ( socklen_t* ) &clilen );
	if ( hSock < 0 )
	{
		m_lastError = "Cannot accept client, ";
		m_lastError += strerror ( errno );
		m_status = ERROR_ACCEPT;
		return m_status;
	}
	clientAddress = inet_ntoa ( cli_addr.sin_addr );

	m_lastError = "";
	m_status = SUCCESS;

	// to have an non-blocked socket
	fcntl ( hSock, F_SETFL, O_NONBLOCK );

	return m_status;
}

int DServerSock::writeMessage ( int hSock,
                                const DString & message,
                                unsigned short int retry,
                                bool checkSock )
{
	unsigned short int i = 0;

	m_status = NO_SEND;
	while ( i < retry &&  m_status != SUCCESS )
	{
		writeMessage ( hSock, message, checkSock );
		usleep ( 10000 );
		i++;
	}
	return m_status;
}

int DServerSock::writeMessage ( int hSock, const DString & message, bool checkSock )
{
	DString buffer;

	buffer = message;
	buffer += "\r\n";
	return ( sendPacket ( hSock, buffer, checkSock ) );
}

int DServerSock::sendPacket ( int hSock, const DString & packet, bool checkSock )
{
	int numberChar;
	fd_set stFdSet;
	struct timeval stTime;
	DString buffer;
	long int timeout;


	if ( checkSock )
	{
		// check if socket is opened
		timeout = m_timeout;
		setTimeout ( 10 );
		m_status = readMessage ( hSock, buffer );
		setTimeout ( timeout );
	}

	if ( m_hSocket < 0 || m_status == NO_SOCKET )
	{
		m_status = NO_SOCKET;
		m_lastError = "No opened socket found";
		return m_status;
	}
	FD_ZERO ( &stFdSet );
	FD_SET ( hSock, &stFdSet );
	stTime.tv_sec = m_timeout;
	stTime.tv_usec = 0;

	if (m_debug)
	{
		printMessage(packet);
	}
	// Check if data can be sent without any blocking
	if ( ( select ( hSock+1, NULL, &stFdSet, NULL, &stTime ) != -1 ) &&
			  ( FD_ISSET ( hSock, &stFdSet ) ) )
	{
		numberChar = send ( hSock, packet.c_str(), packet.length(), 0 );
		if ( numberChar == packet.length() )
		{
			m_lastError = "";
			m_status = SUCCESS;
		}
		else
		{
			m_lastError = "No data sent, ";
			m_lastError =  + strerror ( errno );
			m_status = NO_SEND;
		}
	}
	else
	{
		m_lastError = "No data sent, ";
		m_lastError =  + strerror ( errno );
		m_status = NO_SEND;
	}
	return m_status;
}

int DServerSock::readMessage ( int hSock, DString &message, unsigned short int retry )
{
	unsigned short int i = 0;

	m_status = NO_SEND;
	while ( i < retry &&  m_status != SUCCESS )
	{
		readMessage ( hSock, message );
		i++;
	}
	return m_status;
}

int DServerSock::readMessage ( int hSock, DString &message )
{
	int numberChar;
	char * buffer;
	DTimer timer;

	if ( hSock < 0 || m_status == NO_SOCKET )
	{
		m_status = NO_SOCKET;
		m_lastError = "No opened socket found";
		return m_status;
	}

	buffer = new char[ m_buffSize + 1 ];
	
	// clear line
	message.clear();

	timer.start ( m_timeout );

	while ( message.length() == 0 && timer.timeToTimeout() )
	{
		memset ( buffer, 0x0, m_buffSize );
		numberChar = recv ( hSock, buffer, m_buffSize, 0 );
		if ( numberChar < 0 )
		{
			m_lastError = "No data, ";
			m_lastError += strerror ( errno );
			m_status = RECV_NOTHING;
		}
		else if ( numberChar == 0 )
		{
			m_lastError = "Socket disconnected, ";
			m_lastError += strerror ( errno );
			m_status = NO_SOCKET;
			break;
		}
		else
		{
			message = buffer;
			message.truncate ( numberChar );
			if ( message.length() > 0 )
			{
				if (m_debug)
				{
					printMessage(message);
				}
				m_status = SUCCESS;
				m_lastError = "";
			}
			else
			{
				m_status = RECV_EMPTY;
				m_lastError = "Receive an empty message";
			}
		}
		usleep ( 10000 );
	}

	if ( timer.isStarted() )
	{
		timer.stop();
	}
	delete[]( buffer );

	return m_status;
}

const DString & DServerSock::getClientAddress() const
{
	return clientAddress;
}
