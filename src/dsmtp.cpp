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
 *     (___)_)   File : dsmtp.cpp                           ||--|| *          *
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

#include "dsmtp.h"
#include "dsocket.h"

DSMTP::Data::Data()
{
}

DSMTP::Data::~Data()
{
}

void DSMTP::Data::clear()
{
	host.clear();
	receiver.clear();
	bcc.clear();
	subject.clear();
	body.clear();
}

/******************************************************************************/

DSMTP::DSMTP()
{
	m_data.clear();
	m_timeout = 2000;
	m_errno = SUCCESS;
}

DSMTP::~DSMTP()
{
}

void DSMTP::setHost(const DURL & server)
{
	m_data.host = server;
}

void DSMTP::setSender(const DString & sender)
{
	m_data.sender = sender;
}

void DSMTP::unsetSender()
{
	m_data.sender.clear();
}

void DSMTP::setReceiver(const DStringList & receiver)
{
	m_data.receiver = receiver;
}

void DSMTP::addReceiver(const DString & receiver)
{
	m_data.receiver.push_back(receiver);
}

void DSMTP::removeReceiver(const DString & receiver)
{
	DStringList::iterator it;
	
	if (receiver.isEmpty())
	{
		m_data.receiver.clear();
	}
	else
	{
		for (it = m_data.receiver.begin() ; it != m_data.receiver.end() ; it++)
		{
			if ((*it) == receiver)
			{
				m_data.receiver.erase(it);
			}
		}
	}
}

void DSMTP::setBCC(const DStringList & bcc)
{
	m_data.bcc = bcc;
}

void DSMTP::removeBCC(const DString & receiver)
{
	DStringList::iterator it;
	
	if (receiver.isEmpty())
	{
		m_data.bcc.clear();
	}
	else
	{
		for (it = m_data.bcc.begin() ; it != m_data.bcc.end() ; it++)
		{
			if ((*it) == receiver)
			{
				m_data.bcc.erase(it);
			}
		}
	}
}

void DSMTP::setCC(const DStringList & cc)
{
	m_data.cc = cc;
}

void DSMTP::removeCC(const DString & receiver)
{
	DStringList::iterator it;
	
	if (receiver.isEmpty())
	{
		m_data.cc.clear();
	}
	else
	{
		for (it = m_data.cc.begin() ; it != m_data.cc.end() ; it++)
		{
			if ((*it) == receiver)
			{
				m_data.cc.erase(it);
			}
		}
	}
}

void DSMTP::setEmail(const DString & subject, const DString & body)
{
	m_data.subject = subject;
	m_data.body = body;
}

void DSMTP::unsetEmail()
{
	m_data.subject.clear();
	m_data.body.clear();
}

