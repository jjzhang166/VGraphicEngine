#ifndef __VG_EDEVICETYPE_H_INCLUDE__
#define __VG_EDEVICETYPE_H_INCLUDE__
#include "vgTypes.h"


namespace vg
{
	namespace fw
	{
		enum E_DEVICE_TYPE
		{

			//! A device native to Microsoft Windows
			/** This device uses the Win32 API and works in all versions of Windows. */
			EIDT_WIN32,
			EIDT_CONSOLE,
			EIDT_BEST,
		};
	}
}
#endif//! __VG_EDEVICETYPE_H_INCLUDE__