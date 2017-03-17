#ifndef __VG_SL_IPROGRAMBASE_H_INCLUDE__
#define __VG_SL_IPROGRAMBASE_H_INCLUDE__
#include "ConfigForSL.h"
#include "IReferenceCounted.h"
#include "vgArray.h"
#include "ISLShaderBase.h"
#include "Texture.h"
#include "TransferDatas.h"
#include "IGeometryShaderBase.h"
#include "IFragmentShaderBase.h"
#include "IVertexShaderBase.h"
#include "IDefaultRasiShader.h"
#include "IDefaultPerFragmentHandleShader.h"
#include "IDefaultPatchAssemblyShader.h"
#include "SLEnumPrimitiveType.h"
#include "SBuffer.h"
#include "SSingleDepthBuffer.h"


namespace vg
{
	namespace sl
	{

		enum E_UNIFORM_TARGET_SHADER_TYPE
		{
			EUTST_VS,
			EUTST_GS,
			EUTST_FS,
			EUTST_VS_AND_GS,
			EUTST_VS_AND_FS,
			EUTST_GS_AND_FS,
			EUTST_ALL
		};

		/**
		* Based on this class,you should :
		* new Datas of DataBag
		* new shaders
		* In your structer you should init your own vs gs fs*/
		class ISLProgramBase :public virtual IReferenceCounted
		{

		public:

			ISLProgramBase(int id)
				:ID(id), DataBag()
			{
				PA = new IDefaultPatchAssemblyShader();
				Rasi = new IDefaultRasiShader();
				PerFS = new IDefaultPerFragmentHandleShader();
			}

			~ISLProgramBase()
			{
				if (VS)
					delete VS;
				if (PA)
					delete PA;
				if (GS)
					delete GS;
				if (Rasi)
					delete Rasi;
				if (FS)
					delete FS;
				if (PerFS)
					delete PerFS;
			}
			
			virtual void bindVSGSFS(IVertexShaderBase** vs,
				IGeometryShaderBase** gs, IFragmentShaderBase** fs)
			{
				if (!*vs || !*fs || !*gs || (*vs)->getShaderType() != VG_VERTEX_SHADER
					|| (*fs)->getShaderType() != VG_FRAGMENT_SHADER
					|| (*gs)->getShaderType() != VG_GEOMETRY_SHADER)
				{
					std::runtime_error("!vs || !fs || !gs || vs->getShaderType() != VG_VERTEX_SHADER\
						|| fs->getShaderType() != VG_FRAGMENT_SHADER\
						|| gs->getShaderType() != VG_GEOMETRY_SHADER");
					return;
				}
				VS = *vs;
				GS = *gs;
				FS = *fs;

			}

			virtual void init()
			{
				if (!VS || !GS || !FS)
					throw::std::runtime_error("ISLProgramBase::init,!VS||!GS||!FS");
				//bind databag
					VS->bindDatas(&(DataBag.DataVstoPA), &(DataBag.MachineStatus));
					VS->bindGeometryShader(&GS);
					PA->bindDatas(&(DataBag.DataVstoPA), &(DataBag.DataPAtoGS), &(DataBag.MachineStatus));
					GS->bindDatas(&(DataBag.DataPAtoGS),&(DataBag.DataGstoRasi), &(DataBag.MachineStatus));
					GS->bindRasiAndFS(&Rasi, &FS);
					Rasi->bindDatas(&(DataBag.DataGstoRasi),&(DataBag.DataRasitoFS), &(DataBag.MachineStatus));
					Rasi->bindFragShader(&FS);
					FS->bindDatas(&(DataBag.DataRasitoFS),&(DataBag.DataFstoPerFS),&(DataBag.MachineStatus));
					FS->bindPerFragShader(&PerFS);
					PerFS->bindDatas(&(DataBag.DataFstoPerFS),&(DataBag.MachineStatus));


			}

			//! each time before call run.
			virtual void reset()
			{
				DataBag.DataPAtoGS->pa_out.clear();
				DataBag.DataPAtoGS->vg_PrimitiveID = 0;
			}
			virtual bool setTargetSurface(vr::Texture** surface)
			{
				if (!*surface)
					return false;
				DataBag.MachineStatus->TargetSurface = *surface;
				return true;
			}

