#ifndef __VGRAPHICENGINE_CONFIG_H_INCLUDE__
#define __VGRAPHICENGINE_CONFIG_H_INCLUDE__
#include <iostream>

#define VG_SDK_VERSION_STRING  "VGraphicEngine version 0.0.0"

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


#endif//! __VGRAPHICENGINE_CONFIG_H_INCLUDE__