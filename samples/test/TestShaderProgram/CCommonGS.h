#include "../../Samples.h"
#ifdef __SAMPLE_TEST_3__
#include "CDataTransferGStoFS.h"
#include "CDataTransferVStoGS.h"
#include "CCommonFS.h"
#include "vgArray.h"


#ifndef __CCOMMONGS_H_INCLUDE__
#define __CCOMMONGS_H_INCLUDE__

class CCommonGS :public vg::sl::IGeometryShaderBase
{
public:
	CDataTransferGStoFS GsCustomOut;
	vg::core::array<CDataTransferVStoGS> gs_in;

	CCommonGS()
		:vg::sl::IGeometryShaderBase()
	{
		IGeometryShaderBase::layout(vg::sl::E_Primitive_Type::EPT_TRIANGLES,
			vg::sl::E_Primitive_Type::EPT_TRIANGLES, 3);
		gs_in.set_free_when_destroyed(false);
	}

	~CCommonGS()
	{
		gs_in.set_free_when_destroyed(true);
		gs_in.clear();
	}

	virtual void run() override
	{
		for (unsigned int i = 0; i < DataGsInner->vg_in.size(); ++i)
		{
			DataGsInner->vg_Position = DataGsInner->vg_in[i].vg_Position;
			DataGsInner->vg_Color = DataGsInner->vg_in[i].vg_Color;
			DataGsInner->vg_TexCoord = DataGsInner->vg_in[i].vg_TexCoord;
			DataGsInner->vg_Normal = DataGsInner->vg_in[i].vg_Normal;
			GsCustomOut.fragNormal = gs_in[i].fragNormal;
			EmitVertex();
		}
	}

	virtual void EndPrimitive() override
	{
		((CCommonFS*)Fs)->push(std::move(GsCustomOut));
	}

	virtual void push(CDataTransferVStoGS fromvs)
	{
		gs_in.push_back(std::move(fromvs));
	}

	virtual bool setUniform(int index, void* data, vg::sl::uint size)override
	{
		return false;
	}

	virtual void reset() override
	{
		gs_in.clear();
	}
};
#endif

#endif