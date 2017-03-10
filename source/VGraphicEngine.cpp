#include "VGraphicEngine.h"
#include "FWWin32Device.h"

namespace vg
{
	//! stub for calling createDeviceEx
	VGRAPHIC_API fw::FWDevice* VGCALLCONV createDevice(fw::E_DRIVER_TYPE driverType,
		const core::dimension2d<u32>& windowSize,
		u32 bits, bool fullscreen,
		bool resized,
		bool stencilbuffer, bool vsync, fw::IEventReceiver* res)
	{
		fw::FWCreationParameters p;
		p.DriverType = driverType;
		p.WindowSize = windowSize;
		p.Bits = (u8)bits;
		p.Fullscreen = fullscreen;
		p.Stencilbuffer = stencilbuffer;
		p.Vsync = vsync;
		p.EventReceiver = res;
		p.Resizealbe = resized;

		return createDeviceEx(p);
	}

	extern "C" VGRAPHIC_API fw::FWDevice* VGCALLCONV createDeviceEx(const fw::FWCreationParameters& params)
	{

		fw::FWDevice* dev = 0;

#ifdef _VG_COMPILE_WITH_WINDOWS_DEVICE_
		if (params.DeviceType == fw::EIDT_WIN32 || (!dev && params.DeviceType == fw::EIDT_BEST))
			dev = new fw::FWWin32Device(params);
#endif


		if (dev && !dev->getVideoDriver() && params.DriverType != fw::EDT_NULL)
		{
			dev->closeDevice(); // destroy window
			dev->run(); // consume quit message
			dev->drop();
			dev = 0;
		}

		return dev;
	}


	//! stub for calling createDeviceEx
	fw::FWDevice* createDeviceDebug(fw::E_DRIVER_TYPE driverType,
		const core::dimension2d<u32>& windowSize,
		u32 bits, bool fullscreen,
		bool stencilbuffer, bool vsync, 
		bool resized, fw::IEventReceiver* res)
	{
		fw::FWCreationParameters p;
		p.DriverType = driverType;
		p.WindowSize = windowSize;
		p.Bits = (u8)bits;
		p.Fullscreen = fullscreen;
		p.Stencilbuffer = stencilbuffer;
		p.Vsync = vsync;
		p.EventReceiver = res;
		p.Resizealbe = resized;
		return createDeviceEx(p);
	}

}