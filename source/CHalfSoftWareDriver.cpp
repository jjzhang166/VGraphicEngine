#include "CHalfSoftWareDriver.h"
#include "vgToolFunctions.h"
#include "vgMath.h"
#include "SColor.h"


#pragma comment( lib, "d3d9.lib")   
#pragma comment( lib, "ddraw.lib")
#pragma comment (lib, "dxguid")

namespace vg
{
	namespace fw
	{

#define DEFAULT_PALETTE_FILE "include/PALDATA2.PAL"
		// function ptr to RGB16 builder
		u16(*RGB16Bit)(int r, int g, int b) = NULL;
		// this function simply builds a 5.6.5 format 16 bit pixel
		// assumes input is RGB 0-255 each channel
		u16 RGB16Bit565(int r, int g, int b)
		{
			r >>= 3; g >>= 2; b >>= 3;
			return vr::RGB16BIT565(r, g, b);

		} // end RGB16Bit565

		  // this function simply builds a 5.5.5 format 16 bit pixel
		  // assumes input is RGB 0-255 each channel
		u16 RGB16Bit555(int r, int g, int b)
		{
			r >>= 3; g >>= 3; b >>= 3;
			return vr::RGB16BIT555(r, g, b);
		} // end RGB16Bit555


		CHalfSoftWareDriver::CHalfSoftWareDriver(const core::dimension2d<u32>& screenSize, HWND window, bool fullscreen,
			bool stencibuffer)
			: CNullDriver(screenSize), SceneSourceRect(0), HWnd(window)
		{
		}
		CHalfSoftWareDriver::~CHalfSoftWareDriver()
		{
			DDraw_Shutdown();
		}


		void CHalfSoftWareDriver::setContent(const core::dimension2d<u32>& screenSize,
			HWND hwnd, u32 bits, bool fullScreen)
		{
			// set globals
			HWnd = hwnd;
			screen_bpp = bits;
			isFullScreen = fullScreen;
			ScreenSize = screenSize;
		}

		bool CHalfSoftWareDriver::clear(vr::SColor color,
			core::rect<s32>* sourceRect)
		{
			CNullDriver::clear( color, sourceRect);
			//	RECT rect;
			SceneSourceRect = sourceRect;
			// clear the drawing surface
			DDraw_Fill_Surface(lpddsback, color.color);//?

			// lock the back buffer
			DDraw_Lock_Back_Surface();
			//Graphic2D->InitCGraphic2D(ScreenSize, back_buffer, back_lpitch);
			//之后绘制内容都会知道back_buffer上
			return true;
		}

		bool CHalfSoftWareDriver::swapBuffers()
		{
			CNullDriver::swapBuffers();
			// unlock the back buffer
			DDraw_Unlock_Back_Surface();

			// flip the surfaces
			DDraw_Flip();
			return true;
		}

