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
#include "dthread.h"

DThread::DThread()
{
	m_sleeptime = 100000;
	m_attr = 0;
	m_continue = false;
	m_running = false;
	m_mode = DThread::MULTI_LOOP;
}

DThread::~DThread()
{
	stop();
}

bool DThread::isRunning()
{
	return m_running;
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

void DThread::start()
{
	if( m_running )
	{
		return;
	}
	m_continue = true;
	pthread_create ( &m_handle, m_attr, &DThread::entryPoint, this );
	m_running = true;
	if ( m_mode == SINGLE_LOOP )
	{
		m_continue = false;
	}
}

void DThread::stop()
{
	m_continue = false;
	int ret = pthread_join ( m_handle, NULL );
}

void * DThread::entryPoint( void * pthis )
{
	DThread * th = ( DThread * ) pthis;
	
	do
	{
		th->run();
		if ( th->getRunMode() != DThread::SINGLE_LOOP )
		{
			usleep( th->getSleep() );
		}
		
	} while( th->again() );
	
	th->m_running = false;
	pthread_exit( NULL );
}
