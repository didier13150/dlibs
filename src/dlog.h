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
 *     (___)_)   File : dlog.h                              ||--|| *          *
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

#ifndef _DLOG_H_
#define _DLOG_H_

#include <stdio.h>
#include <string>
#include <list>
#include <map>
#include <fstream>
#include "dstring.h"
#include "dsocket.h"
#include "dskeleton.h"
#include "dprototype.h"
#include "dsingleton.h"
#include "dfactory.h"
#include "ddatabase.h"

class DLogEngine;

class DLogEngineFile;

class DLogEngineStdout;

class DLogEngineSocket;

class DLogEngineSyslog;

class DLogEngineDatabase;

typedef std::list<DLogEngine*, std::allocator<DLogEngine*> > DLogCollection;


/**
 * Shared objects for all log engine, abstract engine and the log factory.
 * @short Log shared definition
 * @author Didier Fabert <didier.fabert@gmail.com>
 */
class DLogShared
{
public:
    /**
     * @typedef Level
     * Defining the log level for message
     */
    typedef enum level
    {
        /// No Level
        NONE = 0x00,
        /// Debug
        DEBUG = 0x01,
        /// Verbose
        VERBOSE = 0x02,
        /// Information
        INFO = 0x03,
        /// Receive signal
        SIGNALS = 0x04,
        /// Warning
        WARNING = 0x05,
        /// Error
        ERROR = 0x06,
        /// Critical Error
        CRITICAL = 0x07,
    } Level;

    /**
     * @typedef Mode
     * Defining the connection mode
     */
    typedef enum mode
    {
        /// Persistant connection
        PERSISTANT,
        /// Connection need to be opened at the beginning and closed at the end
        OPENCLOSE,
    } Mode;

    /**
     * @typedef Type
     * Defining the log engine type
     */
    typedef enum engine_type
    {
        /// stdout log engine
        STDOUT,
        /// file log engine
        FILE,
        /// socket log engine
        SOCKET,
        /// syslog log engine
        SYSLOG,
        /// database log engine
        DATABASE,
    } Type;
};

/**
 * @brief Params for define a log engine
 * @author Didier Fabert <didier.fabert@gmail.com>
 * Description of the logger. It contains required, optionnal and specific
 * options.
 */

class DLogParams : public DLogShared
{
public:
    /**
     * Constructor
     */
    DLogParams();

    /**
     * Destructor
     */
    ~DLogParams();

    /**
     * Clear the parameters
     */
    void clear();

    /**
     * Writes DLogParams to the stream s and returns a reference to the stream.
     */
    friend std::ostream& operator << ( std::ostream& s, const DLogParams & params );

    /**
     * convert Level enum value to a representing string
     */
    static const DString & toString ( const DLogShared::Level & level );

    /**
     * convert Mode enum value to a representing string
     */
    static const DString & toString ( const DLogShared::Mode & mode );

    /// Optionnal options for the logger.
    std::map<DString, DString> optionnal;

    /// Specific options for the logger.
    std::map<DString, DString> specific;

    /// The minimum log level for the logger.
    Level minlevel;

    /// The mode for the logger.
    Mode mode;
};

/**
 * @short Abstract log engine
 * @author Didier Fabert <didier.fabert@gmail.com>
 * Abstract class for all DLog type
 */

class DLogEngine : public DLogShared, public DSkeleton, public DPrototype<DLogEngine>
{

public:

    /**
     * Constructor
     */
    DLogEngine();

    /**
     * Virtual destructor
     */
    virtual ~DLogEngine();

    /**
     * Set the minimum log level
     * @see #Level
     */
    virtual void setMinLogLevel ( const DLogShared::Level & level );

    /**
     * Get the minimum log level
     * @see #Level
     */
    virtual const Level & getMinLogLevel ( void ) const;

    /**
     * Set the mode
     * @see #Mode
     */
    virtual void setMode ( const DLogShared::Mode & mode );

    /**
     * Get the current mode
     * @see #Mode
     */
    virtual const Mode & getMode ( void ) const;

