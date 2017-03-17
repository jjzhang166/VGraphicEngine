#ifndef __VG_SL_PERFRAGHANDLEINNER_H_INCLUDE__
#define __VG_SL_PERFRAGHANDLEINNER_H_INCLUDE__
#include "ConfigForSL.h"
#include "vgArray.h"
#include "vg_PerVertex.h"

namespace vg
{
	namespace sl
	{
		class SDataPerFragHandleInner
		{
		public:
			glm::vec4 vg_FragColor;
			glm::vec4 vg_FragCoord;
		};
	}
}
#endif//! __VG_SL_PERFRAGHANDLEIN_H_INCLUDE__