DSMTP::ERRNO DSMTP::send()
{
	DClientSock sock;
	DString buffer;
	DStringList lines;
	DStringList::iterator it, it2;
	DStringList formatedBody;

	sock.setTimeout(m_timeout);
	sock.setBufferSize( 1024 );
	if (sock.openSock(m_data.host) != DSock::SUCCESS)
	{
		m_serverlog.push_back( m_data.host.toString() );
		m_errno = NO_HOST;
		return m_errno;
	}

    // Listen server informations
	if (sock.readMessage(buffer) != DSock::SUCCESS)
	{
		m_errno = NO_HELO;
		return m_errno;
	}
	m_serverlog.push_back("->" + buffer.simplifyWhiteSpace());
	if (!checkReturn(buffer, "220"))
	{
		m_errno = NO_HELO;
		return m_errno;
	}

    // Say hello
	if ( m_data.host.isIPAddress() )
	{
		buffer = "HELO " + m_data.host.getIPAddress();
	}
	else
	{
		buffer = "HELO " + m_data.host.getHost();
	}
	m_serverlog.push_back(buffer);
	if (sock.writeMessage(buffer) != DSock::SUCCESS)
	{
		m_errno = NO_HELO;
		return m_errno;
	}
	if (sock.readMessage(buffer) != DSock::SUCCESS)
	{
		m_errno = NO_HELO;
		return m_errno;
	}
	m_serverlog.push_back("->" + buffer.simplifyWhiteSpace());
	if (!checkReturn(buffer, "250"))
	{
		m_errno = NO_HELO;
		return m_errno;
	}
	
	// Set sender
	buffer = "MAIL FROM: " + m_data.sender;
	m_serverlog.push_back(buffer);
	if (sock.writeMessage(buffer) != DSock::SUCCESS)
	{
		m_errno = NO_SENDER;
		return m_errno;
	}
	if (sock.readMessage(buffer) != DSock::SUCCESS)
	{
		m_errno = NO_SENDER;
		return m_errno;
	}
	m_serverlog.push_back("->" + buffer.simplifyWhiteSpace());
	if (!checkReturn(buffer, "250"))
	{
		m_errno = NO_SENDER;
		return m_errno;
	}
	
    // Set receiver
	for (it = m_data.receiver.begin() ; it != m_data.receiver.end() ; it++)
	{
		buffer = *it;
		if (!buffer.simplifyWhiteSpace().isEmpty())
		{
			buffer.prepend("RCPT TO: ");
			m_serverlog.push_back(buffer);
			if (sock.writeMessage(buffer) != DSock::SUCCESS)
			{
				m_errno = NO_RECVER;
				return m_errno;
			}
			if (sock.readMessage(buffer) != DSock::SUCCESS)
			{
				m_errno = NO_RECVER;
				return m_errno;
			}
			m_serverlog.push_back("->" + buffer.simplifyWhiteSpace());
			if (!checkReturn(buffer, "250"))
			{
				m_errno = NO_RECVER;
				return m_errno;
			}
		}
	}
	
    // Set CC
	for (it = m_data.cc.begin() ; it != m_data.cc.end() ; it++)
	{
		buffer = *it;
		if (!buffer.simplifyWhiteSpace().isEmpty())
		{
			buffer.prepend("RCPT TO: ");
			m_serverlog.push_back(buffer);
			if (sock.writeMessage(buffer) != DSock::SUCCESS)
			{
				m_errno = NO_RECVER;
				return m_errno;
			}
			if (sock.readMessage(buffer) != DSock::SUCCESS)
			{
				m_errno = NO_RECVER;
				return m_errno;
			}
			m_serverlog.push_back("->" + buffer.simplifyWhiteSpace());
			if (!checkReturn(buffer, "250"))
			{
				m_errno = NO_RECVER;
				return m_errno;
			}
		}
	}
	
    // Set Bcc
	for (it = m_data.bcc.begin() ; it != m_data.bcc.end() ; it++)
	{
		buffer = *it;
		if (!buffer.simplifyWhiteSpace().isEmpty())
		{
			buffer.prepend("RCPT TO: ");
			m_serverlog.push_back(buffer);
			if (sock.writeMessage(buffer) != DSock::SUCCESS)
			{
				m_errno = NO_RECVER;
				return m_errno;
			}
			if (sock.readMessage(buffer) != DSock::SUCCESS)
			{
				m_errno = NO_RECVER;
				return m_errno;
			}
			m_serverlog.push_back("->" + buffer.simplifyWhiteSpace());
			if (!checkReturn(buffer, "250"))
			{
				m_errno = NO_RECVER;
				return m_errno;
			}
		}
	}
	
	// Set mail
	buffer = "DATA";
	m_serverlog.push_back(buffer);
	if (sock.writeMessage(buffer) != DSock::SUCCESS)
	{
		m_errno = NO_SEND_DATA;
		return m_errno;
	}
	if (sock.readMessage(buffer) != DSock::SUCCESS)
	{
		m_errno = NO_SEND_DATA;
		return m_errno;
	}
	m_serverlog.push_back("->" + buffer.simplifyWhiteSpace());
	if (!checkReturn(buffer, "354"))
	{
		m_errno = NO_SEND_DATA;
		return m_errno;
	}
	
	buffer = "Subject: " + m_data.subject;
	m_serverlog.push_back(buffer);
	if (sock.writeMessage(buffer) != DSock::SUCCESS)
	{
		m_errno = NO_SEND_DATA;
		return m_errno;
	}
	
	buffer = "From: " + m_data.sender;
	m_serverlog.push_back(buffer);
	if (sock.writeMessage(buffer) != DSock::SUCCESS)
	{
		m_errno = NO_SEND_DATA;
		return m_errno;
	}

	buffer = "To: ";
	for (it = m_data.receiver.begin() ; it != m_data.receiver.end() ; it++)
	{
		buffer += *it + ",";
	}
	buffer.truncate(buffer.length() - 1); //remove last colon
	m_serverlog.push_back(buffer);
	if (sock.writeMessage(buffer) != DSock::SUCCESS)
	{
		m_errno = NO_SEND_DATA;
		return m_errno;
	}

	if (m_data.cc.size())
	{
		buffer = "Cc: ";
		for (it = m_data.cc.begin() ; it != m_data.cc.end() ; it++)
		{
			buffer += *it + ",";
		}
		buffer.truncate(buffer.length() - 1); //remove last colon
		m_serverlog.push_back(buffer);
		if (sock.writeMessage(buffer) != DSock::SUCCESS)
		{
			m_errno = NO_SEND_DATA;
			return m_errno;
		}
	}

	if (m_data.bcc.size())
	{
		buffer = "BCc: ";
		for (it = m_data.bcc.begin() ; it != m_data.bcc.end() ; it++)
		{
			buffer += *it + ",";
		}
		buffer.truncate(buffer.length() - 1); //remove last colon
		m_serverlog.push_back(buffer);
		if (sock.writeMessage(buffer) != DSock::SUCCESS)
		{
			m_errno = NO_SEND_DATA;
			return m_errno;
		}
	}
	
	buffer = "Date: " + DString::timeToString(time(NULL), "%a, %d %b %Y %H:%M:%S %z");
	m_serverlog.push_back(buffer);
	if (sock.writeMessage(buffer) != DSock::SUCCESS)
	{
		m_errno = NO_SEND_DATA;
		return m_errno;
	}
	
	formatedBody = m_data.body.split("\n");
	for (it = formatedBody.begin() ; it != formatedBody.end() ; it++)
	{
		buffer = *it;
		lines = buffer.splitConstantSize( " ", 78 );
		// send line by line
		for (it2 = lines.begin() ; it2 != lines.end() ; it2++)
		{
			m_serverlog.push_back(*it2);
			if (sock.writeMessage(*it2) != DSock::SUCCESS)
			{
				m_errno = NO_SEND_DATA;
				return m_errno;
			}
		}
	}

	// Send end of data
	buffer = ".";
	m_serverlog.push_back(buffer);
	if (sock.writeMessage(buffer) != DSock::SUCCESS)
	{
		m_errno = NO_END_DATA_SENT;
		return m_errno;
	}
	if (sock.readMessage(buffer) != DSock::SUCCESS)
	{
		m_errno = NO_END_DATA_SENT;
		return m_errno;
	}
	m_serverlog.push_back("->" + buffer.simplifyWhiteSpace());
	if (!checkReturn(buffer, "250"))
	{
		m_errno = NO_END_DATA_SENT;
		return m_errno;
	}
	
	// Quit
	buffer = "QUIT";
	m_serverlog.push_back(buffer);
	if (sock.writeMessage(buffer) != DSock::SUCCESS)
	{
		m_errno = NO_GOOD_QUIT;
		return m_errno;
	}
	if (sock.readMessage(buffer) != DSock::SUCCESS)
	{
		m_errno = NO_GOOD_QUIT;
		return m_errno;
	}
	m_serverlog.push_back("->" + buffer.simplifyWhiteSpace());
	if (!checkReturn(buffer, "221"))
	{
		m_errno = NO_GOOD_QUIT;
		return m_errno;
	}
	m_errno = SUCCESS;
	return m_errno;
}

