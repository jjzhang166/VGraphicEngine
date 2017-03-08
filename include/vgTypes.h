#ifndef __CJ_TYPE_H__
#define __CJ_TYPE_H__
#include "Config.h"
namespace vg
{
	//8bit
	typedef unsigned char u8;
	typedef signed char s8;
	typedef char c8;

	//16bit
	typedef unsigned short u16;
	typedef signed short s16;

	//32bit
	typedef unsigned int u32;
	typedef signed int s32;

	//64bit
	typedef unsigned long long u64;
	typedef long long s64;

	//float
	typedef float f32;
	typedef double f64;


	namespace core
	{
		enum { PRECISION_OF_SQORT = 6 };
	}

#if defined(_CV_WCHAR_FILESYSTEM)
	typedef wchar_t fschar_t;
#else
	typedef char fschar_t;
#endif
	//! Defines a deprecated macro which generates a warning at compile time
	/** The usage is simple
	For typedef:		typedef _cv_DEPRECATED_ int test1;
	For classes/structs:	class _cv_DEPRECATED_ test2 { ... };
	For methods:		class test3 { _cv_DEPRECATED_ virtual void foo() {} };
	For functions:		template<class T> _cv_DEPRECATED_ void test4(void) {}
	**/
#if defined(IGNORE_DEPRECATED_WARNING)
#define _CJ_DEPRECATED_
#elif _MSC_VER >= 1310 //vs 2003 or higher
#define _CV_DEPRECATED_ __declspec(deprecated)
#elif (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1)) // all versions above 3.0 should support this feature
#define _CV_DEPRECATED_  __attribute__ ((deprecated))
#else
#define _CV_DEPRECATED_
#endif



	//! Defines a small statement to work around a microsoft compiler bug.
	/** The microsoft compiler 7.0 - 7.1 has a bug:
	When you call unmanaged code that returns a bool type value of false from managed code,
	the return value may appear as true. See
	http://support.microsoft.com/default.aspx?kbid=823071 for details.
	Compiler version defines: VC6.0 : 1200, VC7.0 : 1300, VC7.1 : 1310, VC8.0 : 1400*/
#if defined(_IRR_WINDOWS_API_) && defined(_MSC_VER) && (_MSC_VER > 1299) && (_MSC_VER < 1400)
#define _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX __asm mov eax,100
#else
#define _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX
#endif // _IRR_MANAGED_MARSHALLING_BUGFIX

#pragma warning(disable:4996)

	// disable truncated debug information warning in visual studio 6 by default
#if defined(_MSC_VER) && (_MSC_VER < 1300 )
#pragma warning( disable: 4786)
#endif // _MSC

	//! creates four CC codes used in cvlicht for simple ids
	/** some compilers can create those by directly writing the
	code like 'code', but some generate warnings so we use this macro here */
#define MAKE_VG_ID(c0, c1, c2, c3) \
		((cv::u32)(cv::u8)(c0) | ((cv::u32)(cv::u8)(c1) << 8) | \
		((cv::u32)(cv::u8)(c2) << 16) | ((cv::u32)(cv::u8)(c3) << 24 ))



#ifdef _DEBUG
#define _VG_DEBUG_BREAK_IF(_CONDITION_)	if(_CONDITION_)	{_asm int 3	}
#endif


}

#endif