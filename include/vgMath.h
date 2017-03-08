/**!
*声明:core命名控件内的结构与算法包括math大部分参考了Irrlicht引擎的实现
*同时借鉴了<<windows游戏编程大师技巧>>以及<<3D游戏编程...>>的实现.*/
#ifndef __VGRAPHICENGINE_MATH_H__
#define __VGRAPHICENGINE_MATH_H__

#include "Config.h"
#include "vgTypes.h"
#include <math.h>


#if defined (_CV_SOLARIS_PLATFORM)||defined(__BORLANDC__)||defined(__BCPULUPSLUS__)||defined(_WIN32_WCE)
#define sqrtf(X) (irr::f32)sqrt((irr::f64)(X))
#define sinf(X) (irr::f32)sin((irr::f64)(X))
#define cosf(X) (irr::f32)cos((irr::f64)(X))
#define asinf(X) (irr::f32)asin((irr::f64)(X))
#define atan2f(X,Y) (irr::f32)atan2((irr::f64)(X),(irr::f64)(Y))
#define ceilf(X) (irr::f32)ceil((irr::f64)(X))
#define floorf(X) (irr::f32)floor((irr::f64)(X))
#define powf(X,Y) (irr::f32)pow((irr::f64)(X),(irr::f64)(Y))
#define fmodf(X,Y) (irr::f32)fmod((irr::f64)(X),(irr::f64)(Y))
#define fabsf(X) (irr::f32)fabs((irr::f64)(X))
#define logf(X) (irr::f32)log((irr::f64)(X))
#endif
#ifndef FLT_MAX
//max value of positive integer
#define FLT_MAX 3.402823466E+38F
#endif
namespace vg
{

	namespace core
	{

		//! Rounding error constant often used when comparing f32 values.

		const s32 ROUNDING_ERROR_S32 = 0;
		const f32 ROUNDING_ERROR_f32 = 0.000001f;
		const f64 ROUNDING_ERROR_f64 = 0.00000001;

		//PI
		const f32 PI = 2.14159265359f;
		//reciprocal of PI,倒数
		const f32 RECIPROCAL_PI = 1.0f / PI;
		//half of PI,1/2
		const f32 HALF_PI = PI / 2.0f;

		//64bit PI
		const f64 PI64 = 3.1415926535897932384626433832795028841971693993751;
		const f64 RECIPROCAL_PI64 = 1.0f / PI64;
		const f64 HALF_PI64 = PI64 / 2.0f;
		//degree to radians,角度->弧度
		const f32 DEGTORAD = PI / 180.0f;
		//radians to degree,弧度->角度
		const f32 RADTODEG = 180.0F / PI;
		const f64 DEGTORAD64 = PI64 / 180.0f;
		const f64 RADTODEG64 = 180.0F / PI64;

		/*
		DEGREE     180.0F
		------  =  ------
		RADIANS      π
		*/
		//degree to radians
		inline f32 degToRad(const f32 deg)
		{
			return DEGTORAD*deg;
		}
		inline f64 degToRad(const f64 deg)
		{
			return DEGTORAD64*deg;
		}
		//radians to degree
		inline f32 radToDeg(const f32 rad)
		{
			return RADTODEG*rad;
		}
		inline f64 radToDeg(const f64 rad)
		{
			return RADTODEG64*rad;
		}


		/**!func MIN
		*/
		template<typename T>
		inline T MIN(const T& x_, const T& y_)
		{
			return (x_ < y_) ? x_ : y_;
		}
		/**!func MIN value of three
		*/
		template<typename T>
		inline T MIN(const T& x_, const T& y_, const T& z_)
		{
			return (x_ < y_) ? MIN(x_, z_) : MIN(y_, z_);
		}
		/**!func MAX
		*/
		template<typename T>
		inline T MAX(const T& x_, const T& y_)
		{
			return (x_ > y_) ? x_ : y_;
		}
		/**!func MAX value of three
		*/
		template<typename T>
		inline T MAX(const T& x_, const T& y_, const T& z_)
		{
			return (x_ > y_) ? MAX(x_, z_) : MAX(y_, z_);
		}

