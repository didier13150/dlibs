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
 *     (___)_)   File : dtimer.h                            ||--|| *          *
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
#ifndef _DTIMER_H_
#define _DTIMER_H_

#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <netdb.h>
#include <iostream>
#include <ctime>
#include "dthread.h"

/**
 * Just a simple example to learn how to use it
 * @include testdtimer.cpp
 * @brief Timer.
 * @author Didier Fabert <didier.fabert@gmail.com>
 */
class DTimer : public DThread
{
	public:
		/**
		 * Default constructor
		 */
		DTimer ( void );

		/**
		 * Default destructor
		 */
		~DTimer ( void );

		/**
		 * Start the timer
		 * @param timeout the timeout in millisecond
		 * @attention precision is about 20 milliseconds for time under 2 seconds and
		 * 500 milliseconds for upper time.
		 */
		void start ( unsigned int timeout );

		/**
		 * Stop the timer
		 */
		void stop ( void );
		

		/**
		 * Start the timer again. It's like a soft reset.\n
		 * Reference time is takken from this moment.\n
		 * timeout is not modify if timeout is set to 0 or not set.
		 */
		void restart ( unsigned int timeout = 0 );

		/**
		 * Return the number of millisecond to reach timeout.\n
		 * When the timeout is reached, the number is always 0.\n
		 * Timeout is always reached if the timer is not started.
		 */
		long unsigned int timeToTimeout ( void );

		/**
		 * Return true if timer is started, false otherwise
		 */
		bool isStarted ( void );

	protected:

		/// The timestamp since the timer was started
		long double m_timestamp;
		
		/// A copy of the timeout start option
		unsigned int m_countdown;

		/// The internal timeout
		long double m_timeout;

		/// The thread mutex for access to the critical zone
		pthread_mutex_t m_Mutex;

		/// Precision flag (for timeout > 2 seconds)
		bool m_precision;

		/// Timestamp (precision one)
		struct timespec m_zeroTimePrec;

		/// Timestamp
		long int m_zeroTime;
		
		/**
		 * What the thread must to do
		 */
		void run();
};

#endif // _DTIMER_H_
