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
 *     (___)_)   File : dpgsql.h                            ||--|| *          *
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
#ifndef _DPGSQL_H_
#define _DPGSQL_H_

#include "ddatabase.h"
#include "dstring.h"
#include "dskeleton.h"

#include <postgres.h>
#include <vector>
#include <map>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>

class PGconnect;

/**
 * @short PostgreSQL database operation.
 * @author Didier FABERT <didier.fabert@gmail.com>
 * \include testdpgsql.cpp
 */
class DPgSQL : public DDatabase
{
public:
	/**
	 * Empty constructor
	 */
	DPgSQL();

	/**
	 * Default constructor for managing exceptions
	 */
	DPgSQL( bool );

	/**
	 * Destructor
	 */
	~DPgSQL();

	/**
	 * Set Database parameters : Host, User, Password, Database and Port.
	 */
	void setParams ( const DDatabaseParams & params );

	/**
	 * Set connection options (connect timeout, read timeout, write timeout).
	 */
	void setOptions ( const DDatabaseOptions & opt );

	/**
	 * Open the Database connection.
	 */
	DDatabaseResult & open();

	/**
	 * Close the Database connection.
	 */
	void close();

	/**
	 * Execute the query on Database.\n
	 * @note You need to open a connection before calling this function if you
	 * want to have a persistant connection. Don't forget to close it when all
	 * is finished.
	 */
	DDatabaseResult & exec ( const DString & query );

	/**
	 * Return true if connection to database is already etablished, false otherwise.
	 */
	bool isOpen();

	DDatabase * Clone() const
	{
		return new DPgSQL ( *this );
	}

private:
	/// MySQL connect parameters : Host, User, Password, Database and Port.
	DDatabaseParams m_params;

	/// The results of the last query.
	DDatabaseResult m_result;

	/// The connection options : connect timeout, read timeout, write timeout.
	DDatabaseOptions m_opt;

	/// The MySQL object.
	PGconnect * pgsql;

	/**
	 * Initialize the class
	 */
	void init();
};

#endif // _DPGSQL_H_