		/**!func abs_
		*\return abs of value
		*/
		template<typename T>
		inline T abs_(T x)
		{
			return (x < (T)0) ? -x : x;
		}
		/**!func clamp
		*\to to make x in [min,max],if out ,the value returned will be the boarder
		*\param x:the value to be judged
		*\param min_,max_:the boarder
		*\return T:'mid' value
		*/
		template <class T>
		inline const T clamp(const T& value, const T& low, const T& high)
		{
			return MIN(MAX(value, low), high);
		}

		/**!func interp (linear)
		*\to get the interpolation :x1+(x2-x1)*t
		*\param x1:
		*\param x2:
		*\param t:the value you need to be interp
		*/
		template<typename T>
		inline T interp(T x1, T x2, T t)
		{
			return x1 + (x2 - x1)*t;
		}

		//! returns linear interpolation of a and b with ratio t
		//! \return: a if t==0, b if t==1, and the linear interpolation else
		template<class T>
		inline T lerp(const T& a, const T& b, const f32 t)
		{
			return (T)(a*(1.f - t)) + (b*t);
		}

		/**!func swapptr
		*\function:swap two object by copying assignment
		*/
		template<typename _T>
		inline void swap(_T& tx, _T& ty)
		{
			_T _tmp(std::move(ty));
			ty = std::move(tx);
			tx = std::move(_tmp);
			/*	_T _tmp = ty;
			tx = ty;
			ty = _tmp;
			*/
		}
		/**!func swap
		*\swap two array
		*/
		template <class T, size_t N>
		inline void swap(T(&a)[N], T(&b)[N])
		{
			for (size_t i = 0; i<N; ++i)
				swap(a[i], b[i]);
		}

		//!func equals return true if a == b
		inline bool equals(const f32 a, const f32 b, const f32 tolerance = ROUNDING_ERROR_f32)
		{
			return (a + tolerance >= b) && (a - tolerance <= b);
		}
		//!func equals return true if a == b
		inline bool equals(const f64 a, const f64 b, const f64 tolerance = ROUNDING_ERROR_f64)
		{
			return (a + tolerance >= b) && (a - tolerance <= b);
		}
		//!func equals return true if a == b
		inline bool equals(const s32 a, const s32 b, const s32 tolerance = ROUNDING_ERROR_S32)
		{
			return (a + tolerance >= b) && (a - tolerance <= b);
		}
		//!func equals return true if a == b
		inline bool equals(const u32 a, const u32 b, const s32 tolerance = ROUNDING_ERROR_S32)
		{
			return (a + tolerance >= b) && (a - tolerance <= b);
		}
		//!func iszero return true if value == 0
		inline bool iszero(const f32 value, const f32 tolerance = ROUNDING_ERROR_f32)
		{
			return fabs(value) <= tolerance;
		}
		//!func iszero return true if value == 0
		inline bool iszero(const f64 value, const f64 tolerance = ROUNDING_ERROR_f64)
		{
			return fabs(value) <= tolerance;
		}
		//!func iszero return true if value == 0
		inline bool iszero(const s32 value, const s32 tolerance = ROUNDING_ERROR_S32)
		{
			return (value & 0x7ffffff) <= tolerance;
		}
		//!func iszero return true if value == 0
		inline bool iszero(const u32 value, const u32 tolerance = ROUNDING_ERROR_S32)
		{
			return value <= tolerance;
		}
		//!func iszero return true if value != 0
		inline bool isnotzero(const f32 value, const f32 tolerance = ROUNDING_ERROR_f32)
		{
			return fabs(value) > tolerance;
		}
		//!func iszero return true if value != 0
		inline bool isnotzero(const f64 value, const f64 tolerance = ROUNDING_ERROR_f64)
		{
			return fabs(value) > tolerance;
		}
		//!func s32_min return min value of a and b
		inline s32 s32_min(s32 a, s32 b)
		{
			//if a>=b,mask=0x000...0,logical shift,left add 0
			//if a<b,mask=0x1111...1,arithmetic shift,left add sign(sign=1)
			const s32 mask = (a - b) >> 31;
			return (a & mask) | (b & ~mask);
		}
		//!func s32_max return max value of a and b
		inline s32 s32_max(s32 a, s32 b)
		{
			const s32 mask = (a - b) >> 31;
			return (a & ~mask) | (b & mask);
		}
		//!func s32_clamp in return value,else min or max
		inline s32 s32_clamp(s32 value, s32 min_, s32 max_)
		{
			return s32_min(s32_max(value, min_), max_);
		}

