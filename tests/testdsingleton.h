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
 *     (___)_)   File : testdsingleton.cpp                  ||--|| *          *
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
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                *
 *                                                                            *
 *   Unit Test for DSingleton                                                 *
 *                                                                            *
 ******************************************************************************/


#ifndef TESTDSINGLETON_H
#define TESTDSINGLETON_H

#include <cpptest.h>
#include "dsingleton.h"

class Foo : public DSingleton<Foo>
{
	// To let DSingleton have access to Foo protected constructor
	friend class DSingleton<Foo>;
	
protected:
	// Protected constructor
	Foo() : nb( 0 ) {}
	
public:
	int getVal()
	{
		return nb;
	}
	void increment()
	{
		nb++;
	}
	void reset()
	{
		nb = 0;
	}
private:
	int nb;
};

class TestDSingleton : public Test::Suite
{
public:
	TestDSingleton()
	{
		TEST_ADD( TestDSingleton::singleton_test )
	}
	
private:
	void singleton_test();
};

#endif // TESTDSINGLETON_H
