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

#ifndef _GFXD3D9ENUMTRANSLATE_H_
#define _GFXD3D9ENUMTRANSLATE_H_

#include "gfx/D3D9/gfxD3D9Shader.h"
#include "gfx/gfxEnums.h"

//------------------------------------------------------------------------------

namespace GFXD3D9EnumTranslate
{
   void init();
};

//------------------------------------------------------------------------------

extern D3DFORMAT GFXD3D9TextureFormat[GFXFormat_COUNT];
extern D3DTEXTUREFILTERTYPE GFXD3D9TextureFilter[GFXTextureFilter_COUNT];
extern D3DBLEND GFXD3D9Blend[GFXBlend_COUNT];
extern D3DBLENDOP GFXD3D9BlendOp[GFXBlendOp_COUNT];
extern D3DSTENCILOP GFXD3D9StencilOp[GFXStencilOp_COUNT];
extern D3DCMPFUNC GFXD3D9CmpFunc[GFXCmp_COUNT];
extern D3DCULL GFXD3D9CullMode[GFXCull_COUNT];
extern D3DFILLMODE GFXD3D9FillMode[GFXFill_COUNT];
extern D3DPRIMITIVETYPE GFXD3D9PrimType[GFXPT_COUNT];
extern D3DTEXTUREADDRESS GFXD3D9TextureAddress[GFXAddress_COUNT];
extern D3DDECLTYPE GFXD3D9DeclType[GFXDeclType_COUNT];

#endif