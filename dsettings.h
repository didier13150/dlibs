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
 *     (___)_)   File : dsettings.h                         ||--|| *          *
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

#ifndef DSETTINGS_H
#define DSETTINGS_H

#include <iostream>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include "dstring.h"
#include "dskeleton.h"

/**
 * @typedef xmlNodePtrList
 */
typedef std::list<xmlNodePtr> xmlNodePtrList;

/**
 * Class for reading and writing XML settings file.\n
 * Settings group are fully supported.\n
 * For now, include in root node are not supported.\n \n
 * Here is the xml test file.
 * @code
 * <?xml version="1.0"?>
 * <settings>
 *  <user1>
 *    <name>doe</name>
 *    <surname>john</surname>
 *  </user1>
 *  <user2>
 *    <name>bud</name>
 *    <surname>weiser</surname>
 *  </user2>
 * </settings>
 * @endcode
 * A little example program.
 * @include testdsettings.cpp
 * @brief Config file.
 */
class DSettings : public DSkeleton
{

	public:
		/**
		 * Empty constructor
		 */
		DSettings ( void );
#ifdef WITH_EXCEPTIONS
		/**
		 * Default constructor
		 */
		DSettings ( bool );
#endif
		/**
		 * Default destructor
		 */
		~DSettings ( void );

		/**
		 * Read the entry
		 * @attention the group must be set before calling this function.
		 * @see #setGroup
		 * @see #sets_errors enum for returned values
		 */
		int readEntry ( const DString & key, DString & value );
		/**
		 * Write the entry
		 * For now, Only a content of an existing node is possible.
		 * @attention the group must be set before calling this function.
		 * @see #setGroup
		 * @see #sets_errors enum for returned values
		 */
		int writeEntry ( const DString & key, const DString & value );

		/**
		 * Set the XML file name
		 * @attention the root node name must be set before calling this function.
		 * @see #sets_errors enum for returned values
		 */
		int setFileName ( const DString & fileName );

		/**
		 * Get the XML file name
		 */
		const DString getFileName ( void ) const;

		/**
		 * Get the root node name
		 */
		const DString getRootNodeName ( void ) const;

		/**
		 * Set the settings group.\n
		 * If create is TRUE (the default), the node is created if not exists;
		 * otherwise an error number is returned.\n
		 * @see #sets_errors enum for returned values
		 */
		int setGroup ( const DString & group, bool create = true );

		/**
		 * Get the current settings group
		 */
		DString & getGroup ( void );

		/**
		 * Return true if DOM have group \em group entry, false otherwise.
		 */
		bool hasGroup ( const DString & group );

		/**
		 * Get the last error code
		 * @see sets_errors enum for returned values
		 */
		int getLastErrno() const;

		/**
		 * Get the last error string
		 */
		const DString & getLastError() const;

		enum sets_errors
		{
			/// No error
			SUCCESS,
			/// File not found
			NO_FILE,
			/// Root node not found
			NO_ROOT_NODE,
			/// Cannot create context
			NO_CONTEXT,
			/// No entry found
			NO_ENTRY,
			/// Entry was not saved
			ENTRY_NOT_SAVED,
			/// Entry was not created because create flag is not set.\n
			/// By default the create flag is set.
			ENTRY_NOT_CREATED,
			/// The DOM is not created
			NO_DOM,
			/// Cannot save the XML file
			FILE_NOT_SAVED,
			/// Group was not exists and create flag is not set.\n
			/// By default the create flag is set.
			GROUP_NOT_EXISTS,
		};
		
		
		/**
		* Get quickly a parameter from an already DSetting class ( must be setup ).
		* This is a function, provided for convenience.
		* @param sets A reference to an existing settings class
		* @param group The group where the key must be found
		* @param key The key to found
		* @param err An error string, empty if no error was encoured.
		* @return The value of the specified key.
		*/
		static const DString & getSettings ( DSettings & sets,
		                                     const DString & group,
		                                     const DString & key,
		                                     DString * err );

	private:
		/// The file name
		DString m_fileName;
		/// The root node name
		DString m_rootNodeName;
		/// The last group name
		DString m_group;
		/// The last entry name
		DString m_key;
		/// The XML document
		xmlDocPtr m_doc;
		/// The XML root node
		xmlNodePtr m_rootNode;
		/// The XML context
		xmlXPathContextPtr m_context;
		/// The last error code
		int m_error;
		/// DOM created flag
		bool DomOK;

		/**
		 * Construct the DOM XML tree in memory
		 */
		int  makeDOM ( void );

		/**
		 * Delete the DOM XML tree from memory
		 */
		void deleteDOM ( void );

		/**
		 * Get a node by its XPath
		 */
		xmlNodePtr getNodeByXPath ( const DString & path );

		/**
		 * Get all nodes by its XPath
		 */
		xmlNodePtrList getNodesByXPath ( const DString & path );

		/**
		 * Init the class
		 */
		void init ( void );
};

/**
 * Get quickly a parameter.
 * This is a function, provided for convenience.
 * @relates DSettings
 * @deprecated Do not use it, it will be remove on next version.
 * @param sets [in] A reference to an existing settings class
 * @param group [in] The group where the key must be found
 * @param key [in] The key to found
 * @param buffer [out] the value of the specified key
 * @param err [out] An error string, empty if no error was encoured.
 * @return TRUE if value for key was found, FALSE otherwise.
 */
bool getSettings ( DSettings & sets,
                   const DString & group,
                   const DString & key,
                   DString & buffer,
                   DString & err );

#endif // DSETTINGS_H
