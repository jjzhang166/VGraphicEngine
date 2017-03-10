#ifndef __VG_CSTRINGEXCEPTION_H_INCLUDE__
#define __VG_CSTRINGEXCEPTION_H_INCLUDE__
#include "IException.h"

namespace vg
{
	namespace io
	{
		class IStringException :public IException
		{
		private:
			std::string Message;
		public:
			IStringException(char* str)
				:Message(str)
			{

			}


			void set(char* str)
			{
				Message = str;
			}
			virtual bool handleException() override
			{
				std::cout << Message.data() << std::endl;
				return true;
			}
		};
	}
}

#endif//! __VG_CSTRINGEXCEPTION_H_INCLUDE__