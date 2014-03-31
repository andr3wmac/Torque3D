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
#include "gfx/D3D9/gfxD3D9EnumTranslate.h"
#include "console/console.h"

//------------------------------------------------------------------------------

D3DFORMAT GFXD3D9TextureFormat[GFXFormat_COUNT];
D3DTEXTUREFILTERTYPE GFXD3D9TextureFilter[GFXTextureFilter_COUNT];
D3DBLEND GFXD3D9Blend[GFXBlend_COUNT];
D3DBLENDOP GFXD3D9BlendOp[GFXBlendOp_COUNT];
D3DSTENCILOP GFXD3D9StencilOp[GFXStencilOp_COUNT];
D3DCMPFUNC GFXD3D9CmpFunc[GFXCmp_COUNT];
D3DCULL GFXD3D9CullMode[GFXCull_COUNT];
D3DFILLMODE GFXD3D9FillMode[GFXFill_COUNT];
D3DPRIMITIVETYPE GFXD3D9PrimType[GFXPT_COUNT];
D3DTEXTUREADDRESS GFXD3D9TextureAddress[GFXAddress_COUNT];
D3DDECLTYPE GFXD3D9DeclType[GFXDeclType_COUNT];

//------------------------------------------------------------------------------

void GFXD3D9EnumTranslate::init()
{
   GFXD3D9TextureFormat[GFXFormatR8G8B8] = D3DFMT_X8R8G8B8; // anis -> behaviour like d3d11 (using 24 bit format, in any case, we still allocate 32 bit for data alignment reason)
   GFXD3D9TextureFormat[GFXFormatR8G8B8A8] = D3DFMT_A8R8G8B8;
   GFXD3D9TextureFormat[GFXFormatR8G8B8X8] = D3DFMT_X8R8G8B8;
   GFXD3D9TextureFormat[GFXFormatB8G8R8A8] = D3DFMT_A8R8G8B8;
   GFXD3D9TextureFormat[GFXFormatR5G6B5] = D3DFMT_R5G6B5;
   GFXD3D9TextureFormat[GFXFormatR5G5B5A1] = D3DFMT_A1R5G5B5;
   GFXD3D9TextureFormat[GFXFormatR5G5B5X1] = D3DFMT_X1R5G5B5;
   GFXD3D9TextureFormat[GFXFormatR32F] = D3DFMT_R32F;
   GFXD3D9TextureFormat[GFXFormatA4L4] = D3DFMT_A4L4;
   GFXD3D9TextureFormat[GFXFormatA8L8] = D3DFMT_A8L8;
   GFXD3D9TextureFormat[GFXFormatA8] = D3DFMT_A8;
   GFXD3D9TextureFormat[GFXFormatL8] = D3DFMT_L8;
   GFXD3D9TextureFormat[GFXFormatDXT1] = D3DFMT_DXT1;
   GFXD3D9TextureFormat[GFXFormatDXT2] = D3DFMT_DXT2;
   GFXD3D9TextureFormat[GFXFormatDXT3] = D3DFMT_DXT3;
   GFXD3D9TextureFormat[GFXFormatDXT4] = D3DFMT_DXT4;
   GFXD3D9TextureFormat[GFXFormatDXT5] = D3DFMT_DXT5;
   GFXD3D9TextureFormat[GFXFormatR32G32B32A32F] = D3DFMT_A32B32G32R32F;
   GFXD3D9TextureFormat[GFXFormatR16G16B16A16F] = D3DFMT_A16B16G16R16F;
   GFXD3D9TextureFormat[GFXFormatL16] = D3DFMT_L16;
   GFXD3D9TextureFormat[GFXFormatR16G16B16A16] = D3DFMT_A16B16G16R16;
   GFXD3D9TextureFormat[GFXFormatR16G16] = D3DFMT_G16R16;
   GFXD3D9TextureFormat[GFXFormatR16F] = D3DFMT_R16F;
   GFXD3D9TextureFormat[GFXFormatR16G16F] = D3DFMT_G16R16F;
   GFXD3D9TextureFormat[GFXFormatR10G10B10A2] = D3DFMT_A2R10G10B10;
   GFXD3D9TextureFormat[GFXFormatD32] = D3DFMT_D32;
   GFXD3D9TextureFormat[GFXFormatD24X8] = D3DFMT_D24X8;
   GFXD3D9TextureFormat[GFXFormatD24S8] = D3DFMT_D24S8;
   GFXD3D9TextureFormat[GFXFormatD24FS8] = D3DFMT_D24FS8;
   GFXD3D9TextureFormat[GFXFormatD16] = D3DFMT_D16;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   GFXD3D9TextureFilter[GFXTextureFilterNone] = D3DTEXF_NONE;
   GFXD3D9TextureFilter[GFXTextureFilterPoint] = D3DTEXF_POINT;
   GFXD3D9TextureFilter[GFXTextureFilterLinear] = D3DTEXF_LINEAR;
   GFXD3D9TextureFilter[GFXTextureFilterAnisotropic] = D3DTEXF_ANISOTROPIC;
   GFXD3D9TextureFilter[GFXTextureFilterPyramidalQuad] = D3DTEXF_PYRAMIDALQUAD;
   GFXD3D9TextureFilter[GFXTextureFilterGaussianQuad] = D3DTEXF_GAUSSIANQUAD;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   GFXD3D9Blend[GFXBlendZero] = D3DBLEND_ZERO;
   GFXD3D9Blend[GFXBlendOne] = D3DBLEND_ONE;
   GFXD3D9Blend[GFXBlendSrcColor] = D3DBLEND_SRCCOLOR;
   GFXD3D9Blend[GFXBlendInvSrcColor] = D3DBLEND_INVSRCCOLOR;
   GFXD3D9Blend[GFXBlendSrcAlpha] = D3DBLEND_SRCALPHA;
   GFXD3D9Blend[GFXBlendInvSrcAlpha] = D3DBLEND_INVSRCALPHA;
   GFXD3D9Blend[GFXBlendDestAlpha] = D3DBLEND_DESTALPHA;
   GFXD3D9Blend[GFXBlendInvDestAlpha] = D3DBLEND_INVDESTALPHA;
   GFXD3D9Blend[GFXBlendDestColor] = D3DBLEND_DESTCOLOR;
   GFXD3D9Blend[GFXBlendInvDestColor] = D3DBLEND_INVDESTCOLOR;
   GFXD3D9Blend[GFXBlendSrcAlphaSat] = D3DBLEND_SRCALPHASAT;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   GFXD3D9BlendOp[GFXBlendOpAdd] = D3DBLENDOP_ADD;
   GFXD3D9BlendOp[GFXBlendOpSubtract] = D3DBLENDOP_SUBTRACT;
   GFXD3D9BlendOp[GFXBlendOpRevSubtract] = D3DBLENDOP_REVSUBTRACT;
   GFXD3D9BlendOp[GFXBlendOpMin] = D3DBLENDOP_MIN;
   GFXD3D9BlendOp[GFXBlendOpMax] = D3DBLENDOP_MAX;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   GFXD3D9StencilOp[GFXStencilOpKeep] = D3DSTENCILOP_KEEP;
   GFXD3D9StencilOp[GFXStencilOpZero] = D3DSTENCILOP_ZERO;
   GFXD3D9StencilOp[GFXStencilOpReplace] = D3DSTENCILOP_REPLACE;
   GFXD3D9StencilOp[GFXStencilOpIncrSat] = D3DSTENCILOP_INCRSAT;
   GFXD3D9StencilOp[GFXStencilOpDecrSat] = D3DSTENCILOP_DECRSAT;
   GFXD3D9StencilOp[GFXStencilOpInvert] = D3DSTENCILOP_INVERT;
   GFXD3D9StencilOp[GFXStencilOpIncr] = D3DSTENCILOP_INCR;
   GFXD3D9StencilOp[GFXStencilOpDecr] = D3DSTENCILOP_DECR;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   GFXD3D9CmpFunc[GFXCmpNever] = D3DCMP_NEVER;
   GFXD3D9CmpFunc[GFXCmpLess] = D3DCMP_LESS;
   GFXD3D9CmpFunc[GFXCmpEqual] = D3DCMP_EQUAL;
   GFXD3D9CmpFunc[GFXCmpLessEqual] = D3DCMP_LESSEQUAL;
   GFXD3D9CmpFunc[GFXCmpGreater] = D3DCMP_GREATER;
   GFXD3D9CmpFunc[GFXCmpNotEqual] = D3DCMP_NOTEQUAL;
   GFXD3D9CmpFunc[GFXCmpGreaterEqual] = D3DCMP_GREATEREQUAL;
   GFXD3D9CmpFunc[GFXCmpAlways] = D3DCMP_ALWAYS;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   GFXD3D9CullMode[GFXCullNone] = D3DCULL_NONE;
   GFXD3D9CullMode[GFXCullCW] = D3DCULL_CW;
   GFXD3D9CullMode[GFXCullCCW] = D3DCULL_CCW;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   GFXD3D9FillMode[GFXFillPoint] = D3DFILL_POINT;
   GFXD3D9FillMode[GFXFillWireframe] = D3DFILL_WIREFRAME;
   GFXD3D9FillMode[GFXFillSolid] = D3DFILL_SOLID;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   GFXD3D9PrimType[GFXPointList] = D3DPT_POINTLIST;
   GFXD3D9PrimType[GFXLineList] = D3DPT_LINELIST;
   GFXD3D9PrimType[GFXLineStrip] = D3DPT_LINESTRIP;
   GFXD3D9PrimType[GFXTriangleList] = D3DPT_TRIANGLELIST;
   GFXD3D9PrimType[GFXTriangleStrip] = D3DPT_TRIANGLESTRIP;
   GFXD3D9PrimType[GFXTriangleFan] = D3DPT_TRIANGLEFAN; // anis -> we need to avoid this... it has been removed on the latest directx 10/11
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   GFXD3D9TextureAddress[GFXAddressWrap] = D3DTADDRESS_WRAP ;
   GFXD3D9TextureAddress[GFXAddressMirror] = D3DTADDRESS_MIRROR;
   GFXD3D9TextureAddress[GFXAddressClamp] = D3DTADDRESS_CLAMP;
   GFXD3D9TextureAddress[GFXAddressBorder] = D3DTADDRESS_BORDER;
   GFXD3D9TextureAddress[GFXAddressMirrorOnce] = D3DTADDRESS_MIRRORONCE;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   GFXD3D9DeclType[GFXDeclType_Float] = D3DDECLTYPE_FLOAT1;
   GFXD3D9DeclType[GFXDeclType_Float2] = D3DDECLTYPE_FLOAT2;
   GFXD3D9DeclType[GFXDeclType_Float3] = D3DDECLTYPE_FLOAT3;
   GFXD3D9DeclType[GFXDeclType_Float4] = D3DDECLTYPE_FLOAT4;
   GFXD3D9DeclType[GFXDeclType_Color] = D3DDECLTYPE_D3DCOLOR;
}

