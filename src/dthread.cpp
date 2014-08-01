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
 *     (___)_)   File : dthread.cpp                         ||--|| *          *
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
#include "dthread.h"
#include <iostream>

DThread::DThread()
{
	m_sleeptime = 100000;
	m_attr = 0;
	m_continue = false;
	m_mode = DThread::MULTI_LOOP;
	m_status = DThread::STOPPED;
	m_return = -1;
	m_handle = 0;
}

DThread::~DThread()
{
	stop();
}

bool DThread::isRunning()
{
	if( m_status == DThread::RUNNING )
	{
		return true;
	}
	return false;
}

bool DThread::again()
{
	return m_continue;
}

void DThread::setRunMode( RunMode mode )
{
	m_mode = mode;
}

DThread::RunMode DThread::getRunMode()
{
	return m_mode;
}

void DThread::setSleep ( unsigned int sleeptime )
{
	m_sleeptime = sleeptime;
}

unsigned int DThread::getSleep()
{
	return m_sleeptime;
}

int DThread::getReturn() const
{
	if( m_status == DThread::RUNNING )
	{
		return 255;
	}
	return m_return;
}

void DThread::start()
{
	if( m_status == DThread::RUNNING )
	{
		return;
	}
	m_continue = true;
	if ( m_mode == DThread::SINGLE_LOOP )
	{
		m_continue = false;
	}
	pthread_create ( &m_handle, m_attr, &DThread::entryPoint, this );
}

void DThread::stop()
{
	m_continue = false;
	usleep( 100000 ); // Let thread a chance to finish himself before cancel it.
	if ( m_handle )
	{
		pthread_cancel( m_handle );
		m_return = pthread_join ( m_handle, NULL );
		m_handle = 0;
	}
}

void * DThread::entryPoint( void * pthis )
{
	DThread * th = ( DThread * ) pthis;
	
	if ( pthread_setcancelstate( PTHREAD_CANCEL_ENABLE, NULL ) != 0 )
	{
		th->m_status = DThread::STOPPED;
		pthread_exit( NULL );
	}
	
	th->m_status = DThread::RUNNING;
	do
	{
		th->run();
		if ( th->getRunMode() != DThread::SINGLE_LOOP )
		{
			usleep( th->getSleep() );
		}
		
	} while( th->again() );
	
	th->m_status = DThread::STOPPED;
	th->m_return = 0;
	pthread_exit( NULL );
}
