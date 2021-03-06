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

#include "dsqlite.h"
#include "sqlite3.h"
#ifdef WITH_EXCEPTIONS
  #include "dexception.h"
#endif

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
	m_opt = opt;
	m_opt.initialized = true;
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
#ifdef WITH_EXCEPTIONS
		if ( m_use_dexceptions )
		{
			throw DEXCEPTION_DB ( m_result.error, m_result.errnb );
		}
#endif
		return this->m_result;
	}
	
	// Try to open the connection
	if ( sqlite3_open ( m_params.base.c_str(), &m_sqlite ) != SQLITE_OK )
	{
		m_result.errnb = NOT_CONNECTED;
		m_result.error = _errors[NOT_CONNECTED];
		m_result.error += ". ";
		m_result.error += sqlite3_errmsg ( m_sqlite );
		m_opened = false;
#ifdef WITH_EXCEPTIONS
		if ( m_use_dexceptions )
		{
			throw DEXCEPTION_DB ( m_result.error, m_result.errnb );
		}
#endif
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
		m_result.errnb = NOT_CONNECTED;
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
			m_result.errnb = NOT_CONNECTED;
			m_result.error = _errors[NOT_CONNECTED];
#ifdef WITH_EXCEPTIONS
			if ( m_use_dexceptions )
			{
				throw DEXCEPTION_DB ( m_result.error, m_result.errnb );
			}
#endif
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
				ptr = const_cast<char*> ( sqlite3_column_name ( statement, i ) );
				if ( !ptr ) continue;
				else key = ptr;
				ptr = const_cast<char*> ( reinterpret_cast<const char*> ( sqlite3_column_text ( statement, i ) ) );
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
		llu = static_cast<long long unsigned int> ( sqlite3_last_insert_rowid ( m_sqlite ) );
		m_result.last_auto_increment = llu;

		// Get the number of affected rows
		llu = static_cast<long long unsigned int> ( sqlite3_changes ( m_sqlite ) );
		m_result.affected_row = llu;
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

