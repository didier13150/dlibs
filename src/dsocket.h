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
 *     (___)_)   File : dsocket.h                           ||--|| *          *
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

#ifndef DCLIENTSOCK_H
#define DCLIENTSOCK_H

#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <netdb.h> // strerror and co
#include <sys/select.h>
//#include <sstream>
#include <string>
#include <iostream>
#include <arpa/inet.h>

#include "dstring.h"
#include "durl.h"
#include "dskeleton.h"

/**
 * This pure virtual class (non-instanciable) give tools for working with socket.
 * A DSock object cannot be declared ( no public constructor ) and you must use
 * a DClientSock or a DServerSock object instead.
 * @brief Pure virtual tools for working with sockets
 * @author Didier Fabert <didier.fabert@gmail.com>
 */
class DSock : public DSkeleton
{
public:
	/**
	 * Communication and connection state
	 */
	enum StatusState
	{
		/// Connection or communication OK
		SUCCESS,
		/// Receive nothing
		RECV_NOTHING,
		/// Cannot open a socket or the socket was closed
		NO_SOCKET,
		/// Host unreachable
		NO_HOST,
		/// Send bloqued by the select
		NO_SEND,
		/// Receive bloqued by the select
		NO_RECV,
		/// Receive an empty message
		RECV_EMPTY,
		/// Bind error
		ERROR_BINDSOCK,
		/// Listen error
		ERROR_LISTEN,
		/// Accept error
		ERROR_ACCEPT,
		/// Buffer allocation error
		ERROR_MALLOC,
	};
 
	/**
	 * Debug mode
	 */
	enum DebugMode
	{
		/// No debug
		NO_DEBUG     = 0x00,
		/// Debug on stdout
		DEBUG_STDOUT = 0x01,
		/// Debug on file
		DEBUG_FILE   = 0x02,
		/// Both debug mode
		DEBUG_ALL    = DEBUG_STDOUT | DEBUG_FILE,
	};

	/**
	 * Close the socket
	 */
	void closeSock();

	/**
	 * Set time (in millisecond) before considers host is unreachable or
	 * message not available.
	 * @param timeout global timeout for read operations.
	 */
	void setTimeout ( unsigned long int timeout );

	/**
	 * Get the last error encoured.\n
	 * If an empty string is returned, no error encoured.
	 */
	const DString & getLastError() const;

	/**
	 * Get the last status code.
	 * @return status code
	 * @see #StatusState
	 */
	int getStatus();

	/**
	 * Set the buffer size for read operations.\n
	 * @param size the size of the buffer which is 80 by default.
	 */
	void setBufferSize ( size_t size = 80 );

	/**
	 * Activate or desactivate debug modes
	 * @param mode the debug mode
	 * @see #DebugMode
	 */
	void setDebug ( int mode );

	/**
	 * Set the file name in case of debug on file
	 * @param filename the file name to write.
	 */
	void setDebugFile ( DString filename );

protected:
	/**
	 * print message into stdout and/or debug file
	 * @param message The message to print
	 */
	void printMessage(DString message);

	/**
	 * Constructor
	 */
	DSock();
	
	/**
	 * Virtual destructor
	 */
	virtual ~DSock();
	
	/// Socket handle.
	int m_hSocket;
	/// Time before consider host is unreachable or host have nothing to sent.
	long unsigned int m_timeout;
	/// The last error.
	DString m_lastError;
	/// status code about connection or communication.
	int m_status;
	/// The buffer size.
	size_t m_buffSize;
	/// The log file for debug
	DString m_debugfile;
	/// The debug flag
	int m_debug;
};

/**
 * This class give tools for working with socket (Client part).\n
 * The host argument of openSock function must be an IP address. For using it
 * with a hostname, a DURL object must be passed.\n
 * @brief Tools for working with sockets, client part
 * @author Didier Fabert <didier.fabert@gmail.com>
 * @include testdsockclient.cpp
 */
class DClientSock : public DSock
{
public:
	/**
	 * Default constructor
	 */
	DClientSock();
	/**
	 * Default destructor
	 */
	~DClientSock();

	/**
	 * Open the socket on host \p host on the port \p port. \n
	 * The host argument of openSock function must be an IP address.\n
	 * @return The status code.\n
	 * @see #StatusState
	 */
	int openSock ( const DString & host, int port );

	/**
	 * Open the socket on host \p host on the port \p port. \n
	 * This is an overloaded member function, provided for convenience.
	 * It behaves essentially like the above function.\n
	 * @return The status code.
	 * @see #StatusState
	 */
	int openSock ( const DString & host, const DString & port );

	/**
	 * Open the socket on URL \p url on the port \p port. \n
	 * This is an overloaded member function, provided for convenience.
	 * It behaves essentially like the above function.\n
	 * @return The status code.
	 * @see StatusState
	 */
	int openSock ( const DURL & url );

	/**
	 * Send the message \p message throught the socket.\n
	 * @param message The message to send.
	 * @param checkSock If checkSock is true, the socket status is checked
	 * by a read operation before writing.
	 * @return The status code.
	 * @see #StatusState
	 */
	int writeMessage ( const DString & message, bool checkSock = true );