		bool CHalfSoftWareDriver::initDriver()
		{
#if(1)
			//	const s32 realWidth = clientSize.right - clientSize.left;
			//	const s32 realHeight = clientSize.bottom - clientSize.top;
			s32 windowLeft = 0, windowTop = 0;
			if (!isFullScreen)
			{
				windowLeft = (GetSystemMetrics(SM_CXSCREEN) - ScreenSize.Width) / 2;
				windowTop = (GetSystemMetrics(SM_CYSCREEN) - ScreenSize.Height) / 2;
				if (windowLeft < 0)
					windowLeft = 0;
				if (windowTop < 0)
					windowTop = 0;	// make sure window menus are in screen on creation
			}
			// now resize the window, so the client area is the actual size requested
			// since there may be borders and controls if this is going to be a windowed app
			// if the app is not windowed then it won't matter
			RECT window_rect = { 0, 0,(long)(ScreenSize.Width - 1),(long)(ScreenSize.Height - 1) };

			// make the call to adjust window_rect
			AdjustWindowRectEx(&window_rect,
				GetWindowStyle(HWnd),
				GetMenu(HWnd) != NULL,
				GetWindowExStyle(HWnd));

			// save the global client offsets, they are needed in DDraw_Flip()
			window_client_x0 = -window_rect.left;
			window_client_y0 = -window_rect.top;

			// now resize the window with a call to MoveWindow()
			MoveWindow(HWnd,
				windowLeft, // x position
				windowTop, // y position
				window_rect.right - window_rect.left, // width
				window_rect.bottom - window_rect.top, // height
				TRUE);
#endif
			// this function initializes directdraw
			int index; // looping variable

			// create IDirectDraw interface 7.0 object and test for error
			if (FAILED(DirectDrawCreateEx(NULL, (void **)&lpdd, IID_IDirectDraw7, NULL)))
				return(0);


			// based on windowed or fullscreen set coorperation level
			if (!isFullScreen)
			{
				// set cooperation level to windowed mode 
				if (FAILED(lpdd->SetCooperativeLevel(HWnd, DDSCL_NORMAL)))
					return(0);

			} // end if
			else
			{
				// set cooperation level to fullscreen mode 
				if (FAILED(lpdd->SetCooperativeLevel(HWnd,
					DDSCL_ALLOWMODEX | DDSCL_FULLSCREEN |
					DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT | DDSCL_MULTITHREADED)))
					return(0);

				// set the display mode
				if (FAILED(lpdd->SetDisplayMode(ScreenSize.Width, ScreenSize.Height, screen_bpp, 0, 0)))
					return(0);

			} // end else

			// Create the primary surface
			memset(&ddsd, 0, sizeof(ddsd));
			ddsd.dwSize = sizeof(ddsd);

			// we need to let dd know that we want a complex 
			// flippable surface structure, set flags for that
			if (isFullScreen)
			{
				// fullscreen mode
				ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
				ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;

				// set the backbuffer count to 0 for windowed mode
				// 1 for fullscreen mode, 2 for triple buffering
				ddsd.dwBackBufferCount = 1;
			} // end if
			else
			{
				// windowed mode
				ddsd.dwFlags = DDSD_CAPS;
				ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

				// set the backbuffer count to 0 for windowed mode
				// 1 for fullscreen mode, 2 for triple buffering
				ddsd.dwBackBufferCount = 0;
			} // end else

			  // create the primary surface
			lpdd->CreateSurface(&ddsd, &lpddsprimary, NULL);

			// get the pixel format of the primary surface
			DDPIXELFORMAT ddpf; // used to get pixel format

								// initialize structure
			DDRAW_INIT_STRUCT(ddpf);

			// query the format from primary surface
			lpddsprimary->GetPixelFormat(&ddpf);

			// based on masks determine if system is 5.6.5 or 5.5.5
			//RGB Masks for 5.6.5 mode
			//DDPF_RGB  16 R: 0x0000F800  
			//             G: 0x000007E0  
			//             B: 0x0000001F  

			//RGB Masks for 5.5.5 mode
			//DDPF_RGB  16 R: 0x00007C00  
			//             G: 0x000003E0  
			//             B: 0x0000001F  
			// test for 6 bit green mask)
			//if (ddpf.dwGBitMask == 0x000007E0)
			//   dd_pixel_format = DD_PIXEL_FORMAT565;

			// use number of bits, better method
			pixel_format = ddpf.dwRGBBitCount;

			printf("\npixel format = %d\n", pixel_format);
			//core::Write_Error("\npixel format = %d\n", pixel_format);

			// set up conversion macros, so you don't have to test which one to use
			if (pixel_format == DD_PIXEL_FORMAT555)
			{
				RGB16Bit = RGB16Bit555;
				core::Write_Error("\npixel format = 5.5.5");
			} // end if
			else if (pixel_format == DD_PIXEL_FORMAT565)
			{
				RGB16Bit = RGB16Bit565;
				core::Write_Error("\npixel format = 5.6.5");
			} // end else
			else if (pixel_format == DD_PIXEL_FORMAT8)
			{
				core::Write_Error("\npixel format = 8.8.8");
			}
			else if (pixel_format == DD_PIXEL_FORMATALPHA888)
			{
				core::Write_Error("\npixel format = 8.8.8.8\n");
			}

			// only need a backbuffer for fullscreen modes
			if (isFullScreen)
			{
				// query for the backbuffer i.e the secondary surface
				ddscaps.dwCaps = DDSCAPS_BACKBUFFER;

				if (FAILED(lpddsprimary->GetAttachedSurface(&ddscaps, &lpddsback)))
					return(0);

			} // end if
			else
			{
				// must be windowed, so create a double buffer that will be blitted
				// rather than flipped as in full screen mode
				lpddsback = DDraw_Create_Surface(ScreenSize.Width, ScreenSize.Height); // int mem_flags, USHORT color_key_flag);

			} // end else

			  // create a palette only if 8bit mode
#if(1)
			if (pixel_format == DD_PIXEL_FORMAT8)
			{
				// create and attach palette
				// clear all entries, defensive programming
				memset(palette, 0, MAX_COLORS_PALETTE * sizeof(PALETTEENTRY));

				// load a pre-made "good" palette off disk
				Load_Palette_From_File(DEFAULT_PALETTE_FILE, palette);

				// load and attach the palette, test for windowed mode
				if (!isFullScreen)
				{
					// in windowed mode, so the first 10 and last 10 entries have
					// to be slightly modified as does the call to createpalette
					// reset the peFlags bit to PC_EXPLICIT for the "windows" colors
					for (index = 0; index < 10; index++)
						palette[index].peFlags = palette[index + 246].peFlags = PC_EXPLICIT;

					// now create the palette object, but disable access to all 256 entries
					if (FAILED(lpdd->CreatePalette(DDPCAPS_8BIT | DDPCAPS_INITIALIZE,
						palette, &lpddpal, NULL)))
						return(0);

				} // end 
				else
				{
					// in fullscreen mode, so simple create the palette with the default palette
					// and fill in all 256 entries
					if (FAILED(lpdd->CreatePalette(DDPCAPS_8BIT | DDPCAPS_INITIALIZE | DDPCAPS_ALLOW256,
						palette, &lpddpal, NULL)))
						return(0);

				} // end if

				  // now attach the palette to the primary surface
				if (FAILED(lpddsprimary->SetPalette(lpddpal)))
					return(0);

			} // end if attach palette for 8bit mode
#endif
			  // clear out both primary and secondary surfaces
			if (!isFullScreen)
			{
				// only clear backbuffer
				DDraw_Fill_Surface(lpddsback, 0);
			} // end if
			else
			{
				// fullscreen, simply clear everything
				DDraw_Fill_Surface(lpddsprimary, 0);
				DDraw_Fill_Surface(lpddsback, 0);
			} // end else

			  // set software algorithmic clipping region
			ViewPort.UpperLeftCorner.X = 0;
			ViewPort.UpperLeftCorner.Y = 0;
			ViewPort.LowerRightCorner.X = ScreenSize.Width - 1;
			ViewPort.LowerRightCorner.Y = ScreenSize.Height - 1;


			// setup backbuffer clipper always
			RECT screen_rect = { 0, 0, (long)ScreenSize.Width,  (long)ScreenSize.Height };
			lpddclipper = DDraw_Attach_Clipper(lpddsback, 1, &screen_rect);

			// set up windowed mode clipper
			if (!isFullScreen)
			{
				// set windowed clipper
				if (FAILED(lpdd->CreateClipper(0, &lpddclipperwin, NULL)))
					return(0);

				if (FAILED(lpddclipperwin->SetHWnd(0, HWnd)))
					return(0);

				if (FAILED(lpddsprimary->SetClipper(lpddclipperwin)))
					return(0);
			} // end if screen windowed

			  // return success
			return(1);
		}


#pragma region InitDriver

