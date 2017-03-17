#ifndef __VG_VR_SSINGLEDEPTHBUFFER_H_INCLUDE__
#define  __VG_VR_SSINGLEDEPTHBUFFER_H_INCLUDE__

#include <malloc.h>

namespace vg
{
	namespace vr
	{
		class SSingleDepthBuffer
		{
		public:
			int width;
			int height;
			float** zBuffer;
			SSingleDepthBuffer(int w, int h)
				:width(w),height(h)
			{
				zBuffer = (float**)malloc(sizeof(float*)*height);
				for (int i = 0; i < height; ++i)
				{
					zBuffer[i] = (float*)malloc(width * sizeof(float));
				}
				
			}
			~SSingleDepthBuffer()
			{
				for (int i = 0; i < height; ++i)
				{
					delete[] zBuffer[i];
				}
				delete[] zBuffer;
			}

			void setEmpty()
			{
				for (int i = 0; i < height; ++i)
				{
					for (int j = 0; j < width; ++j)
					{
						zBuffer[i][j] = 0.f;
					}
				}
			}
		};
	}
}


#endif