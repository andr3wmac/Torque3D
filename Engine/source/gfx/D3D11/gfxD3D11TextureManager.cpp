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
// D3D11 layer created by: Anis A. Hireche (C) 2014 - anishireche@gmail.com
//-----------------------------------------------------------------------------

#include "gfx/D3D11/gfxD3D11Device.h"
#include "gfx/D3D11/gfxD3D11EnumTranslate.h"
#include "gfx/bitmap/bitmapUtils.h"
#include "gfx/gfxCardProfile.h"
#include "gfx/gfxStringEnumTranslate.h"
#include "core/strings/unicode.h"
#include "core/util/swizzle.h"
#include "core/util/safeDelete.h"
#include "console/console.h"
#include "core/resourceManager.h"

GFXD3D11TextureManager::GFXD3D11TextureManager( U32 adapterIndex ) 
{
   mAdapterIndex = adapterIndex;
   dMemset( mCurTexSet, 0, sizeof( mCurTexSet ) );   
   mD3DDevice = static_cast<GFXD3D11Device*>(GFX)->getDevice();
}

GFXD3D11TextureManager::~GFXD3D11TextureManager()
{
   // Destroy texture table now so just in case some texture objects
   // are still left, we don't crash on a pure virtual method call.
   SAFE_DELETE_ARRAY( mHashTable );
}

void GFXD3D11TextureManager::_innerCreateTexture( GFXD3D11TextureObject *retTex, 
                                               U32 height, 
                                               U32 width, 
                                               U32 depth,
                                               GFXFormat format, 
                                               GFXTextureProfile *profile, 
                                               U32 numMipLevels,
                                               bool forceMips,
                                               S32 antialiasLevel)
{
   //GFXD3D11Device* d3d = static_cast<GFXD3D11Device*>(GFX);

   // Some relevant helper information...
   bool supportsAutoMips = GFX->getCardProfiler()->queryProfile("autoMipMapLevel", true);
   
   D3D11_USAGE usage = D3D11_USAGE_DEFAULT;
   UINT bind = D3D11_BIND_SHADER_RESOURCE;
   UINT cpuAccess = 0;
   UINT misc = 0;

   retTex->mProfile = profile;

   DXGI_FORMAT d3dTextureFormat = GFXD3D11TextureFormat[format];

   AssertFatal(d3dTextureFormat != DXGI_FORMAT_UNKNOWN, "Unsupported pixel format");

   if( retTex->mProfile->isDynamic() )
   {
      //d3d11 seems to not allow mipmaped dynamic textures.
      if(numMipLevels == 1)
      {
         usage = D3D11_USAGE_DYNAMIC;
         cpuAccess |= D3D11_CPU_ACCESS_WRITE;
      }
   }

   if( retTex->mProfile->isRenderTarget() )
   {
      bind |= D3D11_BIND_DEPTH_STENCIL;
   }

   if(retTex->mProfile->isZTarget())
   {
      bind |= D3D11_BIND_RENDER_TARGET;
   }

   if( supportsAutoMips && 
       !forceMips &&
       !retTex->mProfile->isSystemMemory() &&
       numMipLevels == 0 &&
       !(depth > 0) )
   {
      //TODO. Call  ID3D11DeviceContext::GenerateMips. d3d9 did it automatically.
      misc |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
      bind |= D3D11_BIND_RENDER_TARGET;
      //static_cast<GFXD3D11Device*>(GFX)->getDeviceContext()->GenerateMips();
   }

   if( depth > 0 )
   {
      D3D11_TEXTURE3D_DESC sTexDesc3D;
      sTexDesc3D.Width				= width;
      sTexDesc3D.Height				= height;
      sTexDesc3D.Depth				= depth;
      sTexDesc3D.MipLevels			= numMipLevels;
      sTexDesc3D.Format				= d3dTextureFormat;
      sTexDesc3D.Usage				= usage;
      sTexDesc3D.BindFlags			= bind;
      sTexDesc3D.CPUAccessFlags		= cpuAccess;
      sTexDesc3D.MiscFlags			= misc;

      ID3D11Texture3D* tex3D;
      HRESULT hr = mD3DDevice->CreateTexture3D(&sTexDesc3D, NULL, &tex3D);
      if ( FAILED(hr) )
         AssertFatal(false, "GFXD3D11TextureManager::_createTexture - failed to create volume texture!");

      retTex->setTex(tex3D);
      retTex->mTextureSize.set( width, height, depth );
      retTex->mMipLevels = numMipLevels;
      // required for 3D texture support - John Kabus
      retTex->mFormat = format;
   }
   else
   {
      D3D11_TEXTURE2D_DESC sTexDesc2D;
      sTexDesc2D.Width				= width;
      sTexDesc2D.Height				= height;
      sTexDesc2D.MipLevels			= numMipLevels;
      sTexDesc2D.ArraySize			= 1;
      sTexDesc2D.Format				= d3dTextureFormat;
      sTexDesc2D.Usage				= usage;
      sTexDesc2D.BindFlags			= bind;
      sTexDesc2D.CPUAccessFlags  = cpuAccess;
      sTexDesc2D.MiscFlags			= misc;

      // Figure out AA settings for depth and render targets
      switch (antialiasLevel)
      {
         case 0:
            sTexDesc2D.SampleDesc.Quality = 0;
            sTexDesc2D.SampleDesc.Count = 1;
            break;

         case AA_MATCH_BACKBUFFER :
            sTexDesc2D.SampleDesc.Quality = 0;
            sTexDesc2D.SampleDesc.Count = 1;
            //sTexDesc2D.SampleDesc = d3d->getMultisampleInfo();
            break;

         default :
         {
            sTexDesc2D.SampleDesc.Quality = 0;
            sTexDesc2D.SampleDesc.Count = antialiasLevel;
#ifdef TORQUE_DEBUG
            UINT numQualityLevels;
            mD3DDevice->CheckMultisampleQualityLevels(d3dTextureFormat, antialiasLevel, &numQualityLevels);
            AssertFatal(numQualityLevels, "Invalid AA level!");
#endif
            break;
         }
      }

      ID3D11Texture2D* tex2D;
      HRESULT hr = mD3DDevice->CreateTexture2D(&sTexDesc2D, NULL, &tex2D);
      if( FAILED(hr) )
         AssertFatal(false, "Failed to create texture!");
      
      retTex->setTex(tex2D);
      retTex->mFormat = format;
      retTex->mMipLevels = numMipLevels;
      retTex->mTextureSize.set(width, height, depth);
   }
}

