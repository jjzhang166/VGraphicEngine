#include "../Samples.h"
#ifdef __SAMPLE_TEST_1__

using namespace vg;
using namespace vg::fw;
int main()
{
	FWDevice* device = createDeviceDebug(EDT_HALFSOFTWARE,core::dimension2du(640,480),
		32, false, false, false, true, 0);
	IVideoDriver* video = device->getVideoDriver();

	while (device->run())
	{
		device->clear(vr::SColor(255, 0, 255, 0), 0);

		device->swapBuffers();
	}

	device->drop();

	return 0;
}
#endif