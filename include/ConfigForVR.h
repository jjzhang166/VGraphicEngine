#ifndef __VG_SL_CONFIG_FRO_VR_H_INCLUDE__
#define __VG_SL_CONFIG_FRO_VR_H_INCLUDE__
#include "Config.h"

namespace vg
{
	namespace vr
	{
#define DEPTH_BUFFER_WIDTH 1024
#define DEPTH_BUFFER_HEIGHT 1024
#define DEPTH_BUFFER_DEPTH 8
#define TEX_NUMBER_SUPORT 128
		//8bit
		typedef unsigned char VGuchar;
		typedef unsigned char VGboolean;
		typedef signed char VGchar;

		//16bit
		typedef unsigned short VGushort;
		typedef signed short VGshort;

		//32bit
		typedef unsigned int VGuint;
		typedef signed int VGint;
		typedef signed int VGsizei;


		//float
		typedef float VGfloat;
		typedef double VGdouble;

		//64bit
		typedef unsigned long long VGulong;
		typedef long long VGlong;


	}
}
#endif//! __VG_SL_CONFIG_FRO_VR_H_INCLUDE__