    /**
     * Get the current type
     */
    virtual const Type & getType ( void ) const;

    /**
     * Set the date format
     * @see #DLogger
     */
    virtual void setDateFormat ( const DString & format );

    /**
     * Get the date format
     * @see #DLogger
     */
    virtual const DString & getDateFormat ( void ) const;

    /**
     * Set the log message pattern. The current implementation
     * give only three variables :
     * - \%DATE for date ( @see date format )
     * - \%TYPE for type ( @see type )
     * - \%MESSAGE for log message
     */
    virtual void setLogPattern ( const DString & pattern );

    /**
     * Get the log message pattern
     */
    virtual const DString & getLogPattern ( void ) const;

    /**
     * Set Log engine parameters
     */
    virtual void setParam ( DLogParams & params );

    /**
     * return TRUE if engine is valid ( correctly initialized ) and ready
     * to receive messages, FALSE otherwise.
     */
    virtual bool isValid();

    /**
     * Open the log
     */
    virtual bool open() = 0;

    /**
     * Close the log
     */
    virtual void close() = 0;

    /**
     * Insert log
     */
    virtual void insert ( const DString & text, Level loglevel = DLogShared::INFO ) = 0;

protected:
    /// The date format
    DString m_dateFormat;

    /// The minimum log level
    Level m_minLevel;

    /// The write mode
    Mode m_mode;

    /// Type of log
    Type m_type;

    /// valid flag.\n TRUE if log is initialized and valid, FALSE otherwise.
    bool m_valid;

    /// The message pattern
    DString m_pattern;
};


/**
 * @short File log engine
 * @author Didier Fabert <didier.fabert@gmail.com>
 * Log engine which write log message in a plain text file
 */
class DLogEngineFile : public DLogEngine
{

public:
    /**
     * Empty Constructor
     */
    DLogEngineFile ( void );
    /**
     * Constructor all in one.\n
     * Usefull for the DLog factory
     */
    DLogEngineFile ( const DString & fileName, Mode mode = OPENCLOSE );

    /**
     * Default destructor
     */
    ~DLogEngineFile ( void );

    /**
     * Set the log file name
     */
    void setFileName ( const DString & fileName, Mode mode = OPENCLOSE );

    /**
     * Get the log file name
     */
    DString getFileName ( void ) const;

    /**
     * Open the log file
     */
    bool open();
    /**
     * Close the log file
     */
    void close();
    /**
     * Insert log ( write into file )
     */
    void insert ( const DString & text, Level loglevel = DLogShared::INFO );

    /**
     * Set Log engine parameters
     */
    void setParam ( DLogParams & params );

    /**
     * Clone method for factory
     * @internal
     */
    DLogEngine * Clone() const
    {
        return new DLogEngineFile ( *this );
    }

private :
    /// The file name
    DString m_fileName;
    /// The file stream
    std::ofstream * m_file;
};

/**
 * @short Stdout log engine
 * @author Didier Fabert <didier.fabert@gmail.com>
 * Log engine which write log message in stdout
 */
class DLogEngineStdout : public DLogEngine
{
public:

    /**
     * Empty Constructor
     */
    DLogEngineStdout ( void );

    /**
     * Default destructor
     */
    ~DLogEngineStdout ( void );

    /**
     * Clone method for factory
     * @internal
     */
    DLogEngine * Clone() const
    {
        return new DLogEngineStdout ( *this );
    }
    /**
     * Open the log file
     */
    bool open();
    /**
     * Close the log file
     */
    void close();
    /**
     * Insert log ( write into file )
     */
    void insert ( const DString & text, Level loglevel = DLogShared::INFO );

    /**
     * Set Log engine parameters
     */
    void setParam ( DLogParams & params );
};

/**
 * @short Syslog log engine
 * @author Didier Fabert <didier.fabert@gmail.com>
 * Log engine which send log message to syslog daemon
 */
class DLogEngineSyslog : public DLogEngine
{

public:
    /**
     * Empty Constructor
     */
    DLogEngineSyslog ( void );

