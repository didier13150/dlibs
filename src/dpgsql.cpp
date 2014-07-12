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
 *     (___)_)   File : dpgsql.cpp                          ||--|| *          *
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

#include "dpgsql.h"
#include <postgres.h>

#ifndef WITH_EXCEPTIONS
#define WITH_EXCEPTIONS 0
#endif

DPgSQL::DPgSQL()
 : DDatabase()
{
}

#if WITH_EXCEPTIONS
DPgSQL::DPgSQL( bool use_dexceptions ) : DDatabase ( use_dexceptions )
{
}
#endif


DPgSQL::~DPgSQL()
{
}

void DPgSQL::init()
{

	m_opened = false;
	m_params.clear();
	m_opt.initialized = false;
	pgsql = 0;
}

void DPgSQL::setParams ( const DDatabaseParams & params )
{
	m_params = params;
}


void DPgSQL::setOptions ( const DDatabaseOptions & opt )
{
}


DDatabaseResult & DPgSQL::open()
{
	DString connInfo;
	
	connInfo = m_params.toString();
	std::cout << connInfo << std::endl;
	return m_result;
}


void DPgSQL::close()
{
}


DDatabaseResult & DPgSQL::exec ( const DString & query )
{
	return m_result;
}


bool DPgSQL::isOpen()
{
	return m_opened;
}

