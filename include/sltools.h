#ifndef __VG_SL_MATH_H_INCLUDE__
#define __VG_SL_MATH_H_INCLUDE__
#include "vgMath.h"
#include "ConfigForSL.h"
#include <math.h>
#include "SSLMachineStatus.h"

namespace vg
{
	namespace sl
	{
		namespace tools
		{
			//
			/**
			*包括:
			* 角度与三角函数
			* 指数函数
			* 公共函数
			* 浮点打包和解包函数
			* 几何函数
			* 矩阵函数
			* 向量关系函数
			* 整数函数
			* 纹理函数
			* 原子计数器函数
			* 图形函数
			* 片元处理函数
			* 噪声函数
			* 几何着色器函数
			* 着色器请求控制函数
			* 着色器内存控制函数
			*/

#pragma region 角度及三角函数

			//! 角度转弧度,degree to radians
			inline float radians(float degrees)
			{
				return core::degToRad(degrees);
			}

			//! 角度转弧度,degree to radians
			inline glm::vec2 radians(const glm::vec2& degrees)
			{
				return glm::vec2(core::degToRad(degrees.x), core::degToRad(degrees.y));
			}

			//! 角度转弧度,degree to radians
			inline glm::vec3 radians(const glm::vec3& degrees)
			{
				return glm::vec3(core::degToRad(degrees.x), core::degToRad(degrees.y)
					, core::degToRad(degrees.z));
			}

			//! 角度转弧度,degree to radians
			inline glm::vec4 radians(const glm::vec4& degrees)
			{
				return glm::vec4(core::degToRad(degrees.x), core::degToRad(degrees.y)
					, core::degToRad(degrees.z), core::degToRad(degrees.w));
			}

			//! 弧度转角度,randians to degrees
			inline float degrees(const float randians)
			{
				return core::radToDeg(randians);
			}

			//! 弧度转角度,randians to degrees
			inline glm::vec2 degrees(const glm::vec2 randians)
			{
				return glm::vec2(core::radToDeg(randians.x), core::radToDeg(randians.y));
			}

			//! 弧度转角度,randians to degrees
			inline glm::vec3 degrees(const glm::vec3 randians)
			{
				return glm::vec3(core::radToDeg(randians.x), core::radToDeg(randians.y),
					core::radToDeg(randians.z));
			}

			//! 弧度转角度,randians to degrees
			inline glm::vec4 degrees(const glm::vec4 randians)
			{
				return glm::vec4(core::radToDeg(randians.x), core::radToDeg(randians.y),
					core::radToDeg(randians.z), core::radToDeg(randians.w));
			}

			//! 三角正弦函数,sin(degrees)
			inline float sin(float angle)
			{
				return sinf(degrees(angle));
			}

			//! 三角正弦函数,sin(degrees)
			inline glm::vec2 sin(glm::vec2 angle)
			{
				return glm::vec2(sin(angle.x),sin(angle.y));
			}

			//! 三角正弦函数,sin(degrees)
			inline glm::vec3 sin(glm::vec3 angle)
			{
				return glm::vec3(sin(angle.x), sin(angle.y), sin(angle.z));
			}

			//! 三角正弦函数,sin(degrees)
			inline glm::vec4 sin(glm::vec4 angle)
			{
				return glm::vec4(sin(angle.x), sin(angle.y), sin(angle.z), sin(angle.w));
			}

			//! 三角形余弦函数,cos(degrees)
			inline float cos(float angle)
			{
				return cosf(degrees(angle));
			}

			//! 三角形余弦函数,cos(degrees)
			inline glm::vec2 cos(glm::vec2 angle)
			{
				return glm::vec2(cos(angle.x),cos(angle.y));
			}


			//! 三角形余弦函数,cos(degrees)
			inline glm::vec3 cos(glm::vec3 angle)
			{
				return glm::vec3(cos(angle.x), cos(angle.y), cos(angle.z));
			}


			//! 三角形余弦函数,cos(degrees)
			inline glm::vec4 cos(glm::vec4 angle)
			{
				return glm::vec4(cos(angle.x), cos(angle.y), cos(angle.z),
					cos(angle.w));
			}