//-----------------------------------------------------------------------------
// createTexture
//-----------------------------------------------------------------------------
GFXTextureObject *GFXD3D11TextureManager::_createTextureObject( U32 height, 
                                                               U32 width,
                                                               U32 depth,
                                                               GFXFormat format, 
                                                               GFXTextureProfile *profile, 
                                                               U32 numMipLevels,
                                                               bool forceMips, 
                                                               S32 antialiasLevel,
                                                               GFXTextureObject *inTex )
{
   GFXD3D11TextureObject *retTex;
   if ( inTex )
   {
      AssertFatal(static_cast<GFXD3D11TextureObject*>( inTex ), "GFXD3D11TextureManager::_createTexture() - Bad inTex type!");
      retTex = static_cast<GFXD3D11TextureObject*>( inTex );
      retTex->release();
   }      
   else
   {
      retTex = new GFXD3D11TextureObject(GFX, profile);
      retTex->registerResourceWithDevice(GFX);
   }

   _innerCreateTexture(retTex, height, width, depth, format, profile, numMipLevels, forceMips, antialiasLevel);

   return retTex;
}

bool GFXD3D11TextureManager::_loadTexture(GFXTextureObject *aTexture, GBitmap *pDL)
{
   PROFILE_SCOPE(GFXD3D11TextureManager_loadTexture);

   GFXD3D11TextureObject *texture = static_cast<GFXD3D11TextureObject*>(aTexture);

   // Check with profiler to see if we can do automatic mipmap generation.
   const bool supportsAutoMips = GFX->getCardProfiler()->queryProfile("autoMipMapLevel", true);

   // Helper bool
   const bool isCompressedTexFmt = aTexture->mFormat >= GFXFormatDXT1 && aTexture->mFormat <= GFXFormatDXT5;

   GFXD3D11Device* dev = static_cast<GFXD3D11Device *>(GFX);

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
      U32 subresource = D3D11CalcSubresource(i, 0, aTexture->mMipLevels);

      DXGI_MAPPED_RECT lockedRect;
      D3D11_MAPPED_SUBRESOURCE* mapping;
      dev->getDeviceContext()->Map(texture->get2DTex(), subresource, D3D11_MAP_WRITE, 0, mapping);

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

      dev->getDeviceContext()->Unmap(texture->get2DTex(), subresource);
   }

   return true;          
}