bool DSMTP::checkReturn(const DString & status, const DString & expected)
{
	if (status.left(3) != expected)
	{
		return false;
	}
	return true;
}

void DSMTP::clear()
{
	m_data.clear();
	m_errno = SUCCESS;
}

const DString & DSMTP::getLastError() const
{
	static DString err;
	
	err.setNum( m_errno );
	err.prepend( "error (" );
	err.append( ")" );
	
	switch( m_errno )
	{
		case SUCCESS:
		{
			err.clear();
			break;
		}
		case NO_HOST:
		{
			err += " during the SMTP server connection";
			break;
		}
		case NO_MESSAGE:
		{
			err += " during the first SMTP server message";
			break;
		}
		case NO_HELO:
		{
			err += " during the beginning of the transaction";
			break;
		}
		case NO_SENDER:
		{
			err += " during the setup of the sender";
			break;
		}
		case NO_RECVER:
		{
			err += " during the setup of the receiver";
			break;
		}
		case NO_SEND_DATA:
		{
			err += " during the setup of body email";
			break;
		}
		case NO_END_DATA_SENT:
		{
			err += " during the end of body email setup";
			break;
		}
		case NO_GOOD_QUIT:
		{
			err += " during the end of transaction";
			break;
		}
		default:
		{
			err += " : Unknow error";
		}
	}
	return err;
}

DSMTP::ERRNO DSMTP::getLastErrno() const
{
	return m_errno;
}

const DStringList & DSMTP::getTransactionLog() const
{
	return m_serverlog;
}

void DSMTP::setTimeOut(unsigned long int timeout)
{
	m_timeout = timeout;
}
