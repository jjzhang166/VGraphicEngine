/**!
* �ֽڶ�����ڴ����.
* ���ʺ�����̬����,�ٶ���
*/
#include "vgTypes.h"
#include "vgAssert.h"

namespace vg
{
	namespace core
	{
		/** ʹ�÷���:
		STest* buffer = (STest*) cv::AllocateAligned(sizeof(STest), 16);
		cv::FreeAligned(buffer);
		aligned allocator.alignment must be 2^n,normally 4 or 16.
		*/
		void* AllocateAligned(u32 sizeBytes, s32 alignment)
		{
			{
				AssertP(0 == (alignment&(alignment - 1)), "AllocateAligned 0==(alignment&(alignment-1))", EAL_MEMALLOC);

				//����Ϊ������ڴ��,������Ϊu32����
				void* rawAddress = (void*)malloc(sizeof(void*) + sizeBytes + alignment);

				//��ַ����
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