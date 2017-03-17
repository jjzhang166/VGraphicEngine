#ifndef __VG_SL_SDATAFSOUT_H_INCLUDE__
#define __VG_SL_SDATAFSOUT_H_INCLUDE__
#include "ConfigForSL.h"
#include "vgArray.h"
#include "vg_PerVertex.h"

namespace vg
{
	namespace sl
	{
		class SDataFSOut
		{
		public:
			SDataFSOut()
			{

			}

			virtual void reset()
			{
				vg_SampleMask.clear();
			}
			float vg_FragDepth;
			glm::vec4 vg_FragCoord;
			glm::vec4 vg_FragColor;//自定义的
			core::array<int> vg_SampleMask;
		};
	}
}
#endif//! __VG_SL_SDATAGSOUT_H_INCLUDE__