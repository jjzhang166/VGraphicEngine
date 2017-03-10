
// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h
#ifndef __VG_VECTOR2D_H_INCLUDE__
#define __VG_VECTOR2D_H_INCLUDE__
#include "vgTypes.h"
#include "vector2d.h"
#include "dimension2d.h"

namespace vg
{
	namespace core
	{
		/**!template vector2d
		*/
		template<typename T>
		class vector2d
		{
		public:
			vector2d() :X(0), Y(0) {}
			vector2d(const T nx, const T ny) :X(nx), Y(ny) {}
			vector2d(const T n) :X(n), Y(n) {}
			vector2d(const vector2d<T> &other) :X(other.X), Y(other.Y) {}
			vector2d(const dimension2d<T> &other) :X(other.Width), Y(other.Height) {}


			vector2d<T>& operator=(const vector2d<T>& other)
			{
				this->X = other.X;
				this->Y = other.Y;
				return *this;

				/*vector2d<T> tmp(other);
				core::swap(*this, tmp);
				return *this;
				*/
			}
			vector2d<T>& operator=(const dimension2d<T>& other)
			{
				/*	this->X = other.X;
				this->Y = other.Y;
				return *this;
				*/
				X = other.Width;
				Y = other.Height;
				return *this;
			}
			//+
			const vector2d<T> operator+(const T val)
			{
				return vector2d<T>(this->X + val, this->Y + val);
			}
			const vector2d<T> operator+(const vector2d<T>& other)
			{
				return vector2d<T>(this->X + other.X, this->Y + other.Y);
			}
			const vector2d<T> operator+(const dimension2d<T>& other)
			{
				return vector2d<T>(this->X + other.Width, this->Y + other.Height);
			}
			vector2d<T>& operator+=(const T val)
			{
				this->X += val; this->Y += val;
				return *this;
			}
			vector2d<T>& operator+=(const vector2d<T>& other)
			{
				this->X += other.X;
				this->Y += other.Y;
				return *this;
			}
			vector2d<T>& operator+=(const dimension2d<T>& other)
			{
				this->X += other.Width;
				this->Y += other.Height;
				return *this;
			}
			//-
			const vector2d<T> operator-(const T val)
			{
				return vector2d<T>(this->X - val, this->Y - val);
			}
			const vector2d<T> operator-(const vector2d<T>& other)
			{
				return vector2d<T>(this->X - other.X, this->Y - other.Y);
			}
			const vector2d<T> operator-(const dimension2d<T>& other)
			{
				return vector2d<T>(this->X - other.Width, this->Y - other.Height);
			}
			vector2d<T>& operator-=(const T val)
			{
				this->X -= val; this->Y -= val;
				return *this;
			}
			vector2d<T>& operator-=(const vector2d<T>& other)
			{
				this->X -= other.X;
				this->Y -= other.Y;
				return *this;
			}
			vector2d<T>& operator-=(const dimension2d<T>& other)
			{
				this->X -= other.Width;
				this->Y -= other.Height;
				return *this;
			}
			//*
			const vector2d<T> operator*(const T rhs)
			{
				return vector3d<T>(this->X* rhs, this->Y* rhs);
			}
			const vector2d<T> operator*(const vector2d<T>& rhs)
			{
				return vector3d<T>(this->X* rhs.X, this->Y* rhs.Y);
			}
			vector2d<T>& operator*=(const T val)
			{
				this->X *= val;
				this->Y *= val;
				return *this;
			}
			vector2d<T>& operator*=(const vector2d<T>& other)
			{
				this->X *= other.X;
				this->Y *= other.Y;
				return *this;
			}

			const vector2d<T> operator/(const T rhs)
			{
				//	return this->operator*(1 / rhs);
				return vector3d<T>(this->X / rhs, this->Y / rhs);
			}
			vector2d<T> operator/=(const T val)
			{
				this->X /= val;
				this->Y /= val;
				return *this;
			}
			//!func getLength
			T getLength()const
			{
				//return nrSqrt(X*X + Y*Y, PRECISION_OF_SQORT);
				return (T)sqrt((f64)(X*X + Y*Y));
			}
			//!func getLenghtSQ
			T getLengthSQ()const
			{
				return X*X + Y*Y;
			}

