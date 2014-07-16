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
 *     (___)_)   File : dpoint.h                            ||--|| *          *
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

#ifndef DPOINT_H
#define DPOINT_H

#include <cmath>
#include <sstream>
#include <string>

/**
 * A simple way to use point and make operations on it.\n
 * Its more simple to use it with a typedef, like this :
 * @code
 * typedef DPoint<int> Point;
 *
 * Point pt1; // is equal to DPoint<int> pt1;
 * @endcode
 *
 * @brief 2D point.
 * @author Didier FABERT <didier.fabert@gmail.com>
 */

template <typename T> class DPoint
{
public:
    /**
     * Constructs a null point (with coordinates {0, 0}).
     */
    DPoint(void)  { X = 0; Y = 0; };
    /**
     * Constructs a point with coordinates {x, y}.
     */
    DPoint(T x, T y) { X = x; Y = y; };
    /**
     * Default destructor
     */
    virtual ~DPoint(void) { };

    /**
     * Sets the X-coordinate of the DPoint to x and the Y-coordinate of the
     * DPoint to y.
     * @see getPoint (x, y)
     */
    void setPoint(const T x, const T y) { X = x; Y = y; };
    /**
     * Sets the X-coordinate of the DPoint to x.
     * @see getX ()
     */
    void setX(T x) { X = x; };
    /**
     * Sets the Y-coordinate of the DPoint to y.
     * @see getY ()
     */
    void setY(T y) { Y = y; };

    /**
     * Gets the X-coordinate and the Y-coordinate of the DPoint.
     * @see setPoint (x, y)
     */
    void getPoint(T &x, T &y) { x = X; y = Y; };
    /**
     * Returns the X-coordinate of the DPoint.
     * @see setX (x)
     */
    T getX(void) { return X; };
    /**
     * Returns the Y-coordinate of the DPoint.
     * @see setY (y)
     */
    T getY(void) { return Y; };

    /**
     * Returns the sum of the absolute values of X and Y from the origin to the
     * point
     */
    T getLength(void) { return (sqrt(pow(X,2)+pow(Y,2))); }

    /**
     * Sets the X and Y values of the DPoint to 0
     */void clear(void) { X = 0; Y = 0; }

    /**
     * Returns TRUE if both the X value and the Y value are null; otherwise
     * returns FALSE.
     */
    bool isNull(void)
    {
        if(X && Y) return false;
        return true;
    }

    /**
     * Returns a reference to the X coordinate of the point.
     * Using a reference makes it possible to directly manipulate X.
     * @code
     * DPoint<int> mtx(5,4);
     * mtx.refX()++; // mtx become (6,4)
     * @endcode
     */
    T& refX(void)
    {
        return X;
    }

    /**
     * Returns a reference to the X coordinate of the point.
     * Using a reference makes it possible to directly manipulate Y.
     * @code
     * DPoint<int> mtx(5,4);
     * mtx.refY()++; // mtx become (5,5)
     * @endcode
     */
    T& refY(void)
    {
        return Y;
    }

// affect
    /**
    * Copy both X and Y values to mtx
    */
    DPoint& operator= (const DPoint &mtx)
    {
        X = mtx.X;
        Y = mtx.Y;
        return *this;
    }

// Compare
    /**
     * Returns TRUE if mtx1 and mtx2 are equal; otherwise returns FALSE.
     */
    friend bool operator== (const DPoint &mtx1, const DPoint &mtx2)
    {
        if ((mtx1.X == mtx2.X) && (mtx1.Y == mtx2.Y))
        {
            return true;
        }
        return false;
    }

    /**
     * Returns TRUE if mtx1 and mtx2 are not equal; otherwise returns FALSE.
     */
    friend bool operator!= (const DPoint &mtx1, const DPoint &mtx2)
    {
        if ((mtx1.X == mtx2.X) && (mtx1.Y == mtx2.Y))
        {
            return false;
        }
        return true;
    }

// Add
    /**
     * Returns the sum of mtx1 and mtx2. Each component is added separately.
     */
    friend DPoint operator+ (DPoint mtx1, DPoint mtx2)
    {
        DPoint c;
        c.X = mtx1.X + mtx2.X;
        c.Y = mtx1.Y + mtx2.Y;
        return c;
    }

    /**
     * Returns the sum of mtx1 and v. Each component is added separately.
     */
    friend DPoint operator+ (DPoint mtx, T v)
    {
        DPoint c;
        c.X = mtx.X + v;
        c.Y = mtx.Y + v;
        return c;
    }

    /**
     * Returns the sum of v and mtx1. Each component is added separately.
     */
    friend DPoint operator+ (T v, DPoint mtx)
    {
        DPoint c;
        c.X = mtx.X + v;
        c.Y = mtx.Y + v;
        return c;
    }

// operator +=
    /**
     * Adds DPoint mtx to this DPoint and returns a reference to this
     * DPoint.
     * Each component is added separately.
     */
    DPoint& operator+= (DPoint mtx)
    {
        X = X + mtx.X;
        Y = Y + mtx.Y;
        return *this;
    }
    /**
     * Adds v to this DPoint and returns a reference to this DPoint.
     */
    DPoint& operator+= (T v)
    {
        X = X + v;
        Y = Y + v;
        return *this;
    }

// Mult
    /**
     * Returns a DPoint formed by multiplying both components of mtx1 and
     * mtx2.
     * Each component is multiplied separately.
     */
    friend DPoint operator* (DPoint mtx1, DPoint mtx2)
    {
        DPoint c;
        c.X = mtx1.X * mtx2.X;
        c.Y = mtx1.Y * mtx2.Y;
        return c;
    }

    /**
     * Returns a DPoint formed by multiplying both components of mtx1 by v.
     */
    friend DPoint operator* (DPoint mtx, T v)
    {
        DPoint c;
        c.X = mtx.X * v;
        c.Y = mtx.Y * v;
        return c;
    }

    /**
     * Returns a DPoint formed by multiplying v by both components of mtx1.
     */
    friend DPoint operator* (T v, DPoint mtx)
    {
        DPoint c;
        c.X = mtx.X * v;
        c.Y = mtx.Y * v;
        return c;
    }

// operator *=
    /**
     * Multiplies this DPoint's x and y by mtx, and returns a reference to
     * this point.
     * Each component is multiplied separately.
     */
    DPoint& operator*= (DPoint mtx)
    {
        X = X * mtx.X;
        Y = Y * mtx.Y;
        return *this;
    }
    /**
     * Multiplies this DPoint's x and y by v, and returns a reference to this
     * point.
     */
    DPoint& operator*= (T v)
    {
        X = X * v;
        Y = Y * v;
        return *this;
    }

// subtract
    /**
     * Returns mtx2 subtracted from mtx1. Each component is subtracted
     * separately.
     */
    friend DPoint operator- (DPoint mtx1, DPoint mtx2)
    {
        DPoint c;
        c.X = mtx1.X - mtx2.X;
        c.Y = mtx1.Y - mtx2.Y;
        return c;
    }

    /**
     * Returns v subtracted from mtx. Each component is subtracted separately.
     */
    friend DPoint operator- (DPoint mtx, T v)
    {
        DPoint c;
        c.X = mtx.X - v;
        c.Y = mtx.Y - v;
        return c;
    }

    /**
     * Returns mtx subtracted from v. Each component is subtracted separately.
     */
    friend DPoint operator- (T v, DPoint mtx)
    {
        DPoint c;
        c.X = v - mtx.X;
        c.Y = v - mtx.Y;
        return c;
    }

// operator -=
    /**
    * Subtracts DPoint mtx from this DPoint and returns a reference to
    * this point.
    */
    DPoint& operator-= (DPoint mtx)
    {
        X = X - mtx.X;
        Y = Y - mtx.Y;
        return *this;
    }
    /**
    * Subtracts v from this DPoint and returns a reference to
    * this point.
    * Each component is Subtracted separately.
    */
    DPoint& operator-= (T v)
    {
        X = X - v;
        Y = Y - v;
        return *this;
    }

// divide
    /**
     * Returns the DPoint formed by dividing mtx1 by mtx2.
     * Each component is divided separately.
     * @attention return a null DPoint in case of divide by 0
     */
    friend DPoint operator/ (DPoint mtx1, DPoint mtx2)
    {
        DPoint c;
        if (mtx2.X) c.X = mtx1.X / mtx2.X;
        else { c.clear(); return c; }
        if (mtx2.Y) c.Y = mtx1.Y / mtx2.Y;
        else { c.clear(); return c; }
        return c;
    }

    /**
     * Returns the DPoint formed by dividing both components of mtx by v.
     * @attention return a null DPoint in case of divide by 0
     */
    friend DPoint operator/ (DPoint mtx, T v)
    {
        DPoint c;
        if (v) { c.X = mtx.X / v; }
        else { c.clear(); return c; }
        if (v) { c.Y = mtx.Y / v; }
        else { c.clear(); return c; }
        return c;
    }

    /**
     * Returns the DPoint formed by dividing v by mtx.
     * Each component is divided separately.
     * @attention return a null DPoint in case of divide by 0
     */
    friend DPoint operator/ (T v, DPoint mtx)
    {
        DPoint c;
        if (mtx.Y) { c.X = v / mtx.X; }
        else { c.clear(); return c; }
        if (mtx.Y) { c.Y = v / mtx.Y; }
        else { c.clear(); return c; }
        return c;
    }

// operator /=
    /**
     * Divides both X and Y by mtx, and returns a reference to this point.
     * Each component is divided separately.
     * @attention return a null DPoint in case of divide by 0
     */
    DPoint& operator/= (DPoint mtx)
    {
        if (mtx.X) X = X / mtx.X;
        else { clear(); return *this; }
        if (mtx.Y) Y = Y / mtx.Y;
        else { clear(); return *this; }
        return *this;
    }
    /**
     * Divides both X and Y by v, and returns a reference to this point.
     * @attention return a null DPoint in case of divide by 0
     */
    DPoint& operator/= (T v)
    {
        if (v) X = X / v;
        else { clear(); return *this; }
        if (v) Y = Y / v;
        else { clear(); return *this; }
        return *this;
    }
// Compare
    /**
     * Compare two points.\n
     * Return true if both X and Y of mtx1 are superior than mtx2 X and Y.
     */
    friend bool operator> (DPoint mtx1, DPoint mtx2)
    {
        if ((mtx1.X > mtx2.X) && (mtx1.Y > mtx2.Y))
        {
            return true;
        }
        return false;
    }

    /**
     * Compare two points.\n
     * Return true if both X and Y of mtx1 are equal or superior than mtx2 X and Y.
     */
    friend bool operator>= (DPoint mtx1, DPoint mtx2)
    {
        if ((mtx1.X >= mtx2.X) && (mtx1.Y >= mtx2.Y))
        {
            return true;
        }
        return false;
    }

    /**
     * Compare two points.\n
     * Return true if both X and Y of mtx1 are inferior than mtx2 X and Y.
     */
    friend bool operator< (DPoint mtx1, DPoint mtx2)
    {
        if ((mtx1.X < mtx2.X) && (mtx1.Y < mtx2.Y))
        {
            return true;
        }
        return false;
    }

    /**
     * Compare two points.\n
     * Return true if both X and Y of mtx1 are equal or inferior than mtx2 X and Y.
     */
    friend bool operator<= (DPoint mtx1, DPoint mtx2)
    {
        if ((mtx1.X <= mtx2.X) && (mtx1.Y <= mtx2.Y))
        {
            return true;
        }
        return false;
    }

    /**
     * Return true if X is sup than mtx.X ; false otherwise.
     * @deprecated Please use (mtx1.getX() > mtx2.getX()) instead.
     */
    bool isX_Sup(DPoint mtx)
    {
        if (X > mtx.X)
        {
            return true;
        }
        return false;
    }

    /**
     * Return true if X is equal or sup than mtx.X ; false otherwise.
     * @deprecated Please use (mtx1.getX() >= mtx2.getX()) instead.
     */
    bool isX_ESup(DPoint mtx)
    {
        if (X >= mtx.X)
        {
            return true;
        }
        return false;
    }

    /**
     * Return true if Y is sup than mtx.Y ; false otherwise.
     * @deprecated Please use (mtx1.getY() < mtx2.getY()) instead.
     */
    bool isY_Sup(DPoint mtx)
    {
        if (Y > mtx.Y)
        {
            return true;
        }
        return false;
    }

    /**
     * Return true if Y is equal or sup than mtx.Y ; false otherwise.
     * @deprecated Please use (mtx1.getY() <= mtx2.getY()) instead.
     */
    bool isY_ESup(DPoint mtx)
    {
        if (Y >= mtx.Y)
        {
            return true;
        }
        return false;
    }

// iostream
    /**
    * Writes DPoint to the stream s and returns a reference to the stream.
    */
    friend std::ostream& operator<< (std::ostream& s, const DPoint &mtx)
    {
        s << "{" << mtx.X << "," << mtx.Y << "}";
        return s;
    }

    /**
     * Reads a DPoint from the stream s into DPoint mtx and returns a
     * reference to the stream.
     */
    friend std::istream& operator>> (std::istream& s, DPoint &mtx)
    {
        std::string str, str1, str2;
        std::string::size_type pos1, pos2;
        std::istringstream iss1, iss2;

        s >> str;
        pos1 = str.find("{");
        pos2 = str.find(",");
        if (pos1 != std::string::npos && pos2 != std::string::npos &&
                                                            ((pos2 - pos1) > 0))
        {
            str1 = str.substr(pos1 + 1, pos2 - pos1 -1);
            std::istringstream iss1(str1);
            iss1 >> mtx.X;
        }
        else
        {
            mtx.X = 0;
        }
        pos1 = str.find("}");
        if (pos1 != std::string::npos && pos2 != std::string::npos &&
                                                            ((pos1 - pos2) > 0))
        {
            str2 = str.substr(pos2 + 1, pos1 - pos2 - 1);
            std::istringstream iss2(str2);
            iss2 >> mtx.Y;
        }
        else
        {
            mtx.Y = 0;
        }

        return s;
    }
	
	std::string toString(void)
	{
		std::ostringstream oss;
		
		oss << "{" << X << "," << Y << "}";
		return oss.str();
	}

private:
    /// The X-Coordinate
    T X;
    /// The Y-Coordinate
    T Y;
};

#endif // DPOINT_H
