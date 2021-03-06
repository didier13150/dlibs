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
 *     (___)_)   File : dmail.cpp                           ||--|| *          *
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
#include "dmail.h"
#include "dbase64.h"
#include <stdlib.h>
#include <ctime>

DMail::DMail()
{
}

DMail::~DMail()
{
}

bool DMail::setMail( const DString & email )
{
	m_mail = email;
	DStringList lines = email.split( '\n', true );
	DStringList mail_parts;
	DString line, key, value, buffer;
	bool is_header = true;
	DMailPart part;
	
	clear();
	// Parse header
	for( DStringList::iterator it = lines.begin() ; it != lines.end() ; ++it ) {
		line = it->remove( '\r' );
		if ( is_header ) {
			if ( line == "" ) {
				// End of header
				is_header = false;
				buffer = key.lower();
				m_real_header_name[ buffer ] = key;
				if ( m_header.find( buffer ) != m_header.end() ) {
					m_header[ buffer ] += " " + value;
				}
				else {
					m_header[ buffer ] = value;
				}
				value.clear();
				// Check if mail is multipart
				if ( getHeader( "Content-Type" ).contains( "multipart") ) {
					m_boundary = getHeader( "Content-Type" ).section( "=", 1).remove( "\"" );
					
				}
			}
			if ( ( line.left(1) != " " ) and ( line.left(1) != "\t" ) ) {
				if ( key != DString::empty() ) {
					buffer = key.lower();
					m_real_header_name[ buffer ] = key;
					if ( m_header.find( buffer ) != m_header.end() ) {
						m_header[ buffer ] += " " + value;
					}
					else {
						m_header[ buffer ] = value;
					}
				}
				key = line.section( ":", 0, 0 ).simplifyWhiteSpace();
				value = line.section( ":", 1 ).simplifyWhiteSpace();
			}
			else {
				line = line.simplifyWhiteSpace();
				if ( line != DString::empty() ) {
					value += " " + line;
				}
			}
		}
		else {
			value += line + "\n";
		}
	}
	if ( m_boundary != DString::empty() ) {
		value.remove( "--" + m_boundary + "--" );
		mail_parts = value.split( "--" + m_boundary + "\n", false );
		
		for( DStringList::iterator it = mail_parts.begin() ; it != mail_parts.end() ; ++it ) {
			int ret = part.setPart( *it );
			if ( ret == DMailPart::MULTIPART )
			{
				DString boundary = part.getBoundary();
				DMailPart part2;
				buffer = *it;
				buffer.remove( "--" + boundary + "--" );
				DStringList mail_parts_second = buffer.split( "--" + boundary + "\n", false );
				for( DStringList::iterator it2 = mail_parts_second.begin() ; it2 != mail_parts_second.end() ; ++it2 ) {
					part2.setPart( *it2 );
					m_content_part.push_back( part2 );
					part2.clear();
				}
			}
			else {
				m_content_part.push_back( part );
			}
			part.clear();
		}
	}
	else {
		part.setPart( value );
		m_content_part.push_back( part );
	}
	return true;
}

const DString & DMail::getMail()
{
	bool is_multipart = false;
	
	if ( m_content_part.size() > 1 ) is_multipart = true;

	m_mail.clear();
	// Write headers first
	for( DMailHeader::iterator it = m_header.begin() ; it != m_header.end() ; ++it )
	{
		m_mail += it->first + ": " + it->second + "\n";
	}
	if ( is_multipart ) {
		if ( m_boundary.isEmpty() ) {
			m_boundary = DMail::getRandomBoundary();
		}
		m_mail += "Content-Type: multipart/alternative;\n";
		m_mail += "\tboundary=\"" + m_boundary + "\"\n";
	}
	else {
		m_mail += "Content-Type: text/plain; \n";
		m_mail += "\tcharset=UTF-8\n";
		m_mail += "Content-Transfer-Encoding: quoted-printable\n";
	}
	m_mail += "\n";
	
	for( DMailPartList::iterator it = m_content_part.begin() ; it != m_content_part.end() ; ++it ) {
		if( is_multipart ) {
			m_mail += "--" + m_boundary + "\n";
		}
		m_mail += it->getPart() + "\n";
	}
	if ( is_multipart ) {
		// Write last boundary
		m_mail += "--" + m_boundary + "--\n";
	}
	return m_mail;
}

DStringList DMail::getHeaderList()
{
	DMailHeader::iterator it;
	DStringList headers;
	for( it = m_real_header_name.begin() ; it != m_real_header_name.end() ; ++it )
	{
		headers.push_back( it->second );
	}
	return headers;
}

void DMail::addMailPart( const DMailPart & part)
{
	m_content_part.push_back( part );
}

const DMailPartList & DMail::getMailPartList()
{
	return m_content_part;
}

void DMail::setBoundary( const DString & boundary )
{
	m_boundary = boundary;
}

const DString & DMail::getBoundary()
{
	return m_boundary;
}

void DMail::addHeader( const DString & key, const DString & value )
{
	m_header[ key.lower() ] = value;
	m_real_header_name[ key.lower() ] = key;
}

const DString & DMail::getHeader( const DString & key )
{
	if ( m_header.find( key ) == m_header.end() ) {
		if ( m_header.find( key.lower() ) != m_header.end() ) {
			return m_header[ key.lower() ];
		}
		m_header[ key.lower() ] = "";
	}
	return m_header[ key.lower() ];
}

