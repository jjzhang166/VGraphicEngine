#ifndef __VG_SL_TTRANSFERSTATION_H_INCLUDE__
#define __VG_SL_TTRANSFERSTATION_H_INCLUDE__
#include "ConfigForSL.h"
namespace vg
{
	namespace sl
	{
		template<typename T>
		class TTransferStation
		{
		public:
			TransferStation()
			{
				node = new T();
			}

			~TransferStation()
			{
				deleteNode();
			}

			T* node;

		private:
			void deleteNode()
			{
				delete node;
			}
		};
	}
}
#endif//! __VG_SL_TTRANSFERSTATION_H_INCLUDE__