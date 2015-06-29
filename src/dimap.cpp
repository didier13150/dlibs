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
 *     (___)_)   File : dimap.cpp                           ||--|| *          *
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
#include "dimap.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <curl/curl.h>

DIMAP::DIMAP():
	m_dir( "INBOX" ), m_timeout( 30 ), m_uid ( 1 )
{
}

DIMAP::~DIMAP()
{
}

void DIMAP::setHostname( const DString & host )
{
	m_host = host;
}

const DString & DIMAP::getHostname()
{
	return m_host;
}

void DIMAP::setLogin( const DString & user, const DString & password )
{
	m_user = user;
	m_password = password;
}
    
void DIMAP::setUser( const DString & user )
{
	m_user = user;
}

const DString & DIMAP::getUser()
{
	return m_user;
}

void DIMAP::setPassword( const DString & password )
{
	m_password = password;
}

const DString & DIMAP::getPassword()
{
	return m_password;
}

void DIMAP::setDir( const DString & dir )
{
	clear();
	m_dir = dir;
}

const DString & DIMAP::getDir()
{
	return m_dir;
}

void DIMAP::setTimeout( unsigned int timeout )
{
	m_timeout = timeout;
}

unsigned int DIMAP::getTimeout()
{
	return m_timeout;
}

unsigned int DIMAP::getUid()
{
	return m_uid;
}

void DIMAP::clear()
{
	m_uid = 1;
	m_current_message.clear();
	m_err.clear();
}

const DString & DIMAP::getMessage()
{
	CURL* curl = 0;
	DString buffer;
	CURLcode res = CURLE_OK;
	std::ostringstream stream;
	
	m_err.clear();
	m_current_message.clear();
	curl = curl_easy_init();
	if( ! curl ) {
		m_err = "curl_easy_init() failed: ";
		m_err += curl_easy_strerror( CURLE_FAILED_INIT );
		m_current_message = DString::empty();
		return m_current_message;
	}
	
	// Set username and password
	curl_easy_setopt( curl, CURLOPT_USERNAME, m_user.c_str() );
	curl_easy_setopt( curl, CURLOPT_PASSWORD, m_password.c_str() );
	
	curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, &data_write );
	curl_easy_setopt( curl, CURLOPT_NOPROGRESS, 1L );
	curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L );
	curl_easy_setopt( curl, CURLOPT_FILE, &stream );
	curl_easy_setopt( curl, CURLOPT_TIMEOUT, m_timeout );
	
	buffer = "imap://" + m_host;
	curl_easy_setopt( curl, CURLOPT_URL, buffer.c_str() );
	
	buffer.setNum( m_uid );
	buffer.prepend( "imap://" + m_host + "/" + m_dir + "/;UID=" );
	curl_easy_setopt( curl, CURLOPT_URL, buffer.c_str() );
	
	// Perform the list
	res = curl_easy_perform( curl );
	if( res != CURLE_OK ) {
		m_err = "curl_easy_perform() failed: ";
		m_err += curl_easy_strerror( res );
		m_current_message = DString::empty();
		return m_current_message;
	}
	curl_easy_cleanup( curl );
	m_current_message = stream.str();
	
	return m_current_message;
}

bool DIMAP::setFlag( DIMAP::DIMAPFlag flag)
{
	DString action, buffer;
	CURL* curl = 0;
	CURLcode res = CURLE_OK;
	std::ostringstream stream;
	
	switch( flag )
	{
		case DIMAP::DELETED:
		{
			action = "Deleted";
			break;
		}
		case DIMAP::SEEN:
		{
			action = "Seen";
			break;
		}
		case DIMAP::ANSWERED:
		{
			action = "Answered";
			break;
		}
		case DIMAP::FLAGGED:
		{
			action = "Flagged";
			break;
		}
		case DIMAP::DRAFT:
		{
			action = "Draft";
			break;
		}
		case DIMAP::RECENT:
		{
			action = "Recent";
			break;
		}
	}
		
	curl = curl_easy_init();
	if( ! curl ) {
		m_err = "curl_easy_init() failed: ";
		m_err += curl_easy_strerror( CURLE_FAILED_INIT );
		return false;
	}
	
	// Set username and password
	curl_easy_setopt( curl, CURLOPT_USERNAME, m_user.c_str() );
	curl_easy_setopt( curl, CURLOPT_PASSWORD, m_password.c_str() );
	
	curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, &data_write );
	curl_easy_setopt( curl, CURLOPT_NOPROGRESS, 1L );
	curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L );
	curl_easy_setopt( curl, CURLOPT_FILE, &stream );
	curl_easy_setopt( curl, CURLOPT_TIMEOUT, m_timeout );
	
	buffer = "imap://" + m_host + "/" + m_dir;
	curl_easy_setopt( curl, CURLOPT_URL, buffer.c_str() );
	
	buffer.setNum( m_uid );
	buffer.prepend( "STORE ");
	buffer.append( " +Flags \\" + action );
	
	curl_easy_setopt( curl, CURLOPT_CUSTOMREQUEST, buffer.c_str() );
	res = curl_easy_perform( curl );
	if( res != CURLE_OK ) {
		m_err = "curl_easy_perform(" + buffer + ") failed: ";
		m_err += curl_easy_strerror( res );
		return false;
	}
	
	if ( flag == DIMAP::DELETED ) {
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "EXPUNGE");
		res = curl_easy_perform( curl );
		if( res != CURLE_OK ) {
			m_err = "curl_easy_perform(EXPUNGE) failed: ";
			m_err += curl_easy_strerror( res );
			return false;
		}
	}
	
	curl_easy_cleanup( curl );
	return true;
}

bool DIMAP::erase()
{
	return setFlag( DIMAP::DELETED );
}

bool DIMAP::read()
{
	return setFlag( DIMAP::SEEN );
}

void DIMAP::next()
{
	m_uid++;
}

const DString & DIMAP::getLastError()
{
	return m_err;
}

// callback function writes data to a std::ostream
static size_t data_write( void* buffer, size_t size, size_t nmemb, void* userp )
{
	if( userp )
	{
		std::ostream& os = *static_cast<std::ostream*>( userp );
		std::streamsize len = size * nmemb;
		if( os.write( static_cast<char*>( buffer ), len ) ) {
			return len;
		}
	}
	return 0;
}