			//! sort in order X,Y.Equality with rounding olerance.
			bool operator<=(const vector2d<T>& other)const
			{
				return (X < other.X || core::equals(X, other.X)) ||
					(core::equals(X, other.X) && (Y < other.Y || core::equals(Y, other.Y)));
			}
			bool operator>=(const vector2d<T>& other)const
			{
				return (X > other.X || core::equals(X, other.X)) ||
					(core::equals(X, other.X) && (Y > other.Y || core::equals(Y, other.Y)));
			}
			//! sort in X,Y.Difference must be in rounding tolerance.
			bool operator<(const vector2d<T>& other)const
			{
				return (X < other.X || !core::equals(X, other.X)) ||
					(core::equals(X, other.X) && (Y < other.Y && !core::equals(Y, other.Y)));
			}
			bool operator>(const vector2d<T>& other)const
			{
				return (X > other.X || !core::equals(X, other.X)) ||
					(core::equals(X, other.X) && (Y > other.Y && !core::equals(Y, other.Y)));
			}
			bool operator==(const vector2d<T>& other)const
			{
				return equals(other);
			}
			bool operator!=(const vector2d<T>& other)const
			{
				return !equals(other);
			}
			bool equals(const vector2d<T>& other)const
			{
				return core::equals(X, other.X) && core::equals(Y, other.Y);
			}

			vector2d<T>& set(T nx, T ny)
			{
				X = nx; Y = ny;
				return *this;
			}
			vector2d<T>& set(const vector2d<T>& other)
			{
				X = other.X; Y = other.Y;
				return *this;
			}
			//!a*b =|a|*|b|*cos($)
			T dotProduct(const vector2d<T>& other)const
			{
				return X*other.X + Y*other.Y;
			}
			//! Gets distance from another point.
			/** Here, the vector is interpreted as a point in 2-dimensional space.
			\param other Other vector to measure from.
			\return Distance from other point. */
			T getDistanceFrom(const vector2d<T>& other)const
			{
				return vector2d<T>(X - other.X, Y - other.Y).getLength();
			}
			T getDistanceFromSQ(const vector2d<T>& other)const
			{
				return vector2d<T>(X - other.X, Y - other.Y).getLengthSQ();
			}

			/*!Rotate around a point by an degrees
			*/
			vector2d<T>& rotateBy(f64 degrees, const vector2d<T>& center = vector2d<T>())
			{
				const f64 sn = sin(degrees);
				const f64 cs = cos(degrees);
				X -= center.X;
				Y -= center.Y;
				set((T)(X*cs - Y*sn), (T)(X*sn + Y*cs));
				X += center.X;
				Y += center.Y;

				return *this;
			}

			vector2d<T>& normalize()
			{
				f32 len = this->getLengthSQ();
				if (0 == len)
					return *this;
				f32 invlen = core::invSqrtf(len);//core::reciprocal_squareroot(len);//?
				X = (T)X*invlen;
				Y = (T)Y*invlen;
				return *this;
			}

			/*!Get the degree between this and (1,0),anticlockwise
			*0 is to the right (3 o'clock)
			*/
			inline f64 getAngleTrig()const
			{
				if (Y == 0)
					return (X >= 0) ? 0 : 180;
				else if (X == 0)
					return (Y >= 0) ? 90 : 270;

				if (Y > 0)
				{
					if (X > 0)
						return atan((f64)Y / (f64)X)*RADTODEG64;
					else
						return 180 - atan((f64)Y / (-(f64)X))*RADTODEG64;
				}
				else
				{
					if (X > 0)
						return 360 - atan((-(f64)Y) / (f64)X)*RADTODEG64;
					else
						return 180 + atan((-(f64)Y) / (-(f64)X))*RADTODEG64;
				}
			}

			/*!Get the degree between this and (1,0),clockwise
			*0 is to the right (3 o'clock)
			*/
			inline f64 getAngle()const
			{
				if (Y == 0)
					return (X >= 0) ? 0 : 180;
				else if (X == 0)
					return (Y >= 0) ? 90 : 270;

				f64 tmp = core::CMID(Y / (f64)this->getLength(), -1.0, 1.0);
				const f64 angle = asin((f64)tmp)*RADTODEG64;
				//	const f64 angle = atan(core::squareroot(1 - tmp*tmp) / tmp) * RADTODEG64;
				if (X > 0 && Y > 0)
					return 270.0 + angle;
				else if (X < 0 && Y>0)
					return 180.0 + angle;
				else if (X < 0 && Y < 0)
					return 90.0 + angle;
				else if (X > 0 && Y < 0)
					return angle;

				return angle;
			}

