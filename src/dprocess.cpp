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
 *     (___)_)   File : dprocess.cpp                        ||--|| *          *
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

#include "dprocess.h"

DProcess::DProcess()
	: DThread(), m_file ( 0 )
{
	setRunMode( DThread::SINGLE_LOOP );
	clear();
}

DProcess::~DProcess()
{
}

void DProcess::setExeMode( ExeMode mode )
{
	m_exe_mode = mode;
}

DProcess::ExeMode DProcess::getExeMode()
{
	return m_exe_mode;
}

void DProcess::setComMode( ComMode mode )
{
	m_com_mode = mode;
}

DProcess::ComMode DProcess::getComMode()
{
	return m_com_mode;
}

void DProcess::start()
{
	m_output.clear();
	DThread::start();
	while( ( m_exe_mode == DProcess::BLOCK ) && isRunning() )
	{
		usleep( 100000 );
	}
}

void DProcess::run()
{
	DString buffer;
	DString cmode;
	DStringList::iterator it;
	char * buf;
	int bufsize = 80 * sizeof( char );

	// construct exe line
	buffer = m_exe;
	for ( it = m_args.begin() ; it != m_args.end() ; ++it )
	{
		if ( !buffer.isEmpty() )
		{
			buffer.append( " " );
		}
		buffer.append( *it );
	}

	if ( m_com_mode == READ_ONLY)
	{
		cmode = "r";
	}
	else
	{
		cmode = "w";
	}
	m_file = popen( buffer.c_str(), cmode.c_str() );

	if ( !m_file )
	{
		return;
	}
	
	if ( m_com_mode == READ_ONLY)
	{
		buf = new char[ bufsize ];

		while ( fgets( buf, bufsize, m_file ) != 0 )
		{
			addOutput( buf );
		}
		delete[]( buf );
	}
	
	pclose( m_file );

	m_file = 0;
}
void DProcess::addOutput( const DString & output )
{
	m_output.append( output );
}

const DString & DProcess::getOutput() const
{
	return m_output;
}

void DProcess::setExecutable( const DString & executable )
{
	m_exe = executable;
}

const DString & DProcess::getExecutable() const
{
	return m_exe;
}

void DProcess::setArgs( const DStringList & arglist )
{
	m_args = arglist;
}

const DStringList & DProcess::getArgs () const
{
	return m_args;
}

void DProcess::clearArgs ()
{
	m_args.clear();
}

DProcess & DProcess::operator << ( const DString & arg )
{
	m_args.push_back( arg );
	return *this;
}

void DProcess::clear()
{
	m_output.clear();
	m_args.clear();
	m_exe.clear();
	setExeMode( DProcess::NOBLOCK );
	setComMode( READ_ONLY );
}
