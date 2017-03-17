#ifndef __VG_VRMANAGER_H_INCLUDE__
#define __VG_VRMANAGER_H_INCLUDE__

#include "Config.h"
#include "IReferenceCounted.h"
#include "Texture.h"
#include "SColor.h"
#include "VRProgramManager.h"
#include "VRBufferManager.h"
#include "VRTexturesManager.h"

//sl
#include "ISLShaderBase.h"
#include "sltools.h"
#include "TransferDatas.h"
#include "ISLProgramBase.h"
#include "IVertexShaderBase.h"
#include "IGeometryShaderBase.h"
#include "IFragmentShaderBase.h"
#include "ConfigForSL.h"
#include "SLEnumPrimitiveType.h"
#include "ISLProgramBase.h"


namespace vg
{
	namespace vr
	{                                           
		/**
		* Usually use like this;
		* u32 vs = VRMgr->addShader(new VS());
		* //....gs,fs
		* int program = VRMgr->createNewProgram(vs,gs,fs);
		* int mybuff VRMgr->BufferData(...);
		* //now drawing:
		* VRMgr->useProgram(program);
		* VRMgr->bindBuffer(mybuffer);
		* VRMgr->drawDirect(.....)
		* VRMgr->stopUsingProgram();
		*/
		class VRenderer final:public virtual IReferenceCounted
		{
		public:
			VRenderer()
				:ProgramMgr(), BufferMgr(), TextureMgr()
			{
				ProgramMgr.bindDepthBuffer(BufferMgr.getDepthBuffer());
			}

#pragma region Program

			/**
			* Bind surface to one program.
			* If you want to use one program to draw on a surface,you must
			* to bind one surface to it.*/
			virtual bool setProgramRenderSurface(u32 programID, u32 surfaceID)
			{
				Texture* surface = TextureMgr.getSurface(surfaceID);
				if (!surface)
					RETURN_WITH_REASON("setProgramRenderSurface: !surface\n", false);
				sl::ISLProgramBase* program = ProgramMgr.getProgram(programID);
				if (!program)
					RETURN_WITH_REASON("setProgramRenderSurface: !program\n", false);
				return program->setTargetSurface(&surface);
			}

			/**
			* Add one new shader.
			*/
			virtual u32 addShader(sl::ISLShaderBase* shader)
			{
				return ProgramMgr.addShader(&shader);
			}

			/**
			* Create a new program with the exsited vs gs fs.
			* Will bind DefaultSurface if DefaultSurface!= nullptr.*/
			virtual int createNewProgram(int vsID, int gsID, int fsID)
			{
				int id = ProgramMgr.createNewProgma(vsID, gsID, fsID);
				if (id >= 0 && DefaultSurface)
				{
					ProgramMgr.setProgramRenderSurface(id, &DefaultSurface);
					ProgramMgr.setViewPort(id);
					ProgramMgr.setTexTexIDMap(id, TextureMgr.getTexTexIDMap());
				}

				return id;
			}

			/**
			* Bind the default program.
			*/
			virtual bool useProgram(u32 id)
			{
				sl::ISLProgramBase* ptr = ProgramMgr.getProgram(id);
				if (ptr == nullptr)
					return false;
				CurrentProgram = ptr;
				return true;
			}

			virtual void stopUsingProgram()
			{
				CurrentProgram = nullptr;
			}

			/**
			* vrender->useProgram(program);
			* vrender->BindBuffer(vbo);
			* vrender->drawDirect(sl::EPT_TRIANGLES, 0, 3);
			*/
			virtual bool drawDirect(sl::E_Primitive_Type primitiveType, int start, int pointSize)
			{
				if (CurrentBuffer == nullptr)
					RETURN_WITH_REASON("No such buffer\n", false);
				if (CurrentProgram == nullptr)
					RETURN_WITH_REASON("No such program\n", false);
				CurrentProgram->drawDirect(primitiveType, start, pointSize,
					CurrentBuffer->Size, CurrentBuffer->Interval, &(CurrentBuffer->Data));
				return true;
			}


			virtual bool setUniform(int index,void* data, u32 size,
				sl::E_UNIFORM_TARGET_SHADER_TYPE enm = sl::EUTST_ALL)
			{
				if (!CurrentProgram)
					return false;
				return CurrentProgram->setUniform(index, data, size, enm);
			}
#pragma endregion


#pragma region Buffer
			virtual bool BindBuffer(int id)
			{
				IBufferBase* cb = BufferMgr.getBufferData(id);
				if (cb == nullptr)
					RETURN_WITH_REASON("No such buffer.\n", false);
				CurrentBuffer = cb;
				return true;
			}

			virtual int BufferData(E_BUFFER_TYPE ebt, int size, void* data, int interial = 0, bool ownForeign = false)
			{
				return BufferMgr.bindBuffer(ebt, size, &data, interial, ownForeign);
			}

			virtual bool setBufferAttrib(int interial)
			{
				if (!CurrentBuffer)
					return false;
				CurrentBuffer->setInterval(interial);
				return true;
			}

			virtual IBufferBase* getBufferData(int id)
			{
				return BufferMgr.getBufferData(id);
			}
#pragma endregion


#pragma region TexAndSurface

			virtual int addSurface(Texture* surface)
			{
				return TextureMgr.addSurface(&surface);
			}

			/**
			* Bind the default render surface.
			* Warning: this doesn't mean bind this surface for all program--
			* just the programs after you call this.*/
			virtual bool setDefaultRenderSurface(int id)
			{
				Texture* tex = TextureMgr.getSurface((u32)id);
				if (!tex)
					RETURN_WITH_REASON("bindSurface: No such surface!\n", false);
				DefaultSurface = tex;
				return true;
			}

			/**
			* After bind the default target surface(setDefaultRenderSurface),
			* can call this function to bind the default surface for all program
			* created before.*/
			virtual void setDefaultSurfaceForAllProgram()
			{
				if (!DefaultSurface)
				{
					std::cout << "setDefaultSurfaceForAllProgram:!DefaultSurface.\n";
					return;
				}
				ProgramMgr.setDefaultSurfaceForAllProgram(&DefaultSurface);
			}

			/**
			* Set the view port.
			*/
			virtual void setViewPort(float xmin, float ymin, float xmax, float ymax)
			{
				ProgramMgr.setDefaultViewPort(glm::vec4(xmin, ymin, xmax, ymax));
			}
			
			virtual u32 getDefaultTextureID()
			{
				return TextureMgr.getDefaultTextureID();
			}

			/**
			* Bind one texture to one slot position by the texture's id.
			* Then can bind the texture to the program by setUniform(slotPosition).
			*/
			virtual bool activeTexture(u32 slotPosition, u32 texID)
			{
				return TextureMgr.activeTexture(slotPosition, texID);

			}

#pragma endregion

#pragma region charge
			virtual void update()
			{
				//size changed
				ProgramMgr.update();
				//clear depth buffer
				BufferMgr.clearDepthBuffer();

			}
#pragma endregion


		private:

			VRProgramManager ProgramMgr;
			VRBufferManager BufferMgr;
			VRTexturesManager TextureMgr;
			Texture* DefaultSurface;
			IBufferBase* CurrentBuffer;
			sl::ISLProgramBase* CurrentProgram;

		};
	}
}
#endif//! __VG_VRMANAGER_H_INCLUDE__