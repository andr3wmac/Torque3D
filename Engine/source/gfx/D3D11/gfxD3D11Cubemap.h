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

#ifndef _GFXD3D11CUBEMAP_H_
#define _GFXD3D11CUBEMAP_H_

#include "gfx/D3D11/gfxD3D11Device.h"
#include "gfx/gfxCubemap.h"
#include "gfx/gfxResource.h"
#include "gfx/gfxTarget.h"

class GFXD3D11Cubemap : public GFXCubemap
{
public:
   virtual void initStatic( GFXTexHandle *faces );
   virtual void initStatic( DDSFile *dds );
   virtual void initDynamic( U32 texSize, GFXFormat faceFormat = GFXFormatR8G8B8A8 );
   virtual void setToTexUnit( U32 tuNum );
   virtual U32 getSize() const { return mTexSize; }
   virtual GFXFormat getFormat() const { return mFaceFormat; }

   GFXD3D11Cubemap();
   virtual ~GFXD3D11Cubemap();

   // GFXResource interface
   virtual void zombify();
   virtual void resurrect();

private:

   friend class GFXD3D11TextureTarget;
   friend class GFXD3D11Device;

   ID3D11Texture2D*				m_pTexture;
   ID3D11ShaderResourceView*	m_pShaderResourceView;
   ID3D11RenderTargetView*		m_pSurfaces[6];

   U32  mTexSize;
   GFXFormat mFaceFormat;
   
   void releaseSurfaces();
};

#endif
