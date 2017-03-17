#include "../Samples.h"
#ifdef __SAMPLE_TEST_1__

using namespace vg;
using namespace vg::fw;

void drawRect(vr::Texture* tex, vr::SColor& color, core::rect<s32>& rec)
{
	s32 ulx = rec.UpperLeftCorner.X;
	s32 uly = rec.UpperLeftCorner.Y;
	s32 lrx = rec.LowerRightCorner.X;
	s32 lry = rec.LowerRightCorner.Y;
	for (s32 i = ulx; i <= lrx; ++i)
	{
		for (s32 j = uly; j < lry; ++j)
		{
			tex->setPixel((u32)i, (u32)j, color, false);
		}
	}
}

int main()
{
	FWDevice* device = createDeviceDebug(EDT_HALFSOFTWARE,core::dimension2du(640,480),
		32, false, false, false, true, 0);
	IVideoDriver* video = device->getVideoDriver();

	vr::Texture* render = device->getDeviceRenderTarget();

	core::rect<s32> rec(core::dimension2di(0, 0), core::dimension2di(50, 50));

	f32 sum = 0.f;
	while (device->run())
	{
		device->clear(vr::SColor(255, 0, 255, 0), 0);
		drawRect(render, vr::SColor(255, 255, 0, 0), rec);
		device->swapBuffers();
		sum += 0.01f;
		if (sum > 1.f)
		{
			rec += 1;
			sum = 0;
		}
	}

	device->drop();

	return 0;
}
#endif