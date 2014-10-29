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

#include "platform/platform.h"
#include "gfx/BGFX/gfxBGFXTextureManager.h"

#include "core/strings/stringFunctions.h"
#include "gfx/gfxCubemap.h"
#include "gfx/screenshot.h"
#include "gfx/gfxPrimitiveBuffer.h"
#include "gfx/gfxCardProfile.h"
#include "gfx/gfxTextureManager.h"
#include "gfx/bitmap/gBitmap.h"
#include "core/util/safeDelete.h"
#include "windowManager/win32/win32Window.h"

#include <bgfx.h>
#include <bgfxplatform.h>
#include <nanovg.h>

GFXBGFXTextureObject::GFXBGFXTextureObject(GFXDevice * aDevice, GFXTextureProfile *profile) :
   GFXTextureObject(aDevice, profile) 
{
   mProfile = profile;
   mTextureSize.set( 0, 0, 0 );
   lockedArea = NULL;
   lockedRect = NULL;
   tempBuf = NULL;
   mBGFXTexture.idx = bgfx::invalidHandle;
}

GFXBGFXTextureObject::~GFXBGFXTextureObject()
{
   Con::printf("Texture Destructor.");

   if ( mBGFXTexture.idx != bgfx::invalidHandle )
      bgfx::destroyTexture(mBGFXTexture);

   SAFE_DELETE(mBitmap);
   delete[] tempBuf;
   kill();
}

GFXLockedRect* GFXBGFXTextureObject::lock( U32 mipLevel, RectI *inRect )
{
   SAFE_DELETE(lockedArea);

   if ( !inRect )
      lockedArea = new RectI(0, 0, mTextureSize.x, mTextureSize.y);
   else
      lockedArea = inRect;

   if ( getFormat() == GFXFormat::GFXFormatR8G8B8 )
   {
      tempBuf = new U8[lockedArea->area() * 4];
      lockedRect = new GFXLockedRect();
      lockedRect->bits = tempBuf;
      lockedRect->pitch = lockedArea->len_x() * 4;
   }

   if ( getFormat() == GFXFormat::GFXFormatA8 )
   {
      tempBuf = new U8[lockedArea->area()];
      lockedRect = new GFXLockedRect();
      lockedRect->bits = tempBuf;
      lockedRect->pitch = lockedArea->len_x();
   }

   if ( getFormat() == GFXFormat::GFXFormatD24S8 )
   {
      tempBuf = new U8[lockedArea->area()];
      lockedRect = new GFXLockedRect();
      lockedRect->bits = tempBuf;
      lockedRect->pitch = lockedArea->len_x();
   }

   return lockedRect;
}

void GFXBGFXTextureObject::unlock( U32 mipLevel )
{
   if ( getFormat() == GFXFormat::GFXFormatR8G8B8 )
   {
      const bgfx::Memory* mem = bgfx::makeRef(tempBuf, lockedArea->area() * 4);
      bgfx::updateTexture2D(mBGFXTexture, 0, lockedArea->point.x, lockedArea->point.y, lockedArea->extent.x, lockedArea->extent.y, mem, lockedArea->extent.x * 4);
   }

   if ( getFormat() == GFXFormat::GFXFormatA8 )
   {
      const bgfx::Memory* mem = bgfx::makeRef(tempBuf, lockedArea->area());
      bgfx::updateTexture2D(mBGFXTexture, 0, lockedArea->point.x, lockedArea->point.y, lockedArea->extent.x, lockedArea->extent.y, mem, lockedArea->extent.x);
   }

   if ( getFormat() == GFXFormat::GFXFormatD24S8 )
   {
      const bgfx::Memory* mem = bgfx::makeRef(tempBuf, lockedArea->area());
      bgfx::updateTexture2D(mBGFXTexture, 0, lockedArea->point.x, lockedArea->point.y, lockedArea->extent.x, lockedArea->extent.y, mem, lockedArea->extent.x * 4);
   }

   SAFE_DELETE(lockedArea);
   SAFE_DELETE(lockedRect);
}

