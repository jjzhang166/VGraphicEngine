#ifndef __VG_SL_SDATAPAOUT_H_INCLUDE__
#define __VG_SL_SDATAPAOUT_H_INCLUDE__
#include "ConfigForSL.h"

namespace vg
{
	namespace sl
	{
		class SDataPAOut
		{
		public:
			void reset()
			{

			}
			core::array<vg_PerVertex> pa_out;
			int vg_PrimitiveID;
			int vg_Layer;
			int vg_ViewportIndex;
		};
	}
}

#endif        