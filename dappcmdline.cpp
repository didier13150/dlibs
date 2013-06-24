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
 *     (___)_)   File : dappcmdline.cpp                     ||--|| *          *
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

#include "dappcmdline.h"

DAppCmdLine::DAppCmdLine()
{
	m_autoID = 0;
	m_found = 0;
}

DAppCmdLine::DAppCmdLine( int argc,
			  char ** argv,
			  const DAppOptionList & optList,
			  const DAppArgList & argList)
{
	m_autoID = 0;
	m_found = 0;
	parse( argc, argv );
}


DAppCmdLine::~DAppCmdLine()
{
}

void DAppCmdLine::addOption ( const DString & name,
                        const DString & description,
                        const char alias,
                        bool argument_required )
{
	DString buffer;
	DAppOption opt ( name, description, alias, argument_required );

	// Insert option
	m_options[ name ] = opt;

	// Save alias name
	if ( alias )
	{
		m_alias[alias] = name;
	}

	// prepare help string
	buffer = "-";
	buffer.append ( alias );
	buffer.append ( ", --" );
	buffer.append ( name );

	if ( argument_required )
	{
		buffer.append ( "=VALUE" );
		buffer.append ( "\t" );
	}

	else
	{
		buffer.append ( "\t\t" );
	}

	buffer.append ( description );

	m_help_options.push_back ( buffer );
}

void DAppCmdLine::addOption ( const DAppOption & opt )
{
	addOption( opt.name, opt.description, opt.alias, opt.have_mandatory_value );
}

void DAppCmdLine::setOptions ( const DAppOptionList & list )
{
	DAppOptionList::const_iterator it;

	m_options.clear();
	m_alias.clear();
	for ( it = list.begin() ; it != list.end() ; ++it )
	{
		addOption( *it );
	}
}


const DString & DAppCmdLine::getOption ( const DString & name ) const
{
	static DString empty;
	
	std::map<DString, DAppOption>::const_iterator ito;
	std::map<DString, DString>::const_iterator its;

	ito = m_options.find ( name );

	if ( ito != m_options.end() )
	{
		return ( ito->second.value );
	}

	// search in alias
	its = m_alias.find( name );

	if ( its != m_alias.end() )
	{
		ito = m_options.find ( its->second );

		if ( ito != m_options.end() )
		{
			return ( ito->second.value );
		}
	}
	
	return empty;
}

bool DAppCmdLine::haveOption ( const DString & name ) const
{
	std::map<DString, DAppOption>::const_iterator ito;
	std::map<DString, DString>::const_iterator its;

	ito = m_options.find( name );
	if ( ito != m_options.end() )
	{
		return ( ito->second.is_set );
	}

	//search in alias
	its = m_alias.find( name );

	if ( its != m_alias.end() )
	{
		ito = m_options.find ( its->second );

		if ( ito != m_options.end() )
		{
			return ( ito->second.is_set );
		}
	}
	
	return false;
}

int DAppCmdLine::getNumberOfOptions() const
{
	return m_options.size();
}

void DAppCmdLine::addArgument ( const DString & description )
{
	DAppArg arg( m_autoID, description );

	m_arguments[m_autoID] = arg;
	m_help_arguments.push_back ( description );
	m_autoID++;
}

void DAppCmdLine::addArgument ( const DAppArg & arg )
{
	addArgument( arg.description );
}

void DAppCmdLine::setArguments ( const DAppArgList & list )
{
	DAppArgList::const_iterator it;

	m_arguments.clear();
	m_autoID = 0;
	for ( it = list.begin() ; it != list.end() ; ++it )
	{
		addArgument( *it );
	}
}

const DString & DAppCmdLine::getArgument ( unsigned int position ) const
{
	static DString empty;
	
	std::map<unsigned int, DAppArg>::const_iterator it;

	it = m_arguments.find ( position );

	if ( it != m_arguments.end() )
	{
		return ( ( *it ).second.value );
	}

	return empty;
}

unsigned int DAppCmdLine::getNbExpectedArgs() const
{
	return m_autoID;
}

unsigned int DAppCmdLine::getNbFoundArgs() const
{
	return m_found;
}

bool DAppCmdLine::haveAllExpectedArgsFound() const
{
	if ( m_autoID == m_found )
	{
		return true;
	}
	return false;
}

