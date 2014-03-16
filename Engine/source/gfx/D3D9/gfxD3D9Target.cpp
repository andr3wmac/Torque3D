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

#include "platform/platform.h"
#include "gfx/D3D9/gfxD3D9Target.h"
#include "gfx/D3D9/gfxD3D9Cubemap.h"
#include "gfx/D3D9/gfxD3D9EnumTranslate.h"
#include "gfx/gfxDebugEvent.h"
#include "gfx/gfxStringEnumTranslate.h"
#include "windowManager/win32/win32Window.h"

GFXD3D9TextureTarget::GFXD3D9TextureTarget() 
   :  mTargetSize( Point2I::Zero ),
      mTargetFormat( GFXFormatR8G8B8A8 )
{
   for(S32 i=0; i<MaxRenderSlotId; i++)
   {
      mTargets[i] = NULL;
      mResolveTargets[i] = NULL;
   }
}

GFXD3D9TextureTarget::~GFXD3D9TextureTarget()
{
   // Release anything we might be holding.
   for(S32 i=0; i<MaxRenderSlotId; i++)
   {
      mResolveTargets[i] = NULL;
      SAFE_RELEASE(mTargets[i]);
   }

   zombify();
}

void GFXD3D9TextureTarget::attachTexture( RenderSlot slot, GFXTextureObject *tex, U32 mipLevel/*=0*/, U32 zOffset /*= 0*/ )
{
   GFXDEBUGEVENT_SCOPE( GFXPCD3D9TextureTarget_attachTexture, ColorI::RED );

   AssertFatal(slot < MaxRenderSlotId, "GFXD3D9TextureTarget::attachTexture - out of range slot.");

   // TODO:  The way this is implemented... you can attach a texture 
   // object multiple times and it will release and reset it.
   //
   // We should rework this to detect when no change has occured
   // and skip out early.

   // Mark state as dirty so device can know to update.
   invalidateState();

   // Release what we had, it's definitely going to change.
   SAFE_RELEASE(mTargets[slot]);
   mTargets[slot] = NULL;
   mResolveTargets[slot] = NULL;

   if(slot == Color0)
   {
      mTargetSize = Point2I::Zero;
      mTargetFormat = GFXFormatR8G8B8A8;
   }

   // Are we clearing?
   if(!tex)
   {
      // Yup - just exit, it'll stay NULL.      
      return;
   }

   // Take care of default targets
   if( tex == GFXTextureTarget::sDefaultDepthStencil )
   {
      mTargets[slot] = static_cast<GFXD3D9Device*>(GFX)->mDeviceDepthStencil;
      mTargets[slot]->AddRef();
   }
   else
   {
      // Cast the texture object to D3D...
      AssertFatal(static_cast<GFXD3D9TextureObject*>(tex), "GFXD3D9TextureTarget::attachTexture - invalid texture object.");

      GFXD3D9TextureObject *d3dto = static_cast<GFXD3D9TextureObject*>(tex);

      // Grab the surface level.
      if( slot == DepthStencil )
      {
         mTargets[slot] = d3dto->getSurface();
         if ( mTargets[slot] )
            mTargets[slot]->AddRef();
      }
      else
      {
         // getSurface will almost always return NULL. It will only return non-NULL
         // if the surface that it needs to render to is different than the mip level
         // in the actual texture. This will happen with MSAA.
         if( d3dto->getSurface() == NULL )
         {
            HRESULT hr = d3dto->get2DTex()->GetSurfaceLevel(mipLevel, &mTargets[slot]);

			if(FAILED(hr)) 
			{
				AssertFatal(false, "GFXD3D9TextureTarget::attachTexture - could not get surface level for the passed texture!");
			}
         } 
         else 
         {
            mTargets[slot] = d3dto->getSurface();
            mTargets[slot]->AddRef();

            // Only assign resolve target if d3dto has a surface to give us.
            //
            // That usually means there is an MSAA target involved, which is why
            // the resolve is needed to get the data out of the target.
            mResolveTargets[slot] = d3dto;

            if ( tex && slot == Color0 )
            {
               mTargetSize.set( tex->getSize().x, tex->getSize().y );
               mTargetFormat = tex->getFormat();
            }
         }           
      }

      // Update surface size
      if(slot == Color0)
      {
         IDirect3DSurface9 *surface = mTargets[Color0];
         if(surface)
         {
            D3DSURFACE_DESC sd;
            surface->GetDesc(&sd);
            mTargetSize = Point2I(sd.Width, sd.Height);

            S32 format = sd.Format;
            GFXREVERSE_LOOKUP(GFXD3D9TextureFormat, GFXFormat, format);
            mTargetFormat = (GFXFormat)format;
         }
      }
   }
}

