/**!
* StackAllocator ����֡��˫�˶�ջ������
* �����ڲ������С�ڴ����,�ر����ظ����ɵ���ʱ��������.
* �����ڹؿ��ȳ�פ
*/
#ifndef __CHANGVOXEL_STACKALLOCATOR_H__
#define __CHANGVOXEL_STACKALLOCATOR_H__
#include "vgTypes.h"

namespace vg
{

	namespace core
	{
#define ALIGNUP( nAddress, nBytes ) ( (((u32)nAddress) + (nBytes)-1) & (~((nBytes)-1)) )


		//���ڱ�ʶ�ǶѶ����Ƕѵ�
		enum EnumHeapNum
		{
			EHN_LOWER = 0,//��
			EHN_UPPER = 1,//��
		};

		//һ��֡������
		class Frame_t
		{
		public:
			u8* pFrame;
			EnumHeapNum nHeapNum;
			Frame_t(u8* pf, EnumHeapNum nhn = EHN_LOWER)
				:pFrame(pf), nHeapNum(nhn) {}
			Frame_t() {};

		};

		/**!
		* ʹ�÷���
		cv::StackAllocator stackAllocator(1024, 16);
		STest* pFirst = NULL;
		for (int i = 0; i < 1025; ++i)
		{
		STest* pNode = (STest*)stackAllocator.alloc(sizeof(STest));
		if (pNode == NULL)
		break;
		if (10 == i)
		stackAllocator.releaseAll();
		}
		*/
		class StackAllocator
		{
		public:

			/*�����ܴ�С,����һ����ջ������
			\param stackSizeBytes �����ֽ���,������nByteAlignment��������
			\param nByteAlignment �ֽڶ�����,������2����
			\eg:stackSizeBytes = 64,nByteAlignment =4
			*/
			explicit StackAllocator(u32 stackSizeBytes, s32 nByteAlignment = 4);

			//�����ڴ���С,�Ӷ�ջ���˷���һ���µ��ڴ��
			void* alloc(u32 sizeBytes, EnumHeapNum nHeapNum = EHN_LOWER);

			/*
			\return return a pointer to the base of the memory block,
			or return 0 if there was insufficient memory.
			\param nHeapNum
			*/
			Frame_t getFrame(EnumHeapNum nHeapNum = EHN_LOWER);

			/*
			* �ͷŻص�frame.pFrame.��Ҫע�����:����pFrame֮��Ľ���һ��"����"*/
			void releaseFrame(Frame_t frame);

			//ȡ��ָ��ǰ��ջ���˵ı��

			//�ͷ�ĳ��ջ:top or lower,���������releaseFrame�����ǲ���ȫ��,�����һ����ֻʹ����һ
			void releaseAll(EnumHeapNum nHeapNum = EHN_LOWER);

			//���������ջ(��ջ����
			void clear();
		private:
			s32 mByteAlignment;//�ڴ������ֽ���
			u8* mMemoryBlock;//�ܵ��ڴ��
			u8* mBaseAndCap[2];//[0] = ��ָ��,[1]=��ָ��
			u8* mFrame[2];//��ǰ [0] = ��ָ֡��,[1] = ��ָ֡��
		};
	}
}
#endif // !__CHANGVOXEL_STACKALLOCATOR_H__