			/*!Get angle with other vector2d
			*Return [0,90]
			*/
			inline f64 getAngleWith(const vector2d<T>& other)const
			{
				f64 tmp = X*other.X + Y*other.Y;
				if (tmp == 0)
					return 90.0;

				tmp = tmp / core::squareroot((f64)((X*X + Y*Y)*(other.X*other.X + other.Y*other.Y)));
				if (tmp < 0)
					tmp = -tmp;
				if (tmp > 1.0)//avoid float-point problem
					tmp = 1.0;
				return atan(sqrt(1 - tmp*tmp) / tmp) * RADTODEG64;
				//return atan(sqrt((f64)1.0 / (f64)(tmp*tmp) - 1.0))*RADTODEG64;
			}

			//! Returns if this vector interpreted as a point is on a line between two other points.
			/*It is assumed that the point is on the line.
			\param begin Beginning vector to compare between.
			\param end Ending vector to compare between.
			\return True if this vector is between begin and end, false if not.
			*/
			bool isBetweenPoints(const vector2d<T>& begin, const vector2d<T>& end) const
			{
				if (begin.X != end.X)
				{
					return ((begin.X <= X && X <= end.X) ||
						(begin.X >= X && X >= end.X));
				}
				else
				{
					return ((begin.Y <= Y && Y <= end.Y) ||
						(begin.Y >= Y && Y >= end.Y));
				}
			}

			//! Return a vector interpolated between this and other by value d
			/*
			\param other vector2
			\param d interpolated value
			\return note it's not normalize
			*note opposite getinterpolated_quadratic
			*/
			vector2d<T> getInterpolated(const vector2d<T>& other, const f64 d)const
			{
				f64 inv = 1.f - d;

				return vector2d<T>((T)(X*d + other.X*inv), (T)(Y*d + other.Y*inv));
			}

			//! Creates a quadratically interpolated vector between this and two other vectors.
			/** \param v2 Second vector to interpolate with.
			\param v3 Third vector to interpolate with (maximum at 1.0f)
			\param d Interpolation value between 0.0f (all this vector) and 1.0f (all the 3rd vector).
			Note that this is the opposite direction of interpolation to getInterpolated() and interpolate()
			\return An interpolated vector. This vector is not modified. */
			vector2d<T> getinterpolated_quadratic(const vector2d<T>& v2, const vector2d<T>& v3, const f64 d) const
			{
				// this*(1-d)*(1-d) + 2 * v2 * (1-d) + v3 * d * d;
				f64 inv = 1.f - d;
				f64 mul0 = inv * inv;
				f64 mul1 = 2.f*d * inv;
				f64 mul2 = d*d;

				return vector2d<T>((T)(X*mul0 + v2.X*mul1 + v3.X*mul2), (T)(Y*mul0 + v2.Y*mul1 + v3.Y*mul2));
			}

			//!Set this vector as the interpolate of two vector a and b by value d
			/* \param a the first vector
			\param b the second vector
			\param d the value tto interpolate with,[0,1]
			Note that this is the opposite direction of interpolation to getinterpolated_quadratic()
			\Return *this An interpolated vector. This vector is not modified.
			*/
			vector2d<T>& getInterpolated(const vector2d<T>& a, const vector2d<T>& b, const f64 d)const
			{
				f64 inv = 1.f - d;
				X = (T)(a.X * d + b.X * inv);
				Y = (T)(a.Y * d + b.Y * inv);
				return *this;
			}


			//X coordinate of vector2d
			T X;
			//Y coordinate of vector2d
			T Y;
		};
		typedef vector2d<f32> vector2df;
		typedef vector2d<s32> vector2di;

		//!avoid scalar*vector2d
		template<class S, class T>
		vector2d<T> operator*(const S scalar, const vector2d<T>& vector)
		{
			return vector * scalar;
		}

		// These methods are declared in dimension2d, but need definitions of vector2d
		template<class T>
		dimension2d<T>::dimension2d(const vector2d<T>& other) :Width(other.X), Height(other.Y) {}

		template<class T>
		bool dimension2d<T>::operator==(const vector2d<T>& other) const
		{
			return Width == other.X&&Height == other.Y;
		}

	}
}
#endif//! __VG_VECTOR2D_H_INCLUDE__