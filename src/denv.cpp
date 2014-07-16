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
 *     (___)_)   File : denv.cpp                            ||--|| *          *
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

#include "denv.h"
#include <stdlib.h>


std::map<DString, DString> DEnv::m_vars = std::map<DString, DString>();

DEnv::DEnv()
{
	m_vars["void"] = DString();
}


DEnv::~DEnv()
{
}

const DString & DEnv::getVar( const DString & name )
{
	std::map<DString,DString>::const_iterator it;
	char * env = 0;

	// if env var is already gotten
	it = m_vars.find( name );
	if ( it != m_vars.end() )
	{
		return it->second;
	}
	// get it if any
	env = getenv( name.c_str() );
	if ( env )
	{
		m_vars[name] = env;
		return m_vars[name];
	}
	// if not, return an empty string
	return m_vars["void"];
}

void DEnv::setVar( const DString & name, const DString & value, bool overwrite )
{
	char * env = 0;
	
	if ( !setenv( name.c_str(), value.c_str(), overwrite ) )
	{
		env = getenv( name.c_str() );
		if ( env )
		{
			m_vars[name] = env;
		}
	}
}

std::ostream & operator << ( std::ostream& s, const DEnv & env )
{
	std::map<DString,DString>::const_iterator it;

	for ( it = env.m_vars.begin() ; it != env.m_vars.end() ; ++it )
	{
		s << it->first << " => " << it->second << std::endl;
	}
	return s;
}
