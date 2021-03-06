// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __VG_DIMENSION2D_H_INCLUDE__
#define __VG_DIMENSION2D_H_INCLUDE__

#include "vgTypes.h"
#include "vgMath.h"
namespace vg
{
	namespace core
	{
		template<typename T>
		class vector2d;

		/**!template dimension
		*/
		template<typename T>
		class dimension2d
		{
		public:
			dimension2d() :Width(0), Height(0) {}
			dimension2d(const T width, const T height) :Width(width), Height(height) {}
			dimension2d(const T &other) :Width(other.Width), Height(other.Height) {}
			dimension2d(const vector2d<T>& other);//Defined in vector2d.h

												  //! Use this constructor only where you are sure that the conversion is valid.
			template<class U>
			explicit dimension2d(const dimension2d<U>& other)
				:Width((T)other.Width), Height((T)other.Height) {}

			template<class U>
			dimension2d<T>& operator=(const dimension2d<U>& other)
			{
				Width = (T)other.Width;
				Height = (T)other.Height;
				return *this;
			}

			//! Equality operator
			bool operator==(const dimension2d<T>& other)const
			{
				return core::equals(Width, other.Width) &&
					core::equals(Height, other.Height);
			}

			bool operator==(const vector2d<T>& other)const;//Defined in vector2d.h

														   //! Inequaliyt operator
			bool operator!=(const dimension2d<T>& other)const
			{
				return !(*this == other);
			}
			bool operator!=(const vector2d<T>& other)const
			{
				return !(*this == other);
			}

			//! Set values
			dimension2d<T>& set(const T& width, const T& height)
			{
				Width = widht;
				Height = height;
				return *this;
			}

			//! operator/= , div by scalar
			dimension2d<T>& operator/=(const T& scale)
			{
				Width /= scale;
				Height /= scale;
				return *this;
			}
			//! operator/,div by scalar
			dimension2d<T> operator/(const T& scale)
			{
				return dimension2d<T>(Width / scale, Height / scale);
			}

			//! operator *=,multiply by scalar
			dimension2d<T>& operator*=(const T& scale)const
			{
				Width *= scale;
				height *= scale;
				return *this;
			}

			//! operator* ,multiply by scalar
			dimension2d<T> operator*(const T& scale)
			{
				return dimension2d<T>(Width*scale, Height*scale);
			}

			//! operator+=,add another dimension to this
			dimension2d<T>& operator+=(const dimension2d<T>& other)
			{
				Widht += other.Width;
				Height += other.Height;
				return *this;
			}

			//! operator-=,subtract a dimension from this
			dimension2d<T>& operator-=(const dimension2d<T>* other)
			{
				Width -= other.Width;
				Height -= other.Height;
				return *this;
			}

			//! operator+ ,add two dimensions
			dimension2d<T> operator+(const dimension2d<T>& other)const
			{
				return dimension2d<T>(Widht + other.Width, Height + other.Height);
			}

			//! Get area
			T getArea()const
			{
				return Width*Height;
			}

			//! Get this optimal size according to some properties
			/** This is a function often used for texture dimension
			calculation which is a power-of-two dimension
			(2^n,2^m) and/or square (Widht=Height).
			\param requirePowerOfTwo Forces the result to use only
			powers of two as values.
			\param requireSquare makes width=height in the result
			\param larger Choose whether the result is larger or
			need not be changed it is kept with any vlaue of larger.
			\param maxValue Maximum texturesize.if value>0 size is
			clamped to maxValue
			\return The optimal dimension under given
			constraints.
			*/
			dimension2d<T> getOptimalSize(
				bool requirePowerOfTwo = true,
				bool requireSquare = false,
				bool larger = true,
				u32 maxValue = 0)const
			{
				u32 i = 1, j = 1;
				if (requirePowerOfTwo)
				{
					while (i < (u32)Width)
						i <<= 1;//i*=2
					if (!larger && i != 1 && i != (u32)Width)
						i >>= 1;//i/=2
					while (j < (u32)Width)
						j <<= 1;
					if (!larger && j != 1 && j != (u32)Width)
						j >>= 1;
				}
				else
				{
					i = (u32)Width;
					j = (u32)Height;
				}

				if (requireSquare)
				{
					if ((larger && (i > j)) || (!larger && (i < j)))
						j = i;
					else
						i = j;
				}

				if (maxValue > 0 && i > maxValue)
					i = maxValue;
				if (maxValue > 0 && j > maxValue)
					j = maxValue;

				return dimension2d<T>((T)i, (T)j);
			}

			//! Get the interpolated dimension
			/**\param other Other dimension to interpolate with.
			\param d Valule [0,1]
			\return Interpolated dimension.
			*/
			dimension2d<T> getInterpolated(const dimension2d<T>& other, f32 d)const
			{
				f32 inv = 1.f - d;
				return dimension2d<T>((T)(Width*d + other.Width*inv), (T)(Height*d + other.Height*inv));
			}

			//! Width of the dimension.
			T Width;
			//! Height of the dimension.
			T Height;
		};

		typedef dimension2d<f32> dimension2df;
		/** There are few cases where negative dimensions make sense. Please consider using
		dimension2du instead. */
		typedef dimension2d<s32> dimension2di;
		typedef dimension2d<u32> dimension2du;
	}
}
#endif//! 