		// this function creates an offscreen plain surface
		LPDIRECTDRAWSURFACE7 CHalfSoftWareDriver::DDraw_Create_Surface(int width,
			int height,
			int mem_flags,
			USHORT color_key_value)
		{
			// this function creates an offscreen plain surface

			DDSURFACEDESC2 ddsd;         // working description
			LPDIRECTDRAWSURFACE7 lpdds;  // temporary surface

										 // set to access caps, width, and height
			memset(&ddsd, 0, sizeof(ddsd));
			ddsd.dwSize = sizeof(ddsd);
			ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;

			// set dimensions of the new bitmap surface
			ddsd.dwWidth = width;
			ddsd.dwHeight = height;

			// set surface to offscreen plain
			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | mem_flags;

			// create the surface
			if (FAILED(lpdd->CreateSurface(&ddsd, &lpdds, NULL)))
				return(NULL);

			// set color key to default color 000
			// note that if this is a 8bit bob then palette index 0 will be 
			// transparent by default
			// note that if this is a 16bit bob then RGB value 000 will be 
			// transparent
			DDCOLORKEY color_key; // used to set color key
			color_key.dwColorSpaceLowValue = color_key_value;
			color_key.dwColorSpaceHighValue = color_key_value;

			// now set the color key for source blitting
			lpdds->SetColorKey(DDCKEY_SRCBLT, &color_key);

			// return surface
			return(lpdds);
		} // end DDraw_Create_Surface

