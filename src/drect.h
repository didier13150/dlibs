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

#ifndef DRECT_H
#define DRECT_H

#include <vector>
#include <sstream>

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
	DRect(void) { Ax = 0; Ay = 0; Bx = 0; By = 0; };

	/**
	 * Constructs a rect with two opposite points.
	 */
	DRect(DPoint<T> pt1, DPoint<T> pt2)
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
	DRect(T ax, T ay, T bx, T by)
	{
		Ax = ax;
		Ay = ay;
		Bx = bx;
		By = by;
		formatRect();
	}

	virtual ~DRect(void) {};
	
	/**
	 * Copy all values to rect
	 */
	DRect& operator= (const DRect &rect)
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
	typedef struct
	{
		T ax;
		T ay;
		T bx;
		T by;
	}Apex;
	
	/**
	 * Set two opposite points of the rect
	 */
	void setPoints(DPoint<T> pt1, DPoint<T> pt2)
	{
		Ax = pt1.getX();
		Ay = pt1.getY();
		Bx = pt2.getX();
		By = pt2.getY();
		formatRect();
	};
	
	/**
	 * Set two opposite points of the rect
	 */
	void setApex(Apex apex)
	{		
		Ax = apex.ax;
		Ay = apex.ay;
		Bx = apex.bx;
		By = apex.by;
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
	
	/**
	 * Make a string with two opposite apex coordinates
	 */
	std::string toString()
	{
		std::ostringstream oss;
		
		oss << "{" << Ax << "," << Ay << "," << Bx << "," << By << "}";
		return oss.str();
	}
	
	bool isInside(DPoint<T> point, bool border = true)
	{
		return true;
	}
	
// iostream
    /**
	 * Writes DRect to the stream s and returns a reference to the stream.
	 */
	friend std::ostream& operator<< (std::ostream& s, const DRect &rect)
	{
		s << "{" << rect.Ax << "," << rect.Ay << "," << rect.Bx << ","
				<< rect.By << "}";
		return s;
	}

private:
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
