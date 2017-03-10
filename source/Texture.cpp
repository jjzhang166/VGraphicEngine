
#include "Texture.h"
#include "CColorConverter.h"
#include "TextureHelper.h"
#include "Blit.h"


namespace vg
{
	namespace vr
	{

		//! Constructor of empty image
		Texture::Texture(ECOLOR_FORMAT format, const core::dimension2d<u32>& size)
			:Data(0), Size(size), Format(format), DeleteMemory(true)
		{
			initData();
		}

		void Texture::reset(ECOLOR_FORMAT format, const core::dimension2d<u32>& size, void* data)
		{
			Format = format;
			Size = size;
			Data = (u8*)data;
		}

		//! Constructor from raw data
		Texture::Texture(ECOLOR_FORMAT format, const core::dimension2d<u32>& size, void* data,
			bool ownForeignMemory, bool deleteForeignMemory)
			: Data(0), Size(size), Format(format), DeleteMemory(deleteForeignMemory)
		{
			if (ownForeignMemory)
			{
				Data = (u8*)0xbe12444;
				initData();
				Data = (u8*)data;
			}
			else
			{
				Data = 0;
				initData();
				memcpy(Data, data, Size.Height * Pitch);
			}
		}


		//! assumes format and size has been set and creates the rest
		void Texture::initData()
		{
#ifdef _DEBUG
			setDebugName("Texture");
#endif
			BytesPerPixel = getBitsPerPixelFromFormat(Format) / 8;

			// Pitch should be aligned...
			Pitch = BytesPerPixel * Size.Width;

			if (!Data)
			{
				DeleteMemory = true;
				Data = new u8[Size.Height * Pitch];
			}
		}


		//! destructor
		Texture::~Texture()
		{
			if (DeleteMemory)
				delete[] Data;
		}


		//! Returns width and height of image data.
		const core::dimension2d<u32>& Texture::getDimension() const
		{
			return Size;
		}


		//! Returns bits per pixel.
		u32 Texture::getBitsPerPixel() const
		{
			return getBitsPerPixelFromFormat(Format);
		}


		//! Returns bytes per pixel
		u32 Texture::getBytesPerPixel() const
		{
			return BytesPerPixel;
		}


		//! Returns image data size in bytes
		u32 Texture::getImageDataSizeInBytes() const
		{
			return Pitch * Size.Height;
		}


		//! Returns image data size in pixels
		u32 Texture::getImageDataSizeInPixels() const
		{
			return Size.Width * Size.Height;
		}


		//! returns mask for red value of a pixel
		u32 Texture::getRedMask() const
		{
			switch (Format)
			{
			case ECF_A1R5G5B5:
				return 0x1F << 10;
			case ECF_R5G6B5:
				return 0x1F << 11;
			case ECF_R8G8B8:
				return 0x00FF0000;
			case ECF_A8R8G8B8:
				return 0x00FF0000;
			default:
				return 0x0;
			}
		}


		//! returns mask for green value of a pixel
		u32 Texture::getGreenMask() const
		{
			switch (Format)
			{
			case ECF_A1R5G5B5:
				return 0x1F << 5;
			case ECF_R5G6B5:
				return 0x3F << 5;
			case ECF_R8G8B8:
				return 0x0000FF00;
			case ECF_A8R8G8B8:
				return 0x0000FF00;
			default:
				return 0x0;
			}
		}


		//! returns mask for blue value of a pixel
		u32 Texture::getBlueMask() const
		{
			switch (Format)
			{
			case ECF_A1R5G5B5:
				return 0x1F;
			case ECF_R5G6B5:
				return 0x1F;
			case ECF_R8G8B8:
				return 0x000000FF;
			case ECF_A8R8G8B8:
				return 0x000000FF;
			default:
				return 0x0;
			}
		}


		//! returns mask for alpha value of a pixel
		u32 Texture::getAlphaMask() const
		{
			switch (Format)
			{
			case ECF_A1R5G5B5:
				return 0x1 << 15;
			case ECF_R5G6B5:
				return 0x0;
			case ECF_R8G8B8:
				return 0x0;
			case ECF_A8R8G8B8:
				return 0xFF000000;
			default:
				return 0x0;
			}
		}

		//! Returns pitch of image
		u32 Texture::getPitch() const
		{
			return Pitch;
		}

