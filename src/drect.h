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
 *     (___)_)   File : drect.h                             ||--|| *          *
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

#ifndef DRECT_H
#define DRECT_H

#include <vector>
#include <iostream>

#include "dpoint.h"
#include "dstring.h"

/**
 * A simple way to define and use rect.\n
 * Its more simple to use it with a typedef, like this :
 * @code
 * typedef DRect<int> Rect;
 *
 * Rect rect1; //is equal to DRect<int> rect1;
 * @endcode
 *
 * @brief 2D rectangle.
 * @author Didier FABERT <didier.fabert@gmail.com>
 */
template <typename T>class DRect
{
public:
	/**
	 * Constructs an empty rect.
	 */
	DRect(void) : Ax ( 0 ), Ay ( 0 ), Bx ( 0 ), By ( 0 ) {};

	/**
	 * Constructs a rect with two opposite points.
	 */
	DRect(const DPoint<T> & pt1, const DPoint<T> & pt2)
	{
		Ax = pt1.getX();
		Ay = pt1.getY();
		Bx = pt2.getX();
		By = pt2.getY();
		formatRect();
	}

	/**
	 * Constructs a rect with two opposite point coordinates.
	 */
	DRect(const T & ax, const T & ay, const T & bx, const T & by)
	{
		Ax = ax;
		Ay = ay;
		Bx = bx;
		By = by;
		formatRect();
	}

	virtual ~DRect( void ) {};
	
	/**
	 * Copy all values to rect
	 */
	DRect & operator= ( const DRect & rect )
	{
		Ax = rect.Ax;
		Ay = rect.Ay;
		Bx = rect.Bx;
		By = rect.By;
		formatRect();
		return *this;
	}
	/**
	 * The opposite apex of the rectangle
	 * the point \p a is always the point A and point \p b, the point B.
	 * @brief Opposite apex of rectangle.
	 * @author Didier FABERT <didier.fabert@gmail.com>
	 */
	class Apex
	{
	public:
		
		/**
		 * Constructs an empty rect.
		 */
		Apex() {}
		
		/**
		 * Constructs rect from values.
		 */
		Apex( const T & vax, const T & vay, const T & vbx, const T & vby )
		{
			ax = vax;
			ay = vay;
			bx = vbx;
			by = vby;
		}
		
		/**
		 * Virtual destructor.
		 */
		virtual ~Apex() {}
	
		/**
		 * Compare two Apex
		 */
		friend bool operator == ( const Apex & apex1, const Apex & apex2 )
		{
			if ( apex1.ax != apex2.ax ) return false;
			if ( apex1.ay != apex2.ay ) return false;
			if ( apex1.bx != apex2.bx ) return false;
			if ( apex1.by != apex2.by ) return false;
			return true;
		}
		
		/// X coordinate of the first apex
		T ax;
		/// Y coordinate of the first apex
		T ay;
		/// X coordinate of the second apex
		T bx;
		/// Y coordinate of the second apex
		T by;
	};

	/**
	 * Define rect from four point coordinates.
	 */
	DRect & setVal( const T & ax, const T & ay, const T & bx, const T & by )
	{
		Ax = ax;
		Ay = ay;
		Bx = bx;
		By = by;
		formatRect();
		return *this;
	}
	
	/**
	 * Define rect from two opposite points of the rect
	 */
	DRect & setPoints( const DPoint<T> & pt1, const DPoint<T> & pt2)
	{
		Ax = pt1.getX();
		Ay = pt1.getY();
		Bx = pt2.getX();
		By = pt2.getY();
		formatRect();
		return *this;
	};
	
	/**
	 * Define rect from apex
	 */
	DRect & setApex(const Apex & apex)
	{		
		Ax = apex.ax;
		Ay = apex.ay;
		Bx = apex.bx;
		By = apex.by;
		formatRect();
		return *this;
	}
	
	/**
	 * Get two opposite points of the rect
	 */
	Apex getApex()
	{
		Apex apex;
		
		apex.ax = Ax;
		apex.ay = Ay;
		apex.bx = Bx;
		apex.by = By;
		return apex;
	}
	
	/**
	 * Make a string with two opposite apex coordinates
	 */
	const DString toString() const
	{
		std::ostringstream oss;
		
		oss << "{" << Ax << "," << Ay << "," << Bx << "," << By << "}";
		return oss.str();
	}
	
	/**
	 * Return true if \p pt is inside rect. False otherwise.
	 * @param pt The point to check
	 * @param border Specify if border rect is a part of rect. True by default. 
	 */
	bool isInside(DPoint<T> pt, bool border = true) const
	{
		if ( border && pt.getX() < Ax ) return false;
		if ( ! border && pt.getX() <= Ax ) return false;
		if ( border && pt.getY() < Ay ) return false;
		if ( ! border && pt.getY() <= Ay ) return false;
		if ( border && pt.getX() > Bx ) return false;
		if ( ! border && pt.getX() >= Bx ) return false;
		if ( border && pt.getY() > By ) return false;
		if ( ! border && pt.getY() >= By ) return false;
		return true;
	}
	
	/**
	 * Return true if rect are equals. False otherwise.
	 * rect are equals if, and only if, all values are equals.
	 */
	friend bool operator == ( const DRect & pt1, const DRect & pt2 )
	{
		if ( pt1.Ax != pt2.Ax ) return false;
		if ( pt1.Ay != pt2.Ay ) return false;
		if ( pt1.Bx != pt2.Bx ) return false;
		if ( pt1.By != pt2.By ) return false;
		return true;
	}
	
    /**
	 * Writes DRect to the stream s and returns a reference to the stream.
	 */
	friend std::ostream& operator<< (std::ostream& s, const DRect &rect)
	{
		s << rect.toString();
		return s;
	}

private:
	
	/**
	 * Make the point \p A, the one which have the smallest coordinates and
	 * point \p B, the biggest coordinates (X and Y).
	 */
	void formatRect()
	{
		T tmp;
		
		if (Bx < Ax)
		{
			tmp = Ax;
			Ax = Bx;
			Bx = tmp;
		}
		if (By < Ay)
		{
			tmp = Ay;
			Ay = By;
			By = tmp;
		}
	};
	
	/// The smaller X corner coordinate
	T Ax;
	/// The smaller Y corner coordinate
	T Ay;
	/// The bigger X corner coordinate
	T Bx;
	/// The bigger Y corner coordinate
	T By;
	
};

#endif // DRECT_H
