#include "os.h"



#if defined(_VG_WINDOWS_API_)
// ----------------------------------------------------------------
// Windows specific functions
// ----------------------------------------------------------------

#ifdef _VG_XBOX_PLATFORM_
#include <xtl.h>
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#endif
namespace vg
{
	namespace fw
	{
		namespace os
		{

			static LARGE_INTEGER HighPerformanceFreq;
			static BOOL HighPerformanceTimerSupport = FALSE;
			static BOOL MultiCore = FALSE;

			void Timer::initTimer()
			{
#if !defined(_WIN32_WCE) && !defined (_IRR_XBOX_PLATFORM_)
				// disable hires timer on multiple core systems, bios bugs result in bad hires timers.
				SYSTEM_INFO sysinfo;
				GetSystemInfo(&sysinfo);
				MultiCore = (sysinfo.dwNumberOfProcessors > 1);
#endif
				HighPerformanceTimerSupport = QueryPerformanceFrequency(&HighPerformanceFreq);
				initVirtualTimer();
			}

			u32 Timer::getRealTime()
			{
				if (HighPerformanceTimerSupport)
				{
#if !defined(_WIN32_WCE) && !defined (_IRR_XBOX_PLATFORM_)
					// Avoid potential timing inaccuracies across multiple cores by
					// temporarily setting the affinity of this process to one core.
					DWORD_PTR affinityMask = 0;
					if (MultiCore)
						affinityMask = SetThreadAffinityMask(GetCurrentThread(), 1);
#endif
					LARGE_INTEGER nTime;
					BOOL queriedOK = QueryPerformanceCounter(&nTime);

#if !defined(_WIN32_WCE)  && !defined (_IRR_XBOX_PLATFORM_)
					// Restore the true affinity.
					if (MultiCore)
						(void)SetThreadAffinityMask(GetCurrentThread(), affinityMask);
#endif
					if (queriedOK)
						return u32((nTime.QuadPart) * 1000 / HighPerformanceFreq.QuadPart);

				}

				return GetTickCount();
			}

			// ------------------------------------------------------
			// virtual timer implementation

			f32 Timer::VirtualTimerSpeed = 1.0f;
			s32 Timer::VirtualTimerStopCounter = 0;
			u32 Timer::LastVirtualTime = 0;
			u32 Timer::StartRealTime = 0;
			u32 Timer::StaticTime = 0;

			//! returns current virtual time
			u32 Timer::getTime()
			{
				if (isStopped())
					return LastVirtualTime;

				return LastVirtualTime + (u32)((StaticTime - StartRealTime) * VirtualTimerSpeed);
			}

			//! ticks, advances the virtual timer
			void Timer::tick()
			{
				StaticTime = getRealTime();
			}

			//! sets the current virtual time
			void Timer::setTime(u32 time)
			{
				StaticTime = getRealTime();
				LastVirtualTime = time;
				StartRealTime = StaticTime;
			}

			//! stops the virtual timer
			void Timer::stopTimer()
			{
				if (!isStopped())
				{
					// stop the virtual timer
					LastVirtualTime = getTime();
				}

				--VirtualTimerStopCounter;
			}

			//! starts the virtual timer
			void Timer::startTimer()
			{
				++VirtualTimerStopCounter;

				if (!isStopped())
				{
					// restart virtual timer
					setTime(LastVirtualTime);
				}
			}

			//! sets the speed of the virtual timer
			void Timer::setSpeed(f32 speed)
			{
				setTime(getTime());

				VirtualTimerSpeed = speed;
				if (VirtualTimerSpeed < 0.0f)
					VirtualTimerSpeed = 0.0f;
			}

			//! gets the speed of the virtual timer
			f32 Timer::getSpeed()
			{
				return VirtualTimerSpeed;
			}

			//! returns if the timer currently is stopped
			bool Timer::isStopped()
			{
				return VirtualTimerStopCounter < 0;
			}

			void Timer::initVirtualTimer()
			{
				StaticTime = getRealTime();
				StartRealTime = StaticTime;
			}

		} // end namespace os
	}
}