void GFXD3D9TextureTarget::attachTexture(RenderSlot slot, GFXCubemap *tex, U32 face, U32 mipLevel/*=0*/)
{
   GFXDEBUGEVENT_SCOPE( GFXPCD3D9TextureTarget_attachTexture_Cubemap, ColorI::RED );

   AssertFatal(slot < MaxRenderSlotId, "GFXD3D9TextureTarget::attachTexture - out of range slot.");

   // Mark state as dirty so device can know to update.
   invalidateState();

   // Release what we had, it's definitely going to change.
   SAFE_RELEASE(mTargets[slot]);
   mTargets[slot] = NULL;
   mResolveTargets[slot] = NULL;

   // Cast the texture object to D3D...
   AssertFatal(!tex || static_cast<GFXD3D9Cubemap*>(tex), "GFXD3DTextureTarget::attachTexture - invalid cubemap object.");

   GFXD3D9Cubemap *cube = static_cast<GFXD3D9Cubemap*>(tex);

   if(slot == Color0)
   {
      mTargetSize = Point2I::Zero;
      mTargetFormat = GFXFormatR8G8B8A8;
   }

   // Are we clearing?
   if(!tex)
   {
      // Yup - just exit, it'll stay NULL.      
      return;
   }

    HRESULT hr = cube->mCubeTex->GetCubeMapSurface((D3DCUBEMAP_FACES)face, mipLevel, &mTargets[slot] );

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3DTextureTarget::attachTexture - could not get surface level for the passed texture!");
	}

   // Update surface size
   if(slot == Color0)
   {
      IDirect3DSurface9 *surface = mTargets[Color0];
      if ( surface )
      {
         D3DSURFACE_DESC sd;
         surface->GetDesc(&sd);
         mTargetSize = Point2I(sd.Width, sd.Height);

         S32 format = sd.Format;
         GFXREVERSE_LOOKUP( GFXD3D9TextureFormat, GFXFormat, format );
         mTargetFormat = (GFXFormat)format;
      }
   }
}

void GFXD3D9TextureTarget::activate()
{
   GFXDEBUGEVENT_SCOPE( GFXPCD3D9TextureTarget_activate, ColorI::RED );

   AssertFatal( mTargets[GFXTextureTarget::Color0], "GFXD3D9TextureTarget::activate() - You can never have a NULL primary render target!" );

   // Clear the state indicator.
   stateApplied();

   IDirect3DSurface9 *depth = mTargets[GFXTextureTarget::DepthStencil];
   
   // First clear the non-primary targets to make the debug DX runtime happy.
   for(U32 i = 1; i < static_cast<GFXD3D9Device*>(GFX)->getNumRenderTargets(); i++)
   {
		HRESULT hr = static_cast<GFXD3D9Device*>(GFX)->getDevice()->SetRenderTarget(i, NULL);

		if(FAILED(hr)) 
		{
			AssertFatal(false, avar("GFXD3D9TextureTarget::activate() - failed to clear texture target %d!", i));
		}
   }

   // Now set all the new surfaces into the appropriate slots.
   for(U32 i = 0; i < static_cast<GFXD3D9Device*>(GFX)->getNumRenderTargets(); i++)
   {
      IDirect3DSurface9 *target = mTargets[GFXTextureTarget::Color0 + i];
      if(target)
      {
         HRESULT hr = static_cast<GFXD3D9Device*>(GFX)->getDevice()->SetRenderTarget(i, target);

		 if(FAILED(hr)) 
		 {
		 	AssertFatal(false, avar("GFXD3D9TextureTarget::activate() - failed to set slot %d for texture target!", i));
		 }
      }
   }

   // TODO: This is often the same shared depth buffer used by most
   // render targets.  Are we getting performance hit from setting it
   // multiple times... aside from the function call?

   HRESULT hr = static_cast<GFXD3D9Device*>(GFX)->getDevice()->SetDepthStencilSurface(depth);

   if(FAILED(hr)) 
   {
	   AssertFatal(false, "GFXD3D9TextureTarget::activate() - failed to set depthstencil target!");
   }
}

