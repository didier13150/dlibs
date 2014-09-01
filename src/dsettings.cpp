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
 *     (___)_)   File : dsettings.cpp                       ||--|| *          *
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

#include "dsettings.h"

#ifdef WITH_EXCEPTIONS
  #include "dexception.h"
#endif
using namespace std;

DSettings::DSettings () : DSkeleton ()
{
	init();
}

DSettings::DSettings ( bool use_dexceptions ) : DSkeleton ( use_dexceptions )
{
	init();
}

DSettings::~DSettings ()
{
	deleteDOM();
}

void DSettings::init()
{
	m_doc = 0;
	m_context = 0;
	m_error = SUCCESS;
	m_isValid = false;
}

int DSettings::setFileName ( const DString & fileName )
{
	m_fileName = fileName;
	return ( makeDOM() );
}

const DString & DSettings::getFileName ( void ) const
{
	return m_fileName;
}

int DSettings::getLastErrno ( void ) const
{
	return this->m_error;
}

const DString & DSettings::getRootNode( void ) const
{
	return this->m_rootNode;
}

const DString & DSettings::getLastError ( void ) const
{
	static DString err;
	
	err.setNum( m_error );
	err.prepend( "error (" );
	err.append( ") : " );
	
	switch ( m_error )
	{
		case DSettings::NO_FILE:
		{
			err += "Cannot open XML file.";
			break;
		}
		case DSettings::NO_ROOT_NODE:
		{
			err += "Cannot find root node.";
			break;
		}
		case DSettings::NO_CONTEXT:
		{
			err += "Cannot create XML context.";
			break;
		}
		case DSettings::SUCCESS:
		{
			err = "OK";
			break;
		}
		case DSettings::NO_DOM:
		{
			err += "DOM is not available.";
			break;
		}
		case DSettings::ENTRY_NOT_SAVED:
		{
			err += "Cannot save entry";
			break;
		}
		case DSettings::ENTRY_NOT_CREATED:
		{
			err += "Cannot create new entry";
			break;
		}
		case DSettings::NO_ENTRY:
		{
			err += "Entry doesn't exists";
			break;
		}
		case DSettings::FILE_NOT_SAVED:
		{
			err += "Cannot save the XML file";
			break;
		}
		default:
		{
			err.append( "unknow error" );
		}
	}

	return err;
}

const DStringList & DSettings::getEntries ( const DString & xpath )
{
	read( xpath );
	return m_values;
}

DString DSettings::getEntry ( const DString & xpath )
{
	DString buffer;
	readEntry( xpath, buffer );
	if ( m_error == DSettings::SUCCESS )
	{
		return buffer;
	}
	return DString::empty();
}

int DSettings::readEntry ( const DString & xpath, DString & value )
{
	DStringList::const_iterator it;
	
	value.clear();
	read( xpath );
	it = m_values.begin();
	if ( it != m_values.end() )
	{
		value = *it;
	}
	return m_error;
}

void DSettings::read ( const DString & xpath, bool onlyone )
{
	m_values.clear();
	
	if ( m_fileName.isEmpty() )
	{
		m_error = NO_FILE;
#ifdef WITH_EXCEPTIONS
		if ( m_use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), NO_FILE );
		}
#endif
		return;
	}
	
	if ( ! m_isValid )
	{
		m_error = NO_DOM;
#ifdef WITH_EXCEPTIONS
		if ( m_use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), NO_DOM );
		}
#endif
		return;
	}

	// Evaluate XPath expression
	getNodeValuesByXPath ( xpath );
	
	if ( m_error == DSettings::NO_ENTRY )
	{
#ifdef WITH_EXCEPTIONS
		if ( m_use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), NO_ENTRY );
		}
#endif
		return;
	}
}

int DSettings::writeEntry ( const DString & xpath, const DString & value, bool replace )
{
	
	if ( m_fileName.isEmpty() )
	{
		m_error = NO_FILE;
#ifdef WITH_EXCEPTIONS
		if ( m_use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), NO_FILE );
		}
