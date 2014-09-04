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
 *     (___)_)   File : dmysql.h                            ||--|| *          *
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

#ifndef _DMYSQL_H_
#define _DMYSQL_H_

#include "ddatabase.h"
#include "dstring.h"
#include "dskeleton.h"

#include <vector>
#include <map>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>

struct st_mysql;

/**
 * @typedef DSQLRow
 * @relates DMySQL
 * @deprecated Use DDatabaseRow object directly
 */
typedef DDatabaseRow DSQLRow;

/**
 * @typedef DSQLRows
 * @relates DMySQL
 * @deprecated Use DDatabaseRows object directly
 */
typedef DDatabaseRows DSQLRows;
/**
 * @typedef DMySQLRow
 * @relates DMySQL
 * @deprecated Use DDatabaseRow object directly
 */
typedef DDatabaseRow DMySQLRow;

/**
 * @typedef DMySQLRows
 * @relates DMySQL
 * @deprecated Use DDatabaseRows object directly
 */
typedef DDatabaseRows DMySQLRows;


/**
 * @typedef DSQLResult
 * @relates DMySQL
 * @deprecated Use DDatabaseResult object directly
 */
typedef DDatabaseResult DSQLResult;

/**
 * @typedef DMySQLResult
 * @relates DMySQL
 * @deprecated Use DDatabaseResult object directly
 */
typedef DDatabaseResult DMySQLResult;


/**
 * @typedef DSQLParams
 * @relates DMySQL
 * @deprecated Use DDatabaseParams object directly
 */
typedef DDatabaseParams DSQLParams;

/**
 * @typedef DMySQLParams
 * @relates DMySQL
 * @deprecated Use DDatabaseParams object directly
 */
typedef DDatabaseParams DMySQLParams;

/**
 * @typedef DMySQLOptions
 * @relates DMySQL
 * @deprecated Use DDatabaseOptions object directly
 */
typedef DDatabaseOptions DMySQLOptions;

/**
 * @typedef DSQLOptions
 * @relates DMySQL
 * @deprecated
 */
typedef DDatabaseOptions DSQLOptions;

/**
 * @short MySQL database operation.
 * @author Didier FABERT <didier.fabert@gmail.com>
 * \include dmysql.dox
 */
class DMySQL : public DDatabase
{
public:
	/**
	 * Empty Constructor
	 */
	DMySQL();

	/**
	 * Default Constructor
	 */
	DMySQL( bool use_dexceptions );

	/**
	 * Destructor
	 */
	~DMySQL();

	DDatabase * Clone() const
	{
		return new DMySQL ( *this );
	}
	/**
	 * Set SQL parameters : Host, User, Password, Database.
	 */
	void setParams ( const DDatabaseParams & params );

	/**
	 * Set connection options (connect timeout, read timeout, write timeout).
	 */
	void setOptions ( const DDatabaseOptions & opt );

	/**
	 * Open the SQL connection.
	 */
	DDatabaseResult & open();
	
	/**
	 * Close the SQL connection.
	 */
	void close();

	/**
	 * Execute the SQL query.\n
	 * @note You need to open a connection before calling this function if you
	 * want to have a persistant connection. Don't forget to close it when all
	 * is finished.
	 */
	DDatabaseResult & exec ( const DString & query );

private:
	/// The MySQL object.
	st_mysql * m_mysql;

	/**
	 * Initialize the class
	 */
	void init();
};

#endif // _DMYSQL_H_
