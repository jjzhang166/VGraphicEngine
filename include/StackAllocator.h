/**!
* StackAllocator 基于帧的双端堆栈分配器
* 适用于不规则大小内存分配,特别是重复生成的临时变量分配.
* 适用于关卡等常驻
*/
#ifndef __CHANGVOXEL_STACKALLOCATOR_H__
#define __CHANGVOXEL_STACKALLOCATOR_H__
#include "vgTypes.h"

namespace vg
{

	namespace core
	{
#define ALIGNUP( nAddress, nBytes ) ( (((u32)nAddress) + (nBytes)-1) & (~((nBytes)-1)) )


		//用于标识是堆顶还是堆底
		enum EnumHeapNum
		{
			EHN_LOWER = 0,//底
			EHN_UPPER = 1,//顶
		};

		//一个帧管理器
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
		* 使用方法
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

			/*给定总大小,构建一个堆栈分配器
			\param stackSizeBytes 分配字节数,必须是nByteAlignment的整数倍
			\param nByteAlignment 字节对齐数,必须是2的幂
			\eg:stackSizeBytes = 64,nByteAlignment =4
			*/
			explicit StackAllocator(u32 stackSizeBytes, s32 nByteAlignment = 4);

			//给定内存块大小,从堆栈顶端分配一个新的内存块
			void* alloc(u32 sizeBytes, EnumHeapNum nHeapNum = EHN_LOWER);

			/*
			\return return a pointer to the base of the memory block,
			or return 0 if there was insufficient memory.
			\param nHeapNum
			*/
			Frame_t getFrame(EnumHeapNum nHeapNum = EHN_LOWER);

			/*
			* 释放回到frame.pFrame.需要注意的是:所有pFrame之后的将被一起"抛弃"*/
			void releaseFrame(Frame_t frame);

			//取得指向当前堆栈顶端的标记

			//释放某个栈:top or lower,这个方法与releaseFrame合用是不安全的,建议对一个堆只使用其一
			void releaseAll(EnumHeapNum nHeapNum = EHN_LOWER);

			//清空整个堆栈(堆栈归零
			void clear();
		private:
			s32 mByteAlignment;//内存对齐的字节数
			u8* mMemoryBlock;//总的内存池
			u8* mBaseAndCap[2];//[0] = 基指针,[1]=顶指针
			u8* mFrame[2];//当前 [0] = 低帧指针,[1] = 高帧指针
		};
	}
}
#endif // !__CHANGVOXEL_STACKALLOCATOR_H__