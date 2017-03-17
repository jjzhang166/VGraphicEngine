#ifndef __VG_SL_SDATAGSOUT_H_INCLUDE__
#define __VG_SL_SDATAGSOUT_H_INCLUDE__
#include "ConfigForSL.h"
#include "vgArray.h"
#include "vg_PerVertex.h"
#include "SDataGSInner.h"

namespace vg
{
	namespace sl
	{
		class SDataGSOut :public vg_PerVertex
		{
		public:
			glm::vec4 vg_Position;
			glm::vec4 vg_Color;
			glm::vec2 vg_TexCoord;
			int vg_PrimitiveIDOut;
			int vg_InvocationID;

			E_Primitive_Type OutPrimitiveType;

			SDataGSOut()
			{

			}
			
			virtual void copy(SDataGSInner* gsin)
			{
				vg_Position = gsin->vg_Position;
				vg_PrimitiveIDOut = gsin->vg_PrimitiveIDIn;
				vg_TexCoord = gsin->vg_TexCoord;
				vg_Color = gsin->vg_Color;
				vg_Normal = gsin->vg_Normal;//注意这里没有插值,采用的是最后一个点的法向量
			}
			virtual void reset() override
			{
				vg_PointSize = 1.0f;
			}

		};
	}
}
#endif//! __VG_SL_SDATAGSOUT_H_INCLUDE__