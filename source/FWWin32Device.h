#ifndef __VG_FWWIN32DEVICE_H_INCLUDE__
#define __VG_FWWIN32DEVICE_H_INCLUDE__
#include "FWMidDevice.h"
#include "vgTypes.h"
#include "Texture.h"
#define WIN32_LEAN_AND_MEAN
#if !defined(_CJ_XBOX_PLATFORM_)
#include <windows.h>
#include <mmsystem.h> // For JOYCAPS
#include <Windowsx.h>
#endif
namespace vg
{
	namespace fw
	{
		class FWWin32Device :public FWMidDevice
		{
		public:
			//! constructor
			FWWin32Device(const FWCreationParameters& params);

			//! destructor
			virtual ~FWWin32Device();

			//! runs the device. Returns false if device wants to be deleted
			virtual bool run() override;

			virtual bool clear(vr::SColor color, core::rect<s32>* sourceRect) override;

			virtual bool swapBuffers();

			//! Cause the device to temporarily pause execution and let other processes to run
			// This should bring down processor usage without major performance loss for Irrlicht
			virtual void yield()override;

			//! Pause execution and let other processes to run for a specified amount of time.
			virtual void sleep(u32 timeMs, bool pauseTimer)override;

			//! sets the caption of the window
			virtual void setWindowCaption(const wchar_t* text)override;

			//! returns if window is active. if not, nothing need to be drawn
			virtual bool isWindowActive() const override;

			//! returns if window has focus
			virtual bool isWindowFocused() const override;

			//! returns if window is minimized
			virtual bool isWindowMinimized() const override;

			//! notifies the device that it should close itself
			virtual void closeDevice() override;


			//! Notifies the device, that it has been resized
			void OnResized() ;

			//! Sets if the window should be resizable in windowed mode.
			virtual void setResizable(bool resize = false) override;

			//! Minimizes the window.
			virtual void minimizeWindow() override;

			//! Maximizes the window.
			virtual void maximizeWindow() override;

			//! Restores the window size.
			virtual void restoreWindow() override;


			//! Set the current Gamma Value for the Display
			virtual bool setGammaRamp(f32 red, f32 green, f32 blue, f32 brightness, f32 contrast) override;

			//! Get the current Gamma Value for the Display
			virtual bool getGammaRamp(f32 &red, f32 &green, f32 &blue, f32 &brightness, f32 &contrast) override;

			//! Remove all messages pending in the system message loop
			//	virtual void clearSystemMessages();

			//! Get the device type
			virtual E_DEVICE_TYPE getType() const  
			{
				return EIDT_WIN32;
			}

			//! Compares to the last call of this function to return double and triple clicks.
			//! \return Returns only 1,2 or 3. A 4th click will start with 1 again.
			virtual u32 checkSuccessiveClicks(s32 mouseX, s32 mouseY, EMOUSE_INPUT_EVENT inputEvent) override
			{
				// we just have to make it public
				return FWMidDevice::checkSuccessiveClicks(mouseX, mouseY, inputEvent);
			}


			//! switchs to fullscreen
			bool switchToFullScreen(bool reset = false) ;

			//! Check for and show last Windows API error to help internal debugging.
			//! Does call GetLastError and on errors formats the errortext and displays it in a messagebox.
			static void ReportLastWinApiError();



			//! Implementation of the win32 cursor control
#if(1)
			class CCursorControl : public fw::ICursorControl
			{
			public:

				CCursorControl(const core::dimension2d<u32>& wsize, HWND hwnd, bool fullscreen)
					: WindowSize(wsize), InvWindowSize(0.0f, 0.0f),
					HWnd(hwnd), BorderX(0), BorderY(0),
					UseReferenceRect(false), IsVisible(true)
				{
					if (WindowSize.Width != 0)
						InvWindowSize.Width = 1.0f / WindowSize.Width;

					if (WindowSize.Height != 0)
						InvWindowSize.Height = 1.0f / WindowSize.Height;

					updateBorderSize(fullscreen, false);
				}

				//! Changes the visible state of the mouse cursor.
				virtual void setVisible(bool visible)
				{
					CURSORINFO info;
					info.cbSize = sizeof(CURSORINFO);
					BOOL gotCursorInfo = GetCursorInfo(&info);
					while (gotCursorInfo)
					{
						if ((visible && info.flags == CURSOR_SHOWING) 	// visible
							|| (!visible && info.flags == 0))			// hidden
						{
							break;
						}
						int showResult = ShowCursor(visible);   // this only increases an internal display counter in windows, so it might have to be called some more
						if (showResult < 0)
						{
							break;
						}
						info.cbSize = sizeof(CURSORINFO);	// yes, it really must be set each time
						gotCursorInfo = GetCursorInfo(&info);
					}
					IsVisible = visible;
				}

				//! Returns if the cursor is currently visible.
				virtual bool isVisible() const
				{
					return IsVisible;
				}

				//! Sets the new position of the cursor.
				virtual void setPosition(const core::position2d<f32> &pos)
				{
					setPosition(pos.X, pos.Y);
				}

