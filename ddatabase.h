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
 *     (___)_)   File : ddatabase.h                         ||--|| *          *
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

#ifndef _DDATABASE_H_
#define _DDATABASE_H_

#include <vector>
#include <map>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>

#include "dstring.h"
#include "dskeleton.h"
#include "dprototype.h"


#ifndef WITH_EXCEPTIONS
#define WITH_EXCEPTIONS 0
#endif
/**
 * @relates DMyDatabase
 */
typedef std::map<DString, DString> DDatabaseRow;
/**
 * @relates DMyDatabase
 */
typedef std::vector<DDatabaseRow> DDatabaseRows;

/**
 * @short Database Parameters.
 * @relates DDatabase
 * @author Didier FABERT <didier.fabert@gmail.com>
 */

class DDatabaseParams
{
public:
	/**
	 * Constructor
	 */
	DDatabaseParams();
	
	/**
	 * Destructor
	 */
	~DDatabaseParams();

	/**
	 * Copy operator
	 */
	DDatabaseParams & operator = ( const DDatabaseParams & params );
	
	/**
	 * TRUE if DDatabaseParams are equal, FALSE otherwise.
	 * All members must be equal to declare DDatabaseParams equality.
	 */
	friend bool operator == ( const DDatabaseParams & ,  const DDatabaseParams & );
	
	/**
	 * FALSE if DDatabaseParams are equal, TRUE otherwise.
	 * All members must be equal to declare DDatabaseParams equality.
	 */
	friend bool operator != ( const DDatabaseParams & ,  const DDatabaseParams & );
	
	/**
	 * Writes DDatabaseParams to the stream s and returns a reference to the stream.
	 */
	friend std::ostream& operator << ( std::ostream& s, const DDatabaseParams & params );

	/// The Database base
	DString base;
	/// The Database host
	DString host;
	/// The Database user
	DString user;
	/// The Database password
	DString password;
	/// The Database port
	DString port;

	/**
	 * Clear all params
	 */
	void clear();

	/**
	 * Check if minimum param are set ( base name ).
	 * @return TRUE if minimum param are set, FALSE otherwise.
	 */
	bool isSet();
	
	/**
	 * Convert to string
	 * @return A connection string
	 */
	DString toString() const;
};

/**
 * @short Database results.
 * @relates DDatabase
 * @author Didier FABERT <didier.fabert@gmail.com>
 */

class DDatabaseResult
{

	public:
		DDatabaseResult();
		~DDatabaseResult();

		void clear();

		/**
		 * Writes DDatabaseResult to the stream s and returns a reference to the stream.
		 */
		friend std::ostream& operator << ( std::ostream& s, const DDatabaseResult & params );
		
		DDatabaseRows rows;
		long long unsigned int last_auto_increment;
		long long unsigned int affected_row;
		long int errnb;
		DString error;
		DString last_query;
		DString info;
};


/**
 * @short Database connection Options.
 * @relates DDatabase
 * @author Didier FABERT <didier.fabert@gmail.com>
 */
class DDatabaseOptions
{
	public:
		/// The connect timeout.
		DString connect_timeout;
		/// The read timeout.
		DString read_timeout;
		/// The write timeout.
		DString write_timeout;
		/// The initialized flag.
		bool initialized;
};

/**
 * Abstract class for database operations :
 * - connect / disconnect
 * - execute query and get the results
 * Support exceptions  via DException class
 * @short Database operation.
 * @author Didier FABERT <didier.fabert@gmail.com>
 */

class DDatabase : public DSkeleton, public DPrototype<DDatabase>
{
	public:
		/**
		 * Empty constructor
		 */
		DDatabase();

#if WITH_EXCEPTIONS
		/**
		 * Default constructor for managing exceptions
		 */
		DDatabase ( bool );
#endif
		
		/**
		 * Virtual destructor
		 */
		virtual ~DDatabase();

		enum Errno
		{
			/// Success, no error reported
			SUCCESS = 0,
			/// There is an error in the query
			QUERY_ERROR,
			/// Option connect failure
			SET_OPT_CONNECT_FAILED,
			/// Option read failure
			SET_OPT_READ_FAILED,
			/// Option write failure
			SET_OPT_WRITE_FAILED,
			/// Connection to database is lose
			CONNECTION_LOSE,
			/// Database is not opened
			NO_CONNECTED,
			/// Parameters are empty or partially filled
			WRONG_PARAM,
			/// Unknow error encoured
			UNKNOW_ERROR,
		};

		/**
		 * Set Database parameters : Host, User, Password, Database and Port.
		 */
		virtual void setParams ( const DDatabaseParams & params );

		/**
			 * Open the Database connection.
			 */
		virtual DDatabaseResult & open() = 0;

		/**
		 * Close the Database connection.
		 */
		virtual void close() = 0;


		/**
		 * Set connection options (connect timeout, read timeout, write timeout).
		 */
		virtual void setOptions ( const DDatabaseOptions & opt ) = 0;

		/**
		 * Execute the query on Database.\n
		 * @note You need to open a connection before calling this function if you
		 * want to have a persistant connection. Don't forget to close it when all
		 * is finished.
		 */
		virtual DDatabaseResult & exec ( const DString & query ) = 0;

		/**
		 * Return true if connection to database is already etablished, false otherwise.
		 */
		bool isOpen();

	protected:

		/// The internal report string
		std::map<int, DString> _errors;

		/// The connection to Database flag.
		bool m_opened;

		/// Database connect parameters : Host, User, Password, Database and Port.
		DDatabaseParams m_params;

		/// The results of the last query.
		DDatabaseResult m_result;

	private:
		void internal_init();
};

#endif // _DDATABASE_H_
