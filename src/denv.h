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
 *     (___)_)   File : denv.h                              ||--|| *          *
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
#ifndef _DENV_H_
#define _DENV_H_

#include "dstring.h"
#include "dsingleton.h"

#include <map>

/**
 * Get and set easily environment variables.
 * @brief Manage environment variables.
 * @author Didier FABERT <didier.fabert@gmail.com>
 * @include denv.dox
 */
class DEnv : public DSingleton<DEnv>
{
	// To let DSingleton have access to DEnv protected constructor
	friend class DSingleton<DEnv>;
protected:
	/**
	 * Constructor
	 */
	DEnv();

	/**
	 * Destructor
	 */
	~DEnv();

	/// environment variables already fetched
	static std::map<DString, DString> m_vars;
	
public:
	/**
	 * Get environment variable
	 * @attention case sensitive
	 * @param name The name of the environment variable
	 * @return The value of the environment variable
	 */
	const DString & getVar( const DString & name );
	
	/**
	 * Set environment variable
	 * @attention case sensitive
	 * @param name The name of the environment variable
	 * @param value The value of the environment variable
	 * @param overwrite If set to TRUE ( the default ) value is overwritten if
	 * value already exists.
	 */
	void setVar( const DString & name, const DString & value, bool overwrite = true );
	
	
	/**
	* Writes DEnv to the stream s and returns a reference to the stream.
	*/
	friend std::ostream & operator << ( std::ostream& s, const DEnv & env );
	 
};

#endif // _DENV_H_