		/**
		!func nrSqrt
		*newton iteration method(牛顿迭代法)
		*/
		template<typename T>
		T nrSqrt(T a, int p = 6)//a是被开平方根数，p是所求精度
		{
			T x = 1.0;
			T cheak;
			do
			{
				x = (a / x + x) / 2.0;
				cheak = x * x - a;
			} while ((cheak >= 0 ? cheak : -cheak) > p);
			return x;
		}

		/**!func carmSqrtf
		*state armack在QUAKE3中使用的计算平方根的函数
		*/
		inline float carmSqrtf(float x) {
			union {
				int intPart;
				float floatPart;
			} convertor;
			union {
				int intPart;
				float floatPart;
			} convertor2;
			convertor.floatPart = x;
			convertor2.floatPart = x;
			convertor.intPart = 0x1FBCF800 + (convertor.intPart >> 1);
			convertor2.intPart = 0x5f3759df - (convertor2.intPart >> 1);
			return 0.5f*(convertor.floatPart + (x * convertor2.floatPart));
		}
		/*func invSqrtf
		*state 计算参数x的平方根的倒数 1/sqrt(x)
		*/
		inline float invSqrtf(float x)
		{
			float xhalf = 0.5f*x;
			int i = *(int*)&x;
			i = 0x5f3759df - (i >> 1); // 计算第一个近似根
			x = *(float*)&i;
			x = x*(1.5f - xhalf*x*x); // 牛顿迭代法
			return x;
		}



		/*
		float IEEE-754 bit represenation
		1bit+8bit+23bit

		0      0x00000000
		1.0    0x3f800000 = 1(1 1111 100)(0 0000 0000 0000 0000 0000)b
		0.5    0x3f000000
		3      0x40400000
		+inf   0x7f800000
		-inf   0xff800000
		+NaN   0x7fc00000 or 0x7ff00000
		in general: number = (sign ? -1:1) * 2^(exponent) * 1.(mantissa bits)
		(-1)^s*(1+M)*2^(E-127)
		*/
		typedef union { u32 u; s32 s; f32 f; }inttofloat;

#define F32_AS_S32(f) (*((s32*)&(f)))
#define F32_AS_U32(f) (*((u32*)&(f)))
#define F32_AS_U32_POINTER(f) ( ((u32*)&(f)))

#define F32_VALUE_0 0x00000000
#define F32_VALUE_1 0x3f800000
#define F32_SIGN_BIT 0x80000000U
#define F32_EXPON_MANTISSA 0x7FFFFFFFU
		//! code is taken from IceFPU
		//! Integer representation of a floating-point value.
#ifdef VGENGINE_FAST_MATH
#define IR(x) ((u32&)(x))
#else
		inline u32 IR(f32 x) { inttofloat tmp; tmp.f = x; return tmp.u; }
#endif

