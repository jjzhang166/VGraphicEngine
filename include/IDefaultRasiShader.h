/**
* Rasterization algorithm in this paper from the mini3d.weiyixiao.zhihu.
* And he owns copyright.
*/
#ifndef __VG_SL_IDEFAULTRASISHADER_H_INCLUDE__
#define __VG_SL_IDEFAULTRASISHADER_H_INCLUDE__
#include "ConfigForSL.h"
#include "TransferDatas.h"
#include "ISLShaderBase.h"
#include "IFragmentShaderBase.h"
#include "vg_PerVertex.h"
#include "sltools.h"

namespace vg
{
	namespace sl
	{
		struct SVertexInner
		{
			glm::vec4 pos; glm::vec3 normal; glm::vec2 tc; glm::vec4 color; float rhw;
		};

		struct SEdgeInner { SVertexInner v, v1, v2; } ;
		struct STrapezoidInner { float top, bottom; SEdgeInner left, right; } ;

		struct SScanlineInner { SVertexInner v, step; int x, y, w; } ;

		class IDefaultRasiShader
		{
		public:
			IDefaultRasiShader()
				:PointCount(0)
			{

			}
			virtual void bindDatas(	SDataGSOut** fromgs, 
				SDataRasiOut** tofs,SSLMachineStatus** status)
			{
				Status = *status;
				DataFromGs = *fromgs;
				DataToFs = *tofs;
			}

			virtual bool drive() 
			{
				//Todo
				Vertexs[PointCount].pos = DataFromGs->vg_Position;
				Vertexs[PointCount].tc = DataFromGs->vg_TexCoord;
				Vertexs[PointCount].color = DataFromGs->vg_Color;
				Vertexs[PointCount].normal = DataFromGs->vg_Normal;
				++PointCount;
				if (PointCount >= 3)//getEPTPointNum(DataFromGs->OutPrimitiveType)
				{
					run_weiyixiao();// 
					PointCount = 0;
				}
				return true;
			}

#if(1)
			virtual void run_weiyixiao() 
			{
				//based on status
				{
					{
						glm::vec4 p1, p2, p3, c1, c2, c3;
						SVertexInner t1 = Vertexs[0], t2 = Vertexs[1], t3 = Vertexs[2];

						transformHomogenize(&p1, &Vertexs[0].pos);
						transformHomogenize(&p2, &Vertexs[1].pos);
						transformHomogenize(&p3, &Vertexs[2].pos);
						
						STrapezoidInner traps[2];
						int n;

						t1.pos = p1;
						t2.pos = p2;
						t3.pos = p3;
						t1.pos.w = Vertexs[0].pos.w;
						t2.pos.w = Vertexs[0].pos.w;
						t3.pos.w = Vertexs[0].pos.w;

						vertexRhwInit(&t1);	// 初始化 w
						vertexRhwInit(&t2);	// 初始化 w
						vertexRhwInit(&t3);	// 初始化 w

												// 拆分三角形为0-2个梯形，并且返回可用梯形数量
						n = trapezoidInitTriangle(traps, &t1, &t2, &t3);

						if (n >= 1) deviceRenderTrap(&traps[0]);
						if (n >= 2) deviceRenderTrap(&traps[1]);
					}
				}
			}
#endif
			virtual void run_mine()
			{
				glm::vec4 p1, p2, p3, c1, c2, c3;
				SVertexInner t1 = Vertexs[0], t2 = Vertexs[1], t3 = Vertexs[2];


			}

			virtual void callFragmentShader()
			{
				//
				Fs->drive();
				//
			}

			virtual void bindFragShader(IFragmentShaderBase** fs) final
			{
				Fs = *fs;
			}


		private:

#if(1)
			// 归一化，得到屏幕坐标
			void transformHomogenize(glm::vec4 *y, glm::vec4 *x)
			{
				/*int width = Status->TargetSurface->getWidth();
				int height = Status->TargetSurface->getHeight();
				float rhw = 1.0f / x->w;
				y->x = (x->x * rhw + 1.0f) * width * 0.5f;
				y->y = (1.0f - x->y * rhw) * height * 0.5f;
				y->z = x->z * rhw;//?
				y->w = 1.0f;
				*/
				float rhw = 1.0f / x->w;
				//y->x = (x->x*rhw- Status->ViewPortAttributes.xmin)*Status->ViewPortAttributes.alphax;
				//y->y = Status->ViewPortAttributes.alphay1- Status->ViewPortAttributes.alphay2*(x->y*rhw);
				///y->z =  -x->z*rhw;
				//y->w = 1.f;
				y->x = (x->x * rhw + 1.0f) * Status->TargetSurface->getWidth()*0.5f;
				y->y = (1.0f - x->y * rhw) * Status->TargetSurface->getHeight()*0.5f;
				y->z = x->z * rhw;
				y->w = 1.0f;
			}

