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
#include "gfx/D3D9/gfxD3D9TextureObject.h"
#include "platform/profiler.h"
#include "console/console.h"

/*
	anis -> GFXFormatR8G8B8 has now the same behaviour as GFXFormatR8G8B8X8. 
	This is because 24 bit format are now deprecated by microsoft, for data alignment reason there's no changes beetween 24 and 32 bit formats.
	DirectX 10-11 both have 24 bit format no longer.
*/

GFXD3D9TextureObject::GFXD3D9TextureObject( GFXDevice * d, GFXTextureProfile *profile) : GFXTextureObject( d, profile )
{
   mD3DTexture = NULL;
   mLocked = false;
   mD3DSurface = NULL;
}

GFXD3D9TextureObject::~GFXD3D9TextureObject()
{
   kill();
}

GFXLockedRect *GFXD3D9TextureObject::lock(U32 mipLevel /*= 0*/, RectI *inRect /*= NULL*/)
{
	AssertFatal(!mLocked, "GFXD3D9TextureObject::lock - The texture is already locked!");

	if(mProfile->isRenderTarget())
	{
		if(!mLockTex || mLockTex->getWidth() != getWidth() || mLockTex->getHeight() != getHeight())
		{
			mLockTex.set(getWidth(), getHeight(), mFormat, &GFXSystemMemProfile, avar("%s() - mLockTex (line %d)", __FUNCTION__, __LINE__));
		}

		PROFILE_START(GFXD3D9TextureObject_lockRT);

		IDirect3DSurface9 *source;
		HRESULT hr = get2DTex()->GetSurfaceLevel( 0, &source );

		if(FAILED(hr)) 
		{
			AssertFatal(false, "GFXD3D9TextureObject::lock - failed to get our own texture's surface.");
		}

		IDirect3DSurface9 *dest;
		GFXD3D9TextureObject *to = (GFXD3D9TextureObject*) &(*mLockTex);
		hr = to->get2DTex()->GetSurfaceLevel(0, &dest);

		if(FAILED(hr)) 
		{
			AssertFatal(false, "GFXD3D9TextureObject::lock - failed to get dest texture's surface.");
		}

		HRESULT rtLockRes = D3D9DEVICE->GetRenderTargetData(source, dest);
		source->Release();

		if(!SUCCEEDED(rtLockRes))
		{
			// This case generally occurs if the device is lost. The lock failed
			// so clean up and return NULL.
			dest->Release();
			PROFILE_END();
			return NULL;
		}

		hr = dest->LockRect( &mLockRect, NULL, D3DLOCK_READONLY );

		if(FAILED(hr)) 
		{
			AssertFatal(false, "LockRect call failure");
		}

		dest->Release();
		mLocked = true;

		PROFILE_END();
	}
	else
	{
		RECT r;

		if(inRect)
		{
			r.top  = inRect->point.y;
			r.left = inRect->point.x;
			r.bottom = inRect->point.y + inRect->extent.y;
			r.right  = inRect->point.x + inRect->extent.x;
		}

		HRESULT hr = get2DTex()->LockRect(mipLevel, &mLockRect, inRect ? &r : NULL, 0);

		if(FAILED(hr)) 
		{
			AssertFatal(false, "GFXD3D9TextureObject::lock - could not lock non-RT texture!");
		}

		mLocked = true;
	}

	// GFXLockedRect is set up to correspond to D3DLOCKED_RECT, so this is ok.
	return (GFXLockedRect*)&mLockRect; 
}

void GFXD3D9TextureObject::unlock(U32 mipLevel)
{
   AssertFatal( mLocked, "GFXD3D9TextureObject::unlock - Attempting to unlock a surface that has not been locked" );

   if( mProfile->isRenderTarget() )
   {
      IDirect3DSurface9 *dest;
      GFXD3D9TextureObject *to = (GFXD3D9TextureObject *) &(*mLockTex);
      HRESULT hr = to->get2DTex()->GetSurfaceLevel( 0, &dest );

      if(FAILED(hr)) 
	  {
		  AssertFatal(false, "GetSurfaceLevel call failure");
	  }

      dest->UnlockRect();
      dest->Release();

      mLocked = false;
   }
   else
   {
      HRESULT hr = get2DTex()->UnlockRect(mipLevel);

	  if(FAILED(hr)) 
	  {
		  AssertFatal(false, "GFXD3D9TextureObject::unlock - could not unlock non-RT texture.");
	  }

      mLocked = false;
   }
}

void GFXD3D9TextureObject::release()
{
   SAFE_RELEASE(mD3DTexture);
   SAFE_RELEASE(mD3DSurface);
}

void GFXD3D9TextureObject::zombify()
{
}

void GFXD3D9TextureObject::resurrect()
{
}

bool GFXD3D9TextureObject::copyToBmp(GBitmap* bmp)
{
   if (!bmp)
      return false;

   // check format limitations
   // at the moment we only support RGBA for the source (other 4 byte formats should
   // be easy to add though)
   AssertFatal(mFormat == GFXFormatR8G8B8A8, "copyToBmp: invalid format");
   if (mFormat != GFXFormatR8G8B8A8)
      return false;

   PROFILE_START(GFXD3D9TextureObject_copyToBmp);

   AssertFatal(bmp->getWidth() == getWidth(), "doh");
   AssertFatal(bmp->getHeight() == getHeight(), "doh");
   U32 width = getWidth();
   U32 height = getHeight();

   bmp->setHasTransparency(mHasTransparency);

   // set some constants
   const U32 sourceBytesPerPixel = 4;
   U32 destBytesPerPixel = 0;

   if(bmp->getFormat() == GFXFormatR8G8B8A8)
      destBytesPerPixel = 4;
   else if(bmp->getFormat() == GFXFormatR8G8B8)
      destBytesPerPixel = 3;
   else
      // unsupported
      AssertFatal(false, "unsupported bitmap format");


   // lock the texture
   D3DLOCKED_RECT* lockRect = (D3DLOCKED_RECT*) lock();

   // set pointers
   U8* srcPtr = (U8*)lockRect->pBits;
   U8* destPtr = bmp->getWritableBits();

   // we will want to skip over any D3D cache data in the source texture
   const S32 sourceCacheSize = lockRect->Pitch - width * sourceBytesPerPixel;
   AssertFatal(sourceCacheSize >= 0, "copyToBmp: cache size is less than zero?");

   PROFILE_START(GFXD3D9TextureObject_copyToBmp_pixCopy);
   // copy data into bitmap
   for (S32 row = 0; row < height; ++row)
   {
      for (S32 col = 0; col < width; ++col)
      {
         destPtr[0] = srcPtr[2]; // red
         destPtr[1] = srcPtr[1]; // green
         destPtr[2] = srcPtr[0]; // blue 
         if (destBytesPerPixel == 4)
            destPtr[3] = srcPtr[3]; // alpha

         // go to next pixel in src
         srcPtr += sourceBytesPerPixel;

         // go to next pixel in dest
         destPtr += destBytesPerPixel;
      }
      // skip past the cache data for this row (if any)
      srcPtr += sourceCacheSize;
   }
   PROFILE_END();

   // assert if we stomped or underran memory
   AssertFatal(U32(destPtr - bmp->getWritableBits()) == width * height * destBytesPerPixel, "copyToBmp: doh, memory error");
   AssertFatal(U32(srcPtr - (U8*)lockRect->pBits) == height * lockRect->Pitch, "copyToBmp: doh, memory error");

   // unlock
   unlock();

   PROFILE_END();

   return true;
}