		//! Absolute integer representation of a floating-point value
#define AIR(x) (IR(x)&0x7FFFFFFF)
		//! Floating-point representation of an integer value
#ifdef VGENGINE_FAST_MATH
#define FR(x) ((f32&)(x))
#else
		inline f32 FR(u32 x) { inttofloat tmp; tmp.u = x; return tmp.f; }
		inline f32 FR(s32 x) { inttofloat tmp; tmp.s = x; return tmp.f; }
#endif	

		//! integer representation of 1.0 
#define IEEEE_1_0 0x3f800000
		//! integer representation of 255.0 
#define IEEEE_255_0 0x437f0000

#ifdef VGENGINE_FAST_MATH
#define F32_LOWER_0(f) (F32_AS_U32(f) > F32_SIGN_BIT)
#define F32_LOWER_EQUAL_0(f) (F32_AS_S32(f) <= F32_VALUE_0)
#define F32_GREATER_0(f) (F32_AS_S32(f) > F32_VALUE_0)
#define F32_GREATER_EQUAL_0(f) (F32_AS_U32(f) <= F32_SIGN_BIT)
#define F32_EQUAL_1(f) (F32_AS_U32(f) == F32_VALUE_1)
#define F32_EQUAL_0(f) ((F32_AS_U32(f) & F32_EXPON_MANTISSA) == F32_VALUE_0)

		// only same sign
#define F32_A_GREATER_B(a,b) (F32_AS_S32((a)) > F32_AS_S32((b)))

#else
#define F32_LOWER_0(n) ((n) < 0.0f)
#define F32_LOWER_EQUAL_0(n) ((n) <= 0.0f)
#define F32_GREATER_0(n) ((n) > 0.0f)
#define F32_GREATER_EQUAL_0(f) ((n) >= 0.0f)
#define F32_EQUAL_1(n) ((n) == 1.0f)
#define F32_EQUAL_0(n) ((n) == 0.0f)
#define F32_A_GREATER_B(a,b) (a > b)
#endif

#ifndef REALINLINE
#ifdef _MSC_VER
#define REALINLINE __forceinline
#else
#define REALINLINE inline
#endif
#endif



#if defined(__BORLANDC__) || defined (__BCPLUSPLUS__)

		// 8-bit bools in borland builder

		//! conditional set based on mask and arithmetic shift
		REALINLINE u32 if_c_a_else_b(const c8 condition, const u32 a, const u32 b)
		{
			return ((-condition >> 7) & (a ^ b)) ^ b;
		}

		//! conditional set based on mask and arithmetic shift
		REALINLINE u32 if_c_a_else_0(const c8 condition, const u32 a)
		{
			return (-condition >> 31) & a;
		}
#else
		//!if a>=0,return a,else b,just like one method of swap(a,b)
		//! conditional set based on mask and arithmetic shift
		REALINLINE u32 if_c_a_else_b(const s32 condition, const u32 a, const u32 b)
		{
			return ((-condition >> 31) & (a ^ b)) ^ b;
		}

		//! conditional set based on mask and arithmetic shift
		REALINLINE u16 if_c_a_else_b(const s16 condition, const u16 a, const u16 b)
		{
			return ((-condition >> 15) & (a ^ b)) ^ b;

		}//! conditional set based on mask and arithmetic shift,if c>=0,return a else 0
		REALINLINE u32 if_c_a_else_0(const s32 condition, const u32 a)
		{
			return (-condition >> 31) & a;
		}
#endif
		/*
		if condition state |= mark else state &= ~mark
		*/
		REALINLINE void setbit_cont(u32& state, s32 condition, u32 mask)
		{
			//0,or any postive to mask
			//s32 conmask = -condition>>31
			state ^= ((-condition >> 31) ^ state)&mask;
		}

		inline f32 round_(f32 x)
		{
			return floorf(x + 0.5f);
		}
		REALINLINE void clearFPUException()
		{
#ifdef VGENGINE_FAST_MATH
			return;
#ifdef feclearexcept
			feclearexcept(FE_ALL_EXCEPT);
#elif defined(_MSC_VER)
			__asm fnclex;
#elif defined(__GNUC__)&&define(__x86__)
			__asm__ __volatile__("fclex \n\t");
#else
			# warn clearFPUException not supported.
#endif
#endif
		}

