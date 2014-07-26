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

#ifndef DSETTINGS_H
#define DSETTINGS_H

#include <iostream>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include "dstring.h"
#include "dskeleton.h"

#ifndef WITH_EXCEPTIONS
#define COMPILE_WITH_EXCEPTIONS 0
#else
#define COMPILE_WITH_EXCEPTIONS 1
#endif

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
 * @include dsettings.dox
 * @brief Config file.
 */
class DSettings : public DSkeleton
{

public:
    /**
     * Empty constructor
     */
    DSettings ( void );
#ifdef COMPILE_WITH_EXCEPTIONS
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
     * @see #sets_errors enum for returned values
     */
    int readEntry ( const DString & xpath, DString & value );

    /**
     * Get the entry
     */
    DString getEntry ( const DString & xpath );

    /**
     * Get all entries
     */
    const DStringList & getEntries ( const DString & xpath );

    /**
     * Write the entry
     * @see #sets_errors enum for returned values
     */
    int writeEntry ( const DString & xpath, const DString & value, bool replace = true );

    /**
     * Set the XML file name
     * @attention the root node name must be set before calling this function.
     * @see #sets_errors enum for returned values
     */
    int setFileName ( const DString & fileName );

    /**
     * Get the XML file name
     */
    const DString & getFileName ( void ) const;
	
	/**
	 * Get the root node
	 */
	const DString & getRootNode( void ) const;

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

private:
    /// The file name
    DString m_fileName;
    /// The root node name
    DString m_rootNode;
    /// The last entries value
    DStringList m_values;
    /// The XML document
    xmlDocPtr m_doc;
    /// The XML context
    xmlXPathContextPtr m_context;
    /// The last error code
    int m_error;
    /// DOM created flag
    bool m_isValid;

    /**
     * Construct the DOM XML tree in memory
     */
    int  makeDOM ( void );

    /**
     * Delete the DOM XML tree from memory
     */
    void deleteDOM ( void );

    /**
     * Get all nodes values by XPath
     */
    void getNodeValuesByXPath ( const DString & path );
	
	/**
	 * Update node value by XPath
	 */
	void updateNodeValueByXPath ( const DString & path, 
								  const DString & value );
	
	/**
	 * Create node value by XPath
	 */
	void insertNodeValueByXPath ( const DString & path, 
								  const DString & value );

    /**
     * Init the class
     */
    void init ( void );

    /**
     * Read the entry matching xpath
     */
    void read ( const DString & xpath, bool onlyone = true );
};

#endif // DSETTINGS_H
