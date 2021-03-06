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
*     (___)_)   File : dappcmdline.h                       ||--|| *          *
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
#ifndef _DAPPCMDLINE_H_
#define _DAPPCMDLINE_H_

#include "dstring.h"
#include <map>
#include <list>

/**
* @short Application option.
* @author Didier FABERT <didier.fabert@gmail.com>
*/
class DAppOption
{

public:
	/**
	* Empty Constructor
	*/
	DAppOption();

	/**
	* Destructor
	*/
	~DAppOption();

	/**
	* Clear the option
	*/
	void clear();

	/**
	* Set the option name ( long name )
	* @param name The option name
	*/
	void setName( const DString & name );

	/**
	* Get the option name
	* @return the option name ( long name )
	*/
	const DString & getName() const;

	/**
	* Set the option description
	* @param description the option description
	*/
	void setDescription( const DString & description );

	/**
	* Get the option description
	* @return the option description
	*/
	const DString & getDescription() const;

	/**
	* Set the option value
	* @param value the option value
	*/
	void setValue( const DString & value );

	/**
	* Get the option value
	* @return the option value
	*/
	const DString & getValue() const;

	/**
	* Set the option example
	* @param value the option example
	*/
	void setExample( const DString & example );

	/**
	* Get the option example
	* @return the option example
	*/
	const DString & getExample() const;
	
	/**
	* Set the option alias ( short name )
	* @param value the option alias
	*/
	void setAlias( char alias );

	/**
	* Get the option alias ( short name )
	* @return the option alias
	*/
	char getAlias() const;
	
	/**
	 * Set option state ( on command line )
	 * @param state. Set to true if option is present on command line. false otherwise.
	 */
	void setState( bool state );
	
	/**
	 * Get option state ( on command line )
	 * @return true if option was set on command line. false otherwise.
	 */
	bool isSet() const;
	
	/**
	 * Set mandatory option state ( on command line )
	 * @param state. Set to true if option must be present on command line. false otherwise.
	 */
	void setMandatoryState( bool state );
	
	/**
	 * Get mandatory option state ( on command line )
	 * @return true if option must be set on command line. false otherwise.
	 */
	bool isMandatory() const;
	
	/**
	* Set option data
	* @param name The option long name
	* @param description The option description
	* @param example The example on help string ( -f, --file=&lt;FILE&gt; )
	* @param alias The alias for option ( short name )
	*/
	void set ( const DString & name,
			const DString & description,
			const DString & example,
			char alias = 0 );

	/**
	* Print DAppOption object in flux
	*/
	friend std::ostream& operator<< ( std::ostream& s, const DAppOption & arg );

protected:
	/// Option name
	DString _name;

	/// Option description ( for displaying help )
	DString _description;

	/// Option example ( for displaying help )
	DString _example;

	/// Option value
	DString _value;

	/// Alias option ( also named short name )
	char _alias;

	/// Mandatory value option flag
	bool _have_mandatory_value;

	/// Option present in command line flag
	bool _is_set;
};

/**
* @typedef DAppOptionList
*/
typedef std::list<DAppOption> DAppOptionList;

/**
* @short Application mandatory argument.
* @author Didier FABERT <didier.fabert@gmail.com>
*/
class DAppArg
{

public:
	/**
	* Empty Constructor
	*/
	DAppArg();

	/**
	* Destructor
	*/
	~DAppArg();

	/**
	* Set the argument description
	* @param description the argument description
	*/
	void setDescription( const DString & description );

	/**
	* Get the argument description
	* @return the argument description
	*/
	const DString & getDescription() const;

	/**
	* Set the argument value
	* @param value the argument value
	*/
	void setValue( const DString & value );

	/**
	* Get the argument value
	* @return the argument value
	*/
	const DString & getValue() const;

	/**
	* Clear the argument
	*/
	void clear();

	/**
	* Print DAppArg object in flux
	*/
	friend std::ostream& operator<< ( std::ostream& s, const DAppArg & opt );

protected:
	/// Argument description ( for displaying help )
	DString _description;

	/// Argument value
	DString _value;
};

