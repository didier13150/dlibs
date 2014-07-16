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
 *     (___)_)   File : dprocess.h                          ||--|| *          *
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
#ifndef _DPROCESS_H_
#define _DPROCESS_H_

#include <stdio.h>
#include <signal.h>

#include "dstring.h"
#include "dthread.h"

/**
 * Launch another program.
 * @brief External process.
 * @author Didier FABERT <didier.fabert@gmail.com>
 * @include testdenv.cpp
*/
class DProcess : public DThread
{
public:
	/**
	 * Constructor
	 */
	DProcess();

	/**
	 * Destructor
	 */
	~DProcess();

	/**
	 * @typedef ComMode
	 * Define all communication mode accepted by the process
	 */
	typedef enum
	{
		/// Read from pipe
		READ_ONLY,
		/// Write on pipe
		WRITE_ONLY,
	}ComMode;

	/**
	 * @typedef ExeMode
	 * Define all execution mode accepted by the process
	 */
	typedef enum
	{
		/// Block start exit until thread termination
		BLOCK,
		/// start exit immediatly
		NOBLOCK,
	}ExeMode;

	/**
	 * Set the process execution mode
	 * @param type The execution mode
	 * @see #ExeMode
	 */
	void setExeMode( ExeMode exe_mode );
	
	/**
	 * Get the current execution mode
	 * @return The execution mode
	 * @see #ExeMode
	 */
	ExeMode getExeMode();
	/**
	 * Set the process communication mode
	 * @param mode The communication mode for the process
	 * @see #ComMode
	 */
	void setComMode( ComMode com_mode );
	
	/**
	 * Get the current communication mode
	 * @return The communication mode
	 * @see #ComMode
	 */
	ComMode getComMode();

	/**
	 * Launch the process in a separate processus
	 */
	virtual void run();

	/**
	 * Set process executable
	 * @param executable The process executable name
	 */
	void setExecutable( const DString & executable );

	/**
	 * Get process executable
	 * @return The current process executable name
	 */
	const DString & getExecutable() const;
	
	/**
	 * Set process argument
	 * @param args The argument list for the process
	 */
	void setArgs( const DStringList & args );

	/**
	 * Get the process arguments
	 * @return The current process argument list
	 */
	const DStringList & getArgs () const;

	/**
	 * Clear the process arguments
	 */
	void clearArgs ();

	/**
	 * Get the process output
	 */
	const DString & getOutput() const;

	/**
	 * Start the process
	 */
	virtual void start();

	/**
	 * Add quickly an argument to process
	 */
	DProcess & operator << ( const DString & arg );

	/**
	 * Clear the process
	 */
	void clear();
	
protected:

	/// Running mode
	ComMode m_com_mode;

	/// Execution Mode
	ExeMode m_exe_mode;

	/// Executable name
	DString m_exe;

	/// Argument list
	DStringList m_args;

	/// file descriptor
	FILE * m_file;

	/// output of the processus
	DString m_output;

	/**
	 * Process the executable output
	 */
	virtual void addOutput( const DString & output );
};

#endif // _DPROCESS_H_
