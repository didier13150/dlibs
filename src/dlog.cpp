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
 *     (___)_)   File : dlog.cpp                            ||--|| *          *
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

#include <stdio.h>
#include <syslog.h>
#include "dlog.h"
#include "dlibs.h"

#define DATE_FORMAT "%Y-%m-%d %H:%M:%S"
#define MESSAGE_PATTERN "%DATE %TYPE %MESSAGE"

using namespace std;

/******************************************************************************
 *                              DLogParams                                    *
 ******************************************************************************/
DLogParams::DLogParams()
{
	clear();
	optionnal["dateformat"] = DATE_FORMAT;
	optionnal["pattern"] = MESSAGE_PATTERN;
}

DLogParams::~DLogParams()
{
}

void DLogParams::clear()
{
	optionnal.clear();
	specific.clear();
	minlevel = DLogShared::INFO;
	mode = DLogShared::OPENCLOSE;
}

std::ostream& operator << ( std::ostream& s, const DLogParams & params )
{
	std::map<DString, DString>::const_iterator it;

	s << "DLogParams :" << std::endl;
	for ( it = params.optionnal.begin() ; it != params.optionnal.end() ; ++it )
	{
		s << "\toptionnal[" << it->first << "] = " << it->second << std::endl;
	}
	for ( it = params.specific.begin() ; it != params.specific.end() ; ++it )
	{
		s << "\tspecific[" << it->first << "] = " << it->second << std::endl;
	}
	s << "\tMinimum log level = " << DLogParams::toString ( params.minlevel ) << std::endl;
	s << "\tMode = " << DLogParams::toString ( params.mode ) << std::endl;
	return s;
}

const DString & DLogParams::toString ( const DLogShared::Level & level )
{
	static DString strlevel;

	switch ( level )
	{
		case DLogShared::NONE:
		{
			strlevel = "NONE";
			break;
		}
		case DLogShared::DEBUG:
		{
			strlevel = "DEBUG";
			break;
		}
		case DLogShared::VERBOSE:
		{
			strlevel = "VERBOSE";
			break;
		}
		case DLogShared::INFO:
		{
			strlevel = "INFO";
			break;
		}
		case DLogShared::SIGNALS:
		{
			strlevel = "SIGNALS";
			break;
		}
		case DLogShared::WARNING:
		{
			strlevel = "WARNING";
			break;
		}
		case DLogShared::ERROR:
		{
			strlevel = "ERROR";
			break;
		}
		case DLogShared::CRITICAL:
		{
			strlevel = "CRITICAL";
			break;
		}
	}
	return strlevel;
}

const DString & DLogParams::toString ( const DLogShared::Mode & mode )
{
	static DString strmode;

	switch ( mode )
	{
		case DLogShared::PERSISTANT:
		{
			strmode = "PERSISTANT";
			break;
		}
		case DLogShared::OPENCLOSE:
		{
			strmode = "OPENCLOSE";
			break;
		}
	}
	return strmode;
}

/******************************************************************************
 *                                DLogger                                     *
 ******************************************************************************/
std::map<DString, DString> DLogger::m_userVar = std::map<DString, DString>();

DLogger::DLogger()
		: m_initialized ( false ), m_have_stdout ( false )
{
	m_have_stdout = false;

	// Register available types
	DFactory<DLogEngine>::Register ( FILE, new DLogEngineFile() );
	DFactory<DLogEngine>::Register ( STDOUT, new DLogEngineStdout() );
	DFactory<DLogEngine>::Register ( SOCKET, new DLogEngineSocket() );
	DFactory<DLogEngine>::Register ( SYSLOG, new DLogEngineSyslog() );
	DFactory<DLogEngine>::Register ( DATABASE, new DLogEngineDatabase() );
}

DLogger::~DLogger()
{
	close();
}

DLogEngine * DLogger::addLogEngine ( Type type, DLogParams & params )
{
	// Only one stdout can be exists
	if ( type == STDOUT )
	{
		if ( m_have_stdout )
		{
			return 0;
		}
		else
		{
			m_have_stdout = true;
		}
	}

	DLogEngine * log = m_factory.create ( type );
	log->setParam ( params );
	m_logs.push_back ( log );
	return log;
}

void DLogger::addLogEngine ( DLogEngine * engine )
{
	m_logs.push_back ( engine );
}


