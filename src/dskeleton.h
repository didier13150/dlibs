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
 *     (___)_)   File : dskeleton.h                         ||--|| *          *
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

#ifndef _DSKELETON_H_
#define _DSKELETON_H_

#include <map>
#include "dstring.h"

/**
 * This is the mother class for all high-level DLibs tools
 * @short DLibs Mother class
 * @author Didier FABERT <didier.fabert@gmail.com>
 */
class DSkeleton
{

protected:
	/**
	 * Empty constructor
	 */
	DSkeleton( void )
	{
		m_use_dexceptions = false;
	}
	
	/**
	 * Default constructor for using exception in program
	 */
	DSkeleton( bool use_dexceptions ) : m_use_dexceptions( use_dexceptions )
	{
	}

	/**
	 * Default destructor
	 */
	virtual ~DSkeleton() {}

	/// Internal flag for exception using
	bool m_use_dexceptions;

public:

	/**
	 * To tell that we want use DExceptions
	 */
	void useDExceptions( bool use_dexceptions = false )
	{
		m_use_dexceptions = use_dexceptions;
	}

};

#endif // _DSKELETON_H_
