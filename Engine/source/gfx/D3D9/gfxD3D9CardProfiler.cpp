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
   AssertISV(D3D9DEVICE, "GFXD3D9CardProfiler::init() - No D3D9 Device found!");

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
   D3D9DEVICE->GetDeviceCaps(&caps);

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
   return false;
}

bool GFXD3D9CardProfiler::_queryFormat(const GFXFormat fmt, const GFXTextureProfile *profile, bool &inOutAutogenMips)
{
   // anis -> just tell to gfx if d3d9 can generate hardware mipmaps. if it can't, a software solution will be used.

   D3DCAPS9 caps;
   D3D9DEVICE->GetDeviceCaps(&caps);
   return (caps.Caps2 & D3DCAPS2_CANAUTOGENMIPMAP) && fmt != D3DFMT_UNKNOWN;
}
