#ifndef __VG_SL_IDEFAULTPERFRAGMENTHANDLESHADER_H_INCLUDE__
#define __VG_SL_IDEFAULTPERFRAGMENTHANDLESHADER_H_INCLUDE__
#include "ISLShaderBase.h"
#include "SDepthTestNode.h"

namespace vg
{
	namespace sl
	{
		class IDefaultPerFragmentHandleShader
		{
		public:

			virtual bool drive()
			{
				vg_Depth = DataFromFS->vg_FragCoord.z;
				vg_Color = DataFromFS->vg_FragColor;
				vg_FragCoord = glm::vec2(DataFromFS->vg_FragCoord.x, DataFromFS->vg_FragCoord.y);
				
				run();

				//Status->DepthBuffer->sortInsert((uint)(vg_FragCoord.x+0.5f),((uint)(vg_FragCoord.y+0.5f)), std::move(depthNode));
				return true;
			}

			
			virtual void run()
			{
				//ºóÐø,blending,pixel	
				//blend();
				//blendAndSetPixels();
				if (depthTest())
				{
					drawPixel();
				}
			}

			virtual void bindDatas(SDataFSOut** fromfs, SSLMachineStatus** status)
			{
				DataFromFS = *fromfs;
				Status = *status;
			}

		private:
			// just 
			/*
			void blend()
			{
				int w = Status->TargetSurface->getWidth();
				int h = Status->TargetSurface->getHeight();
				auto db = Status->DepthBuffer;
				for (int i = 0; i < h; ++i)
				{
					for (int j = 0; j < w; ++j)
					{
						int used = db->getUsed(i, j);
						if (used <= 1)//only 0/1 color continue
							continue;

						//more than 2 color
						glm::vec4 colorBack = db->getSubDataOfIJ(i, j, used-1).color;
						glm::vec4 colorFront(0);
						for (int k = used-2;
							k >= 0; --k)
						{	
							colorFront = db->getSubDataOfIJ(i, j, k).color;
							blendColor2(colorFront, colorBack);
							colorBack = colorFront;
						}
						vr::SDepthTestNode node;
						node.color = colorFront;
						node.zwin = -1.0f;
						db->setForce(i, j, std::move(node));
					}
				}
			}

			void blendAndSetPixels()
			{
				int w = Status->TargetSurface->getWidth();
				int h = Status->TargetSurface->getHeight();
				auto db = Status->DepthBuffer;
				vr::Texture* surface = Status->TargetSurface;
				glm::vec4 color;
				for (int i = 0; i < h; ++i)
				{
					for (int j = 0; j < w; ++j)
					{
						int used = db->getUsed(j,i);
						if (used <= 0)//only 0 color continue
							continue;
						else if (used == 1)
						{
							// just 1 color here
							color = db->getSubDataOfIJ(j,i, 0).color;
							surface->setPixel(j,i, color, false);
						}
						//more than 2 color
						else
						{
							color = db->getSubDataOfIJ(j, i, used-1).color;
							surface->setPixel(j, i, color, false);
							for (int k = used-2;
								k >=0;--k)
							{
								color = db->getSubDataOfIJ(j,i, k).color;

								surface->setPixel(j,i, color, true);
							}
						}			
					}
				}
			}
			*/

			glm::vec4 blendColor(glm::vec4& Dst, glm::vec4& Src)
			{
				glm::vec4 color;
				color.r = Dst.r*Dst.a + Src.r*Src.a*(1.0f - Dst.a);
				color.g = Dst.g*Dst.a + Src.g*Src.a*(1.0f - Dst.a);
				color.b = Dst.b*Dst.a + Src.b*Src.a*(1.0f - Dst.a);
				color.a = Src.a + (1.0f - Dst.a)*Src.a;
				return color;
			}

			void blendColor2(glm::vec4& Dst, glm::vec4& Src)
			{
				Dst.r = Src.r*Src.a + Dst.r*(1.0f - Src.a);
				Dst.g = Dst.g*Src.a + Dst.g*(1.0f - Dst.a);
				Dst.b = Dst.b*Src.a + Dst.b*(1.0f - Src.a);
			}

			bool depthTest()
			{
				if (vg_FragCoord.y > Status->DepthBuffer->height ||
					vg_FragCoord.x > Status->DepthBuffer->width)
					return false;
				float* buffer = Status->DepthBuffer->zBuffer[vg_FragCoord.y];
				if (vg_Depth >= buffer[vg_FragCoord.x])
				{
					buffer[vg_FragCoord.x] = vg_Depth;
					return true;
				}

				return false;
			}

			void drawPixel()
			{
				Status->TargetSurface->setPixel(vg_FragCoord.x, vg_FragCoord.y, vg_Color, false);
			}


		protected:
			SSLMachineStatus* Status;
			//vr::SDepthTestNode depthNode;
			glm::vec4 vg_Color;
			float vg_Depth;
			glm::ivec2 vg_FragCoord;
			SDataFSOut* DataFromFS;

		};
	}
}

#endif//! __VG_SL_IDEFAULTPERFRAGMENTHANDLESHADER_H_INCLUDE__