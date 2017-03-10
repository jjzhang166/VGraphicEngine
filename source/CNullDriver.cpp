#include "CNullDriver.h"

namespace vg
{
	namespace fw
	{
		//! constructor
		CNullDriver::CNullDriver( const core::dimension2d<u32>& screenSize)
			: ViewPort(0, 0, 0, 0), ScreenSize(screenSize)
		{
#ifdef _DEBUG
			setDebugName("CNullDriver");
#endif

			ViewPort = core::rect<s32>(core::position2d<s32>(0, 0), core::dimension2di(screenSize));

		}

		//! destructor
		CNullDriver::~CNullDriver()
		{
	
		}

		bool CNullDriver::clear(vr::SColor color,
			core::rect<s32>* sourceRect)
		{
			//	PrimitivesDrawn = 0;
			return true;
		}

		bool CNullDriver::swapBuffers()
		{
			//updateAllHardwareBuffers();
			return true;
		}

		//! creates a video driver
		IVideoDriver* createNullDriver(const core::dimension2d<u32>& screenSize)
		{
			CNullDriver* nullDriver = new CNullDriver( screenSize);

			/*	// create empty material renderers
			for (u32 i = 0; sBuiltInMaterialTypeNames[i]; ++i)
			{
			IMaterialRenderer* imr = new IMaterialRenderer();
			nullDriver->addMaterialRenderer(imr);
			imr->drop();
			}
			*/
			return nullDriver;
		}


		//! Only used by the internal engine. Used to notify the driver that
		//! the window was resized.
		void CNullDriver::OnResize(const core::dimension2d<u32>& size)
		{
			if (ViewPort.getWidth() == (s32)ScreenSize.Width &&
				ViewPort.getHeight() == (s32)ScreenSize.Height)
				ViewPort = core::rect<s32>(core::position2d<s32>(0, 0),
					core::dimension2di(size));
			
			ScreenSize = size;
		}

		//! returns screen size
		const core::dimension2d<u32>& CNullDriver::getScreenSize() const
		{
			return ScreenSize;
		}



		/**! Get the back surface to do something.
		*/
		void* CNullDriver::getBackSurface()
		{
			return nullptr;
		}

		//*******************************part two*****************
		//! returns the current render target size,
		//! or the screen size if render targets are not implemented
		const core::dimension2d<u32>& CNullDriver::getCurrentRenderTargetSize() const
		{
			return ScreenSize;
		}

	
		//! Remove all hardware buffers
		void CNullDriver::removeAllHardwareBuffers()
		{
			//	while (HWBufferMap.size())
			//	deleteHardwareBuffer(HWBufferMap.getRoot()->getValue());
		}

	}
}