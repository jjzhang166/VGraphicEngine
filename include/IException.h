#ifndef __VG_IEXCEPTION_H_INCLUDE__
#define __VG_IEXCEPTION_H_INCLUDE__
#include "Config.h"
#include "vgTypes.h"

namespace vg
{
	namespace io
	{
		class IException
		{
		public:
			virtual bool handleException()
			{

				return true;
			}
		};
	}
}


#endif//! __VG_IEXCEPTION_H_INCLUDE__