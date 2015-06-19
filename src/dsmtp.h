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
 *     (___)_)   File : dsmtp.h                             ||--|| *          *
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

#ifndef DSMTP_H
#define DSMTP_H

#include "dstring.h"
#include "durl.h"
#include <unistd.h>

class DClientSock;

/**
 * @brief SMTP operations.
 * @author Didier FABERT <didier.fabert@gmail.com>
 * Send easily an email. Define a sender, one or more receiver, set a subject
 * and a message. Send it.
 * @include dsmtp.dox
 */
class DSMTP
{
public:
	/**
	 * Empty creator
	 */
	DSMTP();
	/**
	 * Default destructor
	 */
	~DSMTP();
	
	typedef enum
	{
        /// The email was sent.
		SUCCESS = 0,
        /// Cannot connect to host.
		NO_HOST,
		/// Host is reachable but doesn't sent hello message
		NO_MESSAGE,
		/// Cannot say hello to server.
		NO_HELO,
		/// Cannot set the sender.
		NO_SENDER,
		/// Cannot set the receiver.
		NO_RECVER,
		/// Server cannot accept text.
		NO_SEND_DATA,
		/// No mail data was sent.
		NO_END_DATA_SENT,
		/// Cannot quit sweeply.
		NO_GOOD_QUIT,
	}ERRNO;

	/**
	 * @brief All Email and mail server data.
	 * @author Didier FABERT <didier.fabert@gmail.com>
	 */
	class Data
	{
		public:
			/**
			* Empty creator
			*/
			Data();
			/**
			 * Default destructor
			 */
			~Data();

			/// The SMTP URL
			DURL host;
			/// The email sender
			DString sender;
			/// The email receiver list
			DStringList receiver;
			/** The email receiver list, receivers which are received a copy of
			 * email.
			 */
			DStringList cc;
			/** The email receiver list, receivers which are vanished and which
			 * are received a copy of email.
			 */
			DStringList bcc;
			/// The email subject
			DString subject;
			/// The text email message
			DString txtbody;
			/// The html email message
			DString htmlbody;
			/// Attached document list (with path)
			DStringList attached;

			/**
			 * Clear all email data
			 */
			void clear();
	};
	
	/**
	 * Set the SMTP server parameters (host and port)
	 */
	void setHost(const DURL & server);
	/**
	 * Unset the SMTP server parameters (host and port)
	 */
	void unsetHost();

	/**
	 * Set the sender of mail
	 */
	void setSender(const DString & sender);
	/**
	 * Unset the sender of mail
	 */
	void unsetSender();
	
	/**
	 * Set the mail standart receiver list
	 */
	void setReceiver(const DStringList & receiver);
	/**
	 * Remove standart receiver.\n
	 * If receiver \p receiver is specified, only this one will be remove from 
	 * list. Otherwise, the list will be truncated.
	 */
	void removeReceiver(const DString & receiver = "");
	/**
	 * Add a single standart receiver
	 */
	void addReceiver(const DString & receiver);

	/**
	 * Set CC receiver list.
	 */
	void setCC(const DStringList & cc);
	/**
	 * Remove CC receiver.\n
	 * If receiver \p receiver is specified, only this one will be remove from
	 * list. Otherwise, the list will be truncated.
	 */
	void removeCC(const DString & receiver = "");
	/**
	 * Add a single CC receiver
	 */
	void addCC(const DString & receiver);
	
	/**
	 * Set BCC receiver list.
	 */
	void setBCC(const DStringList & bcc);
	/**
	 * Remove BCC receiver.\n
	 * If receiver \p receiver is specified, only this one will be remove from
	 * list. Otherwise, the list will be truncated.
	 */
	void removeBCC(const DString & receiver = "");
	/**
	 * Add a single BCC receiver
	 */
	void addBCC(const DString & receiver);
	
	/**
	 * Add attached document to email
	 */
	void addAttach( const DString & filename );
	/**
	 * Remove an attached document
	 */
	void removeAttach( const DString & filename );

	/**
	 * Set the email subject and main message
	 * @param subject Email subject
	 * @param txtbody Email text message
	 */
	void setEmail(const DString & subject, const DString & txtbody);

	/**
	 * Set the email subject and main message
	 * @param subject Email subject
	 * @param txtbody Email text message
	 * @param htmlbody Email html message
	 */
	void setEmail(const DString & subject,
				  const DString & txtbody,
				  const DString & htmlbody
				 );
	
	/**
	 * Unset the email subject and main message
	 */
	void unsetEmail();

	/**
	 * Send email. The SMTP server connection is only done at this step.
	 * @return the transaction status.
	 * @see ERRNO
	 */
	ERRNO send();

	/**
	 * Clear all email data
	 */
	void clear();

	/**
	 * Get the last error code
	 * @see ERRNO enum for returned values
	 */
	ERRNO getLastErrno() const;

    /**
	 * Get the last error string
	 */
	const DString & getLastError() const;

	/**
	 * Get all smtp transaction.
	 */
	const DStringList & getTransactionLog() const;

	/**
	 * Set the timeout for getting server answer.
	 */
	void setTimeOut(unsigned long int timeout);
	
	
private:
	/// Email data
	Data m_data;
	/// Internal errno
	ERRNO m_errno;
	/// Internal error string
	DString m_err;
	/// Internal smtp transaction
	DStringList m_serverlog;
	/// The socket read timeout
	unsigned long int m_timeout;

	/// Check if stmp server return is correct
	bool checkReturn( const DString & status, const DString & expected);
	
	inline void readMessage( DClientSock & sock, const DString & code, ERRNO errval );
};


/**
 * @relates DSMTP
 * Get MIME Type from filename
 * \param filename File name
 * \return MIME Type
 */
DString getMimeType( const DString & filename );
#endif // DSMTP_H
