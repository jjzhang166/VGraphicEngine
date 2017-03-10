#include <VGraphicEngine.h>

#pragma comment(lib,"VGraphic.lib")

int main()
{
	vg::fw::FWDevice* device = vg::createDevice();

	while (device->run())
	{

		device->clear(vg::vr::SColor(255,255,0,0),NULL);


		device->swapBuffers();
	}
	return 0;
}