    /**
     * Default Constructor
     */
    DLogEngineSyslog ( const DString & app_name );

    /**
     * Default destructor
     */
    ~DLogEngineSyslog ( void );

    /**
     * Set the application name
     */
    void setAppName( const DString & app_name );

    /**
     * Open the log file
     */
    bool open();
    /**
     * Close the log file
     */
    void close();
    /**
     * Insert log ( write into file )
     */
    void insert ( const DString & text, Level loglevel = DLogShared::INFO );

    /**
     * Set Log engine parameters
     */
    void setParam ( DLogParams & params );

    /**
     * Clone method for factory
     * @internal
     */
    DLogEngine * Clone() const
    {
        return new DLogEngineSyslog ( *this );
    }

private:
    DString m_app_name;
};

/**
 * @short Database log engine
 * @author Didier Fabert <didier.fabert@gmail.com>
 * Log engine which write log message in database :
 * message pattern must be a valid SQL query.
 */
class DLogEngineDatabase : public DLogEngine
{

public:
    /**
     * Empty Constructor.
     */
    DLogEngineDatabase ( void );

    /**
     * Default destructor
     */
    ~DLogEngineDatabase ( void );

    /**
     * Open the log file
     */
    bool open();
    /**
     * Close the log file
     */
    void close();
    /**
     * Insert log ( write into file )
     */
    void insert ( const DString & text, Level loglevel = DLogShared::INFO );

    /**
     * Set Log engine parameters
     */
    void setParam ( DLogParams & params );

    /**
     * Clone method for factory
     * @internal
     */
    DLogEngine * Clone() const
    {
        return new DLogEngineDatabase ( *this );
    }

private:
    DString m_dbtype;
    DString m_create_query;
    DDatabaseParams m_dbparams;
    DDatabase * m_database;
    DFactory<DDatabase> m_factory;
};

/**
 * @short Socket log engine
 * @author Didier Fabert <didier.fabert@gmail.com>
 * Log engine which send log message by a socket.
 */
class DLogEngineSocket : public DLogEngine
{

public:

    /**
     * Empty Constructor
     */
    DLogEngineSocket ( void );

    /**
     * All in one Constructor
     */
    DLogEngineSocket ( const DURL & host, int port );

    /**
     * Default destructor
     */
    ~DLogEngineSocket ( void );

    void setSocket ( const DURL & host );

    /**
     * Open the log file
     */
    bool open();
    /**
     * Close the log file
     */
    void close();
    /**
     * Insert log ( send it through the socket )
     */
    void insert ( const DString & text, Level loglevel = DLogShared::INFO );

    /**
     * Set Log engine parameters
     */
    void setParam ( DLogParams & params );

    /**
     * Clone method for factory
     * @internal
     */
    DLogEngine * Clone() const
    {
        return new DLogEngineSocket ( *this );
    }

private:
    /// Socket handle
    DClientSock m_client;
    /// The log server host
    DURL m_host;
    /// The log server port
    int m_port;
    /// The socket buffer size
    size_t m_bufsize;
};

