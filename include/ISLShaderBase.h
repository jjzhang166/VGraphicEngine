#ifndef __VG_SL_ISLSHADERBASE_H_INCLUDE__
#define __VG_SL_ISLSHADERBASE_H_INCLUDE__
#include "ConfigForSL.h"
#include "IReferenceCounted.h"
#include "IDataHolderBase.h"
#include "TransferDatas.h"
#include "sltools.h"

namespace vg
{
	namespace sl
	{
		enum E_SHADER_TYPE
		{
			VG_VERTEX_SHADER,
			VG_TESS_CONTROL_SHADER,
			VG_TESS_EVALUATION_SHADER,
			VG_GEOMETRY_SHADER,
			VG_FRAGMENT_SHADER,
			//other types,not opengl shader
			//! ͼԪװ��,default id = 0
			VG_PATCHASSEMBLY_SHADER,
			//! ��դ��,default id = 1
			VG_RASTERIZATION_SHADER,
			//! δ����
			VG_NOT_DEFINED,
			MAX_SHADERS_NUM = 1000,
		};



		class ISLShaderBase :public virtual IReferenceCounted
		{
		public:

			//! outData should be new in run
			/**
			* like:
			* NodeA* c = new NodeA;
			* NodeB* inData = static_cast<NodeB*>(b);
			* *outData = c;
			* c->c = bb->d;
			*/
			virtual void run() = 0;


			//! init for outData of run.
			/** This function will be called before run.
			*/
			virtual void reset()
			{

			}

			/**
			\param size size by char
			*/
			virtual bool setUniform(int index, void* data, uint size)
			{
				return false;
			}

			ISLShaderBase(E_SHADER_TYPE type)
				: Type(type), IsBeDeleted(false)
			{
			}

			virtual void setID(int id)final
			{
				ID = id;
			}

			void setDeleted()
			{
				IsBeDeleted = true;
			}

			bool operator==(int id)
			{
				return ID == id;
			}

			bool isBeDeleted()
			{
				return IsBeDeleted;
			}

			E_SHADER_TYPE getShaderType()
			{
				return Type;
			}

			virtual u32 getID()final
			{
				return ID;
			}
		protected:

			E_SHADER_TYPE Type;
			int ID;
			//! ��ǵ�ǰ�����Ƿ񱻱��Ϊɾ��״̬,
			/**��ǵ�ǰ�����Ƿ񱻱��Ϊɾ��״̬,
			* ���½�һ��shader�������һ��id,
			* idΪ��shadervector����ͷ��β������,
			* �ҵ���һ��IsBeDeleted = true�Ļ�
			* ��������β,Ȼ�����(���β����)
			* ������ID,�½�һ����Ⱦ����,
			* ����ľ���һ���ӳ���id,��������
			* ʵ����������.
			*/
			bool IsBeDeleted;
		};
	
	}
}
#endif