			void vertexRhwInit(SVertexInner *v)
			{
				float rhw = 1.0f / v->pos.w;
				v->rhw = rhw;
				v->tc *= rhw;
				v->color.r *= rhw;
				v->color.g *= rhw;
				v->color.b *= rhw;
			}

			// 根据三角形生成 0-2 个梯形，并且返回合法梯形的数量
			int trapezoidInitTriangle(STrapezoidInner *trap, const SVertexInner *p1,
				const SVertexInner *p2, const SVertexInner *p3) {
				const SVertexInner *p;
				float k, x;

				if (p1->pos.y > p2->pos.y) p = p1, p1 = p2, p2 = p;
				if (p1->pos.y > p3->pos.y) p = p1, p1 = p3, p3 = p;
				if (p2->pos.y > p3->pos.y) p = p2, p2 = p3, p3 = p;
				if (p1->pos.y == p2->pos.y && p1->pos.y == p3->pos.y) return 0;
				if (p1->pos.x == p2->pos.x && p1->pos.x == p3->pos.x) return 0;

				if (p1->pos.y == p2->pos.y) {	// triangle down
					if (p1->pos.x > p2->pos.x) p = p1, p1 = p2, p2 = p;
					trap[0].top = p1->pos.y;
					trap[0].bottom = p3->pos.y;
					trap[0].left.v1 = *p1;
					trap[0].left.v2 = *p3;
					trap[0].right.v1 = *p2;
					trap[0].right.v2 = *p3;
					return (trap[0].top < trap[0].bottom) ? 1 : 0;
				}

				if (p2->pos.y == p3->pos.y) {	// triangle up
					if (p2->pos.x > p3->pos.x) p = p2, p2 = p3, p3 = p;
					trap[0].top = p1->pos.y;
					trap[0].bottom = p3->pos.y;
					trap[0].left.v1 = *p1;
					trap[0].left.v2 = *p2;
					trap[0].right.v1 = *p1;
					trap[0].right.v2 = *p3;
					return (trap[0].top < trap[0].bottom) ? 1 : 0;
				}

				trap[0].top = p1->pos.y;
				trap[0].bottom = p2->pos.y;
				trap[1].top = p2->pos.y;
				trap[1].bottom = p3->pos.y;

				k = (p3->pos.y - p1->pos.y) / (p2->pos.y - p1->pos.y);
				x = p1->pos.x + (p2->pos.x - p1->pos.x) * k;

				if (x <= p3->pos.x) {		// triangle left
					trap[0].left.v1 = *p1;
					trap[0].left.v2 = *p2;
					trap[0].right.v1 = *p1;
					trap[0].right.v2 = *p3;
					trap[1].left.v1 = *p2;
					trap[1].left.v2 = *p3;
					trap[1].right.v1 = *p1;
					trap[1].right.v2 = *p3;
				}
				else {					// triangle right
					trap[0].left.v1 = *p1;
					trap[0].left.v2 = *p3;
					trap[0].right.v1 = *p1;
					trap[0].right.v2 = *p2;
					trap[1].left.v1 = *p1;
					trap[1].left.v2 = *p3;
					trap[1].right.v1 = *p2;
					trap[1].right.v2 = *p3;
				}

				return 2;
			}

			// 主渲染函数
			void deviceRenderTrap(STrapezoidInner *trap)
			{
				SScanlineInner scanline;
				int top, bottom;
				int j;
				vr::Texture* surface = Status->TargetSurface;
				top = (int)(trap->top + 0.5f);
				bottom = (int)(trap->bottom + 0.5f);
				for (j = top; j < bottom; j++)
				{
					if (j >= 0 && j <(int)surface->getHeight())
					{
						trapezoidEdgeInterp(trap, (float)j + 0.5f);

						trapezoidInitScanLine(trap, &scanline, j);

						deviceDrawScanline(&scanline);


					}
					else if (j >= (int)surface->getHeight())
						break;
				}
			}

