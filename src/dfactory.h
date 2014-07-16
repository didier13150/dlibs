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
 *     (___)_)   File : dfactory.h                          ||--|| *          *
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

#ifndef _dfactory_h_
#define _dfactory_h_

#include <map>
#include "dstring.h"

/**
 * @brief Template factory class.
 * @author Didier FABERT <didier.fabert@gmail.com>
 * Abstract template class for create object factory.
 */
template <class Object, class Key=DString>
class DFactory
{
public:

	static void Register ( Key key, Object* obj )
	{
		if ( m_map.find ( key ) == m_map.end() )
		{
			m_map[key] = obj;
		}
	}
	
	Object* create ( const Key& key )
	{
		Object* tmp = 0;
		typename std::map<Key, Object*>::iterator it=m_map.find ( key );

		if ( it != m_map.end() )
		{
			tmp= ( ( *it ).second )->Clone();
		}

		return tmp;
	}

private:
	static std::map<Key,Object*> m_map;
};

template <class Object,class Key> std::map<Key, Object*>
		DFactory<Object,Key>::m_map=std::map<Key,Object*>();

#endif // _dfactory_h_
