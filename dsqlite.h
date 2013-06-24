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
 *     (___)_)   File : dsqlite.h                           ||--|| *          *
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

#ifndef _DSQLITE_H_
#define _DSQLITE_H_

#include "dskeleton.h"
#include "ddatabase.h"
#include "dstring.h"

#include <vector>
#include <map>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>


struct sqlite3;

/**
 * @short SQLite abstraction class.
 * @author Didier FABERT <didier.fabert@gmail.com>
 * \include testdsqlite.cpp
 */

class DSQLite : public DDatabase
{

	public:
		/**
		 * Empty Constructor
		 */
		DSQLite();

		/**
		 * Default Constructor
		 */
		DSQLite ( bool use_dexceptions );

		/**
		 * Destructor
		 */
		~DSQLite();

		DDatabase * Clone() const
		{
			return new DSQLite ( *this );
		}

		/**
		 * Set SQL parameters : Host, User, Password, Database.
		 */
		void setParams ( const DDatabaseParams & params );

		/**
		 * Open the SQL connection.
		 */
		DDatabaseResult & open();

		/**
		 * Close the SQL connection.
		 */
		void close();
		
		/**
		 * Set connection options ( not use in DSQLite ).
		 */
		void setOptions ( const DDatabaseOptions & opt );
		
		/**
		 * Execute the SQL query.\n
		 * @note You need to open a connection before calling this function.\n
		 * Don't forget to close it when all is done.
		 */
		DDatabaseResult & exec ( const DString & query );

	private:
		/// The MySQL connected flag.
		bool m_opened;

		/// MySQL connect parameters : Host, User, Password, Database and Port.
		DDatabaseParams m_params;

		/// The results of the last query.
		DDatabaseResult m_result;


		/// The SQLite object.
		sqlite3 * m_sqlite;

		/**
		 * Initialize class
		 */
		void init();
};

#endif // _DSQLITE_H_