#endif
		return m_error;
	}
	
	if ( ! m_isValid )
	{
		m_error = NO_DOM;
#ifdef WITH_EXCEPTIONS
		if ( m_use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), NO_DOM );
		}
#endif
		return m_error;
	}
	//Create full path if not exists (except root node)
	int id = 1;
	int max = xpath.contains( "/" );
	do
	{
		if ( id == max ) break;
		DString key = xpath.section( '/', id, id );
		DString path = "/" + xpath.section( '/', 0, id-1 );
		read( path + "/" + key );
		if ( m_error == DSettings::NO_ENTRY )
		{
			insertNodeValueByXPath( path + "/" + key );
		}
		id++;
	} while ( m_error == DSettings::SUCCESS );
	
	if ( replace )
	{
		updateNodeValueByXPath( xpath, value );
	}
	else
	{
		insertNodeValueByXPath( xpath, value );
	}
	return m_error;
}

int DSettings::makeDOM ( void )
{
	xmlNodePtr rootNode;

	// Create DOM tree from XML file
	xmlKeepBlanksDefault ( 0 );
	if ( ( m_doc = xmlParseFile ( m_fileName.c_str() ) ) == NULL )
	{
		deleteDOM();
		m_error = NO_FILE;
#ifdef WITH_EXCEPTIONS
		if ( m_use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), NO_FILE );
		}
#endif
		return m_error;
	}
	// Get root nood
	rootNode = xmlDocGetRootElement ( m_doc );
	
	if ( rootNode == NULL )
	{
		deleteDOM();
		m_error = NO_ROOT_NODE;
#ifdef WITH_EXCEPTIONS
		if ( m_use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), NO_ROOT_NODE );
		}
#endif
		return m_error;
	}
	
	m_rootNode = reinterpret_cast<const char*> ( rootNode->name );
		
	// Init XPath environnement
	xmlXPathInit();
	// Create context for XPath queries
	m_context = xmlXPathNewContext ( m_doc );
	if ( m_context == NULL )
	{
		deleteDOM();
		m_error = NO_CONTEXT;
#ifdef WITH_EXCEPTIONS
		if ( m_use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), NO_CONTEXT );
		}
#endif
		return m_error;
	}
	
	m_error = SUCCESS;
	m_isValid = true;
	return m_error;
}

void DSettings::deleteDOM ( void )
{
	if ( m_context )
	{
		xmlXPathFreeContext ( m_context );
		m_context = 0;
	}
	if ( m_doc )
	{
		xmlFreeDoc ( m_doc );
		m_doc = 0;
	}
	xmlCleanupParser();
	m_isValid = false;
}

void DSettings::insertNodeValueByXPath ( const DString & xpath,
										 const DString & value )
{
	DString key, path;
	xmlChar * buffer = 0;
	xmlChar * val = 0;
	xmlNodePtr node = 0;
	xmlXPathObjectPtr xpathRes = 0;
	
	key = xpath.section( '/', -1, -1 );
	path = "/" + xpath.section( '/', -2 );
	
	buffer = xmlCharStrdup ( path.c_str() );
	xpathRes = xmlXPathEvalExpression ( buffer, m_context );
	xmlFree( buffer );
	buffer = 0;
	if ( ( xpathRes != NULL ) &&
	     ( xpathRes->type == XPATH_NODESET ) &&
	     ( xpathRes->nodesetval->nodeNr > 0 ) )
	{
		node = xpathRes->nodesetval->nodeTab[0];
		if ( node != NULL )
		{
			if ( ! value.isEmpty() )
			{
				val = xmlCharStrdup ( value.c_str() );
			}
			else
			{
				val = NULL;
			}
			buffer = xmlCharStrdup ( key.c_str() );
			xmlNodePtr newNode = xmlNewTextChild ( node, NULL, buffer, val );
			xmlFree( val );
			xmlFree( buffer );
			val = 0;
			buffer = 0;
			xmlXPathFreeObject ( xpathRes );
			if ( newNode == NULL )
			{
				m_error = ENTRY_NOT_SAVED;
#ifdef WITH_EXCEPTIONS
				if ( m_use_dexceptions )
				{
					throw DEXCEPTION_XML ( getLastError(), ENTRY_NOT_SAVED );
				}
#endif
				return;
			}
		}
		if ( xmlSaveFormatFile ( m_fileName.c_str(), m_doc, 1 ) > 0 )
		{
			m_error = SUCCESS;
		}
		else
		{
			m_error = ENTRY_NOT_CREATED;
#ifdef WITH_EXCEPTIONS
			if ( m_use_dexceptions )
			{
				throw DEXCEPTION_XML ( getLastError(), ENTRY_NOT_CREATED );
			}
#endif
		}
	}
	else
	{
		m_error = ENTRY_NOT_CREATED;
#ifdef WITH_EXCEPTIONS
		if ( m_use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), ENTRY_NOT_CREATED );
		}
