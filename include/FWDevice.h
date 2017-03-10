#ifndef __FWDEVICE_H_INCLUDE__
#define __FWDEVICE_H_INCLUDE__
#include "Config.h"
#include "IReferenceCounted.h"
#include "IEventReceiver.h"
#include "Texture.h"
#include "ICursorControl.h"
#include "ITimer.h"
#include "IVideoDriver.h"
#include "EDeviceTypes.h"



namespace vg
{
	namespace vr
	{
		class VRManager;
	}

	namespace fw
	{



		struct SFWVideo
		{
			vr::ECOLOR_FORMAT ColorFormat;
			core::rect<s32> ViewPort;
			core::dimension2d<u32> ScreenSize;
		};

		class FWDevice : public virtual IReferenceCounted
		{
		public:
			//! Runs the device.
			/** Also increments the virtual timer by calling
			ITimer::tick();. You can prevent this
			by calling ITimer::stop(); before and ITimer::start() after
			calling vgDevice::run(). Returns false if device wants
			to be deleted. Use it in this way:
			\code
			while(device->run())
			{
				device->clear(color);
			// draw everything here

				device->swapBuffers();
			}
			\endcode
			If you want the device to do nothing if the window is inactive
			(recommended), use the slightly enhanced code shown at isWindowActive().

			Note if you are running vg inside an external, custom
			created window: Calling Device->run() will cause vg to
			dispatch windows messages internally.
			If you are running vg in your own custom window, you can
			also simply use your own message loop using GetMessage,
			DispatchMessage and whatever and simply don't use this method.
			But note that vg will not be able to fetch user input
			then. See irr::SvgCreationParameters::WindowId for more
			informations and example code.
			*/
			virtual bool run() = 0;

			virtual bool clear(vr::SColor color, core::rect<s32>* sourceRect) = 0;

			virtual bool swapBuffers() = 0;

			//! Get the device render target.
			/** 
			\param Texture* This image will hold the backbuffer of the device.
			which will be changed when call swap buffer function.
			*/
			//virtual bool setDefaultContent(vr::VRManager* vrMgr) = 0;
			virtual vr::Texture* getDeviceRenderTarget() = 0;

			//! Cause the device to temporarily pause execution and let other processes run.
			/** This should bring down processor usage without major
			performance loss for vg */
			virtual void yield() = 0;

			//! Pause execution and let other processes to run for a specified amount of time.
			/** It may not wait the full given time, as sleep may be interrupted
			\param timeMs: Time to sleep for in milisecs.
			\param pauseTimer: If true, pauses the device timer while sleeping
			*/
			virtual void sleep(u32 timeMs, bool pauseTimer = false) = 0;

			//! Provides access to the cursor control.
			/** \return Pointer to the mouse cursor control interface. */
			virtual ICursorControl* getCursorControl() = 0;

			//! Sets the caption of the window.
			/** \param text: New text of the window caption. */
			virtual void setWindowCaption(const wchar_t* text) = 0;

			//! Returns if the window is active.
			/** If the window is inactive,
			nothing needs to be drawn. So if you don't want to draw anything
			when the window is inactive, create your drawing loop this way:
			\code
			while(device->run())
			{
			if (device->isWindowActive())
			{
			// draw everything here
			}
			else
			device->yield();
			}
			\endcode
			\return True if window is active. */
			virtual bool isWindowActive() const = 0;

			//! Checks if the vg window has focus
			/** \return True if window has focus. */
			virtual bool isWindowFocused() const = 0;

			//! Checks if the vg window is minimized
			/** \return True if window is minimized. */
			virtual bool isWindowMinimized() const = 0;

			//! Checks if the vg window is running in fullscreen mode
			/** \return True if window is fullscreen. */
			virtual bool isFullscreen() const = 0;

			//! Get the current color format of the window
			/** \return Color format of the window. */
			virtual DD_PIXEL_FORMAT getColorFormat() const = 0;

			//! Notifies the device that it should close itself.
			/** vgDevice::run() will always return false after closeDevice() was called. */
			virtual void closeDevice() = 0;


			//! Sets a new user event receiver which will receive events from the engine.
			/** Return true in IEventReceiver::OnEvent to prevent the event from continuing along
			the chain of event receivers. The path that an event takes through the system depends
			on its type. See irr::EEVENT_TYPE for details.
			\param receiver New receiver to be used. */
			virtual void setEventReceiver(IEventReceiver* receiver) = 0;

			//! Provides access to the current event receiver.
			/** \return Pointer to the current event receiver. Returns 0 if there is none. */
			virtual IEventReceiver* getEventReceiver() = 0;

			//! Provides access to the video driver for drawing 3d and 2d geometry.
			/** \return Pointer the video driver. */
			virtual IVideoDriver* getVideoDriver() = 0;

			//! Provides access to the engine's timer.
			/** The system time can be retrieved by it as
			well as the virtual time, which also can be manipulated.
			\return Pointer to the ITimer object. */
			virtual ITimer* getTimer() = 0;

			//! Sends a user created event to the engine.
			/** Is is usually not necessary to use this. However, if you
			are using an own input library for example for doing joystick
			input, you can use this to post key or mouse input events to
			the engine. Internally, this method only delegates the events
			further to the scene manager and the GUI environment. */
			virtual bool postEventFromUser(const SEvent& event) = 0;

			//! Get the version of the engine.
			/** The returned string
			will look like this: "1.2.3" or this: "1.2".
			\return String which contains the version. */
			virtual const c8* getVersion() const = 0;

			//! Sets if the window should be resizable in windowed mode.
			/** The default is false. This method only works in windowed
			mode.
			\param resize Flag whether the window should be resizable. */
			virtual void setResizable(bool resize = false) = 0;

			//! Minimizes the window if possible.
			virtual void minimizeWindow() = 0;

			//! Maximizes the window if possible.
			virtual void maximizeWindow() = 0;

			//! Restore the window to normal size if possible.
			virtual void restoreWindow() = 0;

			//! Check if a driver type is supported by the engine.
			/** Even if true is returned the driver may not be available
			for a configuration requested when creating the device. */
			static bool isDriverSupported(E_DRIVER_TYPE driver)
			{
				switch (driver)
				{
				case EDT_NULL:
					return true;
				case EDT_SOFTWARE:
#ifdef _FW_COMPILE_WITH_SOFTWARE_
					return true;
#else
					return false;
#endif
				case EDT_HALFSOFTWARE:
#ifdef _FW_COMPILE_WITH_HALFSOFTWARE_
					return true;
#else
					return false;
#endif
				case EDT_DIRECT3D8:
#ifdef _FW_COMPILE_WITH_DIRECT3D_8_
					return true;
#else
					return false;
#endif
				case EDT_DIRECT3D9:
#ifdef _FW_COMPILE_WITH_DIRECT3D_9_
					return true;
#else
					return false;
#endif
				case EDT_OPENGL:
#ifdef _FW_COMPILE_WITH_OPENGL_
					return true;
#else
					return false;
#endif
				default:
					return false;
				}
			}
		};
	}
}


#endif//! __FWDEVICE_H_INCLUDE__