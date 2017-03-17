#ifndef __VG_SL_IDEFAULTPATCHASSEMBLYSHADER_H_INCLUDE__
#define __VG_SL_IDEFAULTPATCHASSEMBLYSHADER_H_INCLUDE__
#include "ISLShaderBase.h"
#include "TransferDatas.h"
#include "TDataBag.h"

namespace vg
{
	namespace sl
	{
		class IDefaultPatchAssemblyShader 
		{
		public:
			IDefaultPatchAssemblyShader()
				:PointCount(0)
			{

			}

			~IDefaultPatchAssemblyShader()
			{

			}

			virtual bool drive() final
			{
				// Todo
				++PointCount;
				//...

				InnerBag.DataOutNode.copy(DataFromVs);
				InnerBag.push();
				if (PointCount >= Status->PrimPointsCount)
				{
					PointCount = 0;
					bool ret = run();
					InnerBag.reset();
					return ret;
				}

				return false;
			}


			virtual bool run() 
			{
				int primiteCount = Status->PrimPointsCount;
				if (InnerBag.getSize() != primiteCount)
				{
					throw::std::runtime_error("error:PA::run():InnerBag.getSize() != primiteCount\n");
					return false;
				}
			//	for (int i = InnerBag.getSize() - 1; i >= 0; --i)
				if (!isVisible())
					return false;
				for(uint i =0;i<InnerBag.getSize();++i)
				{
					DataToGs->pa_out.push_back(InnerBag.DataOut[i].Vertex);
				}

				return true;
			}

			virtual bool isVisible()
			{
				float dotvalue = sl::tools::dot(glm::vec3(0,0,-1), InnerBag.DataOut[0].Vertex.vg_Normal);
				if (dotvalue<= 0.f)
					return false;
				return true;
			}

			virtual void reset() 
			{

			}

			virtual void bindDatas(SDataVSOut** fromvs, SDataPAOut** togs, SSLMachineStatus** status) final
			{
				Status = *status;
				DataFromVs = *fromvs;
				DataToGs = *togs;
			}
		
		private:
			//Inner data
			TDataBag<SDataPAInner> InnerBag;
			SSLMachineStatus* Status;
			int PointCount;
			//transfor datas
			SDataVSOut* DataFromVs;
			SDataPAOut* DataToGs;

			bool Discard = false;


		};
	}
}

#endif