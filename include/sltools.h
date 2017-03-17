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
			*����:
			* �Ƕ������Ǻ���
			* ָ������
			* ��������
			* �������ͽ������
			* ���κ���
			* ������
			* ������ϵ����
			* ��������
			* ������
			* ԭ�Ӽ���������
			* ͼ�κ���
			* ƬԪ������
			* ��������
			* ������ɫ������
			* ��ɫ��������ƺ���
			* ��ɫ���ڴ���ƺ���
			*/

#pragma region �Ƕȼ����Ǻ���

			//! �Ƕ�ת����,degree to radians
			inline float radians(float degrees)
			{
				return core::degToRad(degrees);
			}

			//! �Ƕ�ת����,degree to radians
			inline glm::vec2 radians(const glm::vec2& degrees)
			{
				return glm::vec2(core::degToRad(degrees.x), core::degToRad(degrees.y));
			}

			//! �Ƕ�ת����,degree to radians
			inline glm::vec3 radians(const glm::vec3& degrees)
			{
				return glm::vec3(core::degToRad(degrees.x), core::degToRad(degrees.y)
					, core::degToRad(degrees.z));
			}

			//! �Ƕ�ת����,degree to radians
			inline glm::vec4 radians(const glm::vec4& degrees)
			{
				return glm::vec4(core::degToRad(degrees.x), core::degToRad(degrees.y)
					, core::degToRad(degrees.z), core::degToRad(degrees.w));
			}

			//! ����ת�Ƕ�,randians to degrees
			inline float degrees(const float randians)
			{
				return core::radToDeg(randians);
			}

			//! ����ת�Ƕ�,randians to degrees
			inline glm::vec2 degrees(const glm::vec2 randians)
			{
				return glm::vec2(core::radToDeg(randians.x), core::radToDeg(randians.y));
			}

			//! ����ת�Ƕ�,randians to degrees
			inline glm::vec3 degrees(const glm::vec3 randians)
			{
				return glm::vec3(core::radToDeg(randians.x), core::radToDeg(randians.y),
					core::radToDeg(randians.z));
			}

			//! ����ת�Ƕ�,randians to degrees
			inline glm::vec4 degrees(const glm::vec4 randians)
			{
				return glm::vec4(core::radToDeg(randians.x), core::radToDeg(randians.y),
					core::radToDeg(randians.z), core::radToDeg(randians.w));
			}

			//! �������Һ���,sin(degrees)
			inline float sin(float angle)
			{
				return sinf(degrees(angle));
			}

			//! �������Һ���,sin(degrees)
			inline glm::vec2 sin(glm::vec2 angle)
			{
				return glm::vec2(sin(angle.x),sin(angle.y));
			}

			//! �������Һ���,sin(degrees)
			inline glm::vec3 sin(glm::vec3 angle)
			{
				return glm::vec3(sin(angle.x), sin(angle.y), sin(angle.z));
			}

			//! �������Һ���,sin(degrees)
			inline glm::vec4 sin(glm::vec4 angle)
			{
				return glm::vec4(sin(angle.x), sin(angle.y), sin(angle.z), sin(angle.w));
			}

			//! ���������Һ���,cos(degrees)
			inline float cos(float angle)
			{
				return cosf(degrees(angle));
			}

			//! ���������Һ���,cos(degrees)
			inline glm::vec2 cos(glm::vec2 angle)
			{
				return glm::vec2(cos(angle.x),cos(angle.y));
			}


			//! ���������Һ���,cos(degrees)
			inline glm::vec3 cos(glm::vec3 angle)
			{
				return glm::vec3(cos(angle.x), cos(angle.y), cos(angle.z));
			}


			//! ���������Һ���,cos(degrees)
			inline glm::vec4 cos(glm::vec4 angle)
			{
				return glm::vec4(cos(angle.x), cos(angle.y), cos(angle.z),
					cos(angle.w));
			}



			//! ���������к���,tan(degrees)
			inline float tan(float angle)
			{
				return tanf(degrees(angle));
			}

			//! ���������к���,tan(degrees)
			inline glm::vec2 tan(glm::vec2 angle)
			{
				return glm::vec2(tan(angle.x), tan(angle.y));
			}


			//! ���������к���,tan(degrees)
			inline glm::vec3 tan(glm::vec3 angle)
			{
				return glm::vec3(tan(angle.x), tan(angle.y), tan(angle.z));
			}


			//! ���������к���,tan(degrees)
			inline glm::vec4 tan(glm::vec4 angle)
			{
				return glm::vec4(tan(angle.x), tan(angle.y), tan(angle.z),
					cos(angle.w));
			}


			//! �����η����Һ���,asin(degrees)
			inline float asin(float angle)
			{
				return asinf(degrees(angle));
			}

			//! �����η����Һ���,asin(degrees)
			inline glm::vec2 asin(glm::vec2 angle)
			{
				return glm::vec2(asin(angle.x), asin(angle.y));
			}


			//! �����η����Һ���,asin(degrees)
			inline glm::vec3 asin(glm::vec3 angle)
			{
				return glm::vec3(asin(angle.x), asin(angle.y), asin(angle.z));
			}


			//! �����η����Һ���,asin(degrees)
			inline glm::vec4 asin(glm::vec4 angle)
			{
				return glm::vec4(asin(angle.x), asin(angle.y), asin(angle.z),
					cos(angle.w));
			}

			//! �����η����Һ���,acos(degrees)
			inline float acos(float angle)
			{
				return acosf(degrees(angle));
			}

			//! �����η����Һ���,acos(degrees)
			inline glm::vec2 acos(glm::vec2 angle)
			{
				return glm::vec2(acos(angle.x), acos(angle.y));
			}


			//! �����η����Һ���,acos(degrees)
			inline glm::vec3 acos(glm::vec3 angle)
			{
				return glm::vec3(acos(angle.x), acos(angle.y), acos(angle.z));
			}


			//! �����η����Һ���,acos(degrees)
			inline glm::vec4 acos(glm::vec4 angle)
			{
				return glm::vec4(acos(angle.x), acos(angle.y), acos(angle.z),
					cos(angle.w));
			}

			//! �����η����к���,return y/x < [-PI,P]
			inline float atan(float y,float x)
			{
				if (x == 0 && y == 0)
					return -100.f;
				return atan2f(y, x);
			}

			//! �����η����к���,atan(y/x) return < [-PI/2,PI/2]
			inline float atan(float y_over_x)
			{
				return atanf(y_over_x);
			}

			//! ˫�������Һ���return (e^x-e^(-x))/2
			inline float sinh(float x)
			{
				return sinhf(x);
			}

			//! ˫�������Һ���return (e^x+e^(-x))/2
			inline float cosh(float x)
			{
				return coshf(x);
			}

			//! ˫�������к���return sinh(x)/cosh(x)
			inline float tanh(float x)
			{
				return tanhf(x);
			}

			//! ˫���߷����к���return sinh(x)���溯��
			inline float asinh(float x)
			{
				return asinhf(x);
			}

			//! ˫���߷����к���return cosh(x)���溯��,
			// if x< 1 invalid.
			inline float acosh(float x)
			{
				return acoshf(x);
			}

			//! ˫���߷����к���return tanh(x)���溯��,
			// if x>= 1|| x<= -1 invalid.
			inline float atanh(float x)
			{
				return atanhf(x);
			}

#pragma endregion

#pragma region ָ������

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

			//! return ����(x)
			inline float sqrt(float x)
			{
				return core::carmSqrtf(x);
			}

			//! return ����(x),x need>0
			inline double sqrt(double x)
			{
				return std::sqrt(x);
			}

			//! return 1/����(x),x>0
			inline float inversesqrt(float x)
			{
				return core::invSqrtf(x);
			}

			//! return 1/����(x),x>0
			inline double inversesqrt(double x)
			{
				return 1.0/std::sqrt(x);
			}

#pragma endregion

#pragma region ��������
			
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

			//����...
			inline float max(float a, float b)
			{
				return core::MAX(a, b);
			}
#pragma endregion

#pragma region ��ֵ
			//��ֵ

			inline f32 interp(const f32& x, const f32& y, float t)
			{
				return x + (y - x) * t;
			}
			// ʸ����ֵ��tȡֵ [0, 1]
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


#pragma region ����

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