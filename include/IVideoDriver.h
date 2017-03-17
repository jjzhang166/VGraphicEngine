#ifndef __CJ_IVIDEODRIVER_H__
#define __CJ_IVIDEODRIVER_H__
#include "IReferenceCounted.h"
#include "rect.h"
#include "dimension2d.h"
#include "position2d.h"
#include "EDriverTypes.h"
#include "SColor.h"
#include "SColor.h"


namespace vg
{

	namespace fw
	{

		//! Interface to driver which is able to perform 2d and 3d graphics functions.
		/** This interfaces is one of the most important interfaces of
		the Engine:All rendering and texture manipulation is done with
		this interface.*/
		class IVideoDriver :public virtual IReferenceCounted
		{
		public:
			//! Applications must call this method before performing any rendering.
			/** This method can clear the back- and the z-buffer.
			\param backBuffer Specifies if the back buffer should be
			cleared, which means that the screen is filled with the color
			specified. If this parameter is false, the back buffer will
			not be cleared and the color parameter is ignored.
			\param zBuffer Specifies if the depth buffer (z buffer) should
			be cleared. It is not nesesarry to do so if only 2d drawing is
			used.
			\param color The color used for back buffer clearing
			\param videoData Handle of another window, if you want the
			bitmap to be displayed on another window. If this is an empty
			element, everything will be displayed in the default window.
			Note: This feature is not fully implemented for all devices.
			\param sourceRect Pointer to a rectangle defining the source
			rectangle of the area to be presented. Set to null to present
			everything. Note: not implemented in all devices.
			\return False if failed. */
			virtual bool clear(vr::SColor color = vr::SColor(255, 0, 0, 0),
				core::rect<s32>* sourceRect = 0) = 0;

			//! Presents the rendered image to the screen.
			/** Applications must call this method after performing any
			rendering.
			\return False if failed and true if succeeded. */
			virtual bool swapBuffers() = 0;
			

			//! Event handler for resize events. Only used by the engine internally.
			/** Used to notify the driver that the window was resized.
			Usually, there is no need to call this method. */
			virtual void OnResize(const core::dimension2d<u32>& size) = 0;



			//! Get the size of the screen or render window.
			/** \return Size of screen or render window. */
			virtual const core::dimension2d<u32>& getScreenSize() const = 0;

			/**! Get the back surface to do something.
			*/
			virtual void* getBackSurface() = 0;

			//! Get the back buffer of the surfaces
			virtual void* getBackBuffer() = 0;

			//***************************second part*****************
			//! Get the size of the current render target
			/** This method will return the screen size if the driver
			doesn't support render to texture, or if the current render
			target is the screen.
			\return Size of render target or screen/window */
			virtual const core::dimension2d<u32>& getCurrentRenderTargetSize() const = 0;
			
			// Get the default surface's lpitch
			virtual const int getCurrentRenderTargetLpitch() const = 0;

			//! Remove all hardware buffers
			virtual void removeAllHardwareBuffers() = 0;

		};
	}//end video
}//end cj

#endif