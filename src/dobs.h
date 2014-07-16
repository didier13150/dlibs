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

#ifndef _DOBS_H_
#define _DOBS_H_

#include <list>
#include <algorithm>
#include <iterator>

#include "devent.h"

class DObserver;

/******************************************************************************/
/*                                DObservable                                 */
/******************************************************************************/
/**
 * A abstract implementation about observer - observable class.\n
 * This is the observer part
 * @include testdobs.cpp
 * @brief Observer pattern.
 * @author Didier FABERT <didier.fabert@gmail.com>
 * @see DObservable
 */
class DObservable
{
public:

	/**
	 * Add an observer
	 */
	void addObserver( DObserver * observer );

	/**
	 * Remove an observer
	 */
	void removeObserver( DObserver * observer );

	/**
	 * Get the event
	 */
	virtual DBasicEvent & getEvent( void ) = 0;
	
protected:
	/**
	 * @brief Constructor.
	 * This class is abstract and must be overrided.
	 */
	DObservable();

	/**
	 * Virtual destructor
	 */
	virtual ~DObservable();

	/**
	 * @typedef iterator
	 * An iterator for the DObserver pointer list
	 */
	typedef std::list< DObserver * >::iterator iterator;
	/**
	 * @typedef const_iterator
	 * A constant iterator for the DObserver pointer list
	 */
	typedef std::list< DObserver * >::const_iterator const_iterator;

	/**
	 * Send a notification to all observers that a new event is available
	 */
	void notify( void );
	
private:
	/// The internal list of class which look out this class
	std::list< DObserver * > m_obslist;

};

/******************************************************************************/
/*                                 DObserver                                  */
/******************************************************************************/
/**
 * A abstract implementation about [ observer - observable ] class.\n
 * This is the observable part
 * @include testdobs.cpp
 * @brief Observable pattern.
 * @author Didier FABERT <didier.fabert@gmail.com>
*/
class DObserver
{
public:
	/**
	 * Received when an observable has changed.
	 */
	virtual void onEvent( DObservable * observable );

	/**
	 * Remove an observable to look out
	 */
	void addObservable( DObservable * observable );


	/**
	 * Add an observable to look out
	 */
	void removeObservable( DObservable * observable );
	
protected:
	/**
	 * @brief Constructor.
	 * This class is abstract and must be overrided.
	 */
	DObserver();
	
	/**
	 * Virtual destructor
	 */
	virtual ~DObserver();

	/**
	 * @typedef iterator
	 * An iterator for the DObservable pointer list
	 */
	typedef std::list< DObservable * >::iterator iterator;
	
	/**
	 * @typedef const_iterator
	 * A constant iterator for the DObservable pointer list
	 */
	typedef std::list< DObservable * >::const_iterator const_iterator;
	
private:
	/// The internal list of class to look out
	std::list< DObservable * > m_obslist;

};

#endif // _DOBS_H_
