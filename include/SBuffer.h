#ifndef __VG_SL_SBUFFER_H_INCLUDE__
#define __VG_SL_SBUFFER_H_INCLUDE__
#include "ConfigForSL.h"

namespace vg
{
	namespace vr
	{
		enum E_BUFFER_TYPE
		{
			EBT_F32,
			EBT_I32,
			EBT_VOID
		};

		struct IBufferBase
		{
			int Size;
			E_BUFFER_TYPE BufferType;
			void* Data;
			int Interval;

			IBufferBase(int size)
				:Interval(0)
			{
				Data = (void*)new char[size];
			}

			void setInterval(int interval)
			{
				Interval = interval;
			}

			IBufferBase(void** data, int size, bool ownforeign = false)
				:Interval(0)
			{
				if (ownforeign)
				{
					Size = size;
					Data = (void*)(*data);
				}
				else
				{
					Data = (void*) new char[size];
					Size = size;
					if (*data)
						memcpy(Data, *data, size);
				}
			}

		};
		
		class SBufferF32 :public IBufferBase
		{
		public:
			SBufferF32(int size)
				:IBufferBase(size)
			{
				BufferType = EBT_F32;
			}


			SBufferF32(void** data,int size,bool ownforeign = false)
				:IBufferBase(data,size,ownforeign)
			{
				BufferType = EBT_F32;
			}

		};

		class SBufferI32 :public IBufferBase
		{
		public:

			SBufferI32(int size)
				:IBufferBase(size)
			{
				BufferType = EBT_I32;
			}


			SBufferI32(void** data, int size, bool ownforeign = false)
				:IBufferBase(data,size,ownforeign)
			{
				BufferType = EBT_I32;
			}
		};

	}
}
#endif//! __VG_SL_SBUFFER_H_INCLUDE__