		int CHalfSoftWareDriver::DDraw_Fill_Surface(LPDIRECTDRAWSURFACE7 lpdds, u32 color, RECT *client)
		{
			DDBLTFX ddbltfx; // this contains the DDBLTFX structure

							 // clear out the structure and set the size field 
			DDRAW_INIT_STRUCT(ddbltfx);

			// set the dwfillcolor field to the desired color
			ddbltfx.dwFillPixel = color;

			// ready to blt to surface
			lpdds->Blt(client,     // ptr to dest rectangle
				NULL,       // ptr to source surface, NA            
				NULL,       // ptr to source rectangle, NA
				DDBLT_COLORFILL | DDBLT_WAIT,   // fill and wait                   
				&ddbltfx);  // ptr to DDBLTFX structure

							// return success
			return(1);
		} // end DDraw_Fill_Surface

		s32 CHalfSoftWareDriver::Load_Palette_From_File(c8 *filename, LPPALETTEENTRY palette)
		{
			// this function loads a palette from disk into a palette
			// structure, but does not set the pallette

			FILE *fp_file; // working file

						   // try and open file
						   //	if ((fp_file = fopen(filename, "r")) == NULL)
			if (!fopen_s(&fp_file, filename, "r"))
				return(0);

			// read in all 256 colors RGBF
			for (int index = 0; index < MAX_COLORS_PALETTE; index++)
			{
				// read the next entry in
				fscanf_s(fp_file, "%d %d %d %d", (int*)&palette[index].peRed,
					(int*)&palette[index].peGreen,
					(int*)&palette[index].peBlue,
					(int*)&palette[index].peFlags);
			} // end for index

			  // close the file
			fclose(fp_file);

			// return success
			return(1);
		} // end Load_Palette_From_Disk



		LPDIRECTDRAWCLIPPER CHalfSoftWareDriver::DDraw_Attach_Clipper(LPDIRECTDRAWSURFACE7 lpdds,
			int num_rects,
			LPRECT clip_list)

		{
			// this function creates a clipper from the sent clip list and attaches
			// it to the sent surface

			int index;                         // looping var
			LPDIRECTDRAWCLIPPER lpddclipper;   // pointer to the newly created dd clipper
			LPRGNDATA region_data;             // pointer to the region data that contains
											   // the header and clip list

											   // first create the direct draw clipper
			if (FAILED(lpdd->CreateClipper(0, &lpddclipper, NULL)))
				return(NULL);

			// now create the clip list from the sent data

			// first allocate memory for region data
			region_data = (LPRGNDATA)malloc(sizeof(RGNDATAHEADER) + num_rects * sizeof(RECT));

			// now copy the rects into region data
			memcpy(region_data->Buffer, clip_list, sizeof(RECT)*num_rects);

			// set up fields of header
			region_data->rdh.dwSize = sizeof(RGNDATAHEADER);
			region_data->rdh.iType = RDH_RECTANGLES;
			region_data->rdh.nCount = num_rects;
			region_data->rdh.nRgnSize = num_rects * sizeof(RECT);

			region_data->rdh.rcBound.left = 64000;
			region_data->rdh.rcBound.top = 64000;
			region_data->rdh.rcBound.right = -64000;
			region_data->rdh.rcBound.bottom = -64000;

			// find bounds of all clipping regions
			for (index = 0; index < num_rects; index++)
			{
				// test if the next rectangle unioned with the current bound is larger
				if (clip_list[index].left < region_data->rdh.rcBound.left)
					region_data->rdh.rcBound.left = clip_list[index].left;

				if (clip_list[index].right > region_data->rdh.rcBound.right)
					region_data->rdh.rcBound.right = clip_list[index].right;

				if (clip_list[index].top < region_data->rdh.rcBound.top)
					region_data->rdh.rcBound.top = clip_list[index].top;

				if (clip_list[index].bottom > region_data->rdh.rcBound.bottom)
					region_data->rdh.rcBound.bottom = clip_list[index].bottom;

			} // end for index

			  // now we have computed the bounding rectangle region and set up the data
			  // now let's set the clipping list

			if (FAILED(lpddclipper->SetClipList(region_data, 0)))
			{
				// release memory and return error
				free(region_data);
				return(NULL);
			} // end if

			  // now attach the clipper to the surface
			if (FAILED(lpdds->SetClipper(lpddclipper)))
			{
				// release memory and return error
				free(region_data);
				return(NULL);
			} // end if

			  // all is well, so release memory and send back the pointer to the new clipper
			free(region_data);
			return(lpddclipper);

		} // end DDraw_Attach_Clipper  
#pragma endregion

		  /**! Get the back surface to do something.
		  */
		void* CHalfSoftWareDriver::getBackSurface()
		{
			return lpddsback;
		}


		void CHalfSoftWareDriver::reset()
		{
			DDraw_Shutdown();
			initDriver();
		}

