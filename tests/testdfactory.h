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
 *     (___)_)   File : testdfactory.h                      ||--|| *          *
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
 *   Unit Test for DFactory                                                   *
 *                                                                            *
 ******************************************************************************/

#ifndef _TESTDFACTORY_H
#define _TESTDFACTORY_H

#include <cpptest.h>

#include "dfactory.h"

class TestDFactory : public Test::Suite
{
public:
	TestDFactory()
	{
		TEST_ADD( TestDFactory::basic_test )
		TEST_ADD( TestDFactory::ddatabase_test )
	}

private:
	void basic_test();
	void ddatabase_test();
};

class Object
{
public:
	Object()
	{
	}
	virtual ~Object()
	{
	}
	const DString & what()
	{
		return _what;
	}
	virtual Object* Clone() const = 0 ;
protected:
	DString _what;
};

class Square : public Object
{
public:
	Square()
	{
		_what = "Square";
	}
	virtual ~Square()
	{
	}
	Object* Clone() const
	{
		return new Square ( *this );
	}
};

class Round : public Object
{
public:
	Round()
	{
		_what = "Round";
	}
	virtual ~Round()
	{
	}
	Object* Clone() const
	{
		return new Round ( *this );
	}
};

#endif // _TESTDFACTORY_H
