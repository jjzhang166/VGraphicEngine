#ifndef __VG_CNULLDRIVER_H__
#define __VG_CNULLDRIVER_H__
#include "IVideoDriver.h"
#include "SColor.h"
#include <string>
#include <vector>



namespace vg
{
	namespace fw
	{

		class CNullDriver :public IVideoDriver
		{
		public:
			//! constructor
			CNullDriver(const core::dimension2d<u32>& screenSize);

			//! destructor
			virtual ~CNullDriver();

			virtual bool clear(vr::SColor color = vr::SColor(255, 0, 0, 0),
				core::rect<s32>* sourceRect = 0) override;

			virtual bool swapBuffers() override;

			//! Only used by the engine internally.
			/** Used to notify the driver that the window was resized. */
			virtual void OnResize(const core::dimension2d<u32>& size) override;

			//! get screen size
			virtual const core::dimension2d<u32>& getScreenSize() const override;

			/**! Get the back surface to do something.
			*/
			virtual void* getBackSurface() override;

			//*********************part two****************
			//! Get the size of the current render target
			/** This method will return the screen size if the driver
			doesn't support render to texture, or if the current render
			target is the screen.
			\return Size of render target or screen/window */
			virtual const core::dimension2d<u32>& getCurrentRenderTargetSize() const override;


			//! Remove all hardware buffers
			virtual void removeAllHardwareBuffers() override;

		protected:


			core::rect<s32> ViewPort;
			core::dimension2d<u32> ScreenSize;


		};
	}//end video
}//end cj


#endif