		//! sets a pixel
		void Texture::setPixel(u32 x, u32 y, const SColor &color, bool blend)
		{
			if (x >= Size.Width || y >= Size.Height)
				return;

			switch (Format)
			{
			case ECF_A1R5G5B5:
			{
				u16 * dest = (u16*)(Data + (y * Pitch) + (x << 1));
				*dest = A8R8G8B8toA1R5G5B5(color.color);
			} break;

			case ECF_R5G6B5:
			{
				u16 * dest = (u16*)(Data + (y * Pitch) + (x << 1));
				*dest = A8R8G8B8toR5G6B5(color.color);
			} break;

			case ECF_R8G8B8:
			{
				u8* dest = Data + (y * Pitch) + (x * 3);
				dest[0] = (u8)color.getRed();
				dest[1] = (u8)color.getGreen();
				dest[2] = (u8)color.getBlue();
			} break;

			case ECF_A8R8G8B8:
			{
				u32 * dest = (u32*)(Data + (y * Pitch) + (x << 2));
				*dest = blend ? PixelBlend32(*dest, color.color) : color.color;
			} break;
#ifndef _DEBUG
			default:
				break;
#endif
			}
		}

		//! Sets a pixel
		void Texture::setPixel(u32 x, u32 y, const glm::vec4 &color, bool blend )
		{
			setPixel(x, y, SColor(color), blend);
		}

		//! returns a pixel
		SColor Texture::getPixel(u32 x, u32 y) const
		{
			if (x >= Size.Width || y >= Size.Height)
				return SColor(0);

			switch (Format)
			{
			case ECF_A1R5G5B5:
				return A1R5G5B5toA8R8G8B8(((u16*)Data)[y*Size.Width + x]);
			case ECF_R5G6B5:
				return R5G6B5toA8R8G8B8(((u16*)Data)[y*Size.Width + x]);
			case ECF_A8R8G8B8:
				return ((u32*)Data)[y*Size.Width + x];
			case ECF_R8G8B8:
			{
				u8* p = Data + (y * 3)*Size.Width + (x * 3);
				return SColor(255, p[0], p[1], p[2]);
			}
#ifndef _DEBUG
			default:
				break;
#endif
			}

			return SColor(0);
		}


		//! Returns a pixel by ,(u,v)--u,v[0,1]
		//! Returns a pixel by ,(u,v)--u,v[0,1]
		glm::vec4 Texture::getColorf(const glm::vec2 coord) const
		{
			u32 x = (u32)(coord.x*(f32)Size.Width);
			u32 y = (u32)(coord.y*(f32)Size.Height);

			if (x >= Size.Width || y >= Size.Height)
				return glm::vec4(0);


			switch (Format)
			{
			case ECF_A1R5G5B5:
				return A1R5G5B5Toglmvec4(((u16*)Data)[y*Size.Width + x]);
			case ECF_R5G6B5:
				return R5G6B5Toglmvec4(((u16*)Data)[y*Size.Width + x]);
			case ECF_A8R8G8B8:
				return A8R8B8G8toglmvec4(((u32*)Data)[y*Size.Width + x]);
			case ECF_R8G8B8:
			{
				u8* p = Data + (y * 3)*Size.Width + (x * 3);
				return glm::vec4(U8toF32(p[0]), U8toF32(p[1]), U8toF32(p[2]), 1.f);
			}
#ifndef _DEBUG
			default:
				break;
#endif
			}
			return glm::vec4(0);
		}

		//! returns the color format
		ECOLOR_FORMAT Texture::getColorFormat() const
		{
			return Format;
		}


		//! copies this surface into another at given position
		void Texture::copyTo(Texture* target, const core::position2d<s32>& pos)
		{
			Blit(BLITTER_TEXTURE, target, 0, &pos, this, 0, 0);
		}


		//! copies this surface partially into another at given position
		void Texture::copyTo(Texture* target, const core::position2d<s32>& pos, const core::rect<s32>& sourceRect, const core::rect<s32>* clipRect)
		{
			Blit(BLITTER_TEXTURE, target, clipRect, &pos, this, &sourceRect, 0);
		}


		//! copies this surface into another, using the alpha mask, a cliprect and a color to add with
		void Texture::copyToWithAlpha(Texture* target, const core::position2d<s32>& pos, const core::rect<s32>& sourceRect, const SColor &color, const core::rect<s32>* clipRect)
		{
			// color blend only necessary on not full spectrum aka. color.color != 0xFFFFFFFF
			Blit(color.color == 0xFFFFFFFF ? BLITTER_TEXTURE_ALPHA_BLEND : BLITTER_TEXTURE_ALPHA_COLOR_BLEND,
				target, clipRect, &pos, this, &sourceRect, color.color);
		}


