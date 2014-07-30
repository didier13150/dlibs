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
 *     (___)_)   File : dmysql.cpp                          ||--|| *          *
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

#include "dmysql.h"
#include <mysql.h>
#ifdef WITH_EXCEPTIONS
  #include "dexception.h"
#endif

DMySQL::DMySQL() : DDatabase()
{
	init();
}

#ifdef WITH_EXCEPTIONS
DMySQL::DMySQL ( bool use_dexceptions ) : DDatabase ( use_dexceptions )
{
	init();
}
#endif

DMySQL::~DMySQL()
{
	close();
}

void DMySQL::init()
{

	m_opened = false;
	m_params.clear();
	m_opt.initialized = false;
	m_mysql = 0;
}

void DMySQL::setParams ( const DDatabaseParams & params )
{
	m_params = params;
}

void DMySQL::setOptions ( const DDatabaseOptions & opt )
{
	m_opt = opt;
	m_opt.initialized = true;
}

DDatabaseResult & DMySQL::open()
{
	int rtn;
	DString buffer;

	m_result.clear();

	// if connection is already opened, exit
	if ( m_mysql ) { return this->m_result; }
	
	if ( mysql_library_init( 0, NULL, NULL ) )
	{
		m_result.errnb = NOT_INIT;
		m_result.error = _errors[NOT_INIT];
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
	m_mysql = mysql_init ( NULL );
	if ( ! m_mysql )
	{
		m_result.errnb = NOT_CONNECTED;
		m_result.error = _errors[NOT_CONNECTED];
		m_opened = false;
#ifdef WITH_EXCEPTIONS
		if ( m_use_dexceptions )
		{
			throw DEXCEPTION_DB ( m_result.error, m_result.errnb );
		}
#endif
		return this->m_result;
	}

	if ( m_opt.initialized )
	{
		rtn = mysql_options ( m_mysql,
		                      MYSQL_OPT_CONNECT_TIMEOUT,
		                      m_opt.connect_timeout.c_str() );
		if ( rtn )
		{
			m_result.errnb = SET_OPT_CONNECT_FAILED;
			m_result.error = _errors[SET_OPT_CONNECT_FAILED];
#ifdef WITH_EXCEPTIONS
			if ( m_use_dexceptions )
			{
				throw DEXCEPTION_DB ( m_result.error, m_result.errnb );
			}
#endif
			return this->m_result;
		}

		rtn = mysql_options ( m_mysql,
		                      MYSQL_OPT_READ_TIMEOUT,
		                      m_opt.read_timeout.c_str() );
		if ( rtn )
		{
			m_result.errnb = SET_OPT_READ_FAILED;
			m_result.error = _errors[SET_OPT_READ_FAILED];
#ifdef WITH_EXCEPTIONS
			if ( m_use_dexceptions )
			{
				throw DEXCEPTION_DB ( m_result.error, m_result.errnb );
			}
#endif
			return this->m_result;
		}

		rtn = mysql_options ( m_mysql,
		                      MYSQL_OPT_WRITE_TIMEOUT,
		                      m_opt.write_timeout.c_str() );
		if ( rtn )
		{
			m_result.errnb = SET_OPT_WRITE_FAILED;
			m_result.error = _errors[SET_OPT_WRITE_FAILED];
#ifdef WITH_EXCEPTIONS
			if ( m_use_dexceptions )
			{
				throw DEXCEPTION_DB ( m_result.error, m_result.errnb );
			}
#endif
			return this->m_result;
		}
	}

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
	
	if ( ! mysql_real_connect ( m_mysql,
								m_params.host.c_str(),
								m_params.user.c_str(),
								m_params.password.c_str(),
								m_params.base.c_str(),
								m_params.port.toUInt(),
								NULL,
								0
							   ) )
	{
		m_result.errnb = NOT_CONNECTED;
		m_result.error = mysql_error ( m_mysql );
		if ( m_result.error.isEmpty() )
		{
			m_result.error = "Cannot connect to MySQL, check parameters (";
			m_result.error += "host=" + m_params.host;
			m_result.error += ", user=" + m_params.user;
			m_result.error += ", password=" + m_params.password;
			m_result.error += ", base=" + m_params.base;
			m_result.error += ", port=" + m_params.port + ")";
		}
		m_opened = false;
#ifdef WITH_EXCEPTIONS
		if ( m_use_dexceptions )
		{
			throw DEXCEPTION_DB ( m_result.error, m_result.errnb );
		}
#endif
		return this->m_result;
	}
	m_result.errnb = SUCCESS;
	m_opened = true;
	return this->m_result;
}

void DMySQL::close()
{
	if ( m_mysql )
	{
		mysql_close ( m_mysql );
		m_mysql = 0;
		m_opened = false;
		m_result.errnb = NOT_CONNECTED;
	}
	mysql_library_end();
}

DDatabaseResult & DMySQL::exec ( const DString & query )
{
	MYSQL_RES *results;
	MYSQL_FIELD *fields;
	MYSQL_ROW row;
	m_result.clear();
	int errnb;
	uint num_fields;
	unsigned long *lengths;
	DDatabaseRow row_result;
	my_ulonglong llu;
	DString buffer;
	bool closeConnection = false;
	long int old_errnb;

	m_result.clear();

	// If connection was not initialized, try to open it
	if ( !m_opened || m_mysql == 0 )
	{
		closeConnection = true;
		open();
		// If connection was not initialized, quit
		if ( !m_opened || m_mysql == 0 )
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
	m_result.last_query = query;

	// If connection was lose, exit
	errnb = mysql_ping ( m_mysql );
	if ( errnb )
	{
		m_result.errnb = CONNECTION_LOSE;
		m_result.error = _errors[CONNECTION_LOSE];
#ifdef WITH_EXCEPTIONS
		if ( m_use_dexceptions )
		{
			throw DEXCEPTION_DB ( m_result.error, m_result.errnb );
		}
#endif
		return this->m_result;
	}

	// execute query
	errnb = mysql_real_query ( m_mysql, query.c_str(), query.length() );

	if ( errnb ) // if query was not executed
	{
		m_result.errnb = QUERY_ERROR;
		m_result.error = mysql_error ( m_mysql );
#ifdef WITH_EXCEPTIONS
		if ( m_use_dexceptions )
		{
			throw DEXCEPTION_DB ( m_result.error, m_result.errnb );
		}
#endif
		return this->m_result;
	}
	// Get the last AUTO_INCREMENT
	llu = mysql_insert_id ( m_mysql );
	m_result.last_auto_increment = ( long long unsigned int ) llu;

	// Get the number of affected rows
	llu = mysql_affected_rows ( m_mysql );
	if ( llu != static_cast<my_ulonglong>(-1) )
	{
		m_result.affected_row = ( long long unsigned int ) llu;
	}

	// Get info
	// We must pass via a const char * because the pointer can be null
	// (in case of not infos are available).
	const char* str = mysql_info ( m_mysql );
	if ( str )
	{
		m_result.info = str;
	}
	else
	{
		m_result.info = "";
	}

	// Get the number of fields
	num_fields = mysql_field_count ( m_mysql );

	// Get results of query if any
	results = mysql_store_result ( m_mysql );
	if ( results )
	{
		// Get field names
		fields = mysql_fetch_fields ( results );
		while ( ( row = mysql_fetch_row ( results ) ) )
		{
			// Get the length of data by index
			lengths = mysql_fetch_lengths ( results );
			for ( unsigned int i = 0 ; i < num_fields ; i++ )
			{
				if ( lengths[i] == 0 )
				{
					buffer = "NULL";
				}
				else
				{
					buffer = row[i];
				}
				// Affect data to field name
				row_result[fields[i].name] = buffer;
			}
			m_result.rows.push_back ( row_result );
		}
		// free the result memory
		mysql_free_result ( results );
		m_result.errnb = SUCCESS;
	}
	else
	{
		if ( num_fields > 0 )
		{
			m_result.errnb = UNKNOW_ERROR;
			m_result.error = mysql_error ( m_mysql );
		}
		else
		{
			m_result.errnb = SUCCESS;
		}
	}

	if ( closeConnection )
	{
		old_errnb = m_result.errnb;
		close();
		m_result.errnb = old_errnb;
	}

	return this->m_result;
}
