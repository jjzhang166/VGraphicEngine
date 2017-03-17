#ifndef __VG_SL_VGVERTEX_H_INCLUDE__
#define __VG_SL_VGVERTEX_H_INCLUDE__
#include "ConfigForSL.h"
#include "vgArray.h"

namespace vg
{
	namespace sl
	{
		class vg_PerVertex
		{
		public:
			glm::vec4 vg_Position;
			glm::vec2 vg_TexCoord;
			glm::vec4 vg_Color = glm::vec4(0,0,0,0);
			glm::vec3 vg_Normal;
			float vg_PointSize;
			core::array<float> vg_ClipDistance;

			vg_PerVertex()
				:vg_PointSize(1.0f)
			{

			}
			virtual void reset()
			{
				vg_PointSize = 1.0f;
				vg_Normal = glm::vec3(0, -1, 0);
				vg_ClipDistance.clear();
			}
		};
	}
}
#endif