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
 *     (___)_)   File : dsqlite.cpp                         ||--|| *          *
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

#include "dsqlite.h"
#include "dexception.h"
#include "sqlite3.h"



DSQLite::DSQLite()
		: DDatabase()
{
	init();
}

DSQLite::DSQLite ( bool use_dexceptions )
		: DDatabase( use_dexceptions )
{
	init();
}

DSQLite::~DSQLite()
{
	if ( m_opened )
		close();
}

void DSQLite::init()
{
	m_opened = false;
	m_params.clear();
	m_sqlite = 0;
}

void DSQLite::setParams ( const DDatabaseParams & params )
{
	m_params = params;
}

void DSQLite::setOptions ( const DDatabaseOptions & opt )
{
}

DDatabaseResult & DSQLite::open()
{
	m_result.clear();

	// if connection is already opened, exit
	if ( m_opened ) { return this->m_result; }

	// Check if connection parameters are set
	if ( !m_params.isSet() )
	{
		m_result.errnb = WRONG_PARAM;
		m_result.error = _errors[WRONG_PARAM];
		m_opened = false;
		if ( _use_dexceptions )
		{
			throw DEXCEPTION_DB ( m_result.error, m_result.errnb );
		}
		return this->m_result;
	}
	
	// Try to open the connection
	if ( sqlite3_open ( m_params.base.c_str(), &m_sqlite ) != SQLITE_OK )
	{
		m_result.errnb = NO_CONNECTED;
		m_result.error = _errors[NO_CONNECTED];
		m_result.error += ". ";
		m_result.error += sqlite3_errmsg ( m_sqlite );
		m_opened = false;
		if ( _use_dexceptions )
		{
			throw DEXCEPTION_DB ( m_result.error, m_result.errnb );
		}
		return this->m_result;
	}

	m_result.error.clear();
	m_result.errnb = SUCCESS;
	m_opened = true;

	return this->m_result;
}

void DSQLite::close()
{
	if ( m_sqlite )
	{
		sqlite3_close ( m_sqlite );
		m_sqlite = 0;
		m_opened = false;
		m_result.errnb = NO_CONNECTED;
	}
}

DDatabaseResult & DSQLite::exec ( const DString & query )
{
	sqlite3_stmt *statement;
	long long unsigned int llu;
	DDatabaseRow row_result;
	DString key, value, error;
	int num_row = 0;
	int result = 0;
	bool have_result = false;
	char * ptr;

	m_result.clear();
	m_result.last_query = query;

	// If connection was not initialized, try to open it
	if ( !m_opened || m_sqlite == 0 )
	{
		open();
		// If connection was not initialized, quit
		if ( !m_opened || m_sqlite == 0 )
		{
			m_result.errnb = NO_CONNECTED;
			m_result.error = _errors[NO_CONNECTED];
			if ( _use_dexceptions )
			{
				throw DEXCEPTION_DB ( m_result.error, m_result.errnb );
			}
			return this->m_result;
		}
	}

	// execute the query and get the statement
	if ( sqlite3_prepare_v2 ( m_sqlite, query.c_str(), -1, &statement, 0 ) == SQLITE_OK )
	{
		// Get the number of row
		num_row = sqlite3_column_count ( statement );
		// Get results of query if any
		result = 0;
		while ( ( result = sqlite3_step ( statement ) ) == SQLITE_ROW )
		{
			have_result = true;
			for ( int i = 0 ; i < num_row ; ++i )
			{
				ptr = ( char* ) sqlite3_column_name ( statement, i );
				if ( !ptr ) continue;
				else key = ptr;
				ptr = ( char* ) sqlite3_column_text ( statement, i );
				if ( !ptr ) value = "NULL";
				else value = ptr;
				row_result[key] = value;
			}
			m_result.rows.push_back ( row_result );
		}
		
		sqlite3_finalize ( statement );

		if ( !have_result )
		{
			if ( num_row > 0 )
			{
				m_result.errnb = UNKNOW_ERROR;
			}
			else
			{
				m_result.errnb = SUCCESS;
			}
		}
		
		// Get the last AUTO_INCREMENT
		llu = ( long long unsigned int ) sqlite3_last_insert_rowid ( m_sqlite );
		m_result.last_auto_increment = llu;

		// Get the number of affected rows
		llu = ( long long unsigned int ) sqlite3_changes ( m_sqlite );
		if ( llu >= 0 )
		{
			m_result.affected_row = llu;
		}
	}
	else
	{
		m_result.errnb = QUERY_ERROR;
	}

	error = sqlite3_errmsg ( m_sqlite );
	if ( error != "not an error" )
	{
		m_result.error = error;
	}

	return this->m_result;
}

