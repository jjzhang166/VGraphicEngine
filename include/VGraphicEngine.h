/**
* Editor: lcj.uestc
* Time: 2017.03.08
* v0.0.0
*/

#ifndef __VGRAPHICENGINE_H_INCLUDE_H__
#define __VGRAPHICENGINE_H_INCLUDE_H__

//vg
#include "Config.h"
#include "vgAssert.h"
#include "vgCheck.h"
#include "vgTypes.h"
#include "IReferenceCounted.h"



//vg::core
#include "vgMath.h"
#include "StackAllocator.h"
#include "DoubleBufferedAllocator.h"
#include "AllocateAligned.h"
#include "TFreeList.h"

#include "vector2d.h"
#include "position2d.h"
#include "dimension2d.h"
#include "rect.h"
#include "vgMulArray.h"
#include "vgArray.h"
#include "vgList.h"


//vg::fw
#include "FWDevice.h"
#include "ICursorControl.h"
#include "EDeviceTypes.h"
#include "FWCreationParameters.h"
#include "IEventReceiver.h"
#include "Keycodes.h"
#include "SKeyMap.h"
#include "EDriverTypes.h"

//vg::vr
#include "Blit.h"
#include "Texture.h"
#include "SColor.h"
#include "TextureHelper.h"
#include "VRenderer.h"
#include "VRTexturesManager.h"
#include "VRProgramManager.h"
#include "VRBufferManager.h"
#include "Texture.h"

//vg::sl
#include "ConfigForSL.h"
#include "SDepthTestNode.h"
#include "TransferDatas.h"
#include "IDataHolderBase.h"
#include "ISLShaderBase.h"
#include "SLEnumPrimitiveType.h"

//vg::io
#include "IException.h"
#include "IStringException.h"

namespace vg
{
	namespace core
	{
	}//! end namespace core

	namespace fw
	{
	}//! end namespace fw

	namespace vr
	{
	}//! end namespace vr

	namespace sl
	{
	}//! end namespace sl

	extern "C" VGRAPHIC_API fw::FWDevice* VGCALLCONV createDevice(
		fw::E_DRIVER_TYPE deviceType = fw::EDT_HALFSOFTWARE,
		// parantheses are necessary for some compilers
		const core::dimension2d<u32>& windowSize = (core::dimension2d<u32>(640, 480)),
		u32 bits = 24,
		bool fullscreen = false,
		bool stencilbuffer = false,
		bool vsync = false,
		bool resized=  false,
		fw::IEventReceiver* receiver = 0);

	extern "C" VGRAPHIC_API fw::FWDevice* VGCALLCONV createDeviceEx(
		const fw::FWCreationParameters& parameters);

	extern "C"  fw::FWDevice*  createDeviceDebug(
		fw::E_DRIVER_TYPE deviceType = fw::EDT_HALFSOFTWARE,
		// parantheses are necessary for some compilers
		const core::dimension2d<u32>& windowSize = (core::dimension2d<u32>(640, 480)),
		u32 bits = 24,
		bool fullscreen = false,
		bool stencilbuffer = false,
		bool vsync = false,
		bool resized = false,
		fw::IEventReceiver* receiver = 0);

}//! end namespace vg


#endif//! __VGRAPHICENGINE_H_INCLUDE_H__