void DLogger::removeLogEngine ( DLogEngine * engine )
{
	DLogCollection::iterator it;
	DLogCollection::const_iterator itend = m_logs.end();

	for ( it = m_logs.begin() ; it != itend ; ++it )
	{
		if ( *it == engine )
		{
			m_logs.erase ( it );
			delete ( engine );
			// not necessary to continue
			break;
		}
	}
}

void DLogger::insertMessage ( const DString & message, Level loglevel )
{
	DLogCollection::iterator it;
	for ( it = m_logs.begin() ; it != m_logs.end() ; ++it )
	{
		if ( ( *it )->isValid() )
		{
			( *it )->insert ( message, loglevel );
		}
	}
}

void DLogger::close()
{
	DLogCollection::iterator it;
	while ( !m_logs.empty() )
	{
		it = m_logs.begin();
		delete ( *it );
		m_logs.pop_front();
	}
}

bool DLogger::addUserVar( const DString & varname )
{
	return ( addAndSetupUserVar( varname, DString() ) );
}

bool DLogger::addAndSetupUserVar( const DString & varname, const DString & value )
{
	std::map<DString, DString>::const_iterator it;
	
	it = m_userVar.find( varname );
	if ( it == m_userVar.end() )
	{
		m_userVar[ varname ] = value;
		return true;
	}
	return false;
}

void DLogger::removeUserVar( const DString & varname )
{
	std::map<DString, DString>::iterator it;
	
	it = m_userVar.find( varname );
	if ( it != m_userVar.end() )
	{
		m_userVar.erase( varname );
	}
}

void DLogger::setupUserVar( const DString & varname, const DString & value )
{
	std::map<DString, DString>::const_iterator it;
	
	it = m_userVar.find( varname );
	if ( it != m_userVar.end() )
	{
		m_userVar[ varname ] = value;
	}
}

const DString & DLogger::prepare ( const DString & message,
                                   const DString & dateformat,
                                   const DString & pattern,
                                   Level loglevel )
{
	static DString buffer;
	DString date, type;
	std::map<DString, DString>::iterator it;

	// Get current time
	date = DString::timeToString ( time ( NULL ), dateformat.c_str() );

	switch ( loglevel )
	{

		case DLogShared::NONE:
		{
			return message;
		}

		case DLogShared::DEBUG:
		{
			type = "DEBUG";
			break;
		}

		case DLogShared::VERBOSE:
		{
			type = "INFOS";
			break;
		}

		case DLogShared::INFO:
		{
			type = "INFOS";
			break;
		}

		case DLogShared::SIGNALS:
		{
			type = "SIGNL";
			break;
		}

		case DLogShared::WARNING:
		{
			type = "WARNG";
			break;
		}

		case DLogShared::ERROR:
		{
			type = "ERROR";
			break;
		}

		case DLogShared::CRITICAL:
		{
			type = "CRITL";
			break;
		}

		default:
		{
			type.clear();
		}
	}

	if ( !type.isEmpty() )
	{
		buffer = pattern;
		buffer.replace ( "%DATE", date );
		buffer.replace ( "%TYPE", type );
		buffer.replace ( "%MESSAGE", message );
		
		for ( it = m_userVar.begin() ; it != m_userVar .end() ; ++it )
		{
			buffer.replace( it->first, it->second );
		}
	}

	return ( buffer );
}

/******************************    DLogEngine    ******************************/
//empty constructor
DLogEngine::DLogEngine()
{
	m_dateFormat = DATE_FORMAT;
	m_minLevel = DLogShared::INFO;
	m_mode = DLogShared::PERSISTANT;
	m_pattern = MESSAGE_PATTERN;
	m_valid = false;
}

DLogEngine::~DLogEngine()
{
}

void DLogEngine::setDateFormat ( const DString & format )
{
	m_dateFormat = format;
}

const DString & DLogEngine::getDateFormat() const
{
	return m_dateFormat;
}

void DLogEngine::setMinLogLevel ( const DLogShared::Level & level )
{
	m_minLevel = level;
}

const DLogEngine::Level & DLogEngine::getMinLogLevel ( void ) const
{
	return m_minLevel;
}

void DLogEngine::setMode ( const DLogShared::Mode & mode )
{
	m_mode = mode;
}

const DLogEngine::Mode & DLogEngine::getMode ( void ) const
{
	return m_mode;
}

