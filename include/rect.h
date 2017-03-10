// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h
#ifndef __VG_RECT_H_INCLUDE__
#define __VG_RECT_H_INCLUDE__

#include "vgMath.h"
#include "dimension2d.h"
#include "position2d.h"

namespace vg
{
	namespace core
	{
		/**!template rectangle
		*
		*/
		template<typename T>
		class rect
		{
		public:
			rect() :UpperLeftCorner(0, 0), LowerRightCorner(0, 0) {}
			rect(const T ulx, const T uly, const T drx, const T dry)
				:UpperLeftCorner(ulx, uly), LowerRightCorner(drx, dry) {}
			rect(const position2d<T> &upc, const position2d<T> &drc)
				:UpperLeftCorner(upc), LowerRightCorner(drc) {}
			template<typename U>
			rect(const position2d<T>& pos, const dimension2d<U>& size)
				: UpperLeftCorner(pos), LowerRightCorner(pos.X + size.Width, pos.Y + size.Height) {}

			//! move right by given numbers
			rect<T> operator+(const position2d<T>& pos) const
			{
				rect<T> ret(*this);
				return ret += pos;
			}

			//! move right by given numbers
			rect<T>& operator+=(const position2d<T>& pos)
			{
				UpperLeftCorner += pos;
				LowerRightCorner += pos;
				return *this;
			}

			//! move left by given numbers
			rect<T> operator-(const position2d<T>& pos) const
			{
				rect<T> ret(*this);
				return ret -= pos;
			}

			//! move left by given numbers
			rect<T>& operator-=(const position2d<T>& pos)
			{
				UpperLeftCorner -= pos;
				LowerRightCorner -= pos;
				return *this;
			}

			//! equality operator
			bool operator==(const rect<T>& other) const
			{
				return (UpperLeftCorner == other.UpperLeftCorner &&
					LowerRightCorner == other.LowerRightCorner);
			}

			//! inequality operator
			bool operator!=(const rect<T>& other) const
			{
				return (UpperLeftCorner != other.UpperLeftCorner ||
					LowerRightCorner != other.LowerRightCorner);
			}

			//! compares size of rectangles
			bool operator<(const rect<T>& other) const
			{
				return getArea() < other.getArea();
			}

			//! Returns size of rectangle
			T getArea() const
			{
				return getWidth() * getHeight();
			}

			//! Returns if a 2d point is within this rectangle.
			/** \param pos Position to test if it lies within this rectangle.
			\return True if the position is within the rectangle, false if not. */
			bool isPointInside(const position2d<T>& pos) const
			{
				return (UpperLeftCorner.X <= pos.X &&
					UpperLeftCorner.Y <= pos.Y &&
					LowerRightCorner.X >= pos.X &&
					LowerRightCorner.Y >= pos.Y);
			}

			//! Check if the rectangle collides with another rectangle.
			/** \param other Rectangle to test collision with
			\return True if the rectangles collide. */
			bool isRectCollided(const rect<T>& other) const
			{
				return (LowerRightCorner.Y > other.UpperLeftCorner.Y &&
					UpperLeftCorner.Y < other.LowerRightCorner.Y &&
					LowerRightCorner.X > other.UpperLeftCorner.X &&
					UpperLeftCorner.X < other.LowerRightCorner.X);
			}

			//! Clips this rectangle with another one.
			/** \param other Rectangle to clip with */
			void clipAgainst(const rect<T>& other)
			{
				if (other.LowerRightCorner.X < LowerRightCorner.X)
					LowerRightCorner.X = other.LowerRightCorner.X;
				if (other.LowerRightCorner.Y < LowerRightCorner.Y)
					LowerRightCorner.Y = other.LowerRightCorner.Y;

				if (other.UpperLeftCorner.X > UpperLeftCorner.X)
					UpperLeftCorner.X = other.UpperLeftCorner.X;
				if (other.UpperLeftCorner.Y > UpperLeftCorner.Y)
					UpperLeftCorner.Y = other.UpperLeftCorner.Y;

				// correct possible invalid rect resulting from clipping
				if (UpperLeftCorner.Y > LowerRightCorner.Y)
					UpperLeftCorner.Y = LowerRightCorner.Y;
				if (UpperLeftCorner.X > LowerRightCorner.X)
					UpperLeftCorner.X = LowerRightCorner.X;
			}