bool GFXD3D11TextureManager::_loadTexture(GFXTextureObject *inTex, void *raw)
{
   PROFILE_SCOPE(GFXD3D11TextureManager_loadTextureRaw);

   GFXD3D11TextureObject *texture = (GFXD3D11TextureObject *) inTex;

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

   //U32 slicePitch = texture->getWidth() * texture->getHeight() * texture->getDepth() * bytesPerPix;

   D3D11_BOX box;
   box.left    = 0;
   box.right   = texture->getWidth();
   box.front   = 0;
   box.back    = texture->getDepth();
   box.top     = 0;
   box.bottom  = texture->getHeight();

   //LPDIRECT3DVOLUME9 volume = NULL;
   //HRESULT hr = texture->get3DTex()->GetVolumeLevel(0, &volume);

   //if(FAILED(hr)) 
   {
      //AssertFatal(false, "Failed to load volume");
   }

   //D3DLOCKED_BOX lockedBox;
   //volume->LockBox(&lockedBox, &box, 0);
   
   //if(texture->mFormat == GFXFormatR8G8B8) // anis -> converted format also for volume textures
		//dMemcpy(lockedBox.pBits, Bits, slicePitch);
   //else
		//dMemcpy(lockedBox.pBits, raw, slicePitch);

   //volume->UnlockBox();
   //volume->Release();
   return true;
}

bool GFXD3D11TextureManager::_refreshTexture(GFXTextureObject *texture)
{
   U32 usedStrategies = 0;
   GFXD3D11TextureObject *realTex = static_cast<GFXD3D11TextureObject *>(texture);

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

   AssertFatal(usedStrategies < 2, "GFXD3D11TextureManager::_refreshTexture - Inconsistent profile flags!");

   return true;
}

bool GFXD3D11TextureManager::_freeTexture(GFXTextureObject *texture, bool zombify)
{
   GFXD3D11TextureObject *tex = static_cast<GFXD3D11TextureObject *>( texture );

   if(zombify)
      return true;

   tex->release();
   return true;
}

/// Load a texture from a proper DDSFile instance.
bool GFXD3D11TextureManager::_loadTexture(GFXTextureObject *aTexture, DDSFile *dds)
{
   PROFILE_SCOPE(GFXD3D11TextureManager_loadTextureDDS);

   GFXD3D11TextureObject *texture = static_cast<GFXD3D11TextureObject*>(aTexture);
   GFXD3D11Device* dev = static_cast<GFXD3D11Device *>(GFX);

   // Fill the texture...
   for( int i = 0; i < aTexture->mMipLevels; i++ )
   {
      PROFILE_SCOPE(GFXD3DTexMan_loadSurface);
      U32 subresource = D3D11CalcSubresource(i, 0, aTexture->mMipLevels);
      dev->getDeviceContext()->UpdateSubresource(texture->get2DTex(), subresource, 0, dds->mSurfaces[0]->mMips[i], dds->getSurfacePitch(i), 0);
   }

   return true;
}
