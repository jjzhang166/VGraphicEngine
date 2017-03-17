#ifndef __VG_SL_SDATAGSINNER_H_INCLUDE__
#define __VG_SL_SDATAGSINNER_H_INCLUDE__
#include "ConfigForSL.h"
#include "vgArray.h"
#include "vg_PerVertex.h"

namespace vg
{
	namespace sl
	{
		class SDataGSInner
		{
		public:
			core::array<vg_PerVertex> vg_in;
			glm::vec4 vg_Position;
			glm::vec4 vg_Color;
			glm::vec2 vg_TexCoord;
			glm::vec3 vg_Normal;
			int vg_PrimitiveIDIn;
			int vg_InvocationID;
			SDataGSInner()
			{

			}

			virtual void reset()
			{
				vg_in.clear();
			}
		};
	}
}
#endif//! __VG_SL_SDATAGSIN_H_INCLUDE__