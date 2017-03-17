#ifndef __VG_SL_IVERTEXSHADERBASE_H_INCLUDE__
#define __VG_SL_IVERTEXSHADERBASE_H_INCLUDE__
#include "ISLShaderBase.h"
#include "TransferDatas.h"


namespace vg
{
	namespace sl
	{
		class IGeometryShaderBase;
		/**
		* Need relize:
		*   1.void run();
		*   2.bool driver()
		*        call father::driver at last.
		* Operation:
		*   3.void end();
		*	 Need transfer the custom data of vs to
		*	 gs by gs->push(customData);
		*	 and the gs->push should be realized by user.
		*    if you need transfer you own data,you should
		*	 realize this function and at the same time
		*	 realize gs::push which end() call.
		*   4.void reset();
		*	 init for outData of run.
		*	 This function will be called before run.
		*    should call father::reset() first.
		*/
		class IVertexShaderBase :public ISLShaderBase
		{
		public:
			IVertexShaderBase()
				:ISLShaderBase( VG_VERTEX_SHADER)
			{

			}

			virtual bool drive(void* data, int size)
			{
				VsOut->reset();
				// Todo
				run();
				return true;
			}

			/**
			* Need transfer the custom data of vs to
			* gs by gs->push(customData);
			* and the gs->push should be realized by user.
			*/
			virtual void end()
			{

			}


			virtual void bindGeometryShader(IGeometryShaderBase** gs)
			{
				Gs = *gs;
			}

			virtual void bindDatas(SDataVSOut** toprim, SSLMachineStatus** status)
			{
				VsOut = *toprim;
				Status = *status;
			}

		protected:

			IGeometryShaderBase* Gs;
			//Inner data
			SDataVSInner* InnerData;
			//transfer datas
			SSLMachineStatus* Status;
			SDataVSOut* VsOut;


		};
	}
}

#endif//! __VG_SL_IDefaultFragmentShader_H_INCLUDE__