			//! 三角形正切函数,tan(degrees)
			inline float tan(float angle)
			{
				return tanf(degrees(angle));
			}

			//! 三角形正切函数,tan(degrees)
			inline glm::vec2 tan(glm::vec2 angle)
			{
				return glm::vec2(tan(angle.x), tan(angle.y));
			}


			//! 三角形正切函数,tan(degrees)
			inline glm::vec3 tan(glm::vec3 angle)
			{
				return glm::vec3(tan(angle.x), tan(angle.y), tan(angle.z));
			}


			//! 三角形正切函数,tan(degrees)
			inline glm::vec4 tan(glm::vec4 angle)
			{
				return glm::vec4(tan(angle.x), tan(angle.y), tan(angle.z),
					cos(angle.w));
			}


			//! 三角形反正弦函数,asin(degrees)
			inline float asin(float angle)
			{
				return asinf(degrees(angle));
			}

			//! 三角形反正弦函数,asin(degrees)
			inline glm::vec2 asin(glm::vec2 angle)
			{
				return glm::vec2(asin(angle.x), asin(angle.y));
			}


			//! 三角形反正弦函数,asin(degrees)
			inline glm::vec3 asin(glm::vec3 angle)
			{
				return glm::vec3(asin(angle.x), asin(angle.y), asin(angle.z));
			}


			//! 三角形反正弦函数,asin(degrees)
			inline glm::vec4 asin(glm::vec4 angle)
			{
				return glm::vec4(asin(angle.x), asin(angle.y), asin(angle.z),
					cos(angle.w));
			}

			//! 三角形反余弦函数,acos(degrees)
			inline float acos(float angle)
			{
				return acosf(degrees(angle));
			}

			//! 三角形反余弦函数,acos(degrees)
			inline glm::vec2 acos(glm::vec2 angle)
			{
				return glm::vec2(acos(angle.x), acos(angle.y));
			}


			//! 三角形反余弦函数,acos(degrees)
			inline glm::vec3 acos(glm::vec3 angle)
			{
				return glm::vec3(acos(angle.x), acos(angle.y), acos(angle.z));
			}


			//! 三角形反余弦函数,acos(degrees)
			inline glm::vec4 acos(glm::vec4 angle)
			{
				return glm::vec4(acos(angle.x), acos(angle.y), acos(angle.z),
					cos(angle.w));
			}

			//! 三角形反正切函数,return y/x < [-PI,P]
			inline float atan(float y,float x)
			{
				if (x == 0 && y == 0)
					return -100.f;
				return atan2f(y, x);
			}

			//! 三角形反正切函数,atan(y/x) return < [-PI/2,PI/2]
			inline float atan(float y_over_x)
			{
				return atanf(y_over_x);
			}

			//! 双曲线正弦函数return (e^x-e^(-x))/2
			inline float sinh(float x)
			{
				return sinhf(x);
			}

			//! 双曲线余弦函数return (e^x+e^(-x))/2
			inline float cosh(float x)
			{
				return coshf(x);
			}

			//! 双曲线正切函数return sinh(x)/cosh(x)
			inline float tanh(float x)
			{
				return tanhf(x);
			}

			//! 双曲线反正切函数return sinh(x)的逆函数
			inline float asinh(float x)
			{
				return asinhf(x);
			}

			//! 双曲线反余切函数return cosh(x)的逆函数,
			// if x< 1 invalid.
			inline float acosh(float x)
			{
				return acoshf(x);
			}

			//! 双曲线反正切函数return tanh(x)的逆函数,
			// if x>= 1|| x<= -1 invalid.
			inline float atanh(float x)
			{
				return atanhf(x);
			}

#pragma endregion

#pragma region 指数函数

			//! return x^y
			inline float pow(float x, float y)
			{
				return powf(x, y);
			}

			//! return e^x
			inline float exp(float x)
			{
				return expf(x);
			}

			//! return y, = e^x
			inline float log(float x)
			{
				return logf(x);
			}

			//! return 2^x
			inline float exp2(float x)
			{
				return exp2f(x);
			}

