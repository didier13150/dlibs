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
 * Download mail by IMAP
 * @short IMAP utilities.
 * @author Didier FABERT <didier.fabert@gmail.com>
 * @include dimap.dox
*/
class DIMAP
{
public:
    DIMAP();
    ~DIMAP();
    
    typedef enum Flag
    {
	   /// Message is marked as deleted for later removal with expunge or close command.
	   DELETED  = 0x01,
	   /// Message has been read
	   SEEN     = 0x02,
	   /// Message has been answered
	   ANSWERED = 0x03,
	   /// Message is flagged for urgent/special attention
	   FLAGGED  = 0x04,
	   /// Message is in draft format; in other words, not complete
	   DRAFT    = 0x05,
	   /// Message recently arrived in this mailbox. This flag cannot be set by client.
	   RECENT   = 0x06,
    } DIMAPFlag;
    
    /**
     * Set IMAP hostname
     * @param host IMAP hostname
     */
    void setHostname( const DString & host );
    
    /**
     * Get configured IMAP host
	 * @return IMAP host
     */
    const DString & getHostname();
    
    /**
     * Set mail account: user and password.
     * @param user IMAP account
     * @param password IMAP password
     */
    void setLogin( const DString & user, const DString & password );
    
    /**
     * Set mail user.
     * @param user IMAP account
     */
    void setUser( const DString & user );
    
    /**
     * Get configured IMAP user.
	 * @return IMAP user
     */
    const DString & getUser();
    
    /**
     * Set mail user password
     * @param password IMAP password
     */
    void setPassword( const DString & password );
    
    /**
     * Get configured IMAP password
	 * @return IMAP password
     */
    const DString & getPassword();
    
    /**
     * Set IMAP connection timeout.
     * @param timeout Timeout connection in seconds
     */
    void setTimeout( unsigned int timeout );
    
    /**
     * Get IMAP connection timeout.
	 * @return IMAP connection timeout
     */
    unsigned int getTimeout();
    
    /**
     * Change mail Directory (default is INBOX).
     * @param dir mail directory
     */
    void setDir( const DString & dir );
    
    /**
     * Get current directory.
	 * @return IMAP current directory.
     */
    const DString & getDir();
    
    /**
     * Get Message from IMAP server
     * @return Next message or an empty string if no more message was available.
     */
    const DString & getMessage();
    
    /**
     * Set flag to current message.
     * Flag can be Deleted, Seen, Answered, Flagged, Draft and Recent
     * @see DIMAPFlag
     */
    bool setFlag( DIMAPFlag flag);
    
    /**
     * Mark current message as deleted.
	 * @return true if success, false otherwise.
     */
    bool erase();
    
    /**
     * Mark current message as read.
	 * @return true if success, false otherwise.
     */
    bool read();

    /**
     * Go to next message
     */
    void next();
	
	/**
	 * Expunge current IMAP folder: delete messages marked as deleted.
	 * @return true if success, false otherwise.
	 */
	bool expunge();
	
	/**
	 * List IMAP directories
	 * @return IMAP directorie list.
	 */
	const DStringList & getDirList();
	
	/**
	 * Get current mail UID
	 * @return current mail indentifiant.
	 */
	unsigned int getUid();
    
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
	/// IMAP directories 
	DStringList m_dirs;
};

/**
 * callback function for curl to writes data in std::ostream
 */
static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp);

#endif // _DIMAP_H_
