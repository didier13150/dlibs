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
 *     (___)_)   File : dthread.h                           ||--|| *          *
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


#ifndef _DTHREAD_H_
#define _DTHREAD_H_

#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <signal.h>


/**
 * Create easily a threaded job.
 * @author Didier FABERT <didier.fabert@gmail.com>
 * @brief Thread class.
 * @include dthread.dox
 */
class DThread
{
public:

	/**
	 * Constructor
	 */
	DThread();

	/**
	 * Destructor
	 */
	virtual ~DThread();

	/**
	 * @typedef RunMode
	 * Define all running mode accepted by the thread.
	 */
	typedef enum runmode
	{
		/// Thread must make a single loop
		SINGLE_LOOP,
		/// Thread must make infinite number of loop until stop method is called.
		MULTI_LOOP,
	} RunMode;

	/**
	 * Start the thread
	 * @brief start the thread
	 */
	virtual void start();

	/**
	 * Stop the thread
	 * @brief stop the thread
	 */
	virtual void stop();

	/**
	 * Threaded process
	 * @note Must be implemented in a subclacss
	 */
	virtual void run() = 0;

	/**
	 * It's the time ( in micro seconds ) between two loops in multi loop mode.
	 * @note This parameter is ignored in single loop mode.
	 * @brief Set sleep time
	 */
	void setSleep ( unsigned int sleeptime );

	/**
	 * Get sleep time.
	 * @brief Get sleep time
	 */
	unsigned int getSleep();

	/**
	 * Get the current thread status.\n
	 * @return TRUE if thread is running, false otherwise.
	 * @note Even thread process is terminated, return value is TRUE while
	 * stop() method is not called.
	 * @brief Thread status
	 */
	bool isRunning();

	/**
	 * Set DThread mode.\n
	 * @see Mode
	 * @brief Set DThread mode
	 */
	void setRunMode( RunMode mode );

	/**
	 * Get the thread mode
	 * @see Mode
	 * @brief Get the thread mode
	 */
	RunMode getRunMode();

	/**
	 * Get return value about thread
	 * @return The return value of the thread
	 * @brief Get Thread return value
	 */
	int getReturn() const;


private:

	/// Time ( microseconds ) between two thread loop.
	unsigned int m_sleeptime;

	/// The thread Handle
	pthread_t m_handle;

	/**
	 * POSIX Thread attributes
	 */
	pthread_attr_t *m_attr;

	/// Continue thread process flag
	bool m_continue;

	/// The thread status flag
	bool m_running;

	/// Return value about thread
	int m_return;

	/**
	 * Thread Mode
	 * @see Mode
	 */
	RunMode m_mode;

	/**
	 * If thread must make another loop.\n
	 * @return TRUE if run method must make another loop, false otherwise.
	 * @brief Get another loop flag
	 */
	bool again();

	/**
	* @brief It's the real thread.
	* @internal
	*/
	static void * entryPoint ( void * pthis );
};

#endif // _DTHREAD_H_