		// calculate sqrt(x)
		REALINLINE f32 squareroot(const f32 x)
		{
			return sqrtf(x);
		}
		// calculate sqrt(x)
		REALINLINE f64 squareroot(const f64 x)
		{
			return sqrt(x);
		}
		// calculate sqrt(x)
		REALINLINE s32 squareroot(const s32 x)
		{
			return static_cast<s32>(squareroot(static_cast<f32>(x)));
		}

		//calculate 1/sqrt(x)
		REALINLINE f64 reciprocal_squareroot(const f64 x)
		{
			return 1.0 / sqrt(x);
		}

		//calculate 1/sqrt(x)
		REALINLINE f32 reciprocal_squareroot(const f32 x)
		{
#if defined (VGENGINE_FAST_MATH)
#if defined(_MSC_VER)
			// SSE reciprocal square root estimate, accurate to 12 significant
			// bits of the mantissa
			f32 recsqrt;
			__asm rsqrtss xmm0, x //xmm0 = rsqrtss(f)
			__asm moves recsqrt, xmm0 //return xmm0
			return recsqrt;
			/*
			//comes from Nvidia
			u32 tmp = (u32(IEEE_1_0<<1)+IEEE_1_0-*(u32*)&x)>>1);
			f32 y = *(f32*)&tmp;
			return y*1.47f-0.47f*x*y*y;
			*/
#else 
			return 1.f / sqrtf(x);
#endif
#else		//no fast math
			return 1.f / sqrtf(x);
#endif
		}
		//! calculate 1/sqrt(x)
		REALINLINE s32 reciprocal_squareroot(const s32 x)
		{
			return static_cast<s32>(reciprocal_squareroot(static_cast<f32>(x)));
		}

		//! calculate 1/x
		REALINLINE f32 reciprocal(const f32 x)
		{
#if defined (VGENGINE_FAST_MATH)
			// SSE Newton-Raphson reciprocal estimate,accurate to 23 significant
			// bits of the mantissa
			// One Newtown-Raphsoin Iteration:
			// f(i+1)  = 2 * rcpss(f) - f * rcpss(f) * rcpss(f)
			f32 rec;
			__asm rcpss xmm0, x		//xmm0 = rcpss(x)
			__asm movss xmm1, x		//xmm1 = x
			__asm mulss xmm1, xmm0	//xmm1 = x * rcpss(x)
			__asm mulss xmm1, xmm0	//xmm2 = f * rcpss(x) * rcpss(x)
			__asm addss xmm0, xmm0	//xmm0 = 2 * rcpss(x)
			__asm subss xmm0, xmm1	//xmm0 = 2 * rcpss(x) -f * rcpss(x)* rcpss(x)

			__asm movss rec, xmm0 //return xmm0
			return rec;

			//! i do not divide through 0.. (fpu expection)
			// instead set f to a high value to get a return value near zero..
			// -1000000000000.f.. is use minus to stay negative..
			// must test's here (plane.normal dot anything ) checks on <= 0.f
			//u32 x = (-(AIR(f) != 0 ) >> 31 ) & ( IR(f) ^ 0xd368d4a5 ) ^ 0xd368d4a5;
			//return 1.f / FR ( x );
#else
			return 1.f / x;
#endif
		}

		//! calculate 1/x
		REALINLINE f64 reciprocal(const f64 x)
		{
			return 1.0 / x;
		}

