#ifndef __VG_SL_SDATARASIOUT_H_INCLUDE__
#define __VG_SL_SDATARASIOUT_H_INCLUDE__
#include "ConfigForSL.h"
#include "vgArray.h"


namespace vg
{
	namespace sl
	{
		class SDataRasiOut
		{
		public:

			SDataRasiOut()
			{

			}


			virtual void reset()
			{
				

			}

			//ÓÐ´ýÐÞ¸Ä

			glm::vec4 vg_FragCoord;
			glm::vec3 vg_normal;
			glm::vec2 vg_TexCoord;
			glm::vec4 vg_Color;
			glm::vec3 vg_FragVert;
			bool vg_FrontFacing;
			core::array<float> vg_ClipDistance;
			glm::vec2 vg_PointCoord;
			int vg_PrimitiveID;
			int vg_SampleID;
			glm::vec2 vg_SamplePosition;
			core::array<int> vg_SampleMask;
			int vg_Layer;
			int vg_ViewportIndex;
		};
	}
}
#endif//! __VG_SL_SDATARASIOUT_H_INCLUDE__