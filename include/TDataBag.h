#ifndef __VG_SL_TDATABAG_H_INCLUDE__
#define __VG_SL_TDATABAG_H_INCLUDE__

#include "vgArray.h"

namespace vg
{
	namespace sl
	{
		template<typename TDataNodeType>
		class TDataBag
		{
		public:
			core::array<TDataNodeType> DataOut;
			TDataNodeType DataOutNode;

			u32 getSize()
			{
				return DataOut.size();
			}

			void push()
			{
				DataOut.push_back(DataOutNode);
			}

			TDataBag()
			{
			}

			~TDataBag()
			{
				DataOut.set_free_when_destroyed(true);
				DataOut.clear();
			}

			virtual void reset()
			{
				DataOut.clear();
			}

		};
	}
}
#endif//! __VG_SL_SDATAVSOUT_H_INCLUDE__