/**
 * @brief Logger built-in factory.
 * @author Didier Fabert <didier.fabert@gmail.com>
 * @section Date
 * Ordinary characters placed in the format string are copied to log without
 * conversion. Conversion specifications are introduced by a '%' character, and
 * terminated by a conversion specifier character, and are replaced in log as
 * follows:
 * - \%a The abbreviated weekday name according to the current locale.
 * - \%A The full weekday name according to the current locale.
 * - \%b The abbreviated month name according to the current locale.
 * - \%B The full month name according to the current locale.
 * - \%c The preferred date and time representation for the current locale.
 * - \%C The century number (year/100) as a 2-digit integer. (SU)
 * - \%d The day of the month as a decimal number (range 01 to 31).
 * - \%D Equivalent to %m/%d/%y. (Yecch -- for Americans only. Americans should
 * note that in other countries %d/%m/%y is rather common. This means that in
 * international context this format is ambiguous and should not be used.) (SU)
 * - \%e Like %d, the day of the month as a decimal number, but a leading zero
 * is replaced by a space. (SU)
 * - \%E Modifier: use alternative format, see below. (SU)
 * - \%F Equivalent to %Y-%m-%d (the ISO 8601 date format). (C99)
 * - \%G The ISO 8601 year with century as a decimal number. The 4-digit year
 * corresponding to the ISO week number (see %V). This has the same format and
 * value as %y, except that if the ISO week number belongs to the previous or
 * next year, that year is used instead. (TZ)
 * - \%g Like %G, but without century, i.e., with a 2-digit year (00-99). (TZ)
 * - \%h Equivalent to %b. (SU)
 * - \%H The hour as a decimal number using a 24-hour clock (range 00 to 23).
 * - \%I The hour as a decimal number using a 12-hour clock (range 01 to 12).
 * - \%j The day of the year as a decimal number (range 001 to 366).
 * - \%k The hour (24-hour clock) as a decimal number (range 0 to 23); single
 * digits are preceded by a blank. (See also %H.) (TZ)
 * - \%l The hour (12-hour clock) as a decimal number (range 1 to 12); single
 * digits are preceded by a blank. (See also %I.) (TZ)
 * - \%m The month as a decimal number (range 01 to 12).
 * - \%M The minute as a decimal number (range 00 to 59).
 * - \%n A newline character. (SU)
 * - \%O Modifier: use alternative format, see below. (SU)
 * - \%p Either 'AM' or 'PM' according to the given time value, or the
 * corresponding strings for the current locale. Noon is treated as 'pm' and
 * midnight as 'am'.
 * - \%P Like %p but in lowercase: 'am' or 'pm' or a corresponding string for
 * the current locale. (GNU)
 * - \%r The time in a.m. or p.m. notation. In the POSIX locale this is
 * equivalent to '%I:%M:%S %p'. (SU)
 * - \%R The time in 24-hour notation (%H:%M). (SU) For a version including the
 * seconds, see %T below.
 * - \%s The number of seconds since the Epoch, i.e., since 1970-01-01 00:00:00
 * UTC. (TZ)
 * - \%S The second as a decimal number (range 00 to 60). (The range is up to 60
 * to allow for occasional leap seconds.)
 * - \%t A tab character. (SU)
 * - \%T The time in 24-hour notation (%H:%M:%S). (SU)
 * - \%u The day of the week as a decimal, range 1 to 7, Monday being 1.
 * See also %w. (SU)
 * - \%U The week number of the current year as a decimal number,
 * range 00 to 53, starting with the first Sunday as the first day of week 01.
 * See also %V and %W.
 * - \%V The ISO 8601:1988 week number of the current year as a decimal number,
 * range 01 to 53, where week 1 is the first week that has at least 4 days
 * in the current year, and with Monday as the first day of the week.
 * See also %U and %W. (SU)
 * - \%w The day of the week as a decimal, range 0 to 6, Sunday being 0.
 * See also %u.
 * - \%W The week number of the current year as a decimal number,
 * range 00 to 53,
 * starting with the first Monday as the first day of week 01.
 * - \%x The preferred date representation for the current locale without
 * the time.
 * - \%X The preferred time representation for the current locale without the
 * date.
 * - \%y The year as a decimal number without a century (range 00 to 99).
 * - \%Y The year as a decimal number including the century.
 * - \%z The time-zone as hour offset from GMT. Required to emit RFC
 * 822-conformant dates (using "%a, %d %b %Y %H:%M:%S %z"). (GNU)
 * - \%Z The time zone or name or abbreviation.
 * - \%+ The date and time in date(1) format. (TZ) (Not supported in glibc2.)
 * - \%% A literal '%' character.
 * @section Message
 * The message is written as defined in the pattern var.
 *
 * @include testdlog.cpp
 */

class DLogger : public DLogShared, public DSingleton<DLogger>
{
    friend class DSingleton<DLogger>;

public:

    /**
     * Insert a log message to all log element : date-time loglevel message
     * @param message The log message
     * @param loglevel The log level
     * @see #Level for details about log levels.
     */
    void insertMessage ( const DString & message, Level loglevel = DLogShared::INFO );