void GFXD3D9TextureTarget::deactivate()
{
   // Nothing to do... the next activate() call will
   // set all the targets correctly.
}

void GFXD3D9TextureTarget::resolve()
{
   GFXDEBUGEVENT_SCOPE( GFXPCD3D9TextureTarget_resolve, ColorI::RED );

   for (U32 i = 0; i < MaxRenderSlotId; i++)
   {
      // We use existance @ mResolveTargets as a flag that we need to copy
      // data from the rendertarget into the texture.
      if (mResolveTargets[i])
      {
         IDirect3DSurface9 *surf;
         HRESULT hr = mResolveTargets[i]->get2DTex()->GetSurfaceLevel(0, &surf);

		 if(FAILED(hr)) 
		 {
			AssertFatal(false, "GFXD3D9TextureTarget::resolve() - GetSurfaceLevel failed!");
		 }

         hr = static_cast<GFXD3D9Device*>( GFX )->getDevice()->StretchRect(mTargets[i], NULL, surf, NULL, D3DTEXF_NONE);

		 if(FAILED(hr)) 
		 {
			AssertFatal(false, "GFXD3D9TextureTarget::resolve() - StretchRect failed!");
		 }

         surf->Release();
      }
   }
}

void GFXD3D9TextureTarget::resolveTo(GFXTextureObject *tex)
{
   GFXDEBUGEVENT_SCOPE( GFXPCD3D9TextureTarget_resolveTo, ColorI::RED );

   if ( mTargets[Color0] == NULL )
      return;

    IDirect3DSurface9 *surf;
    HRESULT hr = ((GFXD3D9TextureObject*)(tex))->get2DTex()->GetSurfaceLevel(0, &surf);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D9TextureTarget::resolveTo() - GetSurfaceLevel failed!");
	}

    hr = static_cast<GFXD3D9Device*>( GFX )->getDevice()->StretchRect(mTargets[Color0], NULL, surf, NULL, D3DTEXF_NONE);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D9TextureTarget::resolveTo() - StretchRect failed!");
	}

   surf->Release();     
}

void GFXD3D9TextureTarget::zombify()
{
   for(int i = 0; i < MaxRenderSlotId; i++)
      attachTexture(RenderSlot(i), NULL);
}

void GFXD3D9TextureTarget::resurrect()
{

}

GFXD3D9WindowTarget::GFXD3D9WindowTarget()
{
   mSwapChain    = NULL;
   mDepthStencil = NULL;
   mWindow       = NULL;
   mBackbuffer   = NULL;
}

GFXD3D9WindowTarget::~GFXD3D9WindowTarget()
{
   SAFE_RELEASE(mSwapChain);
   SAFE_RELEASE(mDepthStencil);
   SAFE_RELEASE(mBackbuffer);
}

void GFXD3D9WindowTarget::initPresentationParams()
{
   // Get some video mode related info.
   GFXVideoMode vm = mWindow->getVideoMode();

   Win32Window* win = static_cast<Win32Window*>(mWindow);

   HWND hwnd = win->getHWND();

   // At some point, this will become GFXD3D9WindowTarget like trunk has,
   // so this cast isn't as bad as it looks. ;) BTR
   mPresentationParams = static_cast<GFXD3D9Device*>(GFX)->setupPresentParams(vm, hwnd);
   static_cast<GFXD3D9Device*>(GFX)->mMultisampleType = mPresentationParams.MultiSampleType;
   static_cast<GFXD3D9Device*>(GFX)->mMultisampleLevel = mPresentationParams.MultiSampleQuality;
}

const Point2I GFXD3D9WindowTarget::getSize()
{
   return mWindow->getVideoMode().resolution; 
}

GFXFormat GFXD3D9WindowTarget::getFormat()
{ 
   S32 format = mPresentationParams.BackBufferFormat;
   GFXREVERSE_LOOKUP( GFXD3D9TextureFormat, GFXFormat, format );
   return (GFXFormat)format;
}

bool GFXD3D9WindowTarget::present()
{
   AssertFatal(mSwapChain, "GFXD3D9WindowTarget::present - no swap chain present to present!");
   HRESULT res = mSwapChain->Present(NULL, NULL, NULL, NULL, NULL);

   return (res == S_OK);
}

