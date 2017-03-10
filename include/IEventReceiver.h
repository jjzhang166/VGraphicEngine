#ifndef __VG_I_EVENTRECEIVER_H__
#define __VG_I_EVENTRECEIVER_H__
#include "vgTypes.h"
#include "SKeyMap.h"
#include "Keycodes.h"
#include "IReferenceCounted.h"

namespace vg
{
	namespace fw
	{
		//! Enumeration for all event types there are.
		enum EEVENT_TYPE
		{

			//! A mouse input event.
			/** Mouse events are created by the device and passed to IrrlichtDevice::postEventFromUser
			in response to mouse input received from the operating system.
			Mouse events are first passed to the user receiver, then to the GUI environment and its elements,
			then finally the input receiving scene manager where it is passed to the active camera.
			*/
			EET_MOUSE_INPUT_EVENT,

			//! A key input event.
			/** Like mouse events, keyboard events are created by the device and passed to
			IrrlichtDevice::postEventFromUser. They take the same path as mouse events. */
			EET_KEY_INPUT_EVENT,


			//! A user event with user data.
			/** This is not used by Irrlicht and can be used to send user
			specific data though the system. The Irrlicht 'window handle'
			can be obtained from IrrlichtDevice::getExposedVideoData()
			The usage and behaviour depends on the operating system:
			Windows: send a WM_USER message to the Irrlicht Window; the
			wParam and lParam will be used to populate the
			UserData1 and UserData2 members of the SUserEvent.
			Linux: send a ClientMessage via XSendEvent to the Irrlicht
			Window; the data.l[0] and data.l[1] members will be
			casted to s32 and used as UserData1 and UserData2.
			MacOS: Not yet implemented
			*/
			EET_USER_EVENT,

			//! This enum is never used, it only forces the compiler to
			//! compile these enumeration values to 32 bit.
			EGUIET_FORCE_32_BIT = 0x7fffffff

		};

		enum EMOUSE_INPUT_EVENT
		{
			//! Left mouse button was pressed down.
			EMIE_LMOUSE_PRESSED_DOWN = 0,

			//! Right mouse button was pressed down.
			EMIE_RMOUSE_PRESSED_DOWN,

			//! Middle mouse button was pressed down.
			EMIE_MMOUSE_PRESSED_DOWN,

			//! Left mouse button was left up.
			EMIE_LMOUSE_LEFT_UP,

			//! Right mouse button was left up.
			EMIE_RMOUSE_LEFT_UP,

			//! Middle mouse button was left up.
			EMIE_MMOUSE_LEFT_UP,

			//! The mouse cursor changed its position.
			EMIE_MOUSE_MOVED,

			//! The mouse wheel was moved. Use Wheel value in event data to find out
			//! in what direction and how fast.
			EMIE_MOUSE_WHEEL,

			//! Left mouse button double click.
			//! This event is generated after the second EMIE_LMOUSE_PRESSED_DOWN event.
			EMIE_LMOUSE_DOUBLE_CLICK,

			//! Right mouse button double click.
			//! This event is generated after the second EMIE_RMOUSE_PRESSED_DOWN event.
			EMIE_RMOUSE_DOUBLE_CLICK,

			//! Middle mouse button double click.
			//! This event is generated after the second EMIE_MMOUSE_PRESSED_DOWN event.
			EMIE_MMOUSE_DOUBLE_CLICK,

			//! Left mouse button triple click.
			//! This event is generated after the third EMIE_LMOUSE_PRESSED_DOWN event.
			EMIE_LMOUSE_TRIPLE_CLICK,

			//! Right mouse button triple click.
			//! This event is generated after the third EMIE_RMOUSE_PRESSED_DOWN event.
			EMIE_RMOUSE_TRIPLE_CLICK,

			//! Middle mouse button triple click.
			//! This event is generated after the third EMIE_MMOUSE_PRESSED_DOWN event.
			EMIE_MMOUSE_TRIPLE_CLICK,

			//! No real event. Just for convenience to get number of events
			EMIE_COUNT
		};

		enum E_MOUSE_BUTTON_STATE_MASK
		{
			EMBSM_LEFT = 0x01,
			EMBSM_RIGHT = 0x02,
			EMBSM_MIDDLE = 0x04,

			//! currently only on windows
			EMBSM_EXTRA1 = 0x08,

			//! currently only on windows
			EMBSM_EXTRA2 = 0x10,

			EMBSM_FORCE_32_BIT = 0x7fffffff
		};


		struct SEvent
		{

			//! Any kind of mouse event.
			struct SMouseInput
			{
				//! X position of mouse cursor
				s32 X;

				//! Y position of mouse cursor
				s32 Y;

				//! mouse wheel delta, often 1.0 or -1.0, but can have other values < 0.f or > 0.f;
				/** Only valid if event was EMIE_MOUSE_WHEEL */
				f32 Wheel;

				//! True if shift was also pressed
				bool Shift : 1;

				//! True if ctrl was also pressed
				bool Control : 1;

				//! A bitmap of button states. You can use isButtonPressed() to determine
				//! if a button is pressed or not.
				//! Currently only valid if the event was EMIE_MOUSE_MOVED
				u32 ButtonStates;

				//! Is the left button pressed down?
				bool isLeftPressed() const { return (0 != (ButtonStates & EMBSM_LEFT)); }

				//! Is the right button pressed down?
				bool isRightPressed() const
				{ 
					return (0 != (ButtonStates & EMBSM_RIGHT)); 
				}

				//! Is the middle button pressed down?
				bool isMiddlePressed() const { return (0 != (ButtonStates & EMBSM_MIDDLE)); }

				//! Type of mouse event
				EMOUSE_INPUT_EVENT Event;
			};

			//! Any kind of keyboard event.
			struct SKeyInput
			{
				//! Character corresponding to the key (0, if not a character)
				wchar_t Char;

				//! Key which has been pressed or released
				EKEY_CODE Key;

				//! If not true, then the key was left up
				bool PressedDown : 1;

				//! True if shift was also pressed
				bool Shift : 1;

				//! True if ctrl was also pressed
				bool Control : 1;
			};



			//! Any kind of user event.
			struct SUserEvent
			{
				//! Some user specified data as int
				s32 UserData1;

				//! Another user specified data as int
				s32 UserData2;
			};

			EEVENT_TYPE EventType;
			union
			{
				struct SMouseInput MouseInput;
				struct SKeyInput KeyInput;
				struct SUserEvent UserEvent;
			};
		};//end SEvent



		  //! Interface of an object which can receive events.
		  /** Many of the engine's classes VGEngine IEventReceiver so they are able to
		  process events. Events usually start at a postEventFromUser function and are
		  passed down through a chain of event receivers until OnEvent returns true. See
		  VG::EEVENT_TYPE for a description of where each type of event starts, and the
		  path it takes through the system. */
		class IEventReceiver :public virtual IReferenceCounted
		{
		public:

			//! Destructor
			virtual ~IEventReceiver() {}

			//! Called if an event happened.
			/** Please take care that you should only return 'true' when you want to _prevent_ VGEngine
			* from processing the event any further. So 'true' does mean that an event is completely done.
			* Therefore your return value for all unprocessed events should be 'false'.
			\return True if the event was processed.
			*/
			virtual bool OnEvent(const SEvent& event) = 0;

		};

	}
}//end namespace VG
#endif