void DMail::clear()
{
	m_content_part.clear();
	m_real_header_name.clear();
	m_boundary.clear();
	m_header.clear();
	m_mail.clear();
}

const DString & DMail::getRandomBoundary()
{
	static DString boundary;
	DString buffer;
	clock_t t;
	
	boundary = "----=_Part_-";
	buffer.setNum( rand() % 999999999 ).leftJustify( 9, '0' );
	boundary += buffer + '_';
	buffer.setNum( rand() % 999999999 ).rightJustify( 9, '0' );
	boundary += buffer + '.';
	boundary += DString::Now( "%s" );
	t = clock();
	buffer.setNum( static_cast<int>( t / 10 ) );
	boundary += buffer;
	
	return boundary;
}

const DString & DMail::decodeSubject( const DString & encoded )
{
	static DString decoded;
	DString buffer;
	DStringList part;
	DStringList::const_iterator it;
	DBase64 base64;
	
	decoded.clear();
	if ( encoded.contains( "=?" ) ) {
		part = encoded.split( ' ' );
		for ( it = part.begin() ; it != part.end() ; ++it ) {
			if ( it->left( 10 ) == "=?utf-8?B?" or it->left( 10 ) == "=?UTF-8?B?" ) {
				base64.setEncoded( it->section( '?', 3, 3 ) );
				decoded += base64.getDecoded();
			}
			else if ( it->left( 15 ) == "=?iso-8859-1?B?" or it->left( 15 ) == "=?ISO-8859-1?B?" ) {
				base64.setEncoded( it->section( '?', 3, 3 ) );
				decoded += base64.getDecoded();
			}
			else if ( it->left( 10 ) == "=?utf-8?Q?" or it->left( 10 ) == "=?UTF-8?Q?" ) {
				buffer.fromQuotedPrintable( it->section( '?', 3, 3 ) );
				decoded += buffer;
			}
			else if ( it->left( 15 ) == "=?iso-8859-1?Q?" or it->left( 15 ) == "=?ISO-8859-1?Q?" ) {
				buffer.fromQuotedPrintable( it->section( '?', 3, 3 ) );
				decoded += buffer;
			}
			else {
				decoded += *it;
			}
		}
	}
	else {
		decoded = encoded;
	}
	
	return decoded;
}

/******************************************************************************/
DMailPart::DMailPart()
{
}

DMailPart::~DMailPart()
{
}

void DMailPart::clear()
{
	m_type.clear();
	m_charset.clear();
	m_transfert_encoding.clear();
	m_rawpart.clear();
	m_part.clear();
	m_boundary.clear();
}

void DMailPart::setType( const DString & type )
{
	m_type = type;
}

const DString & DMailPart::getType()
{
	return m_type;
}

void DMailPart::setCharset( const DString & charset )
{
	m_charset = charset;
}

const DString & DMailPart::getCharset()
{
	return m_charset;
}

void DMailPart::setTransfertEncoding( const DString & transfert_encoding )
{
	m_transfert_encoding = transfert_encoding;
}

const DString & DMailPart::getTransfertEncoding()
{
	return m_transfert_encoding;
}

void DMailPart::setRawPart( const DString & part )
{
	m_rawpart = part;
}

const DString & DMailPart::getRawPart()
{
	return m_rawpart;
}

int DMailPart::setPart( const DString & part )
{
	DStringList lines = part.split( '\n', true );
	DString line, buffer;
	bool is_header = true;
	
	clear();
	for( DStringList::iterator it = lines.begin() ; it != lines.end() ; ++it ) {
		line = *it;
		if ( is_header && line.left( 12 ).lower() == "content-type" ) {
			m_type = line.section( ';', 0, 0 ).section( ':', 1).toLower().remove( "\"" ).simplifyWhiteSpace();
			buffer = line.section( ';', 1 );
			if ( buffer.lower().contains( "charset" ) ) {
				m_charset = line.section( ';', 1 ).section( '=', 1).remove( "\"" ).simplifyWhiteSpace();
			}
			if ( m_type.contains( "multipart") ) {
				if ( line.contains( "boundary" ) ) {
					m_boundary = line.section( "=", 1).remove( "\"" );
					return DMailPart::MULTIPART;
				}
			}
		}
		else if ( is_header && line.contains( "boundary" ) ) {
			m_boundary = line.section( "=", 1).remove( "\"" );
			return DMailPart::MULTIPART;
		}
		else if ( is_header && line.left( 25 ).lower() == "content-transfer-encoding" ) {
			m_transfert_encoding = line.section( ':', 1).remove( "\"" ).simplifyWhiteSpace();
		}
		else if ( is_header && line == "" ) {
			is_header = false;
		}
		else {
			m_rawpart += line + "\n";
		}
	}
	return DMailPart::SUCCESS;
}

const DString & DMailPart::getPart()
{
	m_part.clear();
	if ( m_type != DString::empty() && m_charset != DString::empty() && m_transfert_encoding != DString::empty() ) {
		m_part += "Content-Type: " + m_type + "; charset=" + m_charset + "\n";
		m_part += "Content-Transfer-Encoding: " + m_transfert_encoding + "\n";
		m_part += "\n";
	}
	m_part += m_rawpart;
	return m_part;
}

const DString & DMailPart::getBoundary()
{
	return m_boundary;
}

/******************************************************************************/

