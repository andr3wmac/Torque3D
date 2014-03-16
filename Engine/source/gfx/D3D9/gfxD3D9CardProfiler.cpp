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
#include "console/console.h"
#include "gfx/primBuilder.h"
#include "gfx/D3D9/gfxD3D9CardProfiler.h"
#include "gfx/D3D9/gfxD3D9EnumTranslate.h"
#include "platformWin32/videoInfo/wmiVideoInfo.h"

GFXD3D9CardProfiler::GFXD3D9CardProfiler(U32 adapterIndex) : GFXCardProfiler()
{
   mAdapterOrdinal = adapterIndex;
}

GFXD3D9CardProfiler::~GFXD3D9CardProfiler()
{

}

void GFXD3D9CardProfiler::init()
{
   AssertISV(static_cast<GFXD3D9Device*>(GFX)->getDevice(), "GFXD3D9CardProfiler::init() - No D3D9 Device found!");

   WMIVideoInfo wmiVidInfo;
   if(wmiVidInfo.profileAdapters())
   {
      const PlatformVideoInfo::PVIAdapter &adapter = wmiVidInfo.getAdapterInformation(mAdapterOrdinal);

      mCardDescription = adapter.description;
      mChipSet = adapter.chipSet;
      mVersionString = adapter.driverVersion;
      mVideoMemory = adapter.vram;
   }

   Parent::init();
}

void GFXD3D9CardProfiler::setupCardCapabilities()
{
   D3DCAPS9 caps;
   static_cast<GFXD3D9Device*>( GFX )->getDevice()->GetDeviceCaps(&caps);

   setCapability( "autoMipMapLevel", ( caps.Caps2 & D3DCAPS2_CANAUTOGENMIPMAP ? 1 : 0 ) );
   setCapability( "maxTextureWidth", caps.MaxTextureWidth );
   setCapability( "maxTextureHeight", caps.MaxTextureHeight );
   setCapability( "maxTextureSize", getMin( (U32)caps.MaxTextureWidth, (U32)caps.MaxTextureHeight) );

   bool canDoLERPDetailBlend = ( caps.TextureOpCaps & D3DTEXOPCAPS_LERP ) && ( caps.MaxTextureBlendStages > 1 );
   bool canDoFourStageDetailBlend = ( caps.TextureOpCaps & D3DTEXOPCAPS_SUBTRACT ) &&
                                    ( caps.PrimitiveMiscCaps & D3DPMISCCAPS_TSSARGTEMP ) &&
                                    ( caps.MaxTextureBlendStages > 3 );

   setCapability( "lerpDetailBlend", canDoLERPDetailBlend );
   setCapability( "fourStageDetailBlend", canDoFourStageDetailBlend );
}

bool GFXD3D9CardProfiler::_queryCardCap(const String &query, U32 &foundResult)
{
   return 0;
}

bool GFXD3D9CardProfiler::_queryFormat( const GFXFormat fmt, const GFXTextureProfile *profile, bool &inOutAutogenMips )
{
   LPDIRECT3D9 pD3D = static_cast<GFXD3D9Device *>(GFX)->getD3D();
   D3DDISPLAYMODE displayMode = static_cast<GFXD3D9Device *>(GFX)->getDisplayMode();

   DWORD usage = 0;
   D3DRESOURCETYPE rType = D3DRTYPE_TEXTURE;
   D3DFORMAT adapterFormat = displayMode.Format;
   D3DFORMAT texFormat = GFXD3D9TextureFormat[fmt];

   if( profile->isRenderTarget() )
      usage |= D3DUSAGE_RENDERTARGET;
   else if( profile->isZTarget() )
   {
      usage |= D3DUSAGE_DEPTHSTENCIL;
      rType = D3DRTYPE_SURFACE;
   }
   
   if( inOutAutogenMips )
      usage |= D3DUSAGE_AUTOGENMIPMAP;

   // Early-check to see if the enum translation table has an unsupported value
   if(texFormat == (_D3DFORMAT)GFX_UNSUPPORTED_VAL)
      return false;

   HRESULT hr = pD3D->CheckDeviceFormat( mAdapterOrdinal, D3DDEVTYPE_HAL, adapterFormat, usage, rType, texFormat );

   bool retVal = SUCCEEDED( hr );

   // If check device format failed, and auto gen mips were requested, try again
   // without autogen mips.
   if( !retVal && inOutAutogenMips )
   {
      usage ^= D3DUSAGE_AUTOGENMIPMAP;

      hr = pD3D->CheckDeviceFormat(mAdapterOrdinal, D3DDEVTYPE_HAL, adapterFormat, usage, D3DRTYPE_TEXTURE, GFXD3D9TextureFormat[fmt]);

      retVal = SUCCEEDED( hr );

      // If this one passed, auto gen mips are not supported with this format, 
      // so set the variable properly
      if( retVal )
         inOutAutogenMips = false;
   }

   return retVal;
}