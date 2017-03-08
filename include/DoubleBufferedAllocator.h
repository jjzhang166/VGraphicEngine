/**
* DoubleBfferedAllocator 双缓冲分配器
*/
#include "Config.h"
#include "vgTypes.h"
#include "StackAllocator.h"

namespace vg
{
	namespace core
	{
		/*
		使用举例:
		//单
		cv::StackAllocator singleAllocator(2014, 8);
		//双缓冲测试
		cv::DoubleBufferedAllocator gdb(1024,8);
		int count = 0;
		while (true)
		{
		//清空每帧单帧分配器缓冲区
		singleAllocator.releaseAll();
		gdb.swapBuffers();
		//清空新的现行缓冲区,保留前帧的缓冲不变
		gdb.releaseCurrentBuffer();
		//..

		//从双缓冲器分配内存,不影响前帧数据
		//要确保仅在本帧或次帧使用
		for (int i = 0; i < 1025; ++i)
		{
		STest* pNode = (STest*)gdb.alloc(sizeof(STest));
		if (pNode == NULL)
		break;
		if (i % 3 == 0)
		pFirst = pNode;
		pNode->a = i;
		pNode->b = 0x1;
		std::cout << pNode->a << " ";
		}
		if (count++ == 2)
		break;
		}
		}
		*/
		class DoubleBufferedAllocator
		{
		public:

			DoubleBufferedAllocator(u32 stackSizeBytes, s32 nByteAlignment = 4);

			~DoubleBufferedAllocator();

			void swapBuffers();

			void releaseCurrentBuffer();

			void* alloc(u32 nBytes);

		private:
			u32 mCurStack;
			StackAllocator* mStacks[2];//双堆
		};
	}
}