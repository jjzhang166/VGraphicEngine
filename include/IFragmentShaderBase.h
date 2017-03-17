#ifndef __VG_SL_IDefaultFragmentShader_H_INCLUDE__
#define __VG_SL_IDefaultFragmentShader_H_INCLUDE__
#include "ISLShaderBase.h"
#include "TransferDatas.h"
#include "IDefaultPerFragmentHandleShader.h"

namespace vg
{
	namespace sl
	{

		/**
		* Need realize:
		*   1.void run();
		* Operation:
		*   2.void push(YourDataType indata)
		*	 If you should transfer your own data,
		*    please realize this function.
		*    In which: cusdata = indata;
		*   3.void reset();
		*	 init for outData of run.
		*	 This function will be called before run.
		*    should call father::reset() first.
		* 
		*/
		class IFragmentShaderBase :public ISLShaderBase
		{
		public:
			IFragmentShaderBase()
				:ISLShaderBase( VG_FRAGMENT_SHADER)
			{
				DataInner = new SDataFSInner();
			}

			~IFragmentShaderBase()
			{
				if (DataInner)
					delete DataInner;
			}

			virtual void bindPerFragShader(IDefaultPerFragmentHandleShader** perfs)final
			{
				PerFs = *perfs;
			}

			virtual void bindDatas(SDataRasiOut** fromrasi, SDataFSOut** toperfs,
				SSLMachineStatus** status)
			{
				Status = *status;
				DataFromRasi = *fromrasi;
				DataToPerFS = *toperfs;
			}

			virtual void drive()final
			{
				DataInner->vg_FragCoord = DataFromRasi->vg_FragCoord;
				DataInner->vg_TexCoord = DataFromRasi->vg_TexCoord;
				DataInner->vg_Normal = DataFromRasi->vg_normal;
				DataInner->vg_Color = DataFromRasi->vg_Color;
				DataInner->vg_FragVert = DataFromRasi->vg_FragVert;
				DataToPerFS->vg_FragCoord = DataFromRasi->vg_FragCoord;
				DataToPerFS->vg_FragColor = DataFromRasi->vg_Color;
				DataToPerFS->vg_FragDepth = DataFromRasi->vg_FragCoord.z;
			
				run();
			}

			/**
			* Call PerFS->drive();
			*/
			virtual void end()final
			{	
				PerFs->drive();
			}

		protected:

			SSLMachineStatus* Status;
			//inner
			SDataFSInner* DataInner;
			//transfer datas
			SDataRasiOut* DataFromRasi;
			SDataFSOut* DataToPerFS;

		private:
			IDefaultPerFragmentHandleShader* PerFs;

		};
	}
}

#endif//! __VG_SL_IDefaultFragmentShader_H_INCLUDE__