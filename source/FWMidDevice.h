#ifndef __VG_FWSTUBDEVICE_H_INCLUDE__
#define __VG_FWSTUBDEVICE_H_INCLUDE__
#include "Config.h"
#include "FWDevice.h"
#include "position2d.h"
#include "FWCreationParameters.h"
#include "ICursorControl.h"
#include "Texture.h"

namespace vg
{
	namespace fw
	{
		IVideoDriver* createNullDriver( const core::dimension2d<u32>& screenSize);

		class FWMidDevice :public FWDevice
		{
		public:

			//! constructor
			FWMidDevice(const struct FWCreationParameters& param);

			//! destructor
			virtual ~FWMidDevice();

			//! Get the device render target.
			virtual vr::Texture* getDeviceRenderTarget() ;

			//! Returns the version of the engine.
			virtual const char* getVersion() const override;

			//! Checks if the window is running in fullscreen mode.
			virtual bool isFullscreen() const override;

			//! get color format of the current window
			virtual DD_PIXEL_FORMAT getColorFormat() const override;

			//! Activate any joysticks, and generate events for them.
			//virtual bool activateJoysticks(core::array<SJoystickInfo> & joystickInfo);

			//! Set the current Gamma Value for the Display
			virtual bool setGammaRamp(f32 red, f32 green, f32 blue, f32 brightness, f32 contrast);

			//! Get the current Gamma Value for the Display
			virtual bool getGammaRamp(f32 &red, f32 &green, f32 &blue, f32 &brightness, f32 &contrast);

			//! Set the maximal elapsed time between 2 clicks to generate doubleclicks for the mouse. It also affects tripleclick behaviour.
			//! When set to 0 no double- and tripleclicks will be generated.
			virtual void setDoubleClickTime(u32 timeMs) ;

			//! Get the maximal elapsed time between 2 clicks to generate double- and tripleclicks for the mouse.
			virtual u32 getDoubleClickTime() const ;

			//*********************************second part***********

			//! Provides access to the cursor control.
			/** \return Pointer to the mouse cursor control interface. */
			virtual ICursorControl* getCursorControl() override;

			//! returns the video driver
			virtual IVideoDriver* getVideoDriver();

			//! Returns a pointer to the ITimer object. With it the current Time can be received.
			virtual ITimer* getTimer();
			
			//! Sets a new user event receiver which will receive events from the engine.
			/** Return true in IEventReceiver::OnEvent to prevent the event from continuing along
			the chain of event receivers. The path that an event takes through the system depends
			on its type. See irr::EEVENT_TYPE for details.
			\param receiver New receiver to be used. */
			virtual void setEventReceiver(IEventReceiver* receiver) override;

			//! Provides access to the current event receiver.
			/** \return Pointer to the current event receiver. Returns 0 if there is none. */
			virtual IEventReceiver* getEventReceiver() override;

			//! Sends a user created event to the engine.
			/** Is is usually not necessary to use this. However, if you
			are using an own input library for example for doing joystick
			input, you can use this to post key or mouse input events to
			the engine. Internally, this method only delegates the events
			further to the scene manager and the GUI environment. */
			virtual bool postEventFromUser(const SEvent& event) override;

		protected:

			//! Compares to the last call of this function to return double and triple clicks.
			//! \return Returns only 1,2 or 3. A 4th click will start with 1 again.
			virtual u32 checkSuccessiveClicks(s32 mouseX, s32 mouseY, EMOUSE_INPUT_EVENT inputEvent);

			void calculateGammaRamp(u16 *ramp, f32 gamma, f32 relativebrightness, f32 relativecontrast);
			void calculateGammaFromRamp(f32 &gamma, const u16 *ramp);


		protected:

			IVideoDriver* VideoDriver;
			ICursorControl* CursorControl;
			IEventReceiver* UserReceiver;
			vr::Texture * DefaultRenderTarget;
			ITimer* Timer;

			SFWVideo FWVideo;

			struct SMouseMultiClicks
			{
				SMouseMultiClicks()
					: DoubleClickTime(500), CountSuccessiveClicks(0), LastClickTime(0), LastMouseInputEvent(EMIE_COUNT)
				{}

				u32 DoubleClickTime;
				u32 CountSuccessiveClicks;
				u32 LastClickTime;
				core::position2di LastClick;
				EMOUSE_INPUT_EVENT LastMouseInputEvent;
			};

			SMouseMultiClicks MouseMultiClicks;
			//video::CVideoModeList VideoModeList;
			struct FWCreationParameters CreationParams;

			bool Close;

		};
	}
}

#endif//! __VG_STUBDEVICE_H_INCLUDE__