/**
* @typedef DAppArgList
*/
typedef std::list<DAppArg> DAppArgList;

/**
* @short Manage command line options and arguments.
* @author Didier FABERT <didier.fabert@gmail.com>
* Get and check the option and argument passed by the command line
* \include dappcmdline.dox
*/

class DAppCmdLine
{

public:
	/**
	* Empty constructor.
	*/
	DAppCmdLine();

	/**
	* Default destructor.
	*/
	~DAppCmdLine();

	/**
	* Add an argument.
	* @param name The (long) name of the option
	* @param description
	* @param alias Alias (short name) for the option
	*/
	void addOption ( const DString & name,
					const DString & description,
					const char alias = 0 );

	/**
	* Add an argument.
	* @param name The (long) name of the option
	* @param description
	* @param example Argument example. Option is required if not empty.
	* @param alias Alias (short name) for the option
	*/
	void addOption ( const DString & name,
					const DString & description,
					const DString & example,
					const char alias = 0 );

	/**
	* Add an argument.
	* @param opt A DAppOption class
	*/
	void addOption ( const DAppOption & opt );

	/**
	* Set argument list.
	* @param list A list of DAppOption
	*/
	void setOptions ( const DAppOptionList & list );

	/**
	* Show application help.
	*/
	void showHelp() const;

	/**
	* Show application version
	*/
	void showVersion() const;

	/**
	* Get option value.
	*/
	const DString & getOptionValue ( const DString & name ) const;

	/**
	* Return TRUE if option was set, FALSE otherwise.
	*/
	bool haveOption ( const DString & name ) const;

	/**
	* Get the number of options
	* @return the number of options, 0 if no option was found.
	*/
	int getNumberOfOptions() const;

	/**
	* Add argument.
	* Arguments must be given in order.
	* @param description A description of the mandatory argument
	*/
	unsigned int addArgument ( const DString & description = DString::empty() );

	/**
	* Add an argument.
	* @param arg A DAppArg class
	*/
	unsigned int addArgument ( const DAppArg & arg );

	/**
	* Set argument list.
	* @param list A list of DAppArg
	*/
	void setArguments ( const DAppArgList & list );

	/**
	* Get the argument.
	* @param position The position number
	*/
	const DString & getArgumentValue ( unsigned int position ) const;

	/**
	* Get the number of expected arguments
	* @return the number of expected mandatory arguments, 0 if no argument was expected.
	*/
	unsigned int getNbExpectedArgs() const;

	/**
	* Check if all arguments are provided
	* @return Return TRUE if number of expected argument and number of
	* really found are equal, FALSE otherwise.
	*/
	bool haveAllExpectedArgsFound() const;

	/**
	* Get the number of found arguments
	* @return the number of mandatory arguments, 0 if no argument was found.
	*/
	unsigned int getNbFoundArgs() const;

	/**
	* Set application version
	* @param version The version number
	*/
	void setAppVersion( const DString & version );

	/**
	* Get application version
	* @return application version
	*/
	const DString & getAppVersion() const;

	/**
	* Get application name
	* @return application name
	*/
	const DString & getAppName() const;

	/**
	* Parse options.
	* @return TRUE if options are set correctly, FALSE otherwise.
	*/
	bool parse ( int argc, char** argv );

	/**
	* Get the last error encoured
	* @return the last error encoured.
	*/
	const DString & getLastError() const;

	/**
	* Print DAppCmdLine object on flux
	*/
	friend std::ostream& operator<< ( std::ostream& s, const DAppCmdLine & app );

protected:
	/// alias for option (long) name ( alias => name )
	std::map<DString, DString> m_alias;

	/// options ( name => option )
	std::map<DString, DAppOption> m_options;

	/// arguments ( ID => argument )
	std::map<unsigned int, DAppArg> m_arguments;

	/// application name without path
	DString m_appname;

	/// application version
	DString m_appversion;

	/// Help list for arguments
	DStringList m_help_arguments;

	/// Last error encoured
	DString m_err;

private:
	unsigned int m_autoID;
	unsigned int m_found;
};

#endif // _DAPPCMDLINE_H_