void GFXD3D9WindowTarget::setImplicitSwapChain()
{
   if(!mSwapChain)
      static_cast<GFXD3D9Device*>(GFX)->getDevice()->GetSwapChain(0, &mSwapChain);
   if(!mDepthStencil)
      static_cast<GFXD3D9Device*>(GFX)->getDevice()->GetDepthStencilSurface(&mDepthStencil);
   if (!mBackbuffer)      
      mSwapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &mBackbuffer);
}

void GFXD3D9WindowTarget::resetMode()
{
   mWindow->setSuppressReset(true);

   if (mSwapChain)
   {
      // The current video settings.
      D3DPRESENT_PARAMETERS pp;
      mSwapChain->GetPresentParameters(&pp);      
      bool ppFullscreen = !pp.Windowed;
      Point2I backbufferSize(pp.BackBufferWidth, pp.BackBufferHeight);

      // The settings we are now applying.
      const GFXVideoMode &mode = mWindow->getVideoMode();
      
      // Convert the current multisample parameters into something
      // we can compare with our GFXVideoMode.antialiasLevel value.
      U32 ppAntiAliaseLevel = 0;
      if (pp.MultiSampleType != D3DMULTISAMPLE_NONE)      
         ppAntiAliaseLevel = pp.MultiSampleQuality + 1;

      // Early out if none of the settings which require a device reset
      // have changed.      
      if (backbufferSize == getSize() && ppFullscreen == mode.fullScreen && ppAntiAliaseLevel == mode.antialiasLevel)
         return;   
   }

   // Setup our presentation params.
   initPresentationParams();

   // Otherwise, we have to reset the device, if we're the implicit swapchain.
   static_cast<GFXD3D9Device*>(GFX)->reset(mPresentationParams);

   // Update our size, too.
   mSize = Point2I(mPresentationParams.BackBufferWidth, mPresentationParams.BackBufferHeight);      

   mWindow->setSuppressReset(false);
}

void GFXD3D9WindowTarget::zombify()
{
   // Release our resources
   SAFE_RELEASE(mSwapChain);
   SAFE_RELEASE(mDepthStencil);
   SAFE_RELEASE(mBackbuffer);
}

void GFXD3D9WindowTarget::resurrect()
{
   setImplicitSwapChain();
}

void GFXD3D9WindowTarget::activate()
{
   GFXDEBUGEVENT_SCOPE(GFXPCD3D9WindowTarget_activate, ColorI::RED);

   HRESULT hr;

   hr = static_cast<GFXD3D9Device*>(GFX)->getDevice()->SetRenderTarget(0, mBackbuffer);

   if(FAILED(hr)) 
   {
      AssertFatal(false, "GFXD3D9WindowTarget::activate() - Failed to set backbuffer target!");
   }

   hr = static_cast<GFXD3D9Device*>(GFX)->getDevice()->SetDepthStencilSurface(mDepthStencil);

   if(FAILED(hr)) 
   {
      AssertFatal(false, "GFXD3D9WindowTarget::activate() - Failed to set depthstencil target!");
   }

   D3DPRESENT_PARAMETERS pp;
   mSwapChain->GetPresentParameters(&pp);

   // Update our video mode here, too.
   GFXVideoMode vm;
   vm = mWindow->getVideoMode();
   vm.resolution.x = pp.BackBufferWidth;
   vm.resolution.y = pp.BackBufferHeight;
   vm.fullScreen = !pp.Windowed;
   mSize = vm.resolution;
}

void GFXD3D9WindowTarget::resolveTo(GFXTextureObject *tex)
{
	GFXDEBUGEVENT_SCOPE(GFXPCD3D9WindowTarget_resolveTo, ColorI::RED);

	IDirect3DSurface9 *surf;
	HRESULT hr;

	hr = ((GFXD3D9TextureObject*)(tex))->get2DTex()->GetSurfaceLevel(0, &surf);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D9WindowTarget::resolveTo() - GetSurfaceLevel failed!");
	}

	hr = static_cast<GFXD3D9Device*>(GFX)->getDevice()->StretchRect(mBackbuffer, NULL, surf, NULL, D3DTEXF_NONE);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D9WindowTarget::resolveTo() - StretchRect failed!");
	}

	surf->Release();    
}