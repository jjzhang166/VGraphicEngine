/**!
* 字节对齐的内存分配.
* 不适合做动态分配,速度慢
*/
#include "vgTypes.h"
#include "vgAssert.h"

namespace vg
{
	namespace core
	{
		/** 使用方法:
		STest* buffer = (STest*) cv::AllocateAligned(sizeof(STest), 16);
		cv::FreeAligned(buffer);
		aligned allocator.alignment must be 2^n,normally 4 or 16.
		*/
		void* AllocateAligned(u32 sizeBytes, s32 alignment)
		{
			{
				AssertP(0 == (alignment&(alignment - 1)), "AllocateAligned 0==(alignment&(alignment-1))", EAL_MEMALLOC);

				//分配为对其的内存快,并换换为u32类型
				void* rawAddress = (void*)malloc(sizeof(void*) + sizeBytes + alignment);

				//地址对齐
				void** temp = (void**)rawAddress + 1;
				void** alignedData = (void**)(((size_t)temp + alignment - 1)&(-alignment));
				alignedData[-1] = rawAddress;
				return alignedData;
			}
		}
		void FreeAligned(void* p)
		{
			{
				if (p)
				{
					free(((void**)p)[-1]);
				}
			}
		}

	}
}