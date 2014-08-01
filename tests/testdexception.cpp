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
 *     (___)_)   File : testdexception.h                    ||--|| *          *
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
 *                                                                            *
 *   Unit Test for DException                                                 *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "testdexception.h"

void TestDException::simul_exception()
{
	// Get a random number between 0 and 1024
	int nb = rand() % 1024;
	DString what("A simple exception for test, with a random error code");
	// Throw an exception
	throw DEXCEPTION( what, nb );
}

void TestDException::simul_exception_db()
{
	// Get a random number between 0 and 1024
	int nb = rand() % 1024;
	DString what("A database exception for test, with a random error code");
	// Throw an exception
	throw DEXCEPTION_DB( what, nb );
}
void TestDException::simul_exception_connection()
{
	// Get a random number between 0 and 1024
	int nb = rand() % 1024;
	DString what("A connection exception for test, with a random error code");
	// Throw an exception
	throw DEXCEPTION_CONNECT( what, nb );
}

void TestDException::simul_exception_xml()
{
	// Get a random number between 0 and 1024
	int nb = rand() % 1024;
	DString what("A XML exception for test, with a random error code");
	// Throw an exception
	throw DEXCEPTION_XML( what, nb );
}

void TestDException::constructor_test()
{
	try
	{
		simul_exception();
	}
	// Catch DExceptions
	catch ( const DException & e )
	{
		std::cout << e.dWhat() << std::endl;
	}
	// Catch all others exceptions
	catch ( ... )
	{
		std::cout << "Another unknow exception encoured" << std::endl;
	}
	std::cout << std::endl;
}

void TestDException::database_test()
{
	try
	{
		simul_exception_db();
	}
	// Catch DExceptions
	catch ( const DException_database & e )
	{
		std::cout << e.dWhat() << std::endl;
	}
	catch ( const DException & e )
	{
		std::cout << e.dWhat() << std::endl;
	}
	// Catch all others exceptions
	catch ( ... )
	{
		std::cout << "Another unknow exception encoured" << std::endl;
	}
	std::cout << std::endl;
}

void TestDException::connection_test()
{
	try
	{
		simul_exception_connection();
	}
	// Catch DExceptions
	catch ( const DException_database & e )
	{
		std::cout << e.dWhat() << std::endl;
		std::cout << "Wrong exception encoured" << std::endl;
	}
	catch ( const DException_connection & e )
	{
		std::cout << e.dWhat() << std::endl;
	}
	catch ( const DException & e )
	{
		std::cout << e.dWhat() << std::endl;
		std::cout << "Generic exception encoured" << std::endl;
	}
	// Catch all others exceptions
	catch ( ... )
	{
		std::cout << "Another unknow exception encoured" << std::endl;
	}
	std::cout << std::endl;
}

void TestDException::xml_test()
{
	try
	{
		simul_exception_xml();
	}
	// Catch DExceptions
	catch ( const DException_xml & e )
	{
		std::cout << e.dWhat() << std::endl;
	}
	// Catch all others exceptions
	catch ( ... )
	{
		std::cout << "Another unknow exception encoured" << std::endl;
	}
	std::cout << std::endl;
}

int main( int argc, char** argv )
{
	std::ofstream file;
	TestDException ets;
	
	Test::TextOutput output( Test::TextOutput::Verbose, std::cout );
	Test::HtmlOutput html;
	
	file.open( "devent.html" );
	ets.run( html );
	html.generate( file, true, "DEvent" );
	file.close();
	
	return ets.run( output ) ? EXIT_SUCCESS : EXIT_FAILURE;
}