GFXTextureObject* GFXBGFXTextureManager::_createTextureObject( U32 height, 
                                                U32 width, 
                                                U32 depth, 
                                                GFXFormat format, 
                                                GFXTextureProfile *profile, 
                                                U32 numMipLevels, 
                                                bool forceMips, 
                                                S32 antialiasLevel, 
                                                GFXTextureObject *inTex )
{ 
   Con::printf("[bgfx] CREATING TEXTURE!");
   GFXBGFXTextureObject *retTex = NULL;
   if ( inTex )
   {
      AssertFatal( dynamic_cast<GFXBGFXTextureObject*>( inTex ), "GFXBGFXTextureManager::_createTexture() - Bad inTex type!" );
      retTex = static_cast<GFXBGFXTextureObject*>( inTex );
   }      
   else
   {
      retTex = new GFXBGFXTextureObject( GFX, profile );
      retTex->registerResourceWithDevice( GFX );
   }
   if ( !retTex ) return NULL;

   retTex->mTextureSize.set(width, height, 0);
   //retTex->u_texColor = bgfx::createUniform("u_texColor", bgfx::UniformType::Uniform1iv);

   SAFE_DELETE( retTex->mBitmap );
   retTex->mBitmap = new GBitmap(width, height);
   if ( format == GFXFormat::GFXFormatR8G8B8 || format == GFXFormat::GFXFormatR8G8B8A8 )
      retTex->mBGFXTexture = bgfx::createTexture2D(width, height, numMipLevels, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_MIN_POINT|BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIP_POINT);

   if ( format == GFXFormat::GFXFormatA8 ) 
      retTex->mBGFXTexture = bgfx::createTexture2D(width, height, numMipLevels, bgfx::TextureFormat::R8, BGFX_TEXTURE_MIN_POINT|BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIP_POINT);

   if ( format == GFXFormat::GFXFormatD24S8 ) 
      retTex->mBGFXTexture = bgfx::createTexture2D(width, height, numMipLevels, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_MIN_POINT|BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIP_POINT);
   

   //else
   //   retTex->mBGFXTexture = bgfx::createTexture2D(width, height, numMipLevels, bgfx::TextureFormat::Unknown, BGFX_TEXTURE_MIN_POINT|BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIP_POINT);

   return retTex;
}

bool GFXBGFXTextureManager::_loadTexture(GFXTextureObject *texture, GBitmap *bmp)
{
   const U8* bits = bmp->getBits(0);
   if ( bmp->getFormat() == GFXFormat::GFXFormatR8G8B8 )
   {
      U32 count = bmp->getBytesPerPixel() * bmp->getHeight() * bmp->getWidth();
      GFXLockedRect* lockedRect = texture->lock();
      U32 tmpPos = 0;
      for(U32 n = 0; n < count; n+=3)
      {
         // Need to Convert RGB to BGRA
         lockedRect->bits[tmpPos] = bits[n + 2];
         lockedRect->bits[tmpPos + 1] = bits[n + 1];
         lockedRect->bits[tmpPos + 2] = bits[n];
         lockedRect->bits[tmpPos + 3] = 255;
         tmpPos += 4;
      }
      texture->unlock();

   } else if ( bmp->getFormat() == GFXFormat::GFXFormatR8G8B8A8 )
   {
      U32 count = bmp->getBytesPerPixel() * bmp->getHeight() * bmp->getWidth();
      GFXLockedRect* lockedRect = texture->lock();
      U32 tmpPos = 0;
      for(U32 n = 0; n < count; n+=4)
      {
         // Need to Convert RGBA to BGRA
         lockedRect->bits[tmpPos] = bits[n + 2];
         lockedRect->bits[tmpPos + 1] = bits[n + 1];
         lockedRect->bits[tmpPos + 2] = bits[n];
         lockedRect->bits[tmpPos + 3] = bits[n + 3];
         tmpPos += 4;
      }
      texture->unlock();
   } else {
      U32 count = bmp->getBytesPerPixel() * bmp->getHeight() * bmp->getWidth();
      GFXLockedRect* lockedRect = texture->lock();
      dMemcpy(lockedRect->bits, bits, count);
      texture->unlock();
   }
   return true;
}

bool GFXBGFXTextureManager::_loadTexture(GFXTextureObject *texture, DDSFile *dds)
{ 
   return true; 
}

bool GFXBGFXTextureManager::_loadTexture(GFXTextureObject *texture, void *raw)
{ 
   return true; 
}

bool GFXBGFXTextureManager::_freeTexture(GFXTextureObject *texture, bool zombify)
{ 
   GFXBGFXTextureObject* bgfxTex = static_cast<GFXBGFXTextureObject*>(texture);
   if ( bgfxTex )
   {
      if ( bgfxTex->mBGFXTexture.idx != bgfx::invalidHandle )
      {
         Con::printf("Destroying BGFX Texture.");
         bgfx::destroyTexture(bgfxTex->mBGFXTexture);
      }
      return true;
   }
   return false;
}

void GFXBGFXTextureObject::release()
{
   Con::printf("TEXTURE RELEASE CALL!");
}

void GFXBGFXTextureObject::zombify()
{
   Con::printf("TEXTURE ZOMBIFY CALL!");
   release();
}

void GFXBGFXTextureObject::resurrect()
{
   Con::printf("TEXTURE RESURRECT CALL!");
}