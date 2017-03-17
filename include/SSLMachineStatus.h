#ifndef __VG_SL_MACHINESTATUS_H_INCLUDE__
#define __VG_SL_MACHINESTATUS_H_INCLUDE__
#include "ConfigForSL.h"
#include "Texture.h"
//#include "SDepthTestNode.h"
#include "SSingleDepthBuffer.h"
namespace vg
{
	namespace sl
	{
		class SSLMachineStatus
		{
		public:
			SSLMachineStatus()
			{
			}
			void reset()
			{

			}

			void updateViewAlhpa()
			{
				if (!TargetSurface)
					return;
				float width = (float)TargetSurface->getWidth();
				float height = (float)TargetSurface->getHeight();
				ViewPortAttributes.alphax = width / (ViewPortAttributes.xmax - 
					ViewPortAttributes.xmin);
				ViewPortAttributes.alphay1 = height*(1.0f - 
					ViewPortAttributes.ymin / (ViewPortAttributes.ymax - ViewPortAttributes.ymin));
				ViewPortAttributes.alphay2 = height / (ViewPortAttributes.ymax - ViewPortAttributes.ymin);
			}

			void setViewPort(float xmin, float ymin, float xmax, float ymax)
			{
				ViewPortAttributes.xmin = xmin;
				ViewPortAttributes.xmax = xmax;
				ViewPortAttributes.ymin = ymin;
				ViewPortAttributes.ymax = ymax;
				updateViewAlhpa();
			}

		public:
			int PrimPointsCount;

			vg::vr::Texture* TargetSurface;

			//eg:(0,0,1,1)->meaas:leftdown(0,0),righttop(width,height)
			struct
			{
				/**
				* x' = w/(xmax-xmin)(x-xmin) = alphax*(x-xmin)
				* y' = h(1-ymin(ymax-ymin))-(h/(ymax-ymin))*y=alphay1-alphay2*y
				* 窗口的坐标系为:左上角(0,0),右下角(w,h)
				* 
				*/
				float xmin, ymin, xmax, ymax;
				float alphax, alphay1, alphay2;
			}ViewPortAttributes;

			//core::mularray<vr::SDepthTestNode>* DepthBuffer;
			vr::SSingleDepthBuffer* DepthBuffer;

			vr::Texture** TexTexIDMap;

		};
	}
}

#endif//! __VG_SL_MACHINESTATUS_H_INCLUDE__