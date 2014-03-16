//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Partial refactor by: Anis A. Hireche (C) 2014 - anishireche@gmail.com
//-----------------------------------------------------------------------------

#include "gfx/D3D9/gfxD3D9Device.h"
#include "gfx/D3D9/gfxD3D9EnumTranslate.h"
#include "gfx/bitmap/bitmapUtils.h"
#include "gfx/gfxCardProfile.h"
#include "gfx/gfxStringEnumTranslate.h"
#include "core/strings/unicode.h"
#include "core/util/swizzle.h"
#include "core/util/safeDelete.h"
#include "console/console.h"
#include "core/resourceManager.h"

/*
	anis -> GFXFormatR8G8B8 has now the same behaviour as GFXFormatR8G8B8X8. 
	This is because 24 bit format are now deprecated by microsoft, for data alignment reason there's no changes beetween 24 and 32 bit formats.
	DirectX 10-11 both have 24 bit format no longer.
*/

GFXD3D9TextureManager::GFXD3D9TextureManager() 
{
   dMemset( mCurTexSet, 0, sizeof( mCurTexSet ) );   
   static_cast<GFXD3D9Device*>( GFX )->getDevice()->GetDeviceCaps(&mDeviceCaps);
}

GFXD3D9TextureManager::~GFXD3D9TextureManager()
{
   // Destroy texture table now so just in case some texture objects
   // are still left, we don't crash on a pure virtual method call.
   SAFE_DELETE_ARRAY( mHashTable );
}