		//! copies this surface into another, scaling it to the target image size
		// note: this is very very slow.
		void Texture::copyToScaling(void* target, u32 width, u32 height, ECOLOR_FORMAT format, u32 pitch)
		{
			if (!target || !width || !height)
				return;

			const u32 bpp = getBitsPerPixelFromFormat(format) / 8;
			if (0 == pitch)
				pitch = width*bpp;

			if (Format == format && Size.Width == width && Size.Height == height)
			{
				if (pitch == Pitch)
				{
					memcpy(target, Data, height*pitch);
					return;
				}
				else
				{
					u8* tgtpos = (u8*)target;
					u8* srcpos = Data;
					const u32 bwidth = width*bpp;
					const u32 rest = pitch - bwidth;
					for (u32 y = 0; y<height; ++y)
					{
						// copy scanline
						memcpy(tgtpos, srcpos, bwidth);
						// clear pitch
						memset(tgtpos + bwidth, 0, rest);
						tgtpos += pitch;
						srcpos += Pitch;
					}
					return;
				}
			}

			const f32 sourceXStep = (f32)Size.Width / (f32)width;
			const f32 sourceYStep = (f32)Size.Height / (f32)height;
			s32 yval = 0, syval = 0;
			f32 sy = 0.0f;
			for (u32 y = 0; y<height; ++y)
			{
				f32 sx = 0.0f;
				for (u32 x = 0; x<width; ++x)
				{
					CColorConverter::convert_viaFormat(Data + syval + ((s32)sx)*BytesPerPixel, Format, 1, ((u8*)target) + yval + (x*bpp), format);
					sx += sourceXStep;
				}
				sy += sourceYStep;
				syval = ((s32)sy)*Pitch;
				yval += pitch;
			}
		}


		//! copies this surface into another, scaling it to the target image size
		// note: this is very very slow.
		void Texture::copyToScaling(Texture* target)
		{
			if (!target)
				return;

			const core::dimension2d<u32>& targetSize = target->getDimension();

			if (targetSize == Size)
			{
				copyTo(target);
				return;
			}

			copyToScaling(target->lock(), targetSize.Width, targetSize.Height, target->getColorFormat());
			target->unlock();
		}


		//! copies this surface into another, scaling it to fit it.
		void Texture::copyToScalingBoxFilter(Texture* target, s32 bias, bool blend)
		{
			const core::dimension2d<u32> destSize = target->getDimension();

			const f32 sourceXStep = (f32)Size.Width / (f32)destSize.Width;
			const f32 sourceYStep = (f32)Size.Height / (f32)destSize.Height;

			target->lock();

			s32 fx = core::ceil32(sourceXStep);
			s32 fy = core::ceil32(sourceYStep);
			f32 sx;
			f32 sy;

			sy = 0.f;
			for (u32 y = 0; y != destSize.Height; ++y)
			{
				sx = 0.f;
				for (u32 x = 0; x != destSize.Width; ++x)
				{
					target->setPixel(x, y,
						getPixelBox(core::floor32(sx), core::floor32(sy), fx, fy, bias), blend);
					sx += sourceXStep;
				}
				sy += sourceYStep;
			}

			target->unlock();
		}


		//! fills the surface with given color
		void Texture::fill(const SColor &color)
		{
			u32 c;

			switch (Format)
			{
			case ECF_A1R5G5B5:
				c = color.toA1R5G5B5();
				c |= c << 16;
				break;
			case ECF_R5G6B5:
				c = A8R8G8B8toR5G6B5(color.color);
				c |= c << 16;
				break;
			case ECF_A8R8G8B8:
				c = color.color;
				break;
			case ECF_R8G8B8:
			{
				u8 rgb[3];
				CColorConverter::convert_A8R8G8B8toR8G8B8(&color, 1, rgb);
				const u32 size = getImageDataSizeInBytes();
				for (u32 i = 0; i<size; i += 3)
				{
					memcpy(Data + i, rgb, 3);
				}
				return;
			}
			break;
			default:
				// TODO: Handle other formats
				return;
			}
			memset32(Data, c, getImageDataSizeInBytes());
		}


		//! get a filtered pixel
		inline SColor Texture::getPixelBox(s32 x, s32 y, s32 fx, s32 fy, s32 bias) const
		{
			SColor c;
			s32 a = 0, r = 0, g = 0, b = 0;

			for (s32 dx = 0; dx != fx; ++dx)
			{
				for (s32 dy = 0; dy != fy; ++dy)
				{
					c = getPixel(core::s32_min(x + dx, Size.Width - 1),
						core::s32_min(y + dy, Size.Height - 1)
					);

					a += c.getAlpha();
					r += c.getRed();
					g += c.getGreen();
					b += c.getBlue();
				}

			}

			s32 sdiv = s32_log2_s32(fx * fy);

			a = core::s32_clamp((a >> sdiv) + bias, 0, 255);
			r = core::s32_clamp((r >> sdiv) + bias, 0, 255);
			g = core::s32_clamp((g >> sdiv) + bias, 0, 255);
			b = core::s32_clamp((b >> sdiv) + bias, 0, 255);

			c.set(a, r, g, b);
			return c;
		}


	} // end namespace video
} // end namespace irr
