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
#include "console/console.h"
#include "gfx/primBuilder.h"
#include "gfx/D3D11/gfxD3D11CardProfiler.h"
#include "gfx/D3D11/gfxD3D11EnumTranslate.h"
#include "platformWin32/videoInfo/wmiVideoInfo.h"

GFXD3D11CardProfiler::GFXD3D11CardProfiler(U32 adapterIndex) : GFXCardProfiler()
{
   mAdapterOrdinal = adapterIndex;
}

GFXD3D11CardProfiler::~GFXD3D11CardProfiler()
{

}

void GFXD3D11CardProfiler::init()
{
   AssertISV(static_cast<GFXD3D11Device*>(GFX)->getDevice(), "GFXD3D11CardProfiler::init() - No D3D11 Device found!");

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

void GFXD3D11CardProfiler::setupCardCapabilities()
{
	// anis -> resource limits direct3d11: http://msdn.microsoft.com/en-us/library/windows/desktop/ff819065(v=vs.85).aspx
}

bool GFXD3D11CardProfiler::_queryCardCap(const String &query, U32 &foundResult)
{
   return 0;
}

bool GFXD3D11CardProfiler::_queryFormat( const GFXFormat fmt, const GFXTextureProfile *profile, bool &inOutAutogenMips )
{
   // anis -> D3D11 feature level should guarantee that any format is valid!
   return GFXD3D11TextureFormat[fmt] != DXGI_FORMAT_UNKNOWN;
}