    /**
     * Insert a debug message to all log element
     * This is an overloaded member function, provided for convenience.
     * It behaves essentially like the above function with Level already set.
     * @param message The log message
     */
    void debug ( const DString & message );

    /**
     * Insert a verbose message to all log element
     * This is an overloaded member function, provided for convenience.
     * It behaves essentially like the above function with Level already set.
     * @param message The log message
     */
    void verbose ( const DString & message );

    /**
     * Insert a information message to all log element
     * This is an overloaded member function, provided for convenience.
     * It behaves essentially like the above function with Level already set.
     * @param message The log message
     */
    void info ( const DString & message );

    /**
     * Insert a message about signal to all log element
     * This is an overloaded member function, provided for convenience.
     * It behaves essentially like the above function with Level already set.
     * @param message The log message
     */
    void signal ( const DString & message );

    /**
     * Insert a warning message to all log element
     * This is an overloaded member function, provided for convenience.
     * It behaves essentially like the above function with Level already set.
     * @param message The log message
     */
    void warning ( const DString & message );

    /**
     * Insert a error message to all log element
     * This is an overloaded member function, provided for convenience.
     * It behaves essentially like the above function with Level already set.
     * @param message The log message
     */
    void error ( const DString & message );

    /**
     * Insert a critical message to all log element
     * This is an overloaded member function, provided for convenience.
     * It behaves essentially like the above function with Level already set.
     * @param message The log message
     */
    void critical ( const DString & message );

    /**
     * Add a log engine to logger
     * @param type The log type to add.
     * @param params The parameters for this log engine.
     * @see #Type for details about all supported types
     * @see DLogParams for details about parameters
     * @return A unique log engine identifiant
     */
    DLogEngine * addLogEngine ( Type type, DLogParams & params );

    /**
     * Add an already defined log engine to logger
     * @param engine The log engine to add.
     * @return A unique log engine identifiant
     */
    void addLogEngine ( DLogEngine * engine );

    /**
     * Remove a log engine from logger
     * @param engine A pointer to the log engine which must be removed.
     */
    void removeLogEngine ( DLogEngine * engine );

    /**
     * Close all log engines
     */
    void close();

    /**
     * Add a new user defined variable
     * @param varname The name of user defined variable.
     * @return TRUE if the variable was inserted, FALSE otherwise.
     */
    bool addUserVar( const DString & varname );

    /**
     * Add and set up a new user defined variable.
     * @param varname The name of user defined variable.
     * @param value The value of user defined variable.
     * @return TRUE if the variable was inserted, FALSE otherwise.
     */
    bool addAndSetupUserVar( const DString & varname, const DString & value );

    /**
     * Remove user defined variable
     * @param varname The name of user defined variable.
     */
    void removeUserVar( const DString & varname );

    /**
     * Set up a new user defined variable.\n
     * @attention User variable will not be inserted if not exists.
     * @param varname The name of user defined variable.
     * @param value The value of user defined variable.
     */
    void setupUserVar( const DString & varname, const DString & value );


    /**
     * Prepare the log message switchin the message pattern, the current
     * date-time and user variables.
     * @param text The log message text
     * @param dateformat The format for the date-time
     * @param pattern The log message pattern
     * @param loglevel The log level
     */
    const DString & prepare ( const DString & text,
                              const DString & dateformat,
                              const DString & pattern,
                              Level loglevel );

protected :
    /**
     * Empty Constructor
     */
    DLogger ( void );

    /**
     * Default Destructor
     */
    ~DLogger ( void );

    /// Internal collection of Log element
    DLogCollection m_logs;

    /// Initialisation flag
    bool m_initialized;

    /** stdout engine pointer.\n
     * It's impossible to have more than one stdout in same time.
     */
    DLogEngine * m_stdout;

    /// user variables
    static std::map<DString, DString> m_userVar;

private:
    DFactory<DLogEngine> m_factory;
	DString m_prepare;

};

#endif // _DLOG_H_