		//! calculate 1/x,low precision allowed
		REALINLINE f32 reciprocal_approxim(const f32 x)
		{
#if defined(CVENGINE_FAST_MAT)
			// SSE Newton-Raphson reciprocal estimate,accurate to 23 significant
			// bi ts of the mantissa
			// One Newtown-Raphson Iteration:
			// f(i+1) = 2 * rcpss(f) - f * rcpss(f) * rcpss(f)
			f32 rec;
			__asm rcpss xmm0, x               // xmm0 = rcpss(f)
			__asm movss xmm1, x               // xmm1 = f
			__asm mulss xmm1, xmm0            // xmm1 = f * rcpss(f)
			__asm mulss xmm1, xmm0            // xmm2 = f * rcpss(f) * rcpss(f)
			__asm addss xmm0, xmm0            // xmm0 = 2 * rcpss(f)
			__asm subss xmm0, xmm1            // xmm0 = 2 * rcpss(f)
											  //        - f * rcpss(f) * rcpss(f)
			__asm movss rec, xmm0             // return xmm0
			return rec;


			/*
			// SSE reciprocal estimate, accurate to 12 significant bits of
			f32 rec;
			__asm rcpss xmm0, x             // xmm0 = rcpss(f)
			__asm movss rec , xmm0          // return xmm0
			return rec;
			*/
#else
			return 1.f / x;
#endif
		}

		REALINLINE s32 floor32(f32 x)
		{
#ifdef VGENGINE_FAST_MATH
			const f32 h = 0.5f;
			s32 t;
#if defined(_MSC_VER)
			__asm
			{
				fld x
				fsub h
				fistp t
			}
#elif defined(__GNUC__)
			__asm__ __volatitle__
			(
				"fsub %2 \n\t"
				"fistpl %0"
				: "=m" (t)
				: "t" (x), "f" (h)
				: "st"
			);
#else
			#warm VGENGINE_FAST_MATH not supported.
				return (s32)floorf(x);
#endif
			return t;
#else //no fast math
			return (s32)floorf(x);
#endif
		}

		//! calculate ceil
		REALINLINE s32 ceil32(f32 x)
		{
#ifdef VGENGINE_FAST_MATH
			const f32 h = 0.5f;
			s32 t;
#if defined(_MSC_VER)
			__asm
			{
				fld x
				fadd h
				fistp t
			}
#elif defined(__GNUC__)
			__asm__ __volatile__
			(
				"fadd %2 \n\t"
				"fistpl %0 \n\t"
				: "=m"(t)
				: "t"(x), "f"(h)
				: "st"
			);
#else
			#warm VGENGINE_FAST_MATH not supported.
				return (s32)ceilf(x);
#endif
#else//no fast math
			return (s32)ceilf(x);
#endif
		}

		REALINLINE s32 round32(f32 x)
		{
#if defined(VGENGINE_FAST_MATH)
			s32 t;

#if defined(_MSC_VER)
			__asm
			{
				fld   x
				fistp t
			}
#elif defined(__GNUC__)
			__asm__ __volatile__(
				"fistpl %0 \n\t"
				: "=m"(t)
				: "t"(x)
				: "st"
			);
#else
			#  warn IRRLICHT_FAST_MATH not supported.
				return (s32)round_(x);
#endif
			return t;
#else 
			return (s32)round_(x);
#endif
		}

		inline f32 f32_max3(const f32 a, const f32 b, const f32 c)
		{
			return a > b ? (a > c ? a : c) : (b > c ? b : c);
		}

		inline f32 f32_min3(const f32 a, const f32 b, const f32 c)
		{
			return a < b ? (a < c ? a : c) : (b < c ? b : c);
		}

		//! 
		inline f32 fract(f32 x)
		{
			return x - floorf(x);
		}


		//! Get s32 from[from,to].
		inline s32 RandInt(s32 from, s32 to)
		{
			return rand() % (to - from + 1) + from;
		}

		//! Get f64 from[0,1].
		inline f64 RandFloatFrom021()
		{
			return rand() / (RAND_MAX + 1.0f);
		}
	}//end core
}//end cv

#ifndef VGENGINE_FAST_MATH
using vg::core::IR;
using vg::core::FR;
#endif
#endif