//-----------------------------------------------------------------------------
// _innerCreateTexture
//-----------------------------------------------------------------------------
void GFXD3D9TextureManager::_innerCreateTexture( GFXD3D9TextureObject *retTex, 
                                               U32 height, 
                                               U32 width, 
                                               U32 depth,
                                               GFXFormat format, 
                                               GFXTextureProfile *profile, 
                                               U32 numMipLevels,
                                               bool forceMips,
                                               S32 antialiasLevel)
{
   GFXD3D9Device* d3d = static_cast<GFXD3D9Device*>(GFX);

   // Some relevant helper information...
   bool supportsAutoMips = GFX->getCardProfiler()->queryProfile("autoMipMapLevel", true);
   
   DWORD usage = 0;
   D3DPOOL pool = D3DPOOL_DEFAULT;

   retTex->mProfile = profile;

   D3DFORMAT d3dTextureFormat = GFXD3D9TextureFormat[format];

   if( retTex->mProfile->isDynamic() )
   {
      usage = D3DUSAGE_DYNAMIC;
   }
   else
   {
      usage = 0;
      pool = D3DPOOL_MANAGED;
   }

   if( retTex->mProfile->isRenderTarget() )
   {
      usage |= D3DUSAGE_RENDERTARGET;
      pool = D3DPOOL_DEFAULT;
   }

   if(retTex->mProfile->isZTarget())
   {
      usage |= D3DUSAGE_DEPTHSTENCIL;
      pool = D3DPOOL_DEFAULT;
   }

   if( retTex->mProfile->isSystemMemory() )
   {
      pool = D3DPOOL_SYSTEMMEM;
   }

   if( supportsAutoMips && 
       !forceMips &&
       !retTex->mProfile->isSystemMemory() &&
       numMipLevels == 0 &&
       !(depth > 0) )
   {
      usage |= D3DUSAGE_AUTOGENMIPMAP;
   }

   // Set the managed flag...
   retTex->isManaged = (pool == D3DPOOL_MANAGED);
   
   if(depth > 0)
   {
		HRESULT hr = static_cast<GFXD3D9Device*>(GFX)->getDevice()->CreateVolumeTexture(width, height, depth, numMipLevels, usage, d3dTextureFormat, pool, retTex->get3DTexPtr(), NULL);

	    if(FAILED(hr)) 
	    {
		   AssertFatal(false, "GFXD3D9TextureManager::_createTexture - failed to create volume texture!");
	    }

        retTex->mTextureSize.set(width, height, depth);
        retTex->mMipLevels = retTex->get3DTex()->GetLevelCount();
        // required for 3D texture support - John Kabus
	    retTex->mFormat = format;
   }
   else
   {
      // Figure out AA settings for depth and render targets
      D3DMULTISAMPLE_TYPE mstype;
      DWORD mslevel;

      switch (antialiasLevel)
      {
         case 0 :
            mstype = D3DMULTISAMPLE_NONE;
            mslevel = 0;
            break;
         case AA_MATCH_BACKBUFFER :
            mstype = d3d->getMultisampleType();
            mslevel = d3d->getMultisampleLevel();
            break;
         default :
            {
               mstype = D3DMULTISAMPLE_NONMASKABLE;
               mslevel = antialiasLevel;
            }
            break;
      }
     
      if(retTex->mProfile->isZTarget())
      {
            HRESULT hr = static_cast<GFXD3D9Device*>( GFX )->getDevice()->CreateDepthStencilSurface(width, height, d3dTextureFormat, mstype, mslevel, retTex->mProfile->canDiscard(), retTex->getSurfacePtr(), NULL);

			if(FAILED(hr)) 
			{
				AssertFatal(false, "Failed to create Z surface");
			}

			retTex->mFormat = format; // Assigning format like this should be fine.
      }
      else
      {
		 HRESULT hr = static_cast<GFXD3D9Device*>( GFX )->getDevice()->CreateTexture(width, height, numMipLevels, usage, d3dTextureFormat, pool, retTex->get2DTexPtr(), NULL);

		 if(FAILED(hr)) 
		 {
			AssertFatal(false, "GFXD3D9TextureManager::_createTexture - failed to create texture!");
		 }

         // If this is a render target, and it wants AA or wants to match the backbuffer (for example, to share the z)
         // Check the caps though, if we can't stretchrect between textures, use the old RT method.  (Which hopefully means
         // that they can't force AA on us as well.)
         if (retTex->mProfile->isRenderTarget() && mslevel != 0 && (mDeviceCaps.Caps2 && D3DDEVCAPS2_CAN_STRETCHRECT_FROM_TEXTURES))
         {
            HRESULT hr = static_cast<GFXD3D9Device*>( GFX )->getDevice()->CreateRenderTarget(width, height, d3dTextureFormat, mstype, mslevel, false, retTex->getSurfacePtr(), NULL);

			if(FAILED(hr)) 
			{
				AssertFatal(false, "GFXD3D9TextureManager::_createTexture - unable to create render target");
			}

         }

         // All done!
         retTex->mMipLevels = retTex->get2DTex()->GetLevelCount();
      }

      // Get the actual size of the texture...
      D3DSURFACE_DESC probeDesc;
      ZeroMemory(&probeDesc, sizeof probeDesc);

      if( retTex->get2DTex() != NULL )
	  {
		 HRESULT hr = retTex->get2DTex()->GetLevelDesc(0, &probeDesc);

		 if(FAILED(hr)) 
		 {
			AssertFatal(false, "Failed to get surface description");
		 }
	  }
      else if( retTex->getSurface() != NULL )
	  {
         HRESULT hr = retTex->getSurface()->GetDesc(&probeDesc);

		 if(FAILED(hr)) 
		 {
			AssertFatal(false, "Failed to get surface description");
		 }
	  }

      retTex->mTextureSize.set(probeDesc.Width, probeDesc.Height, 0);
      
      int fmt = probeDesc.Format;

      GFXREVERSE_LOOKUP( GFXD3D9TextureFormat, GFXFormat, fmt );
      retTex->mFormat = (GFXFormat)fmt;
   }
}

//-----------------------------------------------------------------------------
// createTexture
//-----------------------------------------------------------------------------
GFXTextureObject *GFXD3D9TextureManager::_createTextureObject( U32 height, 
                                                               U32 width,
                                                               U32 depth,
                                                               GFXFormat format, 
                                                               GFXTextureProfile *profile, 
                                                               U32 numMipLevels,
                                                               bool forceMips, 
                                                               S32 antialiasLevel,
                                                               GFXTextureObject *inTex )
{
   GFXD3D9TextureObject *retTex;
   if ( inTex )
   {
      AssertFatal(static_cast<GFXD3D9TextureObject*>( inTex ), "GFXD3D9TextureManager::_createTexture() - Bad inTex type!");
      retTex = static_cast<GFXD3D9TextureObject*>( inTex );
      retTex->release();
   }      
   else
   {
      retTex = new GFXD3D9TextureObject(GFX, profile);
      retTex->registerResourceWithDevice(GFX);
   }

   _innerCreateTexture(retTex, height, width, depth, format, profile, numMipLevels, forceMips, antialiasLevel);

   return retTex;
}

