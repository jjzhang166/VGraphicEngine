#ifndef __VG_VR_TEXTURE_MANAGER_H_INCLUDE__
#define __VG_VR_TEXTURE_MANAGER_H_INCLUDE__
#include "ConfigForVR.h"
#include "IReferenceCounted.h"
#include "Texture.h"
#include "vgArray.h"

namespace vg
{
	namespace vr
	{

		//! Orginized the textures including render surface.
		/**
		*/
		class VRTexturesManager :public virtual IReferenceCounted
		{

		public:

			VRTexturesManager()
			{
				init();
			}

			~VRTexturesManager()
			{
				for (u32 i = 0; i < ArrayTextures.size(); ++i)
				{
					delete ArrayTextures[i];
				}
				ArrayTextures.clear();
				if (TexTexIDMap)
					free(TexTexIDMap);
			}

			virtual int createNewTexture(ECOLOR_FORMAT colorFormat,u32 width,u32 height)
			{
				Texture* tex = new Texture(colorFormat, core::dimension2du(width, height));
				if (!tex)
					return -1;
				ArrayTextures.push_back(tex);
				return ArrayTextures.size() - 1;
			}

			virtual int addSurface(Texture** surface)
			{
				if (*surface)
				{
					ArrayTextures.push_back(*surface);
					return ArrayTextures.size() - 1;
				}
				return -1;
			}

			virtual Texture* getSurface(u32 surfaceID)
			{
				if (surfaceID >= ArrayTextures.size())
					return nullptr;
				return ArrayTextures[surfaceID];
			}

			virtual Texture* getDefaultTexture()
			{
				return ArrayTextures[DefaultTextureID];
			}

			virtual u32 getDefaultTextureID()
			{
				return DefaultTextureID;
			}

			virtual Texture** getTexTexIDMap()
			{
				return TexTexIDMap;
			}

			// Active the slot position with the texture(whose id is texid).
			virtual bool activeTexture(u32 slotPosition,u32 texid)
			{
				if (texid >= ArrayTextures.size())
					return false;
				TexTexIDMap[slotPosition] = ArrayTextures[texid];
				return true;
			}

		private:
			// create the default texture Checkerboard
			virtual void init()
			{
				Texture* tex = new Texture(ECF_A8R8G8B8, core::dimension2du(256, 256), true);
				ArrayTextures.push_back(tex);
				DefaultTextureID = ArrayTextures.size() - 1;
				TexTexIDMap = (Texture**)malloc(TEX_NUMBER_SUPORT * sizeof(Texture*));//(Texture**)new (Texture*)[TEX_NUMBER_SUPORT];
			}

			core::array<Texture*> ArrayTextures;

			u32 DefaultTextureID;
			Texture** TexTexIDMap;
		};
	}
}

#endif