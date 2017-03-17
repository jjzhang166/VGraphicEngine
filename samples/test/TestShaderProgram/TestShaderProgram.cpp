#include "../../Samples.h"
#ifdef __SAMPLE_TEST_3__

#include "CCommonFS.h"
#include "CCommonGS.h"
#include "CCommonVS.h"
#include "VRenderer.h"
#include "CommonEventReceiver.h"

#include "helper\Camera.h"
#include "glm\gtc\matrix_transform.hpp"
#include <vector>

using namespace vg;
using namespace fw;

Light gLights =
{
	glm::vec4(-4, 0, 10, 1),//spotlight.position = glm::vec4(-4, 0, 10, 1);
	glm::vec3(10),//spotlight.intensities = glm::vec3(2, 2, 2);
	0.3f,//spotlight.attenuation = 0.1f;
	0.1f,//spotlight.ambientCoefficient = 0.0f;
	10.0f,//spotlight.coneAngle = 15.0f;
	glm::vec3(0, 0, -1)//spotlight.coneDirection = glm::vec3(0, 0, -1);
};

Material material = { 70, glm::vec3(1.0f, 1.0f, 1.0f) };


int main()
{

	core::dimension2du SCREEN_SIZE(640, 480);

	//camera
	helper::Camera camera;
	camera.setPosition(glm::vec3(0, 0, 10));
	camera.setViewportAspectRatio((float)SCREEN_SIZE.Width / (float)SCREEN_SIZE.Height);
	glm::mat4 model(1);

	//console
	SConsole* console = new SConsole();
	console->camera = &camera;
	console->light = &gLights;
	console->lightOne = true;

	//event 
	CommonEventReceiver* eventReceiver = new CommonEventReceiver(&console);
	vr::VRenderer* vrender = new vr::VRenderer();
	vrender->setViewPort(0.f,0.f, 1.f, 1.f);
	FWDevice* device = createDeviceDebug(EDT_HALFSOFTWARE, SCREEN_SIZE,
		32, false, false, false, true, eventReceiver);
	IVideoDriver* video = device->getVideoDriver();

	vr::Texture* render = device->getDeviceRenderTarget();
	int surfaceID = vrender->addSurface(render);
	if (!vrender->setDefaultRenderSurface(surfaceID))
		throw::std::runtime_error("!vrender->setDefaultRenderSurface(surfaceID)");

	//shader
	u32 vs = vrender->addShader(new CCommonVS());
	u32 gs = vrender->addShader(new CCommonGS());
	u32 fs = vrender->addShader(new CCommonFS());

	int program = vrender->createNewProgram(vs, gs, fs);

	//vrender->setProgramRenderSurface(program, surfaceID);
	//get the default texture id
	u32 defaultTexture = vrender->getDefaultTextureID();
	u32 slotPosition = 0;
	if (!vrender->activeTexture(slotPosition, defaultTexture))
		throw std::runtime_error("!vrender->activeTexture(slotPosition,defaultTexture)");
	//set uniform


	float data[] =
	{
		//  X     Y     Z       U     V          Normal
		// bottom
		-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,   0.0f, -1.0f, 0.0f,
		1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
		-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
		1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
		1.0f,-1.0f, 1.0f,   1.0f, 1.0f,   0.0f, -1.0f, 0.0f,
		-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,   0.0f, -1.0f, 0.0f,

		// top
		-1.0f, 1.0f,-1.0f,   0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
		1.0f, 1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
		1.0f, 1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   0.0f, 1.0f, 0.0f,

		// front
		-1.0f,-1.0f, 1.0f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
		1.0f,-1.0f, 1.0f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
		1.0f,-1.0f, 1.0f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   0.0f, 0.0f, 1.0f,

		// back
		-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,   0.0f, 0.0f, -1.0f,
		-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
		1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
		1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
		-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
		1.0f, 1.0f,-1.0f,   1.0f, 1.0f,   0.0f, 0.0f, -1.0f,

		// left
		-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
		-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
		-1.0f,-1.0f, 1.0f,   1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
		-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
		-1.0f,-1.0f, 1.0f,   1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,

		// right
		1.0f,-1.0f, 1.0f,   1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
		1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
		1.0f, 1.0f,-1.0f,   0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
		1.0f,-1.0f, 1.0f,   1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
		1.0f, 1.0f,-1.0f,   0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   1.0f, 0.0f, 0.0f
	};


	u32 vbo = vrender->BufferData(vg::vr::EBT_F32, sizeof(data), data,8*sizeof(float), false);
	vrender->BindBuffer(vbo);
		
	float xmove = 1.f;
	//model = glm::translate(model, glm::vec3(xmove, 0, -7));
	//model = glm::rotate(model, 35.f, glm::vec3(0, 1, 0));
	xmove += 0.00001f;
	std::cout << "help:\n\t1: set the light position and direction at the camera one.\n";
	std::cout << "\t2: turn on or off the light.\n";
	std::cout << "\tq: turn left.\n";
	std::cout << "\te: turn right.\n";
	std::cout << "\tw: move forward.\n";
	std::cout << "\ts: move backward.\n";
	std::cout << "\ta: move left.\n";
	std::cout << "\td: move right.\n";
	std::cout << "\tr: move up.\n";
	std::cout << "\tf: move down.\n";

	while (device->run())
	{
		device->clear(vr::SColor(0, 0, 255, 255), 0);
		vrender->update();//update size ,must after device->clear
		vrender->useProgram(program);
		//set uniform
		//model = glm::translate(glm::mat4(1), glm::vec3(0, 0, xmove));
		//model = glm::translate(glm::mat4(), glm::vec3(xmove, 0, 0));
		model = glm::rotate(model, .1f, glm::vec3(1, 0, 1));
		xmove += .01f;

		//set uniform for vs
		{
			if (!vrender->setUniform(0, &model, sizeof(model), vg::sl::EUTST_VS))
				throw std::runtime_error("!vrender->setUniform failed!");
			glm::mat4 mat = camera.matrix();
			if (!vrender->setUniform(1, &mat, sizeof(camera), vg::sl::EUTST_VS))
				throw std::runtime_error("!vrender->setUniform failed!");
		}
		glm::vec3 cameraPosition(camera.position());
		//set uniform for fs
		{
			if (!vrender->setUniform(0, &slotPosition, sizeof(slotPosition), vg::sl::EUTST_FS))
				throw std::runtime_error("!vrender->setUniform failed!");
			if (!vrender->setUniform(1, &model, sizeof(model), vg::sl::EUTST_FS))
				throw std::runtime_error("!vrender->setUniform failed!");
			if (!vrender->setUniform(2, &cameraPosition, sizeof(cameraPosition), vg::sl::EUTST_FS))
				throw std::runtime_error("!vrender->setUniform failed!");
			if (!vrender->setUniform(3, &material, sizeof(material), vg::sl::EUTST_FS))
				throw std::runtime_error("!vrender->setUniform failed!");
			if (!vrender->setUniform(4, &gLights, sizeof(gLights), vg::sl::EUTST_FS))
				throw std::runtime_error("!vrender->setUniform failed!");
			if (!vrender->setUniform(5, &console->lightOne, sizeof(console->lightOne), vg::sl::EUTST_FS))
				throw std::runtime_error("!vrender->setUniform failed!");
		}

		vrender->BindBuffer(vbo);
 		vrender->drawDirect(sl::EPT_TRIANGLES, 0,36);
		device->swapBuffers();
	}

	device->drop();
	return 0;
}
#endif