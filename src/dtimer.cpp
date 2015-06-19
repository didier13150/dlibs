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
 *     (___)_)   File : dtimer.cpp                          ||--|| *          *
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

#include "dtimer.h"
#include <time.h>

using namespace std;

DTimer::DTimer()
	: DThread()
{
	m_precision = false;
	m_timestamp = 0.0;
	// Create mutex
	pthread_mutex_init ( &m_Mutex, NULL );
}

DTimer::~DTimer()
{
	DThread::stop();
	pthread_mutex_destroy ( &m_Mutex );
}

void DTimer::start ( unsigned int timeout )
{
	m_timestamp = 0.0;
	m_countdown = timeout;
	
	setRunMode( DThread::MULTI_LOOP );
	setSleep( 100000 );
	
	if ( timeout > 2000 )
	{
		m_timeout = static_cast<long double> ( timeout/1000 );
		m_precision = false;
		m_zeroTime = time ( NULL );
		//cout << "timeout is " << m_timeout << endl;
	}
	else
	{
		m_precision = true;
		m_timeout = ( timeout * 1000000 );
		// Set t0
		clock_gettime ( CLOCK_MONOTONIC, &m_zeroTimePrec );
	}

	// Start thread
	DThread::start();
}

void DTimer::stop()
{
	// Stop the thread
	DThread::stop();
}

void DTimer::restart( unsigned int timeout )
{
	stop();
	if ( timeout )
	{
		start( timeout );
	}
	else
	{
		start( m_countdown );
	}
}

bool DTimer::isStarted()
{
	return isRunning();
}

long unsigned int DTimer::timeToTimeout()
{
	//bool timeoutReached = false;
	long double time_to_timeout;
	long double timestamp;

	// always return 0 if timer is not started
	if ( ! isRunning() )
	{
		return 0.0;
	}
	pthread_mutex_lock ( &m_Mutex );
	timestamp = m_timestamp;
	pthread_mutex_unlock ( &m_Mutex );
	// Compare timestamp to timeout
	if ( timestamp >= m_timeout )
	{
		time_to_timeout = 0.0;
		stop();
	}
	else
	{
		if ( m_precision )
		{
			time_to_timeout = ( m_timeout - timestamp ) / 1000000.0;
		}
		else
		{
			time_to_timeout = ( m_timeout - timestamp ) * 1000.0;
		}
	}
	if ( time_to_timeout <= 0.0 )
	{
		time_to_timeout = 0.0;
		stop();
	}
	return static_cast<unsigned long int>( time_to_timeout );
}

void DTimer::run()
{
	static struct timespec now;

	if ( m_precision )
	{
		clock_gettime ( CLOCK_MONOTONIC, &now );
		// Calculate timestamp
		pthread_mutex_lock ( &m_Mutex );
		m_timestamp = ( ( now.tv_sec - m_zeroTimePrec.tv_sec ) * 1000000000 ) +
						( now.tv_nsec - m_zeroTimePrec.tv_nsec );
		pthread_mutex_unlock ( &m_Mutex );
	}
	else
	{
		pthread_mutex_lock ( &m_Mutex );
		m_timestamp = time ( NULL ) - m_zeroTime;
		pthread_mutex_unlock ( &m_Mutex );
	}
}
