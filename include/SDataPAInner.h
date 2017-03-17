#ifndef __VG_SL_SDATAPAINNER_H_INCLUDE__
#define __VG_SL_SDATAPAINNER_H_INCLUDE__
#include "ConfigForSL.h"

namespace vg
{
	namespace sl
	{
		class SDataPAInner
		{
		public:
			vg_PerVertex Vertex;

			void copy(SDataVSOut* vsout)
			{
				Vertex = *vsout;
			}


		};
	}
}

#endif        