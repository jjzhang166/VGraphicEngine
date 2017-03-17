#ifndef __VG_SL_IGeometryShaderBase_H_INCLUDE__
#define __VG_SL_IGeometryShaderBase_H_INCLUDE__
#include "ISLShaderBase.h"
#include "TransferDatas.h"
#include "IVertexShaderBase.h"
#include "IDefaultRasiShader.h"
#include"IFragmentShaderBase.h"

namespace vg
{
	namespace sl
	{
		/**
		* In your creater ,call father::layout fist.
		* Should realize:
		*  1.void run();
		* operation:
		*  2.void EndPrimitive();
		*	 If you need transfer data from gs to fs,
		*	 please realize this function.
		*    In this function,you should do things like:
		*    ((MyFsType*)Fs)->DataFromGs = DataToFs;
		*  3.void push(YouCustomDataType)
		*    if you need transfer you own data,you should
		*	 realize this function and at the same time
		*	 realize VS::end() which all gs->push(data);
		*  At the same time:declare:array<YouType> array;
		*  4.void reset();
		*	 init for outData of run.
		*	 This function will be called before run.
		*    should call father::reset() first.
		*/
		class IGeometryShaderBase :public ISLShaderBase
		{
		public:
			IGeometryShaderBase()
				:ISLShaderBase( VG_GEOMETRY_SHADER), VerticeCountCir(0)
			{
				DataGsInner = new SDataGSInner();
			}

			virtual void layout(E_Primitive_Type inType, E_Primitive_Type outType, int max_vertexs) final
			{
				InPrimitiveType = inType;
				OutPrimitiveType = outType;
				MaxVertices = max_vertexs;
			}


			virtual bool drive() final
			{
				// Todo
				DataGsInner->vg_in = DataFromPa->pa_out;
				DataGsInner->vg_PrimitiveIDIn = DataFromPa->vg_PrimitiveID++;
				DataFromPa->pa_out.clear();

				VerticesCount = 0;
				run();
				return true;
			}

			/**
			* Push one point into Rasi,if it's time to Rasi
			* then it will.
			*/
			virtual void EmitVertex() final
			{
				if (VerticesCount > MaxVertices)
					return;//drop the extra points
				//Todo
				if (isTimeSendData())
					EndPrimitive();
				DataToRasi->copy(DataGsInner);
				Rasi->drive();
			}

			/**
			* In this function,you should do things like:
			* ((MyFsType*)Fs)->DataFromGs = DataToFs;
			*/
			virtual void EndPrimitive() 
			{

			}

			virtual bool isTimeSendData()
			{
				++VerticeCountCir;
				++VerticesCount;
				if (VerticeCountCir >= getEPTPointNum(OutPrimitiveType))
				{
					VerticeCountCir = 0;
					return true;
				}
				return false;
			}

			virtual void bindRasiAndFS(IDefaultRasiShader** rasi, IFragmentShaderBase** fs) final
			{
				Rasi = *rasi;
				Fs = *fs;
			}


			virtual void bindDatas( SDataPAOut** frompa, 
				SDataGSOut** torasi,SSLMachineStatus** status) final
			{
				Status = *status;
				DataFromPa = *frompa;
				DataToRasi = *torasi;
			}



		protected:
			E_Primitive_Type InPrimitiveType;
			E_Primitive_Type OutPrimitiveType;
			int MaxVertices;
			int VerticesCount;
			int VerticeCountCir;

			SSLMachineStatus* Status;
			//inner
			SDataGSInner* DataGsInner;

			//transfer datas
			SDataPAOut* DataFromPa;
			SDataGSOut* DataToRasi;

			IFragmentShaderBase* Fs;
		private:
			IDefaultRasiShader* Rasi;
		};
	}
}

#endif//! __VG_SL_IDefaultFragmentShader_H_INCLUDE__