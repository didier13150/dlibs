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
 *     (___)_)   File : ddatabase.cpp                       ||--|| *          *
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

#include "ddatabase.h"

#ifndef WITH_EXCEPTIONS
#define WITH_EXCEPTIONS 0
#endif

DDatabase::DDatabase() : DSkeleton()
{
	internal_init();
}

#if WITH_EXCEPTIONS
DDatabase::DDatabase( bool useException ) : DSkeleton( useException )
{
	internal_init();
}
#endif

DDatabase::~DDatabase()
{
}

void DDatabase::internal_init()
{
	_errors[SUCCESS] = "";
	_errors[CONNECTION_LOSE] = "Connection to database was lost and cannot be re-open";
	_errors[NO_CONNECTED] = "Connection to database cannot be initialized";
	_errors[SET_OPT_CONNECT_FAILED] = "Failed to set connection timeout option";
	_errors[SET_OPT_READ_FAILED] = "Failed to set read timeout option";
	_errors[SET_OPT_WRITE_FAILED] = "Failed to set write timeout option";
	_errors[QUERY_ERROR] = "Database engine report a syntax error in the query";
	_errors[WRONG_PARAM] = "Connection parameters are not set or badly";
	_errors[UNKNOW_ERROR] = "An unknow error was encoured";
}

void DDatabase::setParams ( const DDatabaseParams & params )
{
	m_params = params;
}

bool DDatabase::isOpen()
{
	return m_opened;
}

/******************************************************************************
 *                            DDatabaseResult                                 *
 ******************************************************************************/
DDatabaseResult::DDatabaseResult()
{
	clear();
}

DDatabaseResult::~DDatabaseResult()
{
}

void DDatabaseResult::clear()
{
	rows.clear();
	last_auto_increment = 0;
	affected_row = 0;
	errnb = 0;
	error = DString();
	last_query = DString();
	info = DString();
}

std::ostream& operator << ( std::ostream& s, const DDatabaseResult & params )
{
	DDatabaseRow::const_iterator it;
	DDatabaseRows::const_iterator ite;
	
	s << "DDatabaseResult" << std::endl;
	s << "\tLast auto-increment = " << params.last_auto_increment;
	s << ", Affected row number = " << params.affected_row;
	s << ", Error number = " << params.errnb;
	s << ", Error string = \"" << params.error << "\"" << std::endl;
	for ( ite = params.rows.begin() ; ite != params.rows.end() ; ++ite )
	{
		for ( it = (*ite).begin() ; it != (*ite).end() ; ++it )
		{
			s << "\t" << (*it).first << " = " << (*it).second << std::endl;
		}
		s << std::endl;
	}
	return s;
}

/******************************************************************************
 *                            DDatabaseParams                                 *
 ******************************************************************************/
DDatabaseParams::DDatabaseParams()
{
	clear();
}

DDatabaseParams::~DDatabaseParams()
{
}

void DDatabaseParams::clear()
{
	base = DString();
	host = DString();
	user = DString();
	password = DString();
	port = DString();
}

DDatabaseParams & DDatabaseParams::operator = ( const DDatabaseParams & params )
{
	base = params.base;
	host = params.host;
	user = params.user;
	password = params.password;
	port = params.port;
	return *this;
}

bool operator == ( const DDatabaseParams & params1,  const DDatabaseParams & params2 )
{
	if ( params1.base != params2.base ||
	        params1.host != params2.host ||
	        params1.user != params2.user ||
	        params1.password != params2.password ||
	        params1.port != params2.port
	   )
	{
		return false;
	}
	return true;
}

bool operator != ( const DDatabaseParams & params1,  const DDatabaseParams & params2 )
{
	if ( params1.base == params2.base ||
			params1.host == params2.host ||
			params1.user == params2.user ||
			params1.password == params2.password ||
			params1.port == params2.port
	   )
	{
		return false;
	}
	return true;
}

bool DDatabaseParams::isSet()
{
	if ( !base.isEmpty() )
	{
		return true;
	}
	return false;
}

std::ostream & operator << ( std::ostream & s, const DDatabaseParams & params )
{
	s << "DDatabaseParams" << std::endl;
	s << "\thost = " << params.host << std::endl;
	s << "\tuser = " << params.user << std::endl;
	s << "\tpassword = " << params.password << std::endl;
	s << "\tport = " << params.port << std::endl;
	s << "\tbase = " << params.base << std::endl;
	return s;
}

DString DDatabaseParams::toString() const
{
	DString str;
	
	if ( !host.isEmpty() )
	{
		str += "dbhost=" + host;
	}
	
	if ( !user.isEmpty() )
	{
		if ( !str.isEmpty() )
		{
			str += ",";
		}
		str += "dbuser=" + user;
	}
	if ( !password.isEmpty() )
	{
		if ( !str.isEmpty() )
		{
			str += ",";
		}
		str += "dbpassword=" + password;
	}
	if ( !base.isEmpty() )
	{
		if ( !str.isEmpty() )
		{
			str += ",";
		}
		str += "dbbase=" + base;
	}
	if ( !port.isEmpty() )
	{
		if ( !str.isEmpty() )
		{
			str += ",";
		}
		str += "dbport=" + port;
	}
	return str;
}