			// 按照 Y 坐标计算出左右两条边纵坐标等于 Y 的顶点
			void trapezoidEdgeInterp(STrapezoidInner *trap, float y)
			{
				float s1 = trap->left.v2.pos.y - trap->left.v1.pos.y;
				float s2 = trap->right.v2.pos.y - trap->right.v1.pos.y;
				float t1 = (y - trap->left.v1.pos.y) / s1;
				float t2 = (y - trap->right.v1.pos.y) / s2;
				vertexInterp(&trap->left.v, &trap->left.v1, &trap->left.v2, t1);
				vertexInterp(&trap->right.v, &trap->right.v1, &trap->right.v2, t2);
			}

			void vertexInterp(SVertexInner *y, const SVertexInner *x1, const SVertexInner *x2, float t)
			{
				y->pos = sl::tools::interpxyz(x1->pos, x2->pos, t);
				y->tc.x = sl::tools::interp(x1->tc.x, x2->tc.x,t);
				y->tc.y = sl::tools::interp(x1->tc.y, x2->tc.y, t);
				y->color = sl::tools::interpxyzw(x1->color, x2->color, t);
				y->rhw = sl::tools::interp(x1->rhw, x2->rhw, t);
			}

			// 根据左右两边的端点，初始化计算出扫描线的起点和步长
			void trapezoidInitScanLine(const STrapezoidInner *trap, SScanlineInner *scanline, int y)
			{
				float width = trap->right.v.pos.x - trap->left.v.pos.x;
				scanline->x = (int)(trap->left.v.pos.x + 0.5f);
				scanline->w = (int)(trap->right.v.pos.x + 0.5f) - scanline->x;
				scanline->y = y;
				scanline->v = trap->left.v;
				if (trap->left.v.pos.x >= trap->right.v.pos.x) scanline->w = 0;
				vertexDivision(&scanline->step, &trap->left.v, &trap->right.v, width);
			}

			void vertexDivision(SVertexInner *y, const SVertexInner *x1, const SVertexInner *x2, float w)
			{
				float inv = 1.0f / w;
				y->pos = (x2->pos - x1->pos) * inv;				
				y->tc=(x2->tc - x1->tc)*inv;

				y->color = (x2->color - x1->color) * inv;
				y->rhw = (x2->rhw - x1->rhw) * inv;
			}

			// 绘制扫描线
			void deviceDrawScanline(SScanlineInner *scanline)
			{
				int x = scanline->x;
				int w = scanline->w;
				vr::Texture* surface = Status->TargetSurface;
				int width = (int)surface->getWidth();
				float* zbuffer = Status->DepthBuffer->zBuffer[scanline->y];
				for (; w >= 0; x++, w--) 
				{
					if (x >= 0 && x < width)
					{
						{
							float rhw = scanline->v.rhw;
							if (rhw >= zbuffer[x])
							{
								float w = 1.0f / rhw;
								zbuffer[x] = rhw;
								DataToFs->vg_FragCoord.x = (float)x;
								DataToFs->vg_FragCoord.y = (float)scanline->y;
								DataToFs->vg_FragCoord.z = (float)rhw;
								DataToFs->vg_FragCoord.w = (float)scanline->w;
								//tex		
								DataToFs->vg_TexCoord = scanline->v.tc * w;								
								DataToFs->vg_Color = scanline->v.color*w;
								//normal
								DataToFs->vg_normal = Vertexs[0].normal;//没有插值计算
								DataToFs->vg_FragVert = scanline->step.pos;
								//here
								callFragmentShader();
							}
						}
					}
					vertexAdd(&scanline->v, &scanline->step);

					if (x >= width)
						break;
				}
			}

			void vertexAdd(SVertexInner *y, const SVertexInner *x)
			{
				y->pos += x->pos;
				y->rhw += x->rhw;
				y->tc += x->tc;
				y->color += x->color;
			}
#endif


#if(1)
		
#endif
		private:

			IFragmentShaderBase* Fs;
			SSLMachineStatus* Status;
			SVertexInner Vertexs[3];//now only triangle
			//inner
			int PointCount;
			
			//transfer datas
			SDataGSOut* DataFromGs;
			SDataRasiOut* DataToFs;



		};

	}
}

#endif//! __VG_SL_IDEFAULTRASISHADER_H_INCLUDE__