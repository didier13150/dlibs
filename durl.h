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
*     (___)_)   File : durl.h                              ||--|| *          *
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

#ifndef DURL_H
#define DURL_H

#include "dstring.h"

using namespace std;


/**
* Class to manage network address
* @include testdurl.cpp
* @brief Network address.
* @author Didier Fabert <didier.fabert@gmail.com>
*/
class DURL
{
public:
	/**
	* Empty constructor
	*/
	DURL();

	/**
	* Destructor
	*/
	~DURL();

	/**
	* Default constructor
	* @param url the url
	*/
	DURL(DString url);

	/**
	* All URL type
	*/
	enum URLType
	{
		/// The URL is a hostname.
		HOSTNAME,
		/// The URL is a IP address.
		IP_ADDR,
	};

	/**
	* All error messages
	*/
	enum Error
	{
		/// No error
		SUCCESS,
		/// Cannot get host by address
		NO_HOST_BY_ADDR,
		/// Cannot get host by name
		NO_HOST_BY_NAME,
		/// Cannot get service name
		NO_SERVICE,
	};
	
	/**
	* Set the URL (host name or IP address).
	* @param url The url
	*/
	int setURL( const DString & url );

	/**
	* Get the URL.
	*/
	const DString & getURL() const;

	/**
	* Get the hostname of the URL.\n
	* Can be an empty string if URL was set by an IP address.
	*/
	const DString & getHost() const;

	/**
	* Get the IP address of the URL.
	*/
	const DString & getIPAddress() const;
	
	/**
	* Get the port of the URL
	*/
	const int getPort() const;
	
	/**
	* Get the protocol of the URL
	*/
	const DString & getServiceName() const;
	
	/**
	* Get the protocol of the URL
	*/
	const DString & getPath() const;

	/**
	* Return true if the URL contains an IP address, false otherwise.
	*/
	bool isIPAddress() const;
	
	/**
	* Return true if the URL contains a host name, false otherwise.
	*/
	bool isHostname() const;

	/**
	* Get the last error string.
	*/
	const DString & getLastError() const;
	
	/**
	* Get the last errno
	*/
	int getLastErrno();

	/**
	* Clear the URL
	*/
	void clear();
	
	/**
	 * Convert DURL to human readable string
	 */
	const DString & toString() const;
	
	/**
	 * Writes DURL to the stream s and returns a reference to the stream.
	 */
	friend std::ostream & operator << ( std::ostream& s, const DURL & url );

	/**
	 * Get the port number by protocol.
	 * This function search in /etc/services the port according to the protocol name.
	 * @param service The service name ( http, ftp, ssh, etc... )
	 * @param protocol The protocol ( tcp, udp )
	 * @return the port affected to the service or 0 if nothing was found
	 */
	static int getPortByService( const DString & service,
								 const DString & protocol = "tcp" );

private:

	class DURLData
	{
	public:
		/**
		* Constructor
		*/
		DURLData();
		
		/**
		* Destructor
		*/
		~DURLData();
		
		/**
		* Clear the data.
		*/
		void clear();
		
		/**
		* Print the url data
		*/
		const DString & toString() const;
	
		/// The protocol name
		DString service;
		DString hostname;
		DString ip;
		DString path;
		DString url;
		int port;
	};
	
	/// The URL
	DURLData m_url;
	/// IP address only flag
	bool m_isIPAddress;
	/// The last error number
	int m_errno;
	/// The last error string.
	DString m_error;
	
	bool isIP( const DString & address );
};


#endif // DURL_H
