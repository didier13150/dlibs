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

#include "dappcmdline.h"

DAppCmdLine::DAppCmdLine()
{
	m_autoID = 0;
	m_found = 0;
	m_appversion = "VERSION_NOT_SET";
}

DAppCmdLine::~DAppCmdLine()
{
}

void DAppCmdLine::addOption ( const DString & name,
                              const DString & description,
                              const char alias )
{
	DAppOption opt;
	opt.set( name, description, DString::empty(), alias );
	addOption( opt );
}

void DAppCmdLine::addOption ( const DString & name,
                              const DString & description,
                              const DString & example,
                              const char alias )
{
	DAppOption opt;
	opt.set( name, description, example, alias );
	addOption( opt );
}

void DAppCmdLine::addOption ( const DAppOption & opt )
{
	m_options[opt.getName()] = opt;

	// Save alias name
	if ( opt.getAlias() )
	{
		m_alias[opt.getAlias()] = opt.getName();
	}
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


const DString & DAppCmdLine::getOptionValue ( const DString & name ) const
{
	static DString empty;
	
	std::map<DString, DAppOption>::const_iterator ito;
	std::map<DString, DString>::const_iterator its;

	ito = m_options.find ( name );

	if ( ito != m_options.end() )
	{
		return ( ito->second.getValue() );
	}

	// search in alias
	its = m_alias.find( name );

	if ( its != m_alias.end() )
	{
		ito = m_options.find ( its->second );

		if ( ito != m_options.end() )
		{
			return ( ito->second.getValue() );
		}
	}
	
	return empty;
}

bool DAppCmdLine::haveOption ( const DString & name ) const
{
	std::map<DString, DAppOption>::const_iterator ito;
	std::map<DString, DString>::const_iterator its;
	bool haveLong = false;
	bool haveShort = false;
	
	ito = m_options.find( name );
	if ( ito != m_options.end() )
	{
		//if ( ito->second.isMandatory() )
		//	//TODO check if mandatory opt is set before report
		//	haveLong = ito->second.isSet();
		//else
			haveLong =  ito->second.isSet();
	}

	//search in alias
	its = m_alias.find( name );

	if ( its != m_alias.end() )
	{
		ito = m_options.find ( its->second );

		if ( ito != m_options.end() )
		{
			//if ( ito->second.isMandatory() )
			//	haveShort = ito->second.isSet();
			//else
				haveShort = ito->second.isSet();
		}
	}
	
	return ( haveLong || haveShort );
}

int DAppCmdLine::getNumberOfOptions() const
{
	return m_options.size();
}

unsigned int DAppCmdLine::addArgument ( const DString & description )
{
	DAppArg arg;
	arg.setDescription( description );
	return addArgument( arg );
}

unsigned int DAppCmdLine::addArgument ( const DAppArg & arg )
{
	unsigned int id = m_autoID;
	m_autoID++;
	m_arguments[id] = arg;
	return id;
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

const DString & DAppCmdLine::getArgumentValue ( unsigned int position ) const
{
	static DString empty;
	
	std::map<unsigned int, DAppArg>::const_iterator it;

	it = m_arguments.find ( position );

	if ( it != m_arguments.end() )
	{
		return ( ( *it ).second.getValue() );
	}

	return empty;
}

unsigned int DAppCmdLine::getNbExpectedArgs() const
{
	return m_arguments.size();
}

unsigned int DAppCmdLine::getNbFoundArgs() const
{
	return m_found;
}

bool DAppCmdLine::haveAllExpectedArgsFound() const
{
	if ( m_arguments.size() == m_found )
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
		number_of_dash = buffer.left(2).contains ( "-" );

		// It's an option
		if ( value_on_next )
		{
			optarg = buffer.remove ( "=" ).removeWhiteSpace();
			if ( optarg.left( 1 ) == "-" )
			{
				m_err = "No argument found for option " + optname;
				return false;
				
			}
			m_options[optname].setValue( optarg );
			m_options[optname].setState( true );
			value_on_next = false;
		}
		// It's an option
		else if ( number_of_dash )
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
				optarg = buffer.section ( "=", 1 ).removeWhiteSpace();
				m_options[optname].setValue( optarg );
				m_options[optname].setState( true );
			}
			else
			{
				if ( m_options[optname].isMandatory() )
				{
					value_on_next = true;
				}
				else {
					m_options[optname].setState( true );
				}
			}
		}
		// It's a required argument
		else
		{
			if ( m_found <= m_arguments.size() )
			{
				m_arguments[m_found].setValue( buffer );
				m_found++;
			}
		}

		nb++;
	}
	if ( value_on_next ) {
		m_err = "No argument found for option " + optname;
		return false;
	}
	return true;
}

void DAppCmdLine::showHelp() const
{
	DString helpstr;
	DString buffer;
	std::map<unsigned int, DAppArg>::const_iterator it;
	std::map<DString, DAppOption>::const_iterator it2;
	unsigned int summarySize;
	unsigned int  maxSummarySize = 0;
	
	std::cout << std::endl << m_appname;
	
	if ( getNumberOfOptions() ) std::cout << " [opts]";

	for ( it = m_arguments.begin() ; it != m_arguments.end() ; ++it )
	{
		std::cout << " [" << it->second.getDescription() << "]";
	}

	std::cout << std::endl << std::endl;
	
	// prepare help string: found max size of option summary
	for ( it2 = m_options.begin() ; it2 != m_options.end() ; ++it2 )
	{
		summarySize = 2;
		if ( it2->second.getAlias() ) summarySize += 4;
		summarySize += it2->second.getName().length();
		if ( ! it2->second.getExample().isEmpty() ) summarySize += it2->second.getExample().length() + 1;
		if ( summarySize > maxSummarySize ) maxSummarySize = summarySize;
	}
	for ( it2 = m_options.begin() ; it2 != m_options.end() ; ++it2 )
	{
		buffer.clear();
		if ( it2->second.getAlias() )
		{
			buffer = "-";
			buffer.append ( it2->second.getAlias() );
			buffer.append ( ", " );
		}
		buffer.append ( "--" );
		buffer.append ( it2->second.getName() );
		if ( ! it2->second.getExample().isEmpty() )
		{
			buffer.append ( "=" );
			buffer.append ( it2->second.getExample() );
		}
		helpstr = "  " + buffer;
		// Add 3 chars: 2 for beginning spaces and one between name and summary
		for ( unsigned int i = helpstr.length() ; i < ( maxSummarySize +3 ) ; ++i )
		{
			helpstr.append ( " " );
		}
		helpstr.append ( it2->second.getDescription() );
		std::cout << helpstr << std::endl;
	}

	std::cout << std::endl;
}

void DAppCmdLine::showVersion() const
{
	std::cout << m_appname << " Version : " << m_appversion << std::endl;
}

const DString & DAppCmdLine::getLastError() const
{
	return m_err;
}

std::ostream & operator<< ( std::ostream& s, const DAppCmdLine & app )
{
	std::map<unsigned int, DAppArg>::const_iterator it;
	std::map<DString, DAppOption>::const_iterator it2;
	std::map<DString, DString>::const_iterator it3;
	
	s << "DAppCmdLine" << std::endl;
	for ( it = app.m_arguments.begin() ; it != app.m_arguments.end() ; ++it )
	{
		s << "{" << it->first << "} " << it->second << std::endl;
	}
	for ( it2 = app.m_options.begin() ; it2 != app.m_options.end() ; ++it2 )
	{
		s << "{" << it2->first << "} " << it2->second << std::endl;
	}
	for ( it3 = app.m_alias.begin() ; it3 != app.m_alias.end() ; ++it3 )
	{
		s << "{" << it3->first << "} alias " << it3->second << std::endl;
	}
	
	return s;
}
/******************************************************************************
 *                               DAppOption                                   *
 ******************************************************************************/

DAppOption::DAppOption()
{
	_alias = 0;
	_have_mandatory_value = false;
	_is_set = false;
}

DAppOption::~DAppOption()
{
}

void DAppOption::setName( const DString & name )
{
	_name = name;
}

void DAppOption::setDescription( const DString & description )
{
	_description = description;
}

void DAppOption::setValue( const DString & value )
{
	_value = value;
}

void DAppOption::setExample( const DString & example )
{
	_example = example;
	if ( ! example.isEmpty() ) _have_mandatory_value = true;
}

void DAppOption::setAlias( char alias )
{
	_alias = alias;
}

const DString & DAppOption::getName() const
{
	return _name;
}

const DString & DAppOption::getDescription() const
{
	return _description;
}

const DString & DAppOption::getValue() const
{
	return _value;
}

const DString & DAppOption::getExample() const
{
	return _example;
}

char DAppOption::getAlias() const
{
	return _alias;
}

void DAppOption::set( const DString & name,
					  const DString & description,
					  const DString & example,
					  char alias )
{
	_name = name;
	_description = description;
	_value.clear();
	_example = example;
	_alias = alias;
	if ( ! example.isEmpty() ) _have_mandatory_value = true;
	else _have_mandatory_value = false;
}

void DAppOption::setState( bool state )
{
	_is_set = state;
}

bool DAppOption::isSet() const
{
	return _is_set;
}

void DAppOption::setMandatoryState( bool state )
{
	_have_mandatory_value = state;
}

bool DAppOption::isMandatory() const
{
	return _have_mandatory_value;
}

void DAppOption::clear()
{
	_name.clear();
	_description.clear();
	_value.clear();
	_example.clear();
	_alias = 0;
	_have_mandatory_value = false;
}

std::ostream& operator<< ( std::ostream & s, const DAppOption & opt )
{
	
	DString val = opt._value;
	DString alias;
	if ( val.isEmpty() ) {
		if( opt._have_mandatory_value ) {
			val = "NO-VALUE";
		}
	}
	if ( opt._alias ) alias = opt._alias;
	
	s << "opt[" << opt._name << "][" << alias << "] = \"" << val << "\""
	<< " [Example=" << opt._example << "]" << " [Is set=" << opt._is_set << "]"
	<< " [Must have value=" << opt._have_mandatory_value << "]"
	<< " (" << opt._description << ")";
	
	return s;
}

/******************************************************************************
 *                                DAppArg                                     *
 ******************************************************************************/

DAppArg::DAppArg()
{
}

DAppArg::~DAppArg()
{
}

void DAppArg::setDescription( const DString & description )
{
	_description = description;
}

void DAppArg::setValue( const DString & value )
{
	_value = value;
}

const DString & DAppArg::getDescription() const
{
	return _description;
}

const DString & DAppArg::getValue() const
{
	return _value;
}

void DAppArg::clear()
{
	_description.clear();
	_value.clear();
}

std::ostream& operator<< ( std::ostream & s, const DAppArg & arg )
{
	s << "arg[" << arg._description << "] = \"" << arg._value << "\"";
	return s;
}
