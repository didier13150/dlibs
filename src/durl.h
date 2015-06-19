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

#ifndef DURL_H
#define DURL_H

#include "dstring.h"
#include <stdint.h>
 
/**
 * Class to manage network address
 * @include durl.dox
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
     * @typedef Type
	 * Defining All URL type
	 */
	typedef enum type
	{
		/// The URL is a hostname.
		HOSTNAME,
		/// The URL is a IPv4 address.
		IPV4_ADDR,
		/// The URL is a IPv6 address.
		IPV6_ADDR,
	} Type;

	/**
     * @typedef Error
	 * Defining All error messages
	 */
	typedef enum error
	{
		/// No error
		SUCCESS,
		/// Cannot get host by address
		NO_HOST_BY_ADDR,
		/// Cannot get host by name
		NO_HOST_BY_NAME,
		/// Cannot get service name
		NO_SERVICE,
		/// IP address is out of range
		IP_OUT_OF_RANGE,
	} Error;
	
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
	int getPort() const;
	
	/**
	* Get the protocol of the URL
	*/
	const DString & getServiceName() const;
	
	/**
	* Get the protocol of the URL
	*/
	const DString & getPath() const;

	/**
	* Return URL type.
	* 
	*/
	const Type & getType() const;

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
	 * Get the port number by service and protocol.
	 * @param service The service name ( http, ftp, ssh, etc... )
	 * @param protocol The protocol ( tcp, udp )
	 * @return the port related to the service or 0 if nothing was found
	 */
	static int getPortByService( const DString & service,
								 const DString & protocol = "tcp" );
	
	/**
	 * Get the service name by port and protocol.
	 * @param port The service port number
	 * @param protocol The protocol ( tcp, udp )
	 * @return the service name related to the port or an empty DString if nothing was found.
	 */
	static const DString & getServiceByPort( const int port,
											 const DString & protocol = "tcp" );

protected:

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
	/// URL type
	Type m_type;
	/// The last error number
	int m_errno;
	/// The last error string.
	DString m_error;
	
	/**
	 * Check if URL is an IP address.
	 * @return true if URL is an IP address. False otherwise.
	 */
	Type checkType( const DString & address );
	
	/**
	 * Encode URL
	 */
	void encode();
	
	/**
	 * Get string representation about hexadecimal char code
	 */
	inline DString getHexaCharString( uint32_t code );
};


#endif // DURL_H
