#ifndef __VG_SKEY_MAP_H__
#define __VG_SKEY_MAP_H__
#include "vgTypes.h"
#include "Keycodes.h"

namespace vg
{
	namespace fw
	{
		enum EKEY_ACTION
		{
			EKA_MOVE_FORWARD = 0,
			EKA_MOVE_BACKWARD,
			EKA_STRAFE_LEFT,
			EKA_STRAFE_RIGHT,
			EKA_JUMP_UP,
			EKA_CROUCH,
			EKA_COUNT,

			//! This value is not used. It only forces this enumeration to compile in 32 bit.
			EKA_FORCE_32BIT = 0x7fffffff
		};
		struct SKeyMap
		{
			EKEY_ACTION Action;
			EKEY_CODE KeyCode;
		};
	}
}

#endif