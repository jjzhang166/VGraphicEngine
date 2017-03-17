#include "../../Samples.h"
#ifdef __SAMPLE_TEST_3__
#include "CCommonGS.h"
#include "CDataTransferVStoGS.h"

#ifndef __CCOMMONVS_H_INCLUDE__
#define __CCOMMONVS_H_INCLUDE__
class CCommonVS :public vg::sl::IVertexShaderBase
{
private:

	glm::vec2 pos = glm::vec2(0);
	int count = 0;
	uniform glm::mat4 model;//0
	uniform glm::mat4 camera;//1

public:
	CCommonVS()
		:vg::sl::IVertexShaderBase()
	{
		
	}

	in glm::vec3 vert;
	//in glm::vec4 color;
	in glm::vec2 coord;
	in glm::vec3 normal;
	CDataTransferVStoGS VsCustomOut;


	virtual bool drive(void* data, int size) override
	{

		const vg::sl::uint vertlen = sizeof(vert);
		const vg::sl::uint coordlen = sizeof(coord);
		const vg::sl::uint normallen = sizeof(normal);
		if (vertlen +  coordlen+ normallen> size)
			return false;

		memcpy(&vert, data, vertlen);
		memcpy(&coord, (char*)data + vertlen, coordlen);
		memcpy(&normal, (char*)data + vertlen+coordlen, normallen);

		IVertexShaderBase::drive(data, size);
		return true;
	}

	virtual void run()override
	{
		glm::mat4 trans = camera*model;
		VsOut->vg_Position = trans*glm::vec4(vert.x+pos.x,vert.y+pos.y,vert.z,1);
		VsOut->vg_TexCoord = coord;
		trans = glm::transpose(glm::inverse(trans));
		glm::vec4 nor = trans*glm::vec4(normal.x, normal.y, normal.z,1);
		VsOut->vg_Normal = vg::sl::tools::normalize(nor.x, nor.y, nor.z);
		VsOut->vg_Color =glm::vec4(0, 0, 1, 0.5f);

		//to fs
		VsCustomOut.fragNormal = normal;
		end();
	}

	virtual bool setUniform(int index, void* data, vg::sl::uint size)override
	{
		switch (index)
		{
		case 0://model
		{
			model = *((glm::mat4*)data);
			return true;
		}
		break;
		case 1:
		{
			camera = *((glm::mat4*)data);
			return true;
		}
		break;
		default:
			return false;
			break;
		}
		return false;
	}

	virtual void end() override
	{
		((CCommonGS*)Gs)->push(VsCustomOut);
	}

};
#endif
#endif