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
#include "gfx/BGFX/gfxBGFXStateBlock.h"

#include "gfx/gfxDevice.h"
#include "core/strings/stringFunctions.h"
#include "gfx/gfxCubemap.h"
#include "gfx/screenshot.h"
#include "gfx/gfxPrimitiveBuffer.h"
#include "gfx/gfxCardProfile.h"
#include "gfx/gfxTextureManager.h"
#include "gfx/gfxStateBlock.h"
#include "gfx/bitmap/gBitmap.h"
#include "core/util/safeDelete.h"
#include "windowManager/win32/win32Window.h"

#include <bgfx.h>
#include <bgfxplatform.h>

U64 GFXBGFXStateBlock::GFXBGFXBlend[GFXBlend_COUNT];

void GFXBGFXStateBlock::initEnumTranslate()
{
   GFXBGFXBlend[GFXBlendZero] = BGFX_STATE_BLEND_ZERO;
   GFXBGFXBlend[GFXBlendOne] = BGFX_STATE_BLEND_ONE;
   GFXBGFXBlend[GFXBlendSrcColor] = BGFX_STATE_BLEND_SRC_COLOR;
   GFXBGFXBlend[GFXBlendInvSrcColor] = BGFX_STATE_BLEND_INV_SRC_COLOR;
   GFXBGFXBlend[GFXBlendSrcAlpha] = BGFX_STATE_BLEND_SRC_ALPHA;
   GFXBGFXBlend[GFXBlendInvSrcAlpha] = BGFX_STATE_BLEND_INV_SRC_ALPHA;
   GFXBGFXBlend[GFXBlendDestAlpha] = BGFX_STATE_BLEND_DST_ALPHA;
   GFXBGFXBlend[GFXBlendInvDestAlpha] = BGFX_STATE_BLEND_INV_DST_ALPHA;
   GFXBGFXBlend[GFXBlendDestColor] = BGFX_STATE_BLEND_DST_COLOR;
   GFXBGFXBlend[GFXBlendInvDestColor] = BGFX_STATE_BLEND_INV_DST_COLOR;
   GFXBGFXBlend[GFXBlendSrcAlphaSat] = BGFX_STATE_BLEND_SRC_ALPHA_SAT;
}

/// Returns a GFXStateBlockDesc that this block represents
const GFXStateBlockDesc& GFXBGFXStateBlock::getDesc() const
{
   return mDesc;      
}


GFXBGFXStateBlock::GFXBGFXStateBlock(const GFXStateBlockDesc& desc)
{
   mDesc = desc;
}

U64 GFXBGFXStateBlock::getBGFXState()
{
   U64 result = 0;
   if ( mDesc.blendDefined )
      result |= BGFX_STATE_BLEND_FUNC(GFXBGFXStateBlock::GFXBGFXBlend[mDesc.blendSrc], GFXBGFXStateBlock::GFXBGFXBlend[mDesc.blendDest]);

   //if ( mDesc.alphaDefined )
   //   Con::printf("BLEND DEFINED!");

   if ( mDesc.cullDefined )
   {
      result |= mDesc.cullMode == GFXCullMode::GFXCullCCW ? BGFX_STATE_CULL_CCW : 0;
      result |= mDesc.cullMode == GFXCullMode::GFXCullCW ? BGFX_STATE_CULL_CW : 0;
   }

   if ( mDesc.zWriteEnable )
      result |= BGFX_STATE_DEPTH_WRITE;

   result |= BGFX_STATE_RGB_WRITE;
   return result;
}

U64 GFXBGFXStateBlock::getTextureFlags()
{
   U64 result = 0;

   if ( mDesc.samplersDefined )
   {
      result |= mDesc.samplers[0].addressModeU == GFXTextureAddressMode::GFXAddressClamp ? BGFX_TEXTURE_U_CLAMP : 0;
      result |= mDesc.samplers[0].addressModeU == GFXTextureAddressMode::GFXAddressMirror ? BGFX_TEXTURE_U_MIRROR : 0;
      //result |= mDesc.samplers[0].addressModeU == GFXTextureAddressMode::GFXAddressBorder ? BGFX_TEXTURE_U_SHIFT : 0;
      //result |= mDesc.samplers[0].addressModeU == GFXTextureAddressMode::GFXAddressClamp ? BGFX_TEXTURE_U_MASK : 0;

      result |= mDesc.samplers[0].addressModeV == GFXTextureAddressMode::GFXAddressClamp ? BGFX_TEXTURE_V_CLAMP : 0;
      result |= mDesc.samplers[0].addressModeV == GFXTextureAddressMode::GFXAddressMirror ? BGFX_TEXTURE_V_MIRROR : 0;

      result |= mDesc.samplers[0].addressModeW == GFXTextureAddressMode::GFXAddressClamp ? BGFX_TEXTURE_W_CLAMP : 0;
      result |= mDesc.samplers[0].addressModeW == GFXTextureAddressMode::GFXAddressMirror ? BGFX_TEXTURE_W_MIRROR : 0;

      result |= mDesc.samplers[0].magFilter == GFXTextureFilterType::GFXTextureFilterPoint ? BGFX_TEXTURE_MAG_POINT : 0;
      result |= mDesc.samplers[0].magFilter == GFXTextureFilterType::GFXTextureFilterAnisotropic ? BGFX_TEXTURE_MAG_ANISOTROPIC : 0;
      result |= mDesc.samplers[0].minFilter == GFXTextureFilterType::GFXTextureFilterPoint ? BGFX_TEXTURE_MIN_POINT : 0;
      result |= mDesc.samplers[0].minFilter == GFXTextureFilterType::GFXTextureFilterAnisotropic ? BGFX_TEXTURE_MIN_ANISOTROPIC : 0;
      result |= mDesc.samplers[0].mipFilter == GFXTextureFilterType::GFXTextureFilterPoint ? BGFX_TEXTURE_MIP_POINT : 0;

      //GFXTextureOp::
      //mDesc.samplers[0].textureColorOp 
   }

   return result;
}