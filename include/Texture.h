// 
// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h
#ifndef __VG_VR_Texture_H_INCLUDE__
#define __VG_VR_Texture_H_INCLUDE__

#include "IReferenceCounted.h"
#include "position2d.h"
#include "rect.h"
#include "SColor.h"
#include "glm\glm.hpp"

namespace vg
{
	namespace vr
	{

		//! Interface for software image data.
		/** Image loaders create these images from files. IVideoDrivers convert
		these images into their (hardware) textures.
		*/
		class Texture : public virtual IReferenceCounted
		{
		public:

			//! constructor from raw image data
			/** \param useForeignMemory: If true, the image will use the data pointer
			directly and own it from now on, which means it will also try to delete [] the
			data when the image will be destructed. If false, the memory will by copied. */
			Texture(ECOLOR_FORMAT format, const core::dimension2d<u32>& size,
				void* data, bool ownForeignMemory = true, bool deleteMemory = true);

			//! constructor for empty image
			Texture(ECOLOR_FORMAT format, const core::dimension2d<u32>& size,bool DefaultTexture = false);

			void reset(ECOLOR_FORMAT format, const core::dimension2d<u32>& size,int lpitch, void* data);

			//! destructor
			virtual ~Texture();

			//! Lock function.
			virtual void* lock()
			{
				return Data;
			}

			//! Unlock function.
			virtual void unlock() {}

			//! Returns width and height of image data.
			virtual const core::dimension2d<u32>& getDimension() const ;

			//! Returns bits per pixel.
			virtual u32 getBitsPerPixel() const ;

			//! Returns bytes per pixel
			virtual u32 getBytesPerPixel() const ;

			//! Returns image data size in bytes
			virtual u32 getImageDataSizeInBytes() const ;

			// in pixel
			virtual u32 getWidth()
			{
				return Size.Width;
			}

			// in pixel
			virtual u32 getHeight()
			{
				return Size.Height;
			}

			//! Returns image data size in pixels
			virtual u32 getImageDataSizeInPixels() const ;

			//! Returns a pixel
			virtual SColor getPixel(u32 x, u32 y) const ;

			//! Returns a pixel by ,(u,v)--u,v[0,1]
			virtual glm::vec4 getColorf(const glm::vec2 coord) const ;

			//! Sets a pixel
			virtual void setPixel(u32 x, u32 y, const SColor &color, bool blend = false) ;

			//! Sets a pixel
			virtual void setPixel(u32 x, u32 y, const glm::vec4 &color, bool blend = true) ;

			//! Returns the color format
			virtual ECOLOR_FORMAT getColorFormat() const ;

			//! Returns mask for red value of a pixel
			virtual u32 getRedMask() const ;

			//! Returns mask for green value of a pixel
			virtual u32 getGreenMask() const ;

			//! Returns mask for blue value of a pixel
			virtual u32 getBlueMask() const ;

			//! Returns mask for alpha value of a pixel
			virtual u32 getAlphaMask() const ;

			//! Returns pitch of image
			virtual u32 getPitch() const ;

			//! Copies the image into the target, scaling the image to fit
			virtual void copyToScaling(void* target, u32 width, u32 height, ECOLOR_FORMAT format = ECF_A8R8G8B8, u32 pitch = 0) ;

			//! Copies the image into the target, scaling the image to fit
			virtual void copyToScaling(Texture* target) ;

			//! copies this surface into another
			virtual void copyTo(Texture* target, const core::position2d<s32>& pos = core::position2d<s32>(0, 0)) ;

			//! copies this surface into another
			virtual void copyTo(Texture* target, const core::position2d<s32>& pos, const core::rect<s32>& sourceRect, const core::rect<s32>* clipRect = 0) ;

			//! copies this surface into another, using the alpha mask and cliprect and a color to add with
			virtual void copyToWithAlpha(Texture* target, const core::position2d<s32>& pos,
				const core::rect<s32>& sourceRect, const SColor &color,
				const core::rect<s32>* clipRect = 0) ;

			//! copies this surface into another, scaling it to fit, appyling a box filter
			virtual void copyToScalingBoxFilter(Texture* target, s32 bias = 0, bool blend = false) ;

			//! fills the surface with given color
			virtual void fill(const SColor &color) ;

			//! get the amount of Bits per Pixel of the given color format
			static u32 getBitsPerPixelFromFormat(const ECOLOR_FORMAT format)
			{
				switch (format)
				{
				case ECF_A1R5G5B5:
					return 16;
				case ECF_R5G6B5:
					return 16;
				case ECF_R8G8B8:
					return 24;
				case ECF_A8R8G8B8:
					return 32;
				case ECF_R16F:
					return 16;
				case ECF_G16R16F:
					return 32;
				case ECF_A16B16G16R16F:
					return 64;
				case ECF_R32F:
					return 32;
				case ECF_G32R32F:
					return 64;
				case ECF_A32B32G32R32F:
					return 128;
				default:
					return 0;
				}
			}

			//! test if the color format is only viable for RenderTarget textures
			/** Since we don't have support for e.g. floating point Texture formats
			one should test if the color format can be used for arbitrary usage, or
			if it is restricted to RTTs. */
			static bool isRenderTargetOnlyFormat(const ECOLOR_FORMAT format)
			{
				switch (format)
				{
				case ECF_A1R5G5B5:
				case ECF_R5G6B5:
				case ECF_R8G8B8:
				case ECF_A8R8G8B8:
					return false;
				default:
					return true;
				}
			}

			virtual void setSizeChanged(bool value = false)
			{
				sizeChanged = value;
			}

			virtual bool getSizeChanged()
			{
				return sizeChanged;
			}
		private:

			//! assumes format and size has been set and creates the rest
			void initData();

			inline SColor getPixelBox(s32 x, s32 y, s32 fx, s32 fy, s32 bias) const;

			u8* Data;
			core::dimension2d<u32> Size;
			u32 BytesPerPixel;
			u32 Pitch;
			ECOLOR_FORMAT Format;

			bool DeleteMemory;
			bool sizeChanged;
		};

	} // end namespace vr
} // end namespace vg



#endif//! __VG_VR_Texture_H_INCLUDE__