#ifndef __CJ_EDRIVERTYPES_H__
#define __CJ_EDRIVERTYPES_H__
#include "vgTypes.h"

namespace vg
{
	namespace fw
	{
		enum E_DRIVER_TYPE
		{
			//! Null driver, useful for applications to run the engine without visualisation.
			/** The null device is able to load textures, but does not
			render and display any graphics. */
			EDT_NULL,
			/*! Soft ware
			*/
			EDT_SOFTWARE,
			/*! Half soft ware
			This means that the use of DX or OpenGl drive,but use  own algorithms
			*/
			EDT_HALFSOFTWARE,
			/*
			*/
			EDT_DIRECT3D8,
			/*
			*/
			EDT_DIRECT3D9,
			/*
			*/
			EDT_OPENGL,
			/*
			*/
			EDT_COUNT,

		};
		enum DD_PIXEL_FORMAT
		{
			DD_PIXEL_FORMAT8 = 8,
			DD_PIXEL_FORMAT555 = 15,
			DD_PIXEL_FORMAT565 = 16,
			DD_PIXEL_FORMAT888 = 24,
			DD_PIXEL_FORMATALPHA888 = 32
		};
	}//end video
}//end cj
#endif