			virtual void setDefault(E_Primitive_Type primitieType)
			{
				DataBag.MachineStatus->PrimPointsCount = getEPTPointNum(primitieType);
			}
			//! when call draw commond.
			virtual void run(int start, int end, int perSize, void** data, int dataSize)
			{
				int count = dataSize / perSize;
				reset();
				
			}

			virtual void drawDirect(E_Primitive_Type primitieType, int start, int count, int dataSize, int perSize, void** data)
			{
				int counti = dataSize / perSize;
			
				reset();
				setDefault(primitieType);
				char* cptr = (char*)*data;
				for (int i = start; i < counti&&i<start+count; ++i)
				{
					if (i == 24)
						printf("");
					VS->drive(cptr, perSize);
					if (PA->drive())
					{
						GS->drive();
					}
					cptr += perSize;
				}
				//PerFS->run();//blend and draw pixels
			}

			virtual bool setUniform( int index,void* data,uint size, E_UNIFORM_TARGET_SHADER_TYPE enm = EUTST_ALL)
			{
				bool tag = true;
				switch (enm)
				{
				case vg::sl::EUTST_VS:
					if (!VS)
					{
						std::cout << "No vertex shader.setUniform failed!\n";
						return false;
					}
					tag = tag&(VS->setUniform(index, data, size));
					break;
				case vg::sl::EUTST_GS:
					if (!GS)
					{
						std::cout << "No geo shader.setUniform failed!\n";
						return false;
					}
					tag = tag&(GS->setUniform(index, data, size));
					break;
				case vg::sl::EUTST_FS:
					if (!FS)
					{
						std::cout << "No frag shader.setUniform failed!\n";
						return false;
					}
					tag = tag&(FS->setUniform(index, data, size));
					break;
				case vg::sl::EUTST_VS_AND_GS:
					if (!GS||!VS)
					{
						std::cout << "No vs or gs shader.setUniform failed!\n";
						return false;
					}
					tag = tag&(VS->setUniform(index, data, size));
					tag = tag&(GS->setUniform(index, data, size));
					break;
				case vg::sl::EUTST_VS_AND_FS:
					if (!FS || !VS)
					{
						std::cout << "No vs or fs shader.setUniform failed!\n";
						return false;
					}
					tag = tag&(VS->setUniform(index, data, size));
					tag = tag&(FS->setUniform(index, data, size));
					break;
				case vg::sl::EUTST_GS_AND_FS:
					if (!GS || !FS)
					{
						std::cout << "No fs or gs shader.setUniform failed!\n";
						return false;
					}
					tag = tag&(FS->setUniform(index, data, size));
					tag = tag&(GS->setUniform(index, data, size));
					break;
				case vg::sl::EUTST_ALL:
					if (VS)
						VS->setUniform(index,data, size);
					if (GS)
						GS->setUniform(index, data, size);
					if (FS)
						FS->setUniform(index, data, size);
					break;
				default:
					std::cout << "No such shader.setUniform failed!\n";
					tag = false;
					break;
				}
				return tag;
			}


			virtual int getID()
			{
				return ID;
			}

			virtual void bindDepthBuffer(vr::SSingleDepthBuffer** depthBuffer)
			{
				DataBag.MachineStatus->DepthBuffer = *depthBuffer;
			}

			virtual void setViewPort(glm::vec4 view)
			{
				DataBag.MachineStatus->setViewPort(view.x, view.y, view.z, view.w);
			}


			virtual bool setTexTexIDMap( vr::Texture** texmap)
			{
				DataBag.MachineStatus->TexTexIDMap = texmap;
				return true;
			}

			// if surface size changed,refresh the alphas 
			virtual void updateIfNessary()
			{
				if (DataBag.MachineStatus->TargetSurface
					&&DataBag.MachineStatus->TargetSurface->getSizeChanged())
				{
					DataBag.MachineStatus->updateViewAlhpa();//update the alphas 
					DataBag.MachineStatus->TargetSurface->setSizeChanged(false);
				}
			}

		public:

			int ID;

		protected:
			
			IVertexShaderBase* VS;
			IDefaultPatchAssemblyShader* PA;
			IGeometryShaderBase* GS;
			IDefaultRasiShader* Rasi;
			IFragmentShaderBase* FS;
			IDefaultPerFragmentHandleShader* PerFS;

			TransferDatas DataBag;
			
			
		};


	}
}

#endif//! __VG_SL_IPROGRAMBASE_H_INCLUDE__