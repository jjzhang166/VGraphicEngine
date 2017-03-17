#include "../../Samples.h"
#ifdef __SAMPLE_TEST_3__
#include "CCommonGS.h"
#include "CDataTransferVStoGS.h"
#include "CCommonFS.h"
#include "helper\Camera.h"
#ifndef __CCOMMONEVENTRECEIVER_H_INCLUDE__
#define __CCOMMONEVENTRECEIVER_H_INCLUDE__
using namespace vg;

using namespace vg::fw;
struct SConsole
{
	Light* light;
	helper::Camera* camera;
	bool lightOne;
};

class CommonEventReceiver :public vg::fw::IEventReceiver
{
public:
	CommonEventReceiver(SConsole** cons)
	{
	
		Console = *cons;
	}

	virtual bool OnEvent(const SEvent& event) override
	{
		bool tag = false;
		//
		if (event.EventType == EET_KEY_INPUT_EVENT)
		{
#pragma region ¿ØÖÆµÆ¹â
			if (event.KeyInput.PressedDown&&event.KeyInput.Key == EKEY_CODE::KEY_KEY_1)
			{
				Console->light->position = glm::vec4(Console->camera->position(), 1.0);
				Console->light->coneDirection = Console->camera->forward();
				tag = true;
			}
			if (event.KeyInput.PressedDown&&event.KeyInput.Key == EKEY_CODE::KEY_KEY_2)
			{
				Console->lightOne = Console->lightOne ? false : true;
				tag = true;
			}
#pragma endregion
#pragma region ÉãÏñ»ú

			const float moveSpeed = 1.0;
			if (event.KeyInput.PressedDown&&event.KeyInput.Key == KEY_KEY_W)
			{
				Console->camera->offsetPosition(secondsElapsed*moveSpeed*Console->camera->forward());
				tag = true;
			}
			else if(event.KeyInput.PressedDown&&event.KeyInput.Key == KEY_KEY_S)
			{
				Console->camera->offsetPosition(secondsElapsed*moveSpeed*(-Console->camera->forward()));
				tag = true;
			}

			if (event.KeyInput.PressedDown&&event.KeyInput.Key == KEY_KEY_A)
			{
				Console->camera->offsetPosition(secondsElapsed*moveSpeed*(-Console->camera->right()));
				tag = true;
			}
			else if (event.KeyInput.PressedDown&&event.KeyInput.Key == KEY_KEY_D)
			{
				Console->camera->offsetPosition(secondsElapsed*moveSpeed*(Console->camera->right()));
				tag = true;
			}

			if (event.KeyInput.PressedDown&&event.KeyInput.Key == KEY_KEY_R)
			{
				Console->camera->offsetPosition(secondsElapsed*moveSpeed*(Console->camera->up()));
				tag = true;
			}
			else if (event.KeyInput.PressedDown&&event.KeyInput.Key == KEY_KEY_F)
			{
				Console->camera->offsetPosition(secondsElapsed*moveSpeed*(-Console->camera->up()));
				tag = true;
			}
			if (event.KeyInput.PressedDown&&event.KeyInput.Key == KEY_KEY_Q)
			{
				Console->camera->offsetOrientation(0,-1.f);
				tag = true;
			}
			else if (event.KeyInput.PressedDown&&event.KeyInput.Key == KEY_KEY_E)
			{
				Console->camera->offsetOrientation(0, 1.f);
				tag = true;
			}

			
#pragma endregion
		}
		return tag;
	}
private:
	float secondsElapsed = 0.1f;
	const float moveSpeed = 1.0;
	SConsole* Console;
};
#endif
#endif