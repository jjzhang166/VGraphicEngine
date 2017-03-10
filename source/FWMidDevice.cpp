#include "FWMidDevice.h"
#include <string>
#include "Texture.h"
#include "CTimer.h"

namespace vg
{

	namespace fw
	{
		//! constructor
		FWMidDevice::FWMidDevice(const FWCreationParameters& params)
			: FWDevice(), CreationParams(params), Close(false),
			CursorControl(0), UserReceiver(params.EventReceiver)
		{	
			Timer = new CTimer();
			std::string s = "VGraphicEngine Version ";
			s.append(getVersion());
			std::cout << s.c_str() << std::endl;
			DefaultRenderTarget = new vr::Texture(vr::ECF_A8R8G8B8, params.WindowSize, NULL, true, false);
			FWVideo.ColorFormat = vr::ECF_A8R8G8B8;
			FWVideo.ScreenSize = params.WindowSize;

			//checkVersion(params.SDK_version_do_not_use);
		}

		//! destructor
		FWMidDevice::~FWMidDevice()
		{
			if (CursorControl)
				CursorControl->drop();

			Timer->drop();
		}


		vr::Texture* FWMidDevice::getDeviceRenderTarget()
		{
			return DefaultRenderTarget;
		}

		//! Returns the version of the engine.
		const char* FWMidDevice::getVersion() const 
		{
			return VG_SDK_VERSION_STRING;
		}


		//! Checks if the window is running in fullscreen mode.
		bool FWMidDevice::isFullscreen() const
		{
			return CreationParams.Fullscreen;
		}


		//! get color format of the current window
		DD_PIXEL_FORMAT FWMidDevice::getColorFormat() const 
		{
			return DD_PIXEL_FORMATALPHA888;
		}


		//! Activate any joysticks, and generate events for them.
		//bool activateJoysticks(core::array<SJoystickInfo> & joystickInfo)



		//! Set the current Gamma Value for the Display
		bool FWMidDevice::setGammaRamp(f32 red, f32 green, f32 blue, f32 brightness, f32 contrast)
		{
			return false;
		}


		//! Get the current Gamma Value for the Display
		bool FWMidDevice::getGammaRamp(f32 &red, f32 &green, f32 &blue, f32 &brightness, f32 &contrast)
		{
			return false;
		}


		//! Set the maximal elapsed time between 2 clicks to generate doubleclicks for the mouse. It also affects tripleclick behaviour.
		//! When set to 0 no double- and tripleclicks will be generated.
		void FWMidDevice::setDoubleClickTime(u32 timeMs)
		{
			MouseMultiClicks.DoubleClickTime = timeMs;
		}


		//! Get the maximal elapsed time between 2 clicks to generate double- and tripleclicks for the mouse.
		u32 FWMidDevice::getDoubleClickTime() const
		{
			return MouseMultiClicks.DoubleClickTime;
			//return 0;
		}


		//*********************************second part***********

		//! Provides access to the cursor control.
		/** \return Pointer to the mouse cursor control interface. */
		ICursorControl* FWMidDevice::getCursorControl()
		{
			return CursorControl;
		}

		//! \return Returns a pointer to the ITimer object. With it the
		//! current Time can be received.
		ITimer* FWMidDevice::getTimer()
		{
			return Timer;
		}

		//! returns the video driver
		IVideoDriver* FWMidDevice::getVideoDriver()
		{
			return VideoDriver;
		}

		//! Sets a new user event receiver which will receive events from the engine.
		/** Return true in IEventReceiver::OnEvent to prevent the event from continuing along
		the chain of event receivers. The path that an event takes through the system depends
		on its type. See irr::EEVENT_TYPE for details.
		\param receiver New receiver to be used. */
		void FWMidDevice::setEventReceiver(IEventReceiver* receiver) 
		{
			UserReceiver = receiver;
		}


		//! Provides access to the current event receiver.
		/** \return Pointer to the current event receiver. Returns 0 if there is none. */
		IEventReceiver* FWMidDevice::getEventReceiver()
		{
			return UserReceiver;
		}


		//! Sends a user created event to the engine.
		/** Is is usually not necessary to use this. However, if you
		are using an own input library for example for doing joystick
		input, you can use this to post key or mouse input events to
		the engine. Internally, this method only delegates the events
		further to the scene manager and the GUI environment. */
		bool FWMidDevice::postEventFromUser(const SEvent& event) 
		{
			bool absorbed = false;

			if (UserReceiver)
				absorbed = UserReceiver->OnEvent(event);

			return absorbed;
		}


		//! Compares to the last call of this function to return double and triple clicks.
		//! \return Returns only 1,2 or 3. A 4th click will start with 1 again.
		u32 FWMidDevice::checkSuccessiveClicks(s32 mouseX, s32 mouseY, EMOUSE_INPUT_EVENT inputEvent)
		{
			const s32 MAX_MOUSEMOVE = 3;

			vg::u32 clickTime = getTimer()->getRealTime();

			if ((clickTime - MouseMultiClicks.LastClickTime) < MouseMultiClicks.DoubleClickTime
				&& core::abs_(MouseMultiClicks.LastClick.X - mouseX) <= MAX_MOUSEMOVE
				&& core::abs_(MouseMultiClicks.LastClick.Y - mouseY) <= MAX_MOUSEMOVE
				&& MouseMultiClicks.CountSuccessiveClicks < 3
				&& MouseMultiClicks.LastMouseInputEvent == inputEvent
				)
			{
				++MouseMultiClicks.CountSuccessiveClicks;
			}
			else
			{
				MouseMultiClicks.CountSuccessiveClicks = 1;
			}

			MouseMultiClicks.LastMouseInputEvent = inputEvent;
			MouseMultiClicks.LastClickTime = clickTime;
			MouseMultiClicks.LastClick.X = mouseX;
			MouseMultiClicks.LastClick.Y = mouseY;

			return MouseMultiClicks.CountSuccessiveClicks;

		}

		void FWMidDevice::calculateGammaRamp(u16 *ramp, f32 gamma, f32 relativebrightness, f32 relativecontrast)
		{
			s32 i;
			s32 value;
			s32 rbright = (s32)(relativebrightness * (65535.f / 4));
			f32 rcontrast = 1.f / (255.f - (relativecontrast * 127.5f));

			gamma = gamma > 0.f ? 1.0f / gamma : 0.f;

			for (i = 0; i < 256; ++i)
			{
				value = (s32)(pow(rcontrast * i, gamma)*65535.f + 0.5f);
				ramp[i] = (u16)core::s32_clamp(value + rbright, 0, 65535);
			}
		}

		void FWMidDevice::calculateGammaFromRamp(f32 &gamma, const u16 *ramp)
		{
			/* The following is adapted from a post by Garrett Bass on OpenGL
			Gamedev list, March 4, 2000.
			*/
			f32 sum = 0.0;
			s32 i, count = 0;

			gamma = 1.0;
			for (i = 1; i < 256; ++i) {
				if ((ramp[i] != 0) && (ramp[i] != 65535)) {
					f32 B = (f32)i / 256.f;
					f32 A = ramp[i] / 65535.f;
					sum += (f32)(logf(A) / logf(B));
					count++;
				}
			}
			if (count && sum) {
				gamma = 1.0f / (sum / count);
			}
		}

	}//! end namespace fw
}//! end namespace vg