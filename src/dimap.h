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
 *   ||_  \      Date : 2015, June                                            *
 *   \_|  o|                                             ,__,                 *
 *    \___/      Copyright (C) 2015 by didier fabert     (oo)____             *
 *     ||||__                                            (__)    )\           *
 *     (___)_)   File : dimap.h                             ||--|| *          *
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
#ifndef _DIMAP_H_
#define _DIMAP_H_

#include <dstring.h>


/**
* @short IMAP utilities.
* @author Didier FABERT <didier.fabert@gmail.com>
*/
class DIMAP
{
public:
    DIMAP();
    ~DIMAP();
    
    /**
     * Set IMAP hostname
     * @param host IMAP hostname
     */
    void setHostname( const DString & host );
    
    /**
     * Set mail account and password
     * @param user IMAP account
     * @param password IMAP password
     */
    void setLogin( const DString & user, const DString & password );
    
    /**
     * Set IMAP connection timeout
     * @param timeout Timeout connection in seconds
     */
    void setTimeout( unsigned int timeout );
    
    /**
     * Change mail Directory (default is INBOX)
     */
    void setDir( const DString & dir );
    
    /**
     * Get Message from IMAP server. A new message was sent at each call.
     * @return Next message or an empty string if no more message was available.
     */
    const DString & getNextMessage();

    /**
     * Get last error message
     * @return Last error message.
     */
    const DString & getLastError();
    
    /**
     * Reset internal counter and clear current and error messages
     */
    void clear();
        
protected:
	/// Last error message
	DString m_err;
	/// Last mail
	DString m_current_message;
	
	/// IMAP host
	DString m_host;
	/// IMAP user
	DString m_user;
	/// IMAP password
	DString m_password;
	/// IMAP directory (default is INBOX)
	DString m_dir;
	/// IMAP connection timeout (default is 30s)
	unsigned int m_timeout;
	/// internal message counter
	unsigned int m_uid;
};

/**
 * callback function for curl to writes data in std::ostream
 */
static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp);

#endif // _DIMAP_H_
