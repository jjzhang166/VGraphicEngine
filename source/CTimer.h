#ifndef __C_CJ_CTIMER_H__
#define __C_CJ_CTIMER_H__
#include "vgTypes.h"
#include "ITimer.h"
#include "os.h"
namespace vg
{
	namespace fw
	{
		//! Device independent implementation of the timer
		class CTimer :public ITimer
		{
		public:
			CTimer()
			{
				os::Timer::initTimer();
			}

			//! Returns current real time in milliseconds of the system.
			/** This value does not start with 0 when the application starts.
			For example in one implementation the value returned could be the
			amount of milliseconds which have elapsed since the system was started.
			*/
			virtual u32 getRealTime() const
			{
				return os::Timer::getRealTime();
			}

			//! Returns current virtual time in milliseconds.
			/** This value starts with 0 and can be manipulated using setTime(),
			stopTimer(), startTimer(), etc. This value depends on the set speed of
			the timer if the timer is stopped, etc. If you need the system time,
			use getRealTime() */
			virtual u32 getTime() const
			{
				return os::Timer::getTime();
			}

			//! Set current virutal time.
			virtual void setTime(u32 time) const
			{
				os::Timer::setTime(time);
			}

			//! Stops the virtual timer.
			/** The timer is reference counted, which means everything which calls
			stop() will also have to call start(), otherwise the timer may not
			start/stop correctly again. */
			virtual void stop()
			{
				os::Timer::stopTimer();
			}

			//! Starts the virtual timer.
			/** The timer is reference counted, which means everything which calls
			stop() will also have to call start(), otherwise the timer may not
			start/stop correctly again. */
			virtual void start()
			{
				os::Timer::startTimer();
			}

			//! Sets the speed of the timer
			/** The speed is the factor with which the time is running faster or
			slower then the real system time. */
			virtual void setSpeed(f32 speed = 1.0f)
			{
				os::Timer::setSpeed(speed);
			}

			//! Get the speed of the timer.
			virtual f32 getSpeed() const
			{
				return os::Timer::getSpeed();
			}


			//! Returns if the virtual timer is currently stopped
			virtual bool isStopped() const
			{
				return os::Timer::isStopped();
			}

			//! Advances the virtual time
			/** Makes the virtual timer update the time value based on the real
			time. This is called automatically when calling IrrlichtDevice::run(),
			but you can call it manually if you don't use this method. */
			virtual void tick()
			{
				os::Timer::tick();
			}
		};
	}

}//end cj

#endif