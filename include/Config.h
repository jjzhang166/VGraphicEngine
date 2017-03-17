#ifndef __VGRAPHICENGINE_CONFIG_H_INCLUDE__
#define __VGRAPHICENGINE_CONFIG_H_INCLUDE__

#include <iostream>

#ifndef _DEBUG
#define _DEBUG
#endif

#define VG_WINDOWS_API

#define MAX_COLORS_PALETTE  256

#define VG_SDK_VERSION_STRING  "0.0.0"




//#define _VG_SOLARIS_PLATFORM

//! WIN32 for Windows32
//! WIN64 for Windows64
// The windows platform and API support SDL and WINDOW device
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define _VG_WINDOWS_
#define _VG_WINDOWS_API_
#define _VG_COMPILE_WITH_WINDOWS_DEVICE_
#endif

//断言
#ifdef _DEBUG
#ifndef ASSERT_LEVEL 
//断言等级设置
//分6级
/*enum EnumAssertLevel
{
EAL_CLOSE = 0,//关闭
EAL_OPENALL =1,//开启所有
EAL_PROPETY = 2,//资源型
EAL_MEMALLOC = 5,//内存分配型
};*/
#define EAL_CLOSE  0//关闭
#define EAL_OPENALL  1//开启所有
#define EAL_PROPETY 2//资源型
#define EAL_WARNING 3//warning
#define EAL_ERROR 4//error
#define EAL_MEMALLOC  5//内存分配型

#define ASSERT_LEVEL EAL_OPENALL
#endif
//类型检查设置
#else

#endif

#define VGRAPHIC_EXPORTS

#define _VG_COMPILE_WITH_HALFSOFTWARE_

#ifndef _VG_STATIC_LIB_
#ifdef VGRAPHIC_EXPORTS
#define VGRAPHIC_API __declspec(dllexport)
#else
#define VGRAPHIC_API __declspec(dllimport)
#endif // IRRLICHT_EXPORT
#else
#define VGRAPHIC_API
#endif // _IRR_STATIC_LIB_

// Declare the calling convention.
#if defined(_STDCALL_SUPPORTED)
#define IRRCALLCONV __stdcall
#else
#define VGCALLCONV __cdecl
#endif // STDCALL_SUPPORTED


#endif//! __VGRAPHICENGINE_CONFIG_H_INCLUDE__