/**
* DoubleBfferedAllocator ˫���������
*/
#include "Config.h"
#include "vgTypes.h"
#include "StackAllocator.h"

namespace vg
{
	namespace core
	{
		/*
		ʹ�þ���:
		//��
		cv::StackAllocator singleAllocator(2014, 8);
		//˫�������
		cv::DoubleBufferedAllocator gdb(1024,8);
		int count = 0;
		while (true)
		{
		//���ÿ֡��֡������������
		singleAllocator.releaseAll();
		gdb.swapBuffers();
		//����µ����л�����,����ǰ֡�Ļ��岻��
		gdb.releaseCurrentBuffer();
		//..

		//��˫�����������ڴ�,��Ӱ��ǰ֡����
		//Ҫȷ�����ڱ�֡���֡ʹ��
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
			StackAllocator* mStacks[2];//˫��
		};
	}
}