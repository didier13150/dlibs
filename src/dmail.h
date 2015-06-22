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
 *     (___)_)   File : dmail.h                             ||--|| *          *
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
#ifndef _DMAIL_H_
#define _DMAIL_H_

#include <dstring.h>
#include <map>


class DMailPart
{
public:
	DMailPart();
	DMailPart( const DString & raw,
		   const DString & type = "text/plain",
		   const DString & charset = "UTF8",
		   const DString & transfert_encoding = "7bits"
  		 );
	
	enum{
		SUCCESS   = 0x00,
		MULTIPART = 0x01,
		ERROR     = 0x02
	};
	
	~DMailPart();
	int setPart( const DString & part );
	const DString & getPart();
	
	void setType( const DString & type );
	const DString & getType();
	
	void setCharset( const DString & charset );
	const DString & getCharset();
	
	void setTransfertEncoding( const DString & transfert_encoding );
	const DString & getTransfertEncoding();
	
	void setRawPart( const DString & part );
	const DString & getRawPart();
	
	const DString & getBoundary();
	
	void clear();
	
protected:
	DString m_type;
	DString m_charset;
	DString m_transfert_encoding;
	DString m_rawpart;
	DString m_part;
	DString m_boundary;
};

typedef std::map<DString, DString> DMailHeader;
typedef std::list<DMailPart> DMailPartList;

class DMail
{
public:
	DMail();
	~DMail();
	
	/**
	 * Set email as a string, parse and integrate it.
	 * @param email The entire email in a string
	 * @return true if email was integrated, false otherwise.
	 */
	bool setMail( const DString & email );
	
	/**
	 * Get formated email: header, data
	 */
	const DString & getMail();
	
	void addHeader( const DString & key, const DString & value );
	const DString & getHeader( const DString & key );
	
	DStringList getHeaderList();
	
	void addMailPart( const DMailPart & part);
	const DMailPartList & getMailPartList();
	
	void setBoundary( const DString & boundary );
	const DString & getBoundary();
	
	void clear();

	static DString getRandomBoundary();
	
protected:
	DMailHeader m_header;
	DMailHeader m_real_header_name;
	DMailPartList m_content_part;
	DString m_boundary;
	DString m_mail;
};


#endif // _DMAIL_H_
