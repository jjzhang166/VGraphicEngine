#ifndef  __VG_VR_PROGRAMMANAGER_H_INCLUDE__
#define __VG_VR_PROGRAMMANAGER_H_INCLUDE__
#include "ConfigForVR.h"
#include "IReferenceCounted.h"
#include "vgList.h"
#include "ISLShaderBase.h"
#include "ISLProgramBase.h"
#include "ISLShaderBase.h"

namespace vg
{
	namespace vr
	{
		class VRProgramManager :public virtual IReferenceCounted
		{
		public:
			VRProgramManager()
				:ShaderIDCreater(0)	,
				ProgramIDCreater(0),
				DefaultViewPort(0,0,1,1)
			{
				
			}

			virtual int addShader(sl::ISLShaderBase** shader)
			{
				if (shader)
				{
					(*shader)->setID(ArrayShaders.size());
					ArrayShaders.push_back(*shader);
					return (int)(*shader)->getID();
				}
				return -1;
			}

			virtual int createNewProgma(int vsID, int gsID, int fsID)
			{
				bool tag = false;
				sl::ISLShaderBase* shader = ArrayShaders[vsID];
				if (!shader || shader->getShaderType() != sl::VG_VERTEX_SHADER)
					RETURN_WITH_REASON("No such vs.\n", -1);
				sl::IVertexShaderBase* vs = (sl::IVertexShaderBase*)shader;
				shader = ArrayShaders[gsID];
				if (!shader || shader->getShaderType() != sl::VG_GEOMETRY_SHADER)
					RETURN_WITH_REASON("No such gs.\n", -1);
				sl::IGeometryShaderBase* gs = (sl::IGeometryShaderBase*) shader;
				shader = ArrayShaders[fsID];
				if (!shader&&shader->getShaderType() != sl::VG_FRAGMENT_SHADER)
					RETURN_WITH_REASON("No such fs.\n", -1);
				sl::IFragmentShaderBase* fs = (sl::IFragmentShaderBase*) shader;

				sl::ISLProgramBase* prog = new sl::ISLProgramBase(getProgramID());
				prog->bindVSGSFS(&vs, &gs, &fs);
				prog->init();
				if (DepthBuffer)
					prog->bindDepthBuffer(&DepthBuffer);
				prog->setViewPort(DefaultViewPort);
				ArrayPrograms.push_back(prog);
				return prog->getID();
			}

			virtual sl::ISLProgramBase* getProgram(u32 id)
			{
				if (id >= ArrayPrograms.size())
					return nullptr;
				CurrentProgram = id;
				return ArrayPrograms[id];
			}

			virtual bool setProgramRenderSurface(u32 programID,vr::Texture** surface)
			{
				if (programID >= ArrayPrograms.size())
					RETURN_WITH_REASON("setProgramRenderSurface: No such prograID.\n", false);
				return ArrayPrograms[programID]->setTargetSurface(surface);
			}

			virtual void setViewPort(u32 programID, glm::vec4 viewport)
			{
				if (programID >= ArrayPrograms.size())
					std::cout<<"setViewPort: No such prograID.\n";
				return ArrayPrograms[programID]->setViewPort(viewport);
			}

			virtual void setViewPort(u32 programID)
			{
				if (programID >= ArrayPrograms.size())
					std::cout << "setViewPort: No such prograID.\n";
				return ArrayPrograms[programID]->setViewPort(DefaultViewPort);
			}

			virtual void setDefaultViewPort(glm::vec4 viewport)
			{
				DefaultViewPort = viewport;
			}

			virtual void setDefaultSurfaceForAllProgram(Texture** surface)
			{
				for(u32 i =0;i<ArrayPrograms.size();++i)
					setProgramRenderSurface(i, surface);
			}

			virtual bool setTexTexIDMap(int programID,Texture** texmap)
			{
				if (programID >=(int) ArrayPrograms.size())
					RETURN_WITH_REASON("setTexTexIDMap: No such prograID.\n", false);
				return ArrayPrograms[programID]->setTexTexIDMap(texmap);
			}
			virtual void bindDepthBuffer(vr::SSingleDepthBuffer** depthBuffer)
			{
				DepthBuffer = *depthBuffer;
			}

			virtual void update()
			{
				//
				for (u32 i = 0; i < ArrayPrograms.size(); ++i)
				{
					ArrayPrograms[i]->updateIfNessary();
				}
			}

		private:


			u32 getProgramID()
			{
				return ArrayPrograms.size();
			}

			//! Default ones
			int ShaderIDCreater;
			u32 ProgramIDCreater;
			u32 CurrentProgram;

			glm::vec4 DefaultViewPort;//(xmin,ymin,xmax,ymax)
			core::array<sl::ISLShaderBase*> ArrayShaders;
			core::array<sl::ISLProgramBase*> ArrayPrograms;
			//core::mularray<SDepthTestNode>* DepthBuffer;
			vr::SSingleDepthBuffer* DepthBuffer;
		};
	}
}

#endif//! __VG_VR_PROGRAMMANAGER_H_INCLUDE__