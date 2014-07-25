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

#include "gfxD3D9VideoCapture.h"
#include "gfx/D3D9/gfxD3D9Device.h"
#include "platform/tmm_off.h"

GFXD3D9VideoFrameGrabber::GFXD3D9VideoFrameGrabber()
{
   GFXDevice::getDeviceEventSignal().notify( this, &GFXD3D9VideoFrameGrabber::_handleGFXEvent );   
   mCurrentCapture = 0;
}

GFXD3D9VideoFrameGrabber::~GFXD3D9VideoFrameGrabber()
{
   GFXDevice::getDeviceEventSignal().remove( this, &GFXD3D9VideoFrameGrabber::_handleGFXEvent );
}

 
void GFXD3D9VideoFrameGrabber::captureBackBuffer()
{
   AssertFatal( mCapture[mCurrentCapture].stage != eInSystemMemory, "Error! Trying to override a capture resource in \"SystemMemory\" stage!" );

   IDirect3DSurface9 * backBuffer;
   D3D9DEVICE->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

   GFXTexHandle &vidMemTex = mCapture[mCurrentCapture].vidMemTex;

   // Re-init video memory texture if needed
   if (vidMemTex.isNull() || vidMemTex.getWidthHeight() != mResolution)
      vidMemTex.set(mResolution.x, mResolution.y,GFXFormatR8G8B8X8, &GFXDefaultRenderTargetProfile, avar("%s() - mVidMemTex (line %d)", __FUNCTION__, __LINE__) );

   // set up the copy surface   
   IDirect3DSurface9 *surface;

   // grab the top level surface of tex 0
   GFXD3D9TextureObject *to = (GFXD3D9TextureObject *) &(*vidMemTex);
   HRESULT hr = to->get2DTex()->GetSurfaceLevel( 0, &surface );

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GetSurfaceLevel call failure");
	}

   // use StretchRect because it allows a copy from a multisample surface
   // to a normal rendertarget surface
   D3D9DEVICE->StretchRect( backBuffer, NULL, surface, NULL, D3DTEXF_LINEAR );

   // Reelase surfaces
   backBuffer->Release();
   surface->Release();

   // Update the stage
   mCapture[mCurrentCapture].stage = eInVideoMemory;
}

void GFXD3D9VideoFrameGrabber::makeBitmap()
{    
   // Advance the stages for all resources, except the one used for the last capture
   for (U32 i=0; i<eNumStages; i++)
   {
      if (i == mCurrentCapture)
         continue;

      switch (mCapture[i].stage)
      {         
      case eInVideoMemory:
         copyToSystemMemory(mCapture[i]);
         break;
      case eInSystemMemory:
         copyToBitmap(mCapture[i]);
         break;
      }
   }

   // Change the resource being used for backbuffer captures
   mCurrentCapture = (mCurrentCapture + 1) % eNumStages;

   AssertFatal( mCapture[mCurrentCapture].stage != eInSystemMemory, "Error! A capture resource with an invalid state was picked for making captures!" );
}

void GFXD3D9VideoFrameGrabber::releaseTextures()
{
   for (U32 i=0; i<eNumStages; i++)
   {
      mCapture[i].sysMemTex.free();
      mCapture[i].vidMemTex.free();
      mCapture[i].stage = eReadyToCapture;
   }   
}

void GFXD3D9VideoFrameGrabber::copyToSystemMemory(CaptureResource &capture)
{
   AssertFatal( capture.stage == eInVideoMemory, "Error! copyToSystemMemory() can only work in resources in 'eInVideoMemory' stage!" );

   GFXTexHandle &vidMemTex = capture.vidMemTex;
   GFXTexHandle &sysMemTex = capture.sysMemTex;

   // Initialize system memory texture if necessary
   Point2I size = vidMemTex.getWidthHeight();
   if(sysMemTex.isNull() || sysMemTex.getWidthHeight() != size)
      sysMemTex.set(size.x, size.y, GFXFormatR8G8B8X8, &GFXSystemMemProfile, avar("%s() - tex (line %d)", __FUNCTION__, __LINE__));

   // set up the 2 copy surfaces   
   IDirect3DSurface9 *surface[2];

   // grab the top level surface of tex 0
   GFXD3D9TextureObject *to = (GFXD3D9TextureObject *) &(*vidMemTex);
    HRESULT hr = to->get2DTex()->GetSurfaceLevel(0, &surface[0]);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GetSurfaceLevel call failure");
	}

   // grab the top level surface of tex 1
   to = (GFXD3D9TextureObject *) &(*sysMemTex);
   hr = to->get2DTex()->GetSurfaceLevel( 0, &surface[1] );

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GetSurfaceLevel call failure");
	}

   // copy the data from the render target to the system memory texture
   D3D9DEVICE->GetRenderTargetData( surface[0], surface[1] );

   // celease surfaces
   surface[0]->Release();
   surface[1]->Release();

   // Change the resource state
   capture.stage = eInSystemMemory;
}

void GFXD3D9VideoFrameGrabber::copyToBitmap(CaptureResource &capture)
{
   AssertFatal( capture.stage == eInSystemMemory, "Error! copyToBitmap() can only work in resources in 'eInSystemMemory' stage!" );

   GFXTexHandle &sysMemTex = capture.sysMemTex;
   Point2I size = sysMemTex.getWidthHeight();

   // Setup a surface
   IDirect3DSurface9 *surface;

   GFXD3D9TextureObject *to = (GFXD3D9TextureObject *) &(*sysMemTex);
   HRESULT hr = to->get2DTex()->GetSurfaceLevel( 0, &surface );
   
	if(FAILED(hr)) 
	{
		AssertFatal(false, "GetSurfaceLevel call failure");
	}

   // Lock the system memory surface
   D3DLOCKED_RECT r;
   D3DSURFACE_DESC d;
   surface->GetDesc(&d);
   surface->LockRect( &r, NULL, D3DLOCK_READONLY);

   // Allocate a GBitmap and copy into it.
   GBitmap *gb = new GBitmap(size.x, size.y);
   
   // We've got the X8 in there so we have to manually copy stuff.
   const U32* src = (const U32*)r.pBits;
   U8* dst = gb->getWritableBits();
   S32 pixels = size.x*size.y;
   for(S32 i=0; i<pixels; i++)
   {
      U32 px = *src++;      
      *dst++ = px >> 16;
      *dst++ = px >> 8;
      *dst++ = px;
   }
   surface->UnlockRect();
   
   // celease surfaces
   surface->Release();   

   // Push this new bitmap
   pushNewBitmap(gb);

   // Change the resource state
   capture.stage = eReadyToCapture;
}

bool GFXD3D9VideoFrameGrabber::_handleGFXEvent( GFXDevice::GFXDeviceEventType event_ )
{
   switch ( event_ )
   {
      case GFXDevice::deDestroy :
         releaseTextures();
         break;

      default:
         break;
   }

   return true;
}