	/**
	 * Try to send the message \p message \p retry time throught the socket.\n
	 * This is an overloaded member function, provided for convenience.
	 * It behaves essentially like the above function.\n
	 * @param message The message to send.
	 * @param retry The number of attempt.
	 * @param checkSock If checkSock is true, the socket status is checked
	 * by a read operation before writing.
	 * @return The status code.\n
	 * @see #StatusState
	 */
	int writeMessage ( const DString & message,
					   unsigned short int retry,
					   bool checkSock = true );

	/**
	 * Send packet \p packet throught the socket.\n
	 * It behaves essentially like the above function, but without adding a
	 * line feed and return carriage to the packet before send it.\n
	 * @param packet The packet to send.
	 * @param checkSock If checkSock is true, the socket status is checked
	 * by a read operation before writing.
	 * @return The status code.
	 * @see StatusStateSend a message \p message
	 */
	int sendPacket ( const DString & packet, bool checkSock = true );

	/**
	 * Receive the message \p message from the socket.\n
	 * @param message A reference to the message which must be fetched.
	 * @return The status code.\n
	 * @see #StatusState
	 */
	int readMessage ( DString & message );

	/**
	 * Try to receive the message \p message \p retry time from the socket.\n
	 * This is an overloaded member function, provided for convenience.
	 * It behaves essentially like the above function.
	 * @param message A reference to the message which must be fetched.
	 * @param retry The number of attempt.
	 * @return The status code.\n
	 * @see #StatusState
	 */
	int readMessage ( DString & message, unsigned short int retry );
};

/**
 * This class give tools for working with socket (Server part)\n
 * @include testdsockserver.cpp
 * @brief Tools for working with sockets, server part
 * @author Didier Fabert <didier.fabert@gmail.com>
 */
class DServerSock : public DSock
{
public:
	/**
	 * Default constructor
	 */
	DServerSock();
	/**
	 * Default destructor
	 */
	~DServerSock();

	/**
	 * Open the socket on the port \p port.\n
	 * @param port The port to listen new connection.
	 * @return The status code.
	 * @see #StatusState
	 */
	int openSock ( int port );

	/**
	 * Open the socket on the port \p port. \n
	 * This is an overloaded member function, provided for convenience.\n
	 * It behaves essentially like the above function.\n
	 * @param port The port to listen new connection.
	 * @return The status code.
	 * @see #StatusState
	 */
	int openSock ( const DString & port );

	/**
	 * Get socket from super daemon ( inetd, xinetd, etc ... ). \n
	 * @return The status code.
	 * @see #StatusState
	 */
	int dupSock ();

	/**
	 * Accept a new socket client connection and get its handle by reference.\n
	 * @param hSock A reference to the client socket handle.
	 * @return the status code.
	 * @see #StatusState
	 */
	int openConnection ( int & hSock );

	/**
	 * Close the internal server socket.
	 * @param hSock A reference to the client socket handle.
	 */
	void closeConnection ( int & hSock );

	/**
	 * Send the message \p message throught the socket
	 * pointed by handle \p hSock. \n
	 * If checkSock is true, the socket status is checked before write
	 * operation.\n
	 * @param hSock The client socket handle.
	 * @param message The message to send.
	 * @param checkSock If checkSock is true, the socket status is checked
	 * by a read operation before writing.
	 * @return the status code.
	 * @see #StatusState
	 */
	int writeMessage ( int hSock, const DString & message, bool checkSock = true );

	/**
	 * Try to send the message \p message \p retry time throught the socket
	 * pointed by handle \p hSock. \n
	 * This is an overloaded member function, provided for convenience.
	 * It behaves essentially like the above function.\n
	 * @param hSock The client socket handle.
	 * @param message The message to send.
	 * @param retry The number of attempt.
	 * @param checkSock If checkSock is true, the socket status is checked
	 * by a read operation before writing.
	 * @return the status code.\n
	 * @see #StatusState
	 */
	int writeMessage ( int hSock,
						const DString & message,
						unsigned short int retry,
						bool checkSock = true );


	/**
	 * Send packet \p packet throught the socket pointed by handle \p hSock. \n
	 * It behaves essentially like the above function, but without adding a
	 * line feed and return carriage to the packet before send it.\n
	 * @param hSock The client socket handle.
	 * @param packet The packet to send.
	 * @param checkSock If checkSock is true, the socket status is checked
	 * by a read operation before writing.
	 * @return the status code.
	 * @see #StatusState
	 */
	int sendPacket ( int hSock, const DString & packet, bool checkSock = true );
	
	/**
	 * Receive the message \p message from the socket
	 * pointed by handle \p hSock. \n
	 * @param hSock The client socket handle.
	 * @param message A reference to the message which must be fetched.
	 * @return the status code.\n
	 * @see #StatusState
	 */
	int readMessage ( int hSock, DString & message );

	/**
	 * Try to receive the message \p message \p retry time from the socket
	 * pointed by handle \p hSock. \n
	 * This is an overloaded member function, provided for convenience.
	 * It behaves essentially like the above function.
	 * @param hSock The client socket handle.
	 * @param message A reference to the message which must be fetched.
	 * @param retry The number of attempt.
	 * @return the status code.\n
	 * @see #StatusState
	 */
	int readMessage ( int hSock, DString & message, unsigned short int retry );

	/**
	 * Get client address
	 * @return The client address.
	 */
	const DString & getClientAddress() const;

private:
	/// Client address.
	DString clientAddress;
};


#endif // DCLIENTSOCK_H