bool GFXD3D9TextureManager::_loadTexture(GFXTextureObject *aTexture, GBitmap *pDL)
{
   PROFILE_SCOPE(GFXD3D9TextureManager_loadTexture);

   GFXD3D9TextureObject *texture = static_cast<GFXD3D9TextureObject*>(aTexture);

   // Check with profiler to see if we can do automatic mipmap generation.
   const bool supportsAutoMips = GFX->getCardProfiler()->queryProfile("autoMipMapLevel", true);

   // Helper bool
   const bool isCompressedTexFmt = aTexture->mFormat >= GFXFormatDXT1 && aTexture->mFormat <= GFXFormatDXT5;

   // Settings for mipmap generation
   U32 maxDownloadMip = pDL->getNumMipLevels();
   U32 nbMipMapLevel  = pDL->getNumMipLevels();

   if( supportsAutoMips && !isCompressedTexFmt )
   {
      maxDownloadMip = 1;
      nbMipMapLevel  = aTexture->mMipLevels;
   }

   // Fill the texture...
   for( int i = 0; i < maxDownloadMip; i++ )
   {
		LPDIRECT3DSURFACE9 surf = NULL;
		HRESULT hr = texture->get2DTex()->GetSurfaceLevel( i, &surf );

		if(FAILED(hr)) 
		{
			AssertFatal(false, "Failed to get surface");
		}

	  D3DLOCKED_RECT lockedRect;
      surf->LockRect( &lockedRect, NULL, 0 );

      switch( texture->mFormat )
      {
      case GFXFormatR8G8B8:
         {
			 PROFILE_SCOPE(Swizzle24_Upload);
             AssertFatal(pDL->getFormat() == GFXFormatR8G8B8, "Assumption failed");

			 U8* Bits = new U8[pDL->getWidth(i) * pDL->getHeight(i) * 4];
             dMemcpy(Bits, pDL->getBits(i), pDL->getWidth(i) * pDL->getHeight(i) * 3);
			 bitmapConvertRGB_to_RGBX(&Bits, pDL->getWidth(i) * pDL->getHeight(i));

             GFX->getDeviceSwizzle32()->ToBuffer(lockedRect.pBits, Bits, pDL->getWidth(i) * pDL->getHeight(i) * 4);
         }
         break;

      case GFXFormatR8G8B8A8:
      case GFXFormatR8G8B8X8:
         {
            PROFILE_SCOPE(Swizzle32_Upload);
            GFX->getDeviceSwizzle32()->ToBuffer(lockedRect.pBits, pDL->getBits(i), pDL->getWidth(i) * pDL->getHeight(i) * pDL->getBytesPerPixel());
         }
         break;

      default:
         {
            // Just copy the bits in no swizzle or padding
            PROFILE_SCOPE(SwizzleNull_Upload);
            AssertFatal( pDL->getFormat() == texture->mFormat, "Format mismatch");
            dMemcpy( lockedRect.pBits, pDL->getBits(i), pDL->getWidth(i) * pDL->getHeight(i) * pDL->getBytesPerPixel() );
         }
      }

      surf->UnlockRect();
      surf->Release();
   }

   return true;          
}

bool GFXD3D9TextureManager::_loadTexture(GFXTextureObject *inTex, void *raw)
{
   PROFILE_SCOPE(GFXD3D9TextureManager_loadTextureRaw);

   GFXD3D9TextureObject *texture = (GFXD3D9TextureObject *) inTex;

   // currently only for volume textures...
   if(texture->getDepth() < 1) return false;
  
   U8* Bits = NULL;

   if(texture->mFormat == GFXFormatR8G8B8)
   {
	   // anis -> convert 24 bit to 32 bit
	   Bits = new U8[texture->getWidth() * texture->getHeight() * texture->getDepth() * 4];
	   dMemcpy(Bits, raw, texture->getWidth() * texture->getHeight() * texture->getDepth() * 3);
	   bitmapConvertRGB_to_RGBX(&Bits, texture->getWidth() * texture->getHeight() * texture->getDepth());
   }

   U32 bytesPerPix = 1;

   switch(texture->mFormat)
   {
      case GFXFormatR8G8B8:
      case GFXFormatR8G8B8A8:
      case GFXFormatR8G8B8X8:
         bytesPerPix = 4;
         break;
   }

   U32 slicePitch = texture->getWidth() * texture->getHeight() * texture->getDepth() * bytesPerPix;

   D3DBOX box;
   box.Left    = 0;
   box.Right   = texture->getWidth();
   box.Front   = 0;
   box.Back    = texture->getDepth();
   box.Top     = 0;
   box.Bottom  = texture->getHeight();

   LPDIRECT3DVOLUME9 volume = NULL;
   HRESULT hr = texture->get3DTex()->GetVolumeLevel(0, &volume);

   if(FAILED(hr)) 
   {
      AssertFatal(false, "Failed to load volume");
   }

   D3DLOCKED_BOX lockedBox;
   volume->LockBox(&lockedBox, &box, 0);
   
   if(texture->mFormat == GFXFormatR8G8B8) // anis -> converted format also for volume textures
		dMemcpy(lockedBox.pBits, Bits, slicePitch);
   else
		dMemcpy(lockedBox.pBits, raw, slicePitch);

   volume->UnlockBox();
   volume->Release();
   return true;
}