const DLogEngine::Type & DLogEngine::getType ( void ) const
{
	return m_type;
}

void DLogEngine::setLogPattern ( const DString & pattern )
{
	m_pattern = pattern;
}

const DString & DLogEngine::getLogPattern() const
{
	return m_pattern;
}

void DLogEngine::setParam ( DLogParams & params )
{
	if ( !params.optionnal["dateformat"].isEmpty() )
	{
		setDateFormat ( params.optionnal["dateformat"] );
	}
	if ( !params.optionnal["pattern"].isEmpty() )
	{
		setLogPattern ( params.optionnal["pattern"] );
	}
	setMode ( params.mode );
	setMinLogLevel ( params.minlevel );
}

bool DLogEngine::isValid()
{
	return m_valid;
}

/******************************************************************************
 *                            DLogEngineFile                                  *
 ******************************************************************************/
DLogEngineFile::DLogEngineFile ( void )
		: DLogEngine(), m_file ( 0 )
{
	m_type = FILE;
}

DLogEngineFile::DLogEngineFile ( const DString & fileName, Mode mode )
{
	m_type = FILE;
	setFileName ( fileName, mode );
}

DLogEngineFile::~DLogEngineFile ( void )
{
	close();
}

void DLogEngineFile::setParam ( DLogParams & params )
{
	setFileName ( params.specific["filename"], params.mode );
	DLogEngine::setParam ( params );
}

void DLogEngineFile::setFileName ( const DString & fileName, Mode mode )
{
	DString buffer;

	m_mode = mode;

	if ( ( fileName == m_fileName ) && ( !m_fileName.isEmpty() ) )
	{
		return;
	}

	m_fileName = fileName;

	for ( int i = 0 ; i < 80 ; i++ )
	{
		buffer += "-";
	}

	buffer += "\n";

	if ( m_mode == DLogShared::PERSISTANT )
	{
		open();
	}
	insert ( buffer, DLogShared::NONE );
}

DString DLogEngineFile::getFileName() const
{
	return m_fileName;
}

bool DLogEngineFile::open()
{
	if ( m_file )
	{
		close();
	}
	m_file = new std::ofstream();
	m_file->open ( m_fileName.c_str(), std::ios::out | std::ios::app | std::ios::ate );

	if ( m_file->fail() )
	{
		m_valid = false;
		return false;
	}
	
	m_valid = true;
	return true;
}

void DLogEngineFile::close()
{
	if ( m_file )
	{
		m_file->close();
		delete m_file;
		m_file = 0;
	}
	if ( m_mode == DLogShared::PERSISTANT )
	{
		m_valid = false;
	}
}

void DLogEngineFile::insert ( const DString & text, Level loglevel )
{
	//ofstream file;
	DString message;

	// write message only if loglevel is highter or equal to minimum log level
	// or not equal to NONE
	if ( ( loglevel < m_minLevel ) && ( loglevel != DLogShared::NONE ) )
	{
		return;
	}
	
	if ( m_mode == DLogShared::OPENCLOSE )
	{
		open();
	}
	
	if ( loglevel == DLogShared::NONE )
	{
		message = text;
	}
	else
	{
		message = DLogger::prepare ( text, m_dateFormat, m_pattern, loglevel );
	}
	
	*m_file << message << endl;
	
	if ( m_mode == DLogShared::OPENCLOSE )
	{
		close();
	}
}

/******************************************************************************
 *                           DLogEngineStdout                                 *
 ******************************************************************************/
DLogEngineStdout::DLogEngineStdout ( void )
		: DLogEngine()
{
	m_type = STDOUT;
	m_valid = true;
}

DLogEngineStdout::~DLogEngineStdout ( void )
{
	close();
}

bool DLogEngineStdout::open()
{
	return true;
}

void DLogEngineStdout::close()
{
}

void DLogEngineStdout::insert ( const DString & text, Level loglevel )
{
	// write message only if loglevel is highter or equal to minimum log level
	// or not equal to NONE
	if ( ( loglevel < m_minLevel ) && ( loglevel != DLogShared::NONE ) )
	{
		return;
	}
	std::cout << text << std::endl;
}

void DLogEngineStdout::setParam ( DLogParams & params )
{
	DLogEngine::setParam ( params );
}

/******************************************************************************
 *                           DLogEngineSyslog                                 *
 ******************************************************************************/