			//! Moves this rectangle to fit inside another one.
			/** \return True on success, false if not possible */
			bool constrainTo(const rect<T>& other)
			{
				if (other.getWidth() < getWidth() || other.getHeight() < getHeight())
					return false;

				T diff = other.LowerRightCorner.X - LowerRightCorner.X;
				if (diff < 0)
				{
					LowerRightCorner.X += diff;
					UpperLeftCorner.X += diff;
				}

				diff = other.LowerRightCorner.Y - LowerRightCorner.Y;
				if (diff < 0)
				{
					LowerRightCorner.Y += diff;
					UpperLeftCorner.Y += diff;
				}

				diff = UpperLeftCorner.X - other.UpperLeftCorner.X;
				if (diff < 0)
				{
					UpperLeftCorner.X -= diff;
					LowerRightCorner.X -= diff;
				}

				diff = UpperLeftCorner.Y - other.UpperLeftCorner.Y;
				if (diff < 0)
				{
					UpperLeftCorner.Y -= diff;
					LowerRightCorner.Y -= diff;
				}

				return true;
			}

			//! Get width of rectangle.
			T getWidth() const
			{
				return LowerRightCorner.X - UpperLeftCorner.X;
			}

			//! Get height of rectangle.
			T getHeight() const
			{
				return LowerRightCorner.Y - UpperLeftCorner.Y;
			}

			//! If the lower right corner of the rect is smaller then the upper left, the points are swapped.
			void repair()
			{
				if (LowerRightCorner.X < UpperLeftCorner.X)
				{
					T t = LowerRightCorner.X;
					LowerRightCorner.X = UpperLeftCorner.X;
					UpperLeftCorner.X = t;
				}

				if (LowerRightCorner.Y < UpperLeftCorner.Y)
				{
					T t = LowerRightCorner.Y;
					LowerRightCorner.Y = UpperLeftCorner.Y;
					UpperLeftCorner.Y = t;
				}
			}

			//! Returns if the rect is valid to draw.
			/** It would be invalid if the UpperLeftCorner is lower or more
			right than the LowerRightCorner. */
			bool isValid() const
			{
				return ((LowerRightCorner.X >= UpperLeftCorner.X) &&
					(LowerRightCorner.Y >= UpperLeftCorner.Y));
			}

			//! Get the center of the rectangle
			position2d<T> getCenter() const
			{
				return position2d<T>(
					(UpperLeftCorner.X + LowerRightCorner.X) / 2,
					(UpperLeftCorner.Y + LowerRightCorner.Y) / 2);
			}

			//! Get the dimensions of the rectangle
			dimension2d<T> getSize() const
			{
				return dimension2d<T>(getWidth(), getHeight());
			}


			//! Adds a point to the rectangle
			/** Causes the rectangle to grow bigger if point is outside of
			the box
			\param p Point to add to the box. */
			void addInternalPoint(const position2d<T>& p)
			{
				addInternalPoint(p.X, p.Y);
			}

			//! Adds a point to the bounding rectangle
			/** Causes the rectangle to grow bigger if point is outside of
			the box
			\param x X-Coordinate of the point to add to this box.
			\param y Y-Coordinate of the point to add to this box. */
			void addInternalPoint(T x, T y)
			{
				if (x > LowerRightCorner.X)
					LowerRightCorner.X = x;
				if (y > LowerRightCorner.Y)
					LowerRightCorner.Y = y;

				if (x < UpperLeftCorner.X)
					UpperLeftCorner.X = x;
				if (y < UpperLeftCorner.Y)
					UpperLeftCorner.Y = y;
			}




			//вСио╫г
			position2d<T> UpperLeftCorner;
			//сроб╫г
			position2d<T> LowerRightCorner;
		};
		typedef rect<f32> rectf;
		typedef rect<s32> recti;
	}
}

#endif//! __VG_RECT_H_INCLUDE__