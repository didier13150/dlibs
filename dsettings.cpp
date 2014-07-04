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

#include "dsettings.h"
#ifndef WITH_EXCEPTIONS
#define WITH_EXCEPTIONS 0
#endif
#if WITH_EXCEPTIONS
#include "dexception.h"
#endif
using namespace std;

DSettings::DSettings () : DSkeleton ()
{
	init();
}

#if WITH_EXCEPTIONS
DSettings::DSettings ( bool use_dexceptions ) : DSkeleton ( use_dexceptions )
{
	init();
}
#endif

DSettings::~DSettings ()
{
	deleteDOM();
}

void DSettings::init()
{
	m_doc = 0;
	m_context = 0;
	m_error = SUCCESS;
	DomOK = false;
}

int DSettings::setFileName ( const DString & fileName )
{
	m_fileName = fileName;
	return ( makeDOM() );
}

const DString DSettings::getFileName ( void ) const
{
	return m_fileName;
}

int DSettings::setGroup ( const DString & group, bool create )
{
	DString buffer;
	xmlNodePtr n = NULL;

	m_group = group;

	if ( !DomOK )
	{
		m_error = NO_DOM;
#if WITH_EXCEPTIONS
		if ( _use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), NO_DOM );
		}
#endif
		return m_error;
	}

	// Evaluate XPath expression
	buffer = "/";
	buffer += m_rootNodeName;
	buffer += "/";
	buffer += m_group;
	n = getNodeByXPath ( buffer.c_str() );

	if ( n == NULL )
	{
		m_error = GROUP_NOT_EXISTS;
		if ( create )
		{
			xmlNodePtr newNode = xmlNewTextChild ( m_rootNode,
			                                       NULL,
			                                       xmlCharStrdup ( m_group.c_str() ),
			                                       0 );
			if ( newNode == NULL )
			{
				m_error =  ENTRY_NOT_CREATED;
#if WITH_EXCEPTIONS
				if ( _use_dexceptions )
				{
					throw DEXCEPTION_XML ( getLastError(), ENTRY_NOT_CREATED );
				}
#endif
			}
			else
			{
				m_error = SUCCESS;
			}
		}
		else
		{
#if WITH_EXCEPTIONS
			if ( _use_dexceptions )
			{
				throw DEXCEPTION_XML ( getLastError(), GROUP_NOT_EXISTS );
			}
#endif
		}
	}
	else
	{
		m_error = SUCCESS;
	}
	return m_error;
}

DString & DSettings::getGroup ( void )
{
	return this->m_group;
}

bool DSettings::hasGroup ( const DString & group )
{
	DString buffer;
	xmlNodePtr n = NULL;

	if ( !DomOK )
	{
		m_error = NO_DOM;
#if WITH_EXCEPTIONS
		if ( _use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), NO_DOM );
		}
#endif
		return false;
	}

	// Evaluate XPath expression
	buffer = "/";
	buffer += m_rootNodeName;
	buffer += "/";
	buffer += group;
	n = getNodeByXPath ( buffer.c_str() );

	if ( n != NULL )
	{
		return true;
	}
	return false;
}

int DSettings::getLastErrno ( void ) const
{
	return this->m_error;
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
			err += "Cannot setup entry (";
			err += m_group;
			err += "/";
			err += m_key;
			err += ")";
			break;
		}
		case DSettings::ENTRY_NOT_CREATED:
		{
			err += "Cannot create new entry (";
			err += m_group;
			err += "/";
			err += m_key;
			err += ")";
			break;
		}
		case DSettings::NO_ENTRY:
		{
			err += "Entry doesn't exists (";
			err += m_group;
			err += "/";
			err += m_key;
			err += ")";
			break;
		}
		case DSettings::FILE_NOT_SAVED:
		{
			err += "Cannot save the XML file";
			break;
		}
		case DSettings::GROUP_NOT_EXISTS:
		{
			err += "Cannot found selected group (";
			err += m_group;
			err += ")";
			break;
		}
		default:
		{
			err.append( "unknow error" );
		}
	}

	return err;
}

int DSettings::readEntry ( const DString & key, DString & value )
{
	xmlNodePtr n = NULL;
	DString str = "";
	DString buffer;

	m_key = key;
	if ( !DomOK )
	{
		m_error = NO_DOM;
		value.clear();
#if WITH_EXCEPTIONS
		if ( _use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), NO_DOM );
		}
#endif
		return m_error;
	}

	// Evaluate XPath expression
	buffer = "/";
	buffer += m_rootNodeName;
	buffer += "/";
	buffer += m_group;
	buffer += "/";
	buffer += key;
	n = getNodeByXPath ( buffer );

	if ( n != NULL )
	{
		value = reinterpret_cast<char*> ( xmlNodeGetContent ( n ) );
		m_error = SUCCESS;
	}
	else
	{
		m_error = NO_ENTRY;
		value.clear();
#if WITH_EXCEPTIONS
		if ( _use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), NO_ENTRY );
		}
#endif
	}
	return m_error;
}

int DSettings::writeEntry ( const DString & key, const DString & value )
{
	DString bufVal ( value );
	DString buffer;
	DString node;
	xmlNodePtr xpathnode;

	if ( !DomOK )
	{
		m_error = NO_DOM;
#if WITH_EXCEPTIONS
		if ( _use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), NO_DOM );
		}