DLogEngineSyslog::DLogEngineSyslog ( void )
		: DLogEngine()
{
	m_type = SYSLOG;
	m_app_name = "dlibs";
	m_valid = true;
}

DLogEngineSyslog::DLogEngineSyslog ( const DString & app_name )
	: DLogEngine()
{
	m_type = SYSLOG;
	m_app_name = app_name;
}

DLogEngineSyslog::~DLogEngineSyslog ( void )
{
	close();
}

void DLogEngineSyslog::setAppName( const DString & app_name )
{
	m_app_name = app_name;
	if ( m_mode == DLogShared::PERSISTANT )
	{
		open();
	}
}

bool DLogEngineSyslog::open()
{
	openlog ( m_app_name.c_str(), LOG_PID|LOG_CONS, LOG_USER );
	return true;
}

void DLogEngineSyslog::close()
{
	closelog();
}

void DLogEngineSyslog::insert ( const DString & text, Level loglevel )
{
	int sysloglevel = LOG_DEBUG;
	DString message;
	
	// write message only if loglevel is highter or equal to minimum log level
	// or not equal to NONE
	if ( ( loglevel < m_minLevel ) && ( loglevel != DLogShared::NONE ) )
	{
		return;
	}

	if ( m_mode == DLogShared::OPENCLOSE )
	{
		open();
	}
	switch ( loglevel )
	{

		case DLogShared::NONE:
		{
			return;
		}

		case DLogShared::DEBUG:
		{
			sysloglevel = LOG_DEBUG;
			break;
		}

		case DLogShared::VERBOSE:
		{
			sysloglevel = LOG_NOTICE;
			break;
		}

		case DLogShared::INFO:
		{
			sysloglevel = LOG_INFO;
			break;
		}

		case DLogShared::SIGNALS:
		{
			sysloglevel = LOG_INFO;
			break;
		}

		case DLogShared::WARNING:
		{
			sysloglevel = LOG_WARNING;
			break;
		}

		case DLogShared::ERROR:
		{
			sysloglevel = LOG_ERR;
			break;
		}

		case DLogShared::CRITICAL:
		{
			sysloglevel = LOG_CRIT;
			break;
		}
	}
	message = "[";
	message.append( DLogParams::toString( loglevel ) );
	message.append( "] " );
	message.append( text );
	syslog ( sysloglevel, message.c_str() );
	if ( m_mode == DLogShared::OPENCLOSE )
	{
		close();
	}
}

void DLogEngineSyslog::setParam ( DLogParams & params )
{
	DLogEngine::setParam ( params );
	setAppName ( params.specific["appname"] );
}

/******************************************************************************
 *                          DLogEngineDatabase                                *
 ******************************************************************************/
DLogEngineDatabase::DLogEngineDatabase ( void )
		: DLogEngine()
{
	m_type = DATABASE;
	m_pattern = "\"%DATE\", \"%TYPE\", \"%MESSAGE\"";
	m_dateFormat = DString::getFormat( DString::ISO_DATETIME_T );
#ifdef DLIBS_HAVE_MYSQL
#if WITH_EXCEPTIONS
	DFactory<DDatabase>::Register ( "dmysql", new DMySQL( true ) );
#else
	DFactory<DDatabase>::Register ( "dmysql", new DMySQL() );
#endif
#endif
#ifdef DLIBS_HAVE_PGSQL
#if WITH_EXCEPTIONS
	DFactory<DDatabase>::Register ( "dpgsql", new DPgSQL( true ) );
#else
	DFactory<DDatabase>::Register ( "dpgsql", new DPgSQL() );
#endif
#endif
#if WITH_EXCEPTIONS
	DFactory<DDatabase>::Register ( "dsqlite", new DSQLite( true ) );
#else
	DFactory<DDatabase>::Register ( "dsqlite", new DSQLite() );
#endif
	m_database = 0;
	m_valid = true;
}

DLogEngineDatabase::~DLogEngineDatabase ( void )
{
	close();
}

bool DLogEngineDatabase::open()
{
	try
	{
		m_database->open();
		if ( !m_create_query.isEmpty() )
		{
			m_database->exec( m_create_query );
			m_create_query.clear();
		}
		m_valid = true;
	}
	catch ( ... )
	{
		m_valid = false;
	}
	return true;
}

