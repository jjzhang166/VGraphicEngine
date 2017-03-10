#ifndef __C_CJ_CHALFSOFTWAREDRIVER_H__
#define __C_CJ_CHALFSOFTWAREDRIVER_H__
#include "CNullDriver.h"
#include "vgTypes.h"
#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <mmsystem.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <fcntl.h>
#include <sys/timeb.h>
#include <time.h>


#include <ddraw.h>    // directX includes



namespace vg
{
	namespace fw
	{

		class CHalfSoftWareDriver :public CNullDriver
		{
		public:
			//! constructor
			CHalfSoftWareDriver(const core::dimension2d<u32>& screenSize, HWND window, bool fullscreen,
				bool stencibuffer);

			~CHalfSoftWareDriver();

			virtual bool clear(vr::SColor color = vr::SColor(255, 0, 0, 0),core::rect<s32>* sourceRect = 0)  override;

			virtual bool swapBuffers()  override;

			bool initDriver();

			//draw 2D
		

			/**! Get the back surface to do something.
			*/
			virtual void* getBackSurface();

			//! Only used by the engine internally.
			/** Used to notify the driver that the window was resized. */
			virtual void OnResize(const core::dimension2d<u32>& size) override;

			//*******************part two********************
			const core::dimension2d<u32>& getCurrentRenderTargetSize() const;

			void reset();

			void setContent(const core::dimension2d<u32>& screenSize, 
				HWND hwnd, u32 bits, bool fullScreen);

		private:
			//Init²¿·Ö
			LPDIRECTDRAWSURFACE7 DDraw_Create_Surface(int width, int height, int = 0, u16 color_key_value = 0);
			int Load_Palette_From_File(char *filename, LPPALETTEENTRY palette);
			int DDraw_Fill_Surface(LPDIRECTDRAWSURFACE7 lpdds, u32 color, RECT *client = NULL);
			LPDIRECTDRAWCLIPPER DDraw_Attach_Clipper(LPDIRECTDRAWSURFACE7 lpdds, int num_rects, LPRECT clip_list);
			//end Init

			s32 DDraw_Flip(void);
			u8 *DDraw_Lock_Back_Surface(void);
			s32 DDraw_Unlock_Back_Surface(void);

			int DDraw_Shutdown(void);

		private:

			// directdraw stuff
			PALETTEENTRY          palette[MAX_COLORS_PALETTE];         // color palette
			PALETTEENTRY          save_palette[MAX_COLORS_PALETTE];    // used to save palettes
			LPDIRECTDRAW7         lpdd = NULL;   // dd object
			LPDIRECTDRAWSURFACE7  lpddsprimary = NULL;   // dd primary surface
			LPDIRECTDRAWSURFACE7  lpddsback = NULL;   // dd back surface
			LPDIRECTDRAWPALETTE   lpddpal = NULL;   // a pointer to the created dd palette
			LPDIRECTDRAWCLIPPER   lpddclipper = NULL;   // dd clipper
			LPDIRECTDRAWCLIPPER   lpddclipperwin = NULL; // dd clipper for window
			DDSURFACEDESC2        ddsd;                  // a direct draw surface description struct
			DDBLTFX               ddbltfx;               // used to fill
			DDSCAPS2              ddscaps;               // a direct draw surface capabilities struct
			HRESULT               ddrval;                // result back from dd calls
			DWORD                 start_clock_count = 0; // used for timing

			u8                    *primary_buffer = NULL; // primary video buffer
			u8                    *back_buffer = NULL; // secondary back buffer
			int                   primary_lpitch = 0;    // memory line pitch for primary buffer
			int                   back_lpitch = 0;    // memory line pitch for back buffer

			s32 window_client_x0 = 0;
			s32 window_client_y0 = 0;
			//	core::recti rect_clip;
			bool isFullScreen;
			s32 screen_bpp = 0;
			int pixel_format = 0;                        // global to hold the bits per pixel
			char buffer[80];                             // general printing buffer


			core::rect<s32>* SceneSourceRect;
			HWND HWnd;


			core::position2d<s32> Render2DTranslation;
			core::dimension2d<u32> RenderTargetSize;
			//	core::dimension2d<u32> ViewPortSize;

		};
	}//end video
}//end cj


#endif