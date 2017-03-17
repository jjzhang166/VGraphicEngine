#ifndef __VG_SL_SDATAFSINNER_H_INCLUDE__
#define __VG_SL_SDATAFSINNER_H_INCLUDE__
#include "ConfigForSL.h"
#include "vgArray.h"
#include "vg_PerVertex.h"

namespace vg
{
	namespace sl
	{
		class SDataFSInner
		{
		public:
			SDataFSInner()
			{

			}

			virtual void reset()
			{

			}

			glm::vec4 vg_FragCoord;
			glm::vec3 vg_Normal;
			glm::vec2 vg_TexCoord;
			glm::vec3 vg_FragVert;
			glm::vec4 vg_Color = glm::vec4(0, 0, 0, 0);
			bool vg_FrontFacing;
			core::array<float> vg_ClipDistance;
			glm::vec2 vg_PointCoord;
			int vg_PrimitiveID;
			int vg_SampleID;
			glm::vec2 vg_SamplePosition;
			int vg_Layer;
			int gl_ViewportIndex;
		};
	}
}
#endif//! __VG_SL_SDATAGSIN_H_INCLUDE__