#endif
	}
}

void DSettings::updateNodeValueByXPath ( const DString & xpath,
										 const DString & value )
{
	DString buffer;
	xmlNodePtr node = 0;
	xmlXPathObjectPtr xpathRes = 0;
	xmlChar * val = 0;

	m_values.clear();
	val = xmlCharStrdup ( xpath.c_str() );
	xpathRes = xmlXPathEvalExpression ( val, m_context );
	xmlFree( val );
	val = 0;
	if ( ( xpathRes != NULL ) &&
	     ( xpathRes->type == XPATH_NODESET ) &&
	     ( xpathRes->nodesetval->nodeNr > 0 ) )
	{
		node = xpathRes->nodesetval->nodeTab[0];
		if ( node != NULL )
		{
			val = xmlCharStrdup ( value.c_str() );
			xmlNodeSetContent ( node, val );
			xmlFree( val );
			val = 0;
		}
		xmlXPathFreeObject ( xpathRes );
		if ( xmlSaveFormatFile ( m_fileName.c_str(), m_doc, 1 ) > 0 )
		{
			m_error = SUCCESS;
		}
		else
		{
			m_error = FILE_NOT_SAVED;
#ifdef WITH_EXCEPTIONS
			if ( m_use_dexceptions )
			{
				throw DEXCEPTION_XML ( getLastError(), FILE_NOT_SAVED );
			}
#endif
		}
	}
	else
	{
		xmlXPathFreeObject ( xpathRes );
		m_error = NO_ENTRY;
		insertNodeValueByXPath( xpath, value );
	}
}

void DSettings::getNodeValuesByXPath ( const DString & xpath )
{
	DString buffer;
	xmlNodePtr node = 0;
	xmlXPathObjectPtr xpathRes = 0;
	xmlChar * val = 0;

	m_values.clear();
	val = xmlCharStrdup ( xpath.c_str() );
	xpathRes = xmlXPathEvalExpression ( val, m_context );
	xmlFree( val );
	val = 0;
	if ( ( xpathRes != NULL ) &&
	     ( xpathRes->type == XPATH_NODESET ) &&
	     ( xpathRes->nodesetval->nodeNr > 0 ) )
	{
		m_error = SUCCESS;
		for ( int i = 0 ; i < xpathRes->nodesetval->nodeNr ; ++i )
		{
			node = xpathRes->nodesetval->nodeTab[i];
			if ( node != NULL )
			{
				val = xmlNodeGetContent( node );
				if ( val != NULL )
				{
					buffer = reinterpret_cast<char*> ( val );
					m_values.push_back( buffer );
					xmlFree( val );
					val = 0;
				}
			}
		}
	}
	else
	{
		m_error = NO_ENTRY;
	}
	xmlXPathFreeObject ( xpathRes );
}
