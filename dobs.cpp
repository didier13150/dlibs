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
 *     (___)_)   File : dobs.h                              ||--|| *          *
 *                                                                            *
 *   This program is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU General Public License as published by     *
 *   the Free Software Foundation; either version 2 of the License, or        *
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
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                *
 ******************************************************************************/
#include "dobs.h"

/******************************************************************************/
/*                                 DObserver                                  */
/******************************************************************************/

DObserver::DObserver()
{
}

DObserver::~DObserver()
{
	const_iterator end = m_obslist.end();
	for ( iterator it = m_obslist.begin() ; it != end ; ++it )
	{
		( *it )->removeObserver ( this );
	}
}

void DObserver::addObservable ( DObservable * observable )
{
	m_obslist.push_back ( observable );
}

void DObserver::removeObservable ( DObservable * observable )
{
	iterator it = std::find ( m_obslist.begin(), m_obslist.end(), observable );
	if ( it != m_obslist.end() )
	{
		m_obslist.erase ( it );
	}
}

void DObserver::onEvent ( DObservable * observable )
{
}

/******************************************************************************/
/*                                DObservable                                 */
/******************************************************************************/

DObservable::DObservable()
{
}

DObservable::~DObservable()
{
	const_iterator end = m_obslist.end();
	for ( iterator it = m_obslist.begin() ; it != end ; ++it )
	{
		( *it )->removeObservable ( this );
	}
}

void DObservable::addObserver ( DObserver * observer )
{
	m_obslist.push_back ( observer );
}

void DObservable::removeObserver ( DObserver * observer )
{
	iterator it = std::find ( m_obslist.begin(), m_obslist.end(), observer );
	if ( it != m_obslist.end() )
	{
		m_obslist.erase ( it );
	}
}

void DObservable::notify ( void )
{
	const_iterator end = m_obslist.end();
	for ( iterator it = m_obslist.begin() ; it != end ; ++it )
	{
		( *it )->onEvent ( this );
	}
}