void DAppCmdLine::setAppVersion( const DString & version )
{
	m_appversion = version;
}

const DString & DAppCmdLine::getAppVersion() const
{
	return m_appversion;
}

const DString & DAppCmdLine::getAppName() const
{
	return m_appname;
}

bool DAppCmdLine::parse ( int argc, char** argv )
{
	int nb = 0;
	DString buffer, optname, optarg;
	bool value_on_next = false;
	int number_of_dash = 0;
	m_found = 0;

	m_appname = argv[0];
	m_appname = m_appname.section ( "/", -1,-1 );
	nb = 1;
	
	while ( nb < argc )
	{
		buffer = argv[ nb ];
		number_of_dash = buffer.contains ( "-" );

		// It's an option
		if ( number_of_dash || value_on_next )
		{
			if ( value_on_next )
			{
				optarg = buffer.remove ( "=" ).removeWhiteSpace();
				if ( optarg.left( 1 ) == "-" )
				{
					m_err = "No argument found for option " + optname;
					return false;
					
				}
				m_options[optname].value = optarg;
				m_options[optname].is_set = true;
				value_on_next = false;
			}
			else
			{
				optname = buffer.section ( "=", 0, 0 ).remove ( "-" );
				// it's an option alias name
				if ( number_of_dash == 1 )
				{
					optname = m_alias[ optname ];
					if ( !optname.length() )
					{
						m_err = "Unknow option found : " + buffer.section ( "=", 0, 0 );
						return false;
					}
				}

				
				if ( buffer.contains ( "=" ) )
				{
					optarg = buffer.section ( "=", 1, 1 ).removeWhiteSpace();
					m_options[optname].value = optarg;
					m_options[optname].is_set = true;
				}
				else
				{
					if ( m_options[optname].have_mandatory_value)
					{
						value_on_next = true;
					}
				}
			}
		}
		// It's a required argument
		else
		{
			if ( m_found <= m_autoID )
			{
				m_arguments[m_found].value = buffer;
				m_found++;
			}
		}

		nb++;
	}

	return true;
}

void DAppCmdLine::showHelp() const
{
	DString helpstr;
	DStringList::const_iterator it;
	//std::list<DString>::const_iterator it;

	std::cout << "Usage : " << m_appname;

	for ( it = m_help_arguments.begin() ; it != m_help_arguments.end() ; ++it )
	{
		std::cout << " <" << ( *it ) << ">";
	}

	std::cout << std::endl;

	for ( it = m_help_options.begin() ; it != m_help_options.end() ; ++it )
	{
		std::cout << ( *it );
		std::cout << std::endl;
	}
}

void DAppCmdLine::showVersion() const
{
	std::cout << m_appname << " Version : " << m_appversion << std::endl;
}

const DString & DAppCmdLine::getLastError() const
{
	return m_err;
}

/******************************************************************************
 *                               DAppOption                                   *
 ******************************************************************************/

DAppOption::DAppOption()
{
	alias = 0;
	have_mandatory_value = false;
}

DAppOption::DAppOption ( DString option_name,
                         DString option_description,
                         char option_alias,
                         bool argument_mandatory )
		: name ( option_name ),
		description ( option_description ),
		alias ( option_alias ),
		have_mandatory_value ( argument_mandatory ),
							   is_set(false)
{
}

DAppOption::~DAppOption()
{
}

void DAppOption::clear()
{
	name.clear();
	description.clear();
	value.clear();
	alias = 0;
}

std::ostream& operator<< ( std::ostream& s, const DAppOption & opt )
{
	s << "opt[" << opt.name << "(" << opt.alias << ")] = " << opt.value << "(" << opt.description << ")";
	return s;
}

/******************************************************************************
 *                                DAppArg                                     *
 ******************************************************************************/

DAppArg::DAppArg() : id ( -1 )
{
}

DAppArg::DAppArg ( unsigned int arg_id, DString arg_description )
		: id ( arg_id ), description ( arg_description )
{
}

DAppArg::~DAppArg()
{
}

void DAppArg::clear()
{
	description.clear();
	value.clear();
	id = 0;
}

std::ostream& operator<< ( std::ostream& s, const DAppArg & arg )
{
	s << "opt[" << arg.id << "] = " << arg.value << "(" << arg.description << ")";
	return s;
}