bool GFXD3D9TextureManager::_refreshTexture(GFXTextureObject *texture)
{
   U32 usedStrategies = 0;
   GFXD3D9TextureObject *realTex = static_cast<GFXD3D9TextureObject *>(texture);

   if(texture->mProfile->doStoreBitmap())
   {
      if(texture->mBitmap)
         _loadTexture(texture, texture->mBitmap);

      if(texture->mDDS)
         _loadTexture(texture, texture->mDDS);

      usedStrategies++;
   }

   if(texture->mProfile->isRenderTarget() || texture->mProfile->isDynamic() || texture->mProfile->isZTarget())
   {
      realTex->release();
      _innerCreateTexture(realTex, texture->getHeight(), texture->getWidth(), texture->getDepth(), texture->mFormat, texture->mProfile, texture->mMipLevels, false, texture->mAntialiasLevel);
      usedStrategies++;
   }

   AssertFatal(usedStrategies < 2, "GFXD3D9TextureManager::_refreshTexture - Inconsistent profile flags!");

   return true;
}

bool GFXD3D9TextureManager::_freeTexture(GFXTextureObject *texture, bool zombify)
{
   AssertFatal(static_cast<GFXD3D9TextureObject *>(texture),"Not an actual d3d texture object!");
   GFXD3D9TextureObject *tex = static_cast<GFXD3D9TextureObject *>( texture );

   // If it's a managed texture and we're zombifying, don't blast it, D3D allows
   // us to keep it.
   if(zombify && tex->isManaged)
      return true;

   tex->release();

   return true;
}

/// Load a texture from a proper DDSFile instance.
bool GFXD3D9TextureManager::_loadTexture(GFXTextureObject *aTexture, DDSFile *dds)
{
   PROFILE_SCOPE(GFXD3D9TextureManager_loadTextureDDS);

   GFXD3D9TextureObject *texture = static_cast<GFXD3D9TextureObject*>(aTexture);

   // Fill the texture...
   for( int i = 0; i < aTexture->mMipLevels; i++ )
   {
		PROFILE_SCOPE(GFXD3DTexMan_loadSurface);

		LPDIRECT3DSURFACE9 surf = NULL;
		HRESULT hr = texture->get2DTex()->GetSurfaceLevel( i, &surf );

		if(FAILED(hr)) 
		{
			AssertFatal(false, "Failed to get surface");
		}

		D3DLOCKED_RECT lockedRect;
		hr = surf->LockRect( &lockedRect, NULL, 0 );

		if(FAILED(hr)) 
		{
			AssertFatal(false, "Failed to lock surface level for load");
		}

		AssertFatal( dds->mSurfaces.size() > 0, "Assumption failed. DDSFile has no surfaces." );

		if ( dds->getSurfacePitch( i ) != lockedRect.Pitch )
		{
			// Do a row-by-row copy.
			U32 srcPitch = dds->getSurfacePitch( i );
			U32 srcHeight = dds->getHeight();
			U8* srcBytes = dds->mSurfaces[0]->mMips[i];
			U8* dstBytes = (U8*)lockedRect.pBits;
			for (U32 i = 0; i<srcHeight; i++)          
			{
				dMemcpy( dstBytes, srcBytes, srcPitch );
				dstBytes += lockedRect.Pitch;
				srcBytes += srcPitch;
			}           
			surf->UnlockRect();
			surf->Release();
			return true;
		}

		dMemcpy(lockedRect.pBits, dds->mSurfaces[0]->mMips[i], dds->getSurfaceSize(i));

		surf->UnlockRect();
		surf->Release();
   }

   return true;
}