		void CHalfSoftWareDriver::OnResize(const core::dimension2d<u32>& size)
		{
			if (!lpdd)
				return;

			CNullDriver::OnResize(size);

			ScreenSize = size;

			reset();

		}

		s32 CHalfSoftWareDriver::DDraw_Flip(void)
		{
			// this function flip the primary surface with the secondary surface

			// test if either of the buffers are locked
			if (primary_buffer || back_buffer)
				return(0);

			// flip pages
			if (isFullScreen)
				while (FAILED(lpddsprimary->Flip(NULL, DDFLIP_WAIT)));
			else
			{
				RECT    dest_rect;    // used to compute destination rectangle

									  // get the window's rectangle in screen coordinates
				GetWindowRect(HWnd, &dest_rect);

				// compute the destination rectangle
				dest_rect.left += window_client_x0;
				dest_rect.top += window_client_y0;

				dest_rect.right = dest_rect.left + ScreenSize.Width;
				dest_rect.bottom = dest_rect.top + ScreenSize.Height;

				// clip the screen coords 
				/*	RECT* srcRct = 0;
				RECT sourceRectData;
				if (SceneSourceRect)
				{
				srcRct = &sourceRectData;
				sourceRectData.left = SceneSourceRect->UpperLeftCorner.X;
				sourceRectData.top = SceneSourceRect->UpperLeftCorner.Y;
				sourceRectData.right = SceneSourceRect->LowerRightCorner.X;
				sourceRectData.bottom = SceneSourceRect->LowerRightCorner.Y;
				}
				*/

				// blit the entire back surface to the primary
				if (FAILED(lpddsprimary->Blt(&dest_rect, lpddsback, NULL, DDBLT_WAIT, NULL)))//dest_rect
					return(0);

			} // end if

			  // return success
			return(1);

		} // end DDraw_Flip


		u8 *CHalfSoftWareDriver::DDraw_Lock_Back_Surface(void)
		{
			// this function locks the secondary back surface and returns a pointer to it
			// and updates the global variables secondary buffer, and back_lpitch

			// is this surface already locked
			if (back_buffer)
			{
				// return to current lock
				return(back_buffer);
			} // end if

			  // lock the primary surface
			DDRAW_INIT_STRUCT(ddsd);
			lpddsback->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL);

			// set globals
			back_buffer = (UCHAR *)ddsd.lpSurface;
			back_lpitch = ddsd.lPitch;

			// return pointer to surface
			return(back_buffer);

		} // end DDraw_Lock_Back_Surface

		s32 CHalfSoftWareDriver::DDraw_Unlock_Back_Surface(void)
		{
			// this unlocks the secondary

			// is this surface valid
			if (!back_buffer)
				return(0);

			// unlock the secondary surface
			lpddsback->Unlock(NULL);

			// reset the secondary surface
			back_buffer = NULL;
			back_lpitch = 0;

			// return success
			return(1);
		} // end DDraw_Unlock_Back_Surface

		int CHalfSoftWareDriver::DDraw_Shutdown(void)
		{
			// this function release all the resources directdraw
			// allocated, mainly to com objects

			// release the clippers first
			if (lpddclipper)
				lpddclipper->Release();

			if (lpddclipperwin)
				lpddclipperwin->Release();

			// release the palette if there is one
			if (lpddpal)
				lpddpal->Release();

			// release the secondary surface
			if (lpddsback)
				lpddsback->Release();

			// release the primary surface
			if (lpddsprimary)
				lpddsprimary->Release();

			// finally, the main dd object
			if (lpdd)
				lpdd->Release();

			// return success
			return(1);
		} // end DDraw_Shutdown


		//**************part two***************
		// returns the current size of the screen or rendertarget
		const core::dimension2d<u32>& CHalfSoftWareDriver::getCurrentRenderTargetSize() const
		{
			//if (CurrentRendertargetSize.Width == 0)
			return ScreenSize;
			//else
			//	return CurrentRendertargetSize;
		}




	}//end video
}//end cj

namespace vg
{
	namespace fw
	{
		CHalfSoftWareDriver* createHalfSoftDriver(const core::dimension2d<u32>& screenSize, HWND window, u32 bits,
			bool fullscreen, bool stencibuffer)
		{
			CHalfSoftWareDriver* swd = new CHalfSoftWareDriver(screenSize, window, fullscreen,
				stencibuffer);

			swd->setContent(screenSize, window, bits, fullscreen);

			if (!swd->initDriver())
			{
				swd->drop();
				swd = 0;
			}
			return swd;
		}
	}
}