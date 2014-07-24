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
 *     (___)_)   File : dsingleton.h                        ||--|| *          *
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

#ifndef _DSINGLETON_H_
#define _DSINGLETON_H_

/**
 * Create unique objet instance and distribute the same instance of it.
 * @author Didier FABERT <didier.fabert@gmail.com>
 * @brief Unique objet instance.
 */

template <class T> class DSingleton
{

public:
	/**
	 * Get single instance of object().\n
	 * @warning Not thread safe
	 */
    static T * getInstance()
	{
		//static T * t = 0;
		
		if ( ! t )
		{
			t = new T();
		}
		return t;
	}
	
	/**
	 * Delete the instancied object if any.
	 */
	static void deleteInstance()
	{
		if ( t )
		{
			delete t;
			t = 0;
		}
	}
	
	/**
	 * Return true if object was instancied. False otherwise.
	 */
	static bool isInstancied()
	{
		if ( ! t )
		{
			return false;
		}
		return true;
	}

protected:
	/// The single object
	static T * t;

private:
	/**
	 * Private copying function
	 */
	T & operator= ( const T & ) {}
};

/// Initialize object to zero
template <class T> T* DSingleton<T>::t = 0;

#endif // _DSINGLETON_H_
