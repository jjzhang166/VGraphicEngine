#include "../../Samples.h"
#ifdef __SAMPLE_TEST_3__
#include "CDataTransferGStoFS.h"

#ifndef __CCOMMONFS_H_INCLUDE__
#define __CCOMMONFS_H_INCLUDE__

struct Light
{
	glm::vec4 position;
	glm::vec3 intensities;//光的颜色
	float ambientCoefficient;//漫反射系数
	float attenuation;//衰减英子,用于漫反射,镜面反射
	float coneAngle;//聚光灯,光柱半角
	glm::vec3 coneDirection;//聚光灯方向
};

struct Material
{
	//材质设置
	float materialShininess;//
	glm::vec3 materialSpecularColor;
};

class CCommonFS :public vg::sl::IFragmentShaderBase
{
public:
	CDataTransferGStoFS fs_in;
	uniform vg::sl::uint textureSlot;//0
	uniform glm::mat4 model;//1
	uniform glm::vec3 cameraPosition;//2
	uniform Material material;//3
	//#define MAX_LIGHTS 2
	//uniform int numLights;//实际光源数//4
	uniform Light allLights;//4	
	uniform bool lightOn;//5

	CCommonFS()
		:vg::sl::IFragmentShaderBase()
	{

	}

	virtual void run()override
	{
		if (lightOn)
		{
			//计算世界做表内,面法线
			glm::vec3 normal = glm::normalize(glm::transpose(glm::inverse(glm::mat3(model)))*fs_in.fragNormal);//单位化
			glm::vec3 surfacePos = glm::vec3(model * glm::vec4(DataInner->vg_FragVert, 1));
			glm::vec4 surfaceColor = vg::sl::tools::texture2D(&Status, textureSlot, DataInner->vg_TexCoord);
			glm::vec3 surfaceToCamera = normalize(cameraPosition - surfacePos);

			glm::vec3 linearColor(0);
			//for (int i = 0; i < numLights; ++i)
			linearColor += ApplyLight(allLights, glm::vec3(surfaceColor), normal, surfacePos, surfaceToCamera);


			//gamma correction
			const glm::vec3 gamma = glm::vec3(1.0f / 2.2f);
			DataToPerFS->vg_FragColor = glm::vec4(pow(linearColor, gamma), surfaceColor.a);//分量各自平方
		}
		else
		{
			DataToPerFS->vg_FragColor = vg::sl::tools::texture2D(&Status, textureSlot, DataInner->vg_TexCoord);
		}
		
			//DataInner->vg_Color;
		// glm::vec4(1.0, 0.0, 0.0, 0.5);//red
		end();
	}

	glm::vec3 ApplyLight(Light light, glm::vec3 surfaceColor,
		glm::vec3 normal, glm::vec3 surfacePos, glm::vec3 surfaceToCamera)
	{
		glm::vec3 surfaceToLight;
		float attenuation = 1.0;
		if (light.position.w == 0.0)
		{
			//平行光
			surfaceToLight = vg::sl::tools::normalize(glm::vec3(light.position.x, light.position.y, light.position.z));
			attenuation = 1.0f;//平行光没有衰减
		}
		else
		{
			//点光源
			glm::vec3 sptolip(glm::vec3((light.position.x, light.position.y, light.position.z)) - surfacePos);
			surfaceToLight = vg::sl::tools::normalize(glm::vec3(sptolip));
			float distanceToLight = vg::sl::tools::length(sptolip);
			attenuation = 1.0f / (1.0f + light.attenuation*pow(distanceToLight, 2.0f));

			//聚光灯限制
			float lightToSurfaceAngle = vg::sl::tools::degrees(acos(-dot(surfaceToLight, normalize(light.coneDirection))));
			if (lightToSurfaceAngle>light.coneAngle)
				attenuation = 0.0;//衰减为0,只剩下环境光了
		}
		//开始计算三种基本:环境光,漫反射光,镜面反射光
		//ambient 
		glm::vec3 ambient = light.ambientCoefficient * surfaceColor * light.intensities;

		//diffuse
		float diffuseCoefficient = vg::sl::tools::max(0.0, dot(normal, surfaceToLight));//漫反射参数,因为都是单位向量
		glm::vec3 diffuse = diffuseCoefficient*surfaceColor* light.intensities;//漫反射

																			  //specular
		float specularCoefficient = 0.0;
		if (diffuseCoefficient>0.0)//背面不计算
			specularCoefficient = pow(
				vg::sl::tools::max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))),
				material.materialShininess);
		glm::vec3 specular = specularCoefficient*material.materialSpecularColor*light.intensities;

		return ambient + attenuation*(diffuse + specular);
	}


	virtual bool setUniform(int index, void* data, vg::sl::uint size)override
	{
		switch (index)
		{
		case 0:
			textureSlot = *((vg::sl::uint*)data);
			return true;
			break;
		case 1:
			model = *((glm::mat4*)data);
			return true;
			break;
		case 2:
			cameraPosition = *((glm::vec3*)data);
			return true;
			break;
		case 3:
			material = *((Material*)data);
			return true;
			break;
		case 4:
			allLights = *((Light*)data);
			return true;
			break;
		case 5:
			lightOn = *((bool*)data);
			return true;
		default:
			return false;
			break;
		}
		return false;
	}


	virtual void push(CDataTransferGStoFS inData)
	{
		fs_in = std::move(inData);
	}
};
#endif
#endif