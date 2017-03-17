#ifndef __VG_SL_SDATAVSINNER_H_INCLUDE__
#define __VG_SL_SDATAVSINNER_H_INCLUDE__
#include "ConfigForSL.h"

namespace vg
{
	namespace sl
	{
		class SDataVSInner
		{
		public:
			int vg_VertexID;
			int vg_InstanceID = 0;

			SDataVSInner()
				:vg_VertexID(0),
				vg_InstanceID(0)
			{

			}

			virtual void reset()
			{
				vg_VertexID = 0;
				vg_InstanceID = 0;
			}
		};
	}
}
#endif