#endif
		return m_error;
	}

	// Evaluate XPath expression
	buffer = "/";
	buffer += m_rootNodeName;
	buffer += "/";
	buffer += m_group;
	buffer += "/";
	buffer += key;
	xpathnode = getNodeByXPath ( buffer );

	// no node yet, create it
	if ( xpathnode == NULL )
	{
		m_error = NO_ENTRY;
		//return m_error;
		node = "/";
		//node += m_rootNodeName;
		//node += "/";
		node += m_group;
		xpathnode = getNodeByXPath ( node );
		if ( xpathnode != NULL )
		{
			xmlNodePtr newNode = xmlNewTextChild ( xpathnode,
			                                       NULL,
			                                       xmlCharStrdup ( key.c_str() ),
			                                       xmlCharStrdup ( value.c_str() ) );
			if ( newNode == NULL )
			{
				m_error = ENTRY_NOT_SAVED;
#if WITH_EXCEPTIONS
				if ( _use_dexceptions )
				{
					throw DEXCEPTION_XML ( getLastError(), ENTRY_NOT_SAVED );
				}
#endif
				return m_error;
			}
		}
		else
		{
			m_error = ENTRY_NOT_CREATED;
#if WITH_EXCEPTIONS
			if ( _use_dexceptions )
			{
				throw DEXCEPTION_XML ( getLastError(), ENTRY_NOT_CREATED );
			}
#endif
			return m_error;
		}
	}
	// node exists, modify it
	else
	{
		xmlNodeSetContent ( xpathnode, xmlCharStrdup ( bufVal.c_str() ) );
	}

	if ( xmlSaveFormatFile ( m_fileName.c_str(), m_doc, 1 ) > 0 )
	{
		m_error = SUCCESS;
	}
	else
	{
		m_error = FILE_NOT_SAVED;
#if WITH_EXCEPTIONS
		if ( _use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), FILE_NOT_SAVED );
		}
#endif
	}
	return m_error;
}

int DSettings::makeDOM ( void )
{
	// Create DOM tree from XML file
	xmlKeepBlanksDefault ( 0 );
	if ( ( m_doc = xmlParseFile ( m_fileName.c_str() ) ) == NULL )
	{
		deleteDOM();
		m_error = NO_FILE;
#if WITH_EXCEPTIONS
		if ( _use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), NO_FILE );
		}
#endif
		return m_error;
	}
	// Get root nood
	m_rootNode = xmlDocGetRootElement ( m_doc );
	if ( m_rootNode == NULL )
	{
		deleteDOM();
		m_error = NO_ROOT_NODE;
#if WITH_EXCEPTIONS
		if ( _use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), NO_ROOT_NODE );
		}
#endif
		return m_error;
	}
	
	// Init XPath environnement
	xmlXPathInit();
	// Create context for XPath queries
	m_context = xmlXPathNewContext ( m_doc );
	if ( m_context == NULL )
	{
		deleteDOM();
		m_error = NO_CONTEXT;
#if WITH_EXCEPTIONS
		if ( _use_dexceptions )
		{
			throw DEXCEPTION_XML ( getLastError(), NO_CONTEXT );
		}
#endif
		return m_error;
	}
	
	m_rootNodeName = reinterpret_cast<const char*> ( m_rootNode->name );
	m_error = SUCCESS;
	DomOK = true;
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
	DomOK = false;
}

xmlNodePtr DSettings::getNodeByXPath ( const DString & key )
{
	xmlNodePtr n = NULL;
	xmlXPathObjectPtr xpathRes;

	xpathRes = xmlXPathEvalExpression ( xmlCharStrdup ( key.c_str() ), m_context );
	if ( ( xpathRes ) &&
	     ( xpathRes->type == XPATH_NODESET ) &&
	     ( xpathRes->nodesetval->nodeNr == 1 ) )
	{
		n = xpathRes->nodesetval->nodeTab[0];
	}
	xmlXPathFreeObject ( xpathRes );

	return n;
}

xmlNodePtrList DSettings::getNodesByXPath ( const DString & key )
{
	xmlNodePtrList list;
	xmlNodePtr n = NULL;
	xmlXPathObjectPtr xpathRes;

	xpathRes = xmlXPathEvalExpression ( xmlCharStrdup ( key.c_str() ), m_context );
	if ( ( xpathRes ) &&
	     ( xpathRes->type == XPATH_NODESET ) )
	{
		int i = 0;
		n = xpathRes->nodesetval->nodeTab[i];
		while( n != NULL ) {
			list.push_back( n );
			i++;
			n = xpathRes->nodesetval->nodeTab[i];
		}
	}
	xmlXPathFreeObject ( xpathRes );

	return list;
}

const DString & DSettings::getSettings ( DSettings & sets,
                                         const DString & group,
                                         const DString & key,
                                         DString * err = 0 )
{
	static DString entry;

	if ( sets.setGroup ( group, false ) != DSettings::SUCCESS )
	{
		if ( sets.getLastErrno() == DSettings::GROUP_NOT_EXISTS )
		{
			if ( err )
			{
				*err = sets.getLastError();
			}
		}
		else
		{
			if ( err )
			{
				*err = sets.getLastError();
			}
		}
		entry.clear();
		return entry;
	}
	if ( sets.readEntry ( key, entry ) != DSettings::SUCCESS )
	{
		if ( sets.getLastErrno() == DSettings::NO_ENTRY )
		{
			if ( err )
			{
				*err = sets.getLastError();
			}
		}
		else
		{
			if ( err )
			{
				*err = sets.getLastError();
			}
		}
		entry.clear();
		return entry;
	}
	if ( err )
	{
		err->clear();
	}
	return entry;
}

bool getSettings ( DSettings & sets,
                   const DString & group,
                   const DString & key,
                   DString & buffer,
                   DString & err )
{
	buffer = DSettings::getSettings ( sets, group, key, &err );
	if ( buffer.isEmpty() )
	{
		return false;
	}
	return true;
}