				//! Sets the new position of the cursor.
				virtual void setPosition(f32 x, f32 y)
				{
					if (!UseReferenceRect)
						setPosition(core::round32(x*WindowSize.Width), core::round32(y*WindowSize.Height));
					else
						setPosition(core::round32(x*ReferenceRect.getWidth()), core::round32(y*ReferenceRect.getHeight()));
				}

				//! Sets the new position of the cursor.
				virtual void setPosition(const core::position2d<s32> &pos)
				{
					setPosition(pos.X, pos.Y);
				}

				//! Sets the new position of the cursor.
				virtual void setPosition(s32 x, s32 y)
				{
					if (UseReferenceRect)
					{
						SetCursorPos(ReferenceRect.UpperLeftCorner.X + x,
							ReferenceRect.UpperLeftCorner.Y + y);
					}
					else
					{
						RECT rect;
						if (GetWindowRect(HWnd, &rect))
							SetCursorPos(x + rect.left + BorderX, y + rect.top + BorderY);
					}

					CursorPos.X = x;
					CursorPos.Y = y;
				}

				//! Returns the current position of the mouse cursor.
				virtual const core::position2d<s32>& getPosition()
				{
					updateInternalCursorPosition();
					return CursorPos;
				}

				//! Returns the current position of the mouse cursor.
				virtual core::position2d<f32> getRelativePosition()
				{
					updateInternalCursorPosition();

					if (!UseReferenceRect)
					{
						return core::position2d<f32>(CursorPos.X * InvWindowSize.Width,
							CursorPos.Y * InvWindowSize.Height);
					}

					return core::position2d<f32>(CursorPos.X / (f32)ReferenceRect.getWidth(),
						CursorPos.Y / (f32)ReferenceRect.getHeight());
				}

				//! Sets an absolute reference rect for calculating the cursor position.
				virtual void setReferenceRect(core::rect<s32>* rect = 0)
				{
					if (rect)
					{
						ReferenceRect = *rect;
						UseReferenceRect = true;

						// prevent division through zero and uneven sizes

						if (!ReferenceRect.getHeight() || ReferenceRect.getHeight() % 2)
							ReferenceRect.LowerRightCorner.Y += 1;

						if (!ReferenceRect.getWidth() || ReferenceRect.getWidth() % 2)
							ReferenceRect.LowerRightCorner.X += 1;
					}
					else
						UseReferenceRect = false;
				}

				/** Used to notify the cursor that the window was resized. */
				virtual void OnResize(const core::dimension2d<u32>& size)
				{
					WindowSize = size;
					if (size.Width != 0)
						InvWindowSize.Width = 1.0f / size.Width;
					else
						InvWindowSize.Width = 0.f;

					if (size.Height != 0)
						InvWindowSize.Height = 1.0f / size.Height;
					else
						InvWindowSize.Height = 0.f;
				}

				/** Used to notify the cursor that the window resizable settings changed. */
				void updateBorderSize(bool fullscreen, bool resizable)
				{
					if (!fullscreen)
					{
						if (resizable)
						{
							BorderX = GetSystemMetrics(SM_CXSIZEFRAME);
							BorderY = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYSIZEFRAME);
						}
						else
						{
							BorderX = GetSystemMetrics(SM_CXDLGFRAME);
							BorderY = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYDLGFRAME);
						}
					}
					else
					{
						BorderX = BorderY = 0;
					}
				}

			private:

				//! Updates the internal cursor position
				void updateInternalCursorPosition()
				{
					POINT p;
					if (!GetCursorPos(&p))
					{
						DWORD xy = GetMessagePos();
						p.x = GET_X_LPARAM(xy);
						p.y = GET_Y_LPARAM(xy);
					}

					if (UseReferenceRect)
					{
						CursorPos.X = p.x - ReferenceRect.UpperLeftCorner.X;
						CursorPos.Y = p.y - ReferenceRect.UpperLeftCorner.Y;
					}
					else
					{
						RECT rect;
						if (GetWindowRect(HWnd, &rect))
						{
							CursorPos.X = p.x - rect.left - BorderX;
							CursorPos.Y = p.y - rect.top - BorderY;
						}
						else
						{
							// window seems not to be existent, so set cursor to
							// a negative value
							CursorPos.X = -1;
							CursorPos.Y = -1;
						}
					}
				}

				core::position2d<s32> CursorPos;
				core::dimension2d<u32> WindowSize;
				core::dimension2d<f32> InvWindowSize;
				HWND HWnd;

				s32 BorderX, BorderY;
				core::rect<s32> ReferenceRect;
				bool UseReferenceRect;
				bool IsVisible;
			};

			//! returns the win32 cursor control
			CCursorControl* getWin32CursorControl();
#endif
		private:

		private:

			//! create the driver
			void createDriver();

			void getWindowsVersion(std::string& version);

			void resizeIfNecessary();


			HWND HWnd;

			bool ChangedToFullScreen;
			bool IsNonNTWindows;
			bool Resized;
			bool ExternalWindow;
			CCursorControl* Win32CursorControl;


			//for video


		};
	}//! end namespace fw
}//! end namespace vg

#endif//! __VG_FWWIN32DEVICE_H_INCLUDE__