			//! return y,x = 2^y
			inline float log2(float x)
			{
				return log2f(x);
			}

			//! return 根号(x)
			inline float sqrt(float x)
			{
				return core::carmSqrtf(x);
			}

			//! return 根号(x),x need>0
			inline double sqrt(double x)
			{
				return std::sqrt(x);
			}

			//! return 1/根号(x),x>0
			inline float inversesqrt(float x)
			{
				return core::invSqrtf(x);
			}

			//! return 1/根号(x),x>0
			inline double inversesqrt(double x)
			{
				return 1.0/std::sqrt(x);
			}

#pragma endregion

#pragma region 公共函数
			
			//! |x|
			template<typename T>
			inline T abs(T x)
			{
				return (x < (T)0) ? -x : x;
			}



			//! x>0,ret =1.0,x=0,ret=0,x<0,ret =-1.0
			inline float sign(float x)
			{
				return (x > 0.f) ? 1.f :
					(core::iszero(x) ? 0.f : -1.f);
			}

			//! x>0,ret =1.0,x=0,ret=0,x<0,ret =-1.0
			inline int sign(int x)
			{
				return (x > 0) ? 1 :
					(x==0 ? 0 : -1);
			}

			//! x>0,ret =1.0,x=0,ret=0,x<0,ret =-1.0
			inline double sign(double x)
			{
				return (x > 0.0) ? 1.0 :
					(core::iszero(x) ? 0.0 : -1.0);
			}

			//! ret <=x
			inline float floor(float x)
			{
				return floorf(x);
			}

			//! ret <=x
			inline double floor(double x)
			{
				return std::floor(x);
			}

			//! ret m,|m|<=|x|
			inline float trunc(float x)
			{
				return truncf(x);
			}

			//! ret m,|m|<=|x|
			inline double trunc(double x)
			{
				return std::trunc(x);
			}

			//待续...
			inline float max(float a, float b)
			{
				return core::MAX(a, b);
			}
#pragma endregion

#pragma region 插值
			//插值

			inline f32 interp(const f32& x, const f32& y, float t)
			{
				return x + (y - x) * t;
			}
			// 矢量插值，t取值 [0, 1]
			inline glm::vec4 interpxyz(const glm::vec4 &x1, const glm::vec4 &x2, float t)
			{
				glm::vec4 z;
				z.x = interp(x1.x, x2.x, t);
				z.y = interp(x1.y, x2.y, t);
				z.z = interp(x1.z, x2.z, t);
				z.w = 1.0f;
				return z;
			}

			inline glm::vec4 interpxyzw(const glm::vec4 &x1, const glm::vec4 &x2, float t)
			{
				glm::vec4 z;
				z.x = interp(x1.x, x2.x, t);
				z.y = interp(x1.y, x2.y, t);
				z.z = interp(x1.z, x2.z, t);
				z.w = interp(x1.w, x2.w, t);
				return z;
			}

			inline float length(const glm::vec3 m)
			{
				return core::carmSqrtf(m.x*m.x + m.y*m.y + m.z*m.z);
			}

			inline glm::vec3 normalize(const glm::vec3 n)
			{
				float len = length(n);
				return glm::vec3(n.x / len, n.y / len, n.z / len);
			}

			inline glm::vec3 normalize(const float x, const float y, const float z)
			{
				return normalize(glm::vec3(x, y, z));
			}

			inline float dot(const glm::vec3 v1, const glm::vec3 v2)
			{
				return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
			}
#pragma endregion


#pragma region 纹理

			/** get the color at coord of the texture whose slot position is slotposition
			* in machine->TexTexIDMap array.*/
			inline glm::vec4 texture2D(SSLMachineStatus** machine, u32 slotPosition,glm::vec2 coord)
			{
				if (*machine && (*machine)->TexTexIDMap&&
					slotPosition < TEX_NUMBER_SUPORT &&
					(*machine)->TexTexIDMap[slotPosition])
					return (*machine)->TexTexIDMap[slotPosition]->getColorf(coord);
				return glm::vec4(1, 0, 0, 1);
			}

#pragma endregion

	
		}

	}
}

#endif//! __VG_SL_MATH_H_INCLUDE__