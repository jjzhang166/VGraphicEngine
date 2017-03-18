#ifndef __VG_VR_VRBUFFERMANAGER_H_INCLUDE__
#define __VG_VR_VRBUFFERMANAGER_H_INCLUDE__
#include "ConfigForVR.h"
#include "IReferenceCounted.h"
#include "SBuffer.h"
#include "vgArray.h"
#include "vgMulArray.h"
#include "SSingleDepthBuffer.h"


namespace vg
{
	namespace vr
	{

		//! VBO and buffers manager.
		class VRBufferManager :public virtual IReferenceCounted
		{
		public:
			VRBufferManager()
			{
				DepthBuffer = new SSingleDepthBuffer(DEPTH_BUFFER_WIDTH, DEPTH_BUFFER_HEIGHT);
				//	new core::mularray<SDepthTestNode>(DEPTH_BUFFER_WIDTH,
				//	DEPTH_BUFFER_HEIGHT, DEPTH_BUFFER_DEPTH);
				// set insert(sort) function.
				//DepthBuffer->setSortInsertFunction(SortInsertFuncForSDepthTestNode);
			}
			~VRBufferManager()
			{
				delete DepthBuffer;
			}
			virtual int bindBuffer(E_BUFFER_TYPE ebt, int size, void** data,int interinal = 0,bool ownForeign = false)
			{
				IBufferBase* newBuffer = nullptr;
				switch (ebt)
				{
				case vg::vr::EBT_F32:
					newBuffer = new SBufferF32(data, size, ownForeign);
					break;
				case vg::vr::EBT_I32:
					newBuffer = new SBufferI32(data, size, ownForeign);
					break;
				default:
					break;
				}
				if (!newBuffer)
					return -1;
				newBuffer->setInterval(interinal);
				ArrayBuffers.push_back(newBuffer);
				return ArrayBuffers.size() - 1;

			}


			virtual IBufferBase* getBufferData(int id)
			{
				if (id >= 0 && id < (int)ArrayBuffers.size())
					return ArrayBuffers[id];
				return nullptr;

			}

			~VRBufferManager()
			{
				for (u32 i = 0; i < ArrayBuffers.size(); ++i)
				{
					delete ArrayBuffers[i];
				}
				ArrayBuffers.clear();

				delete DepthBuffer;
			}

			SSingleDepthBuffer** getDepthBuffer()
			{
				return &DepthBuffer;
			}

			virtual void clearDepthBuffer()
			{
				DepthBuffer->setEmpty();
			}
		private:

			core::array<IBufferBase*> ArrayBuffers;
			//core::mularray<SDepthTestNode>* DepthBuffer;

			SSingleDepthBuffer* DepthBuffer;
		};
	}
}
#endif