void DLogEngineDatabase::close()
{
	try
	{
		m_database->close();
	}
	catch ( ... )
	{
	}
}

void DLogEngineDatabase::insert ( const DString & text, Level loglevel )
{
	// write message only if loglevel is highter or equal to minimum log level
	// or not equal to NONE
	if ( ( loglevel < m_minLevel ) && ( loglevel != DLogShared::NONE ) )
	{
		return;
	}
	
	try
	{
		if ( m_mode == DLogShared::OPENCLOSE )
		{
			open();
		}
		m_database->exec( DLogger::prepare ( text, m_dateFormat, m_pattern, loglevel ) );
		if ( m_mode == DLogShared::OPENCLOSE )
		{
			close();
		}
	}
	catch ( ... )
	{
		std::cout << DLogger::prepare ( text, m_dateFormat, m_pattern, loglevel ) << std::endl;
	}
}

void DLogEngineDatabase::setParam ( DLogParams & params )
{
	DLogEngine::setParam ( params );
	
	if ( !params.specific["dbtype"].isEmpty() )
	{
		m_database = m_factory.create ( params.specific["dbtype"] );
	}
	else
	{
		m_database = m_factory.create ( "dsqlite" );
	}
	
	if ( !params.specific["dbbase"].isEmpty() )
	{
		m_dbparams.base = params.specific["dbbase"];
	}
	else
	{
		m_dbparams.base = "/tmp/dlibs.db";
	}
	if ( !params.specific["dbhost"].isEmpty() )
	{
		m_dbparams.host = params.specific["dbhost"];
	}
	if ( !params.specific["dbuser"].isEmpty() )
	{
		m_dbparams.user = params.specific["dbuser"];
	}
	if ( !params.specific["dbpassword"].isEmpty() )
	{
		m_dbparams.password = params.specific["dbpassword"];
	}
	if ( !params.specific["dbport"].isEmpty() )
	{
		m_dbparams.port = params.specific["dbport"];
	}
	m_database->setParams ( m_dbparams );
	
	if ( !params.specific["dbcreate"].isEmpty() )
	{
		m_create_query = params.specific["dbcreate"];
	}
	
	if ( m_mode == DLogShared::PERSISTANT )
	{
		open();
	}
}

/******************************************************************************
 *                           DLogEngineSocket                                 *
 ******************************************************************************/
DLogEngineSocket::DLogEngineSocket ( void )
		: DLogEngine()
{
	m_type = SOCKET;
	m_bufsize = 0;
	m_valid = true;
}

DLogEngineSocket::~DLogEngineSocket ( void )
{
	close();
}

void DLogEngineSocket::setSocket ( const DURL & host )
{
	m_host = host;
	
	if ( m_mode == DLogShared::PERSISTANT )
	{
		open();
	}
}

bool DLogEngineSocket::open()
{
	if ( m_client.openSock ( m_host ) != DSock::SUCCESS )
	{
		std::cout << m_host << std::endl;
		m_valid = false;
		return false;
	}
	//TODO
	std::cout << m_host << std::endl;

	m_client.setTimeout ( 2000 );
	if ( m_bufsize )
	{
		m_client.setBufferSize( m_bufsize );
	}

	m_valid = true;
	return true;
}

void DLogEngineSocket::close()
{
	m_client.closeSock();
}

void DLogEngineSocket::insert ( const DString & text, Level loglevel )
{
	// write message only if loglevel is highter or equal to minimum log level
	// or not equal to NONE
	if ( ( loglevel < m_minLevel ) && ( loglevel != DLogShared::NONE ) )
	{
		return;
	}
	if ( m_mode == DLogShared::OPENCLOSE )
	{
		open();
	}
	m_client.writeMessage ( text );
	if ( m_mode == DLogShared::OPENCLOSE )
	{
		close();
	}
}

void DLogEngineSocket::setParam ( DLogParams & params )
{
	DURL url;
	std::map<DString, DString>::const_iterator it;

	DLogEngine::setParam ( params );
	it = params.specific.find ( "sockhost" );
	if ( it != params.specific.end() )
	{
		url.setURL ( params.specific["sockhost"] );
	}

	it = params.specific.find ( "sockbufsize" );
	if ( it != params.specific.end() )
	{
		m_bufsize = params.specific["sockbufsize"].toULong();
	}

	setSocket ( url );
}



