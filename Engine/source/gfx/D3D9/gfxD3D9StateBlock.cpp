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

#include "gfx/gfxDevice.h"
#include "gfx/D3D9/gfxD3D9StateBlock.h"
#include "gfx/D3D9/gfxD3D9EnumTranslate.h"

GFXD3D9StateBlock::GFXD3D9StateBlock(const GFXStateBlockDesc& desc)
{
   AssertFatal(D3D9DEVICE, "Invalid D3DDevice!");

   mDesc = desc;
   mCachedHashValue = desc.getHashValue();

   // Color writes
   mColorMask = 0; 
   mColorMask |= ( mDesc.colorWriteRed   ? D3DCOLORWRITEENABLE_RED   : 0 );
   mColorMask |= ( mDesc.colorWriteGreen ? D3DCOLORWRITEENABLE_GREEN : 0 );
   mColorMask |= ( mDesc.colorWriteBlue  ? D3DCOLORWRITEENABLE_BLUE  : 0 );
   mColorMask |= ( mDesc.colorWriteAlpha ? D3DCOLORWRITEENABLE_ALPHA : 0 );
}

GFXD3D9StateBlock::~GFXD3D9StateBlock()
{
   
}

/// Returns the hash value of the desc that created this block
U32 GFXD3D9StateBlock::getHashValue() const
{
   return mCachedHashValue;
}

/// Returns a GFXStateBlockDesc that this block represents
const GFXStateBlockDesc& GFXD3D9StateBlock::getDesc() const
{
   return mDesc;      
}

/// Called by D3D9 device to active this state block.
/// @param oldState  The current state, used to make sure we don't set redundant states on the device.  Pass NULL to reset all states.
void GFXD3D9StateBlock::activate(GFXD3D9StateBlock* oldState)
{
   PROFILE_SCOPE( GFXD3D9StateBlock_Activate );

   // blending
   if(!oldState || mDesc.blendEnable != oldState->mDesc.blendEnable)
	   D3D9DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, mDesc.blendEnable);
   if(!oldState || mDesc.blendSrc != oldState->mDesc.blendSrc)
	   D3D9DEVICE->SetRenderState(D3DRS_SRCBLEND, GFXD3D9Blend[mDesc.blendSrc]);
   if(!oldState || mDesc.blendDest != oldState->mDesc.blendDest)
	   D3D9DEVICE->SetRenderState(D3DRS_DESTBLEND, GFXD3D9Blend[mDesc.blendDest]);
   if(!oldState || mDesc.blendOp != oldState->mDesc.blendOp)
	   D3D9DEVICE->SetRenderState(D3DRS_BLENDOP, GFXD3D9BlendOp[mDesc.blendOp]);

   // alpha blending
   if(!oldState || mDesc.separateAlphaBlendEnable != oldState->mDesc.separateAlphaBlendEnable)
	   D3D9DEVICE->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, mDesc.separateAlphaBlendEnable);
   if(!oldState || mDesc.separateAlphaBlendSrc != oldState->mDesc.separateAlphaBlendSrc)
	   D3D9DEVICE->SetRenderState(D3DRS_SRCBLENDALPHA, GFXD3D9Blend[mDesc.separateAlphaBlendSrc]);
   if(!oldState || mDesc.separateAlphaBlendDest != oldState->mDesc.separateAlphaBlendDest)
	   D3D9DEVICE->SetRenderState(D3DRS_DESTBLENDALPHA, GFXD3D9Blend[mDesc.separateAlphaBlendDest]);
   if(!oldState || mDesc.separateAlphaBlendOp != oldState->mDesc.separateAlphaBlendOp)
	   D3D9DEVICE->SetRenderState(D3DRS_BLENDOPALPHA, GFXD3D9BlendOp[mDesc.separateAlphaBlendOp]);

   // alpha test
   if(!oldState || mDesc.alphaTestEnable != oldState->mDesc.alphaTestEnable)
	   D3D9DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, mDesc.alphaTestEnable);
   if(!oldState || mDesc.alphaTestFunc != oldState->mDesc.alphaTestFunc)
	   D3D9DEVICE->SetRenderState(D3DRS_ALPHAFUNC, GFXD3D9CmpFunc[mDesc.alphaTestFunc]);
   if(!oldState || mDesc.alphaTestRef != oldState->mDesc.alphaTestRef)
	   D3D9DEVICE->SetRenderState(D3DRS_ALPHAREF, mDesc.alphaTestRef);

   // color writes
   if(!oldState || mColorMask != oldState->mColorMask)
	   D3D9DEVICE->SetRenderState(D3DRS_COLORWRITEENABLE, mColorMask);

   // culling
   if(!oldState || mDesc.cullMode != oldState->mDesc.cullMode)
	   D3D9DEVICE->SetRenderState(D3DRS_CULLMODE, GFXD3D9CullMode[mDesc.cullMode]);

   // depth
   if(!oldState || mDesc.zEnable != oldState->mDesc.zEnable)
	   D3D9DEVICE->SetRenderState(D3DRS_ZENABLE, mDesc.zEnable);
   if(!oldState || mDesc.zWriteEnable != oldState->mDesc.zWriteEnable)
	   D3D9DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, mDesc.zWriteEnable);
   if(!oldState || mDesc.zFunc != oldState->mDesc.zFunc)
	   D3D9DEVICE->SetRenderState(D3DRS_ZFUNC, GFXD3D9CmpFunc[mDesc.zFunc]);

   if(!oldState || mDesc.zBias != oldState->mDesc.zBias)
	   D3D9DEVICE->SetRenderState(D3DRS_DEPTHBIAS, *((U32*)&mDesc.zBias));
   if(!oldState || mDesc.zSlopeBias != oldState->mDesc.zSlopeBias)
	   D3D9DEVICE->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, *((U32*)&mDesc.zSlopeBias));

   // stencil
   if(!oldState || mDesc.stencilEnable != oldState->mDesc.stencilEnable)
	   D3D9DEVICE->SetRenderState(D3DRS_STENCILENABLE, mDesc.stencilEnable);
   if(!oldState || mDesc.stencilFailOp != oldState->mDesc.stencilFailOp)
	   D3D9DEVICE->SetRenderState(D3DRS_STENCILFAIL, GFXD3D9StencilOp[mDesc.stencilFailOp]);
   if(!oldState || mDesc.stencilZFailOp != oldState->mDesc.stencilZFailOp)
	   D3D9DEVICE->SetRenderState(D3DRS_STENCILZFAIL, GFXD3D9StencilOp[mDesc.stencilZFailOp]);
   if(!oldState || mDesc.stencilPassOp != oldState->mDesc.stencilPassOp)
	   D3D9DEVICE->SetRenderState(D3DRS_STENCILPASS, GFXD3D9StencilOp[mDesc.stencilPassOp]);
   if(!oldState || mDesc.stencilFunc != oldState->mDesc.stencilFunc)
	   D3D9DEVICE->SetRenderState(D3DRS_STENCILFUNC, GFXD3D9CmpFunc[mDesc.stencilFunc]);
   if(!oldState || mDesc.stencilRef != oldState->mDesc.stencilRef)
	   D3D9DEVICE->SetRenderState(D3DRS_STENCILREF, mDesc.stencilRef);
   if(!oldState || mDesc.stencilMask != oldState->mDesc.stencilMask)
	   D3D9DEVICE->SetRenderState(D3DRS_STENCILMASK, mDesc.stencilMask);
   if(!oldState || mDesc.stencilWriteMask != oldState->mDesc.stencilWriteMask)
	   D3D9DEVICE->SetRenderState(D3DRS_STENCILWRITEMASK, mDesc.stencilWriteMask);
   if(!oldState || mDesc.fillMode != oldState->mDesc.fillMode)
	   D3D9DEVICE->SetRenderState(D3DRS_FILLMODE, GFXD3D9FillMode[mDesc.fillMode]);

   // samplers
   for(U32 i = 0; i < getOwningDevice()->getNumSamplers(); i++)
   {      
      if (!oldState || oldState->mDesc.samplers[i].minFilter != mDesc.samplers[i].minFilter) 
		  D3D9DEVICE->SetSamplerState(i, D3DSAMP_MINFILTER, GFXD3D9TextureFilter[mDesc.samplers[i].minFilter]);
      if (!oldState || oldState->mDesc.samplers[i].magFilter != mDesc.samplers[i].magFilter) 
		  D3D9DEVICE->SetSamplerState(i, D3DSAMP_MAGFILTER, GFXD3D9TextureFilter[mDesc.samplers[i].magFilter]);
      if (!oldState || oldState->mDesc.samplers[i].mipFilter != mDesc.samplers[i].mipFilter) 
		  D3D9DEVICE->SetSamplerState(i, D3DSAMP_MIPFILTER, GFXD3D9TextureFilter[mDesc.samplers[i].mipFilter]);

      if (!oldState || oldState->mDesc.samplers[i].mipLODBias != mDesc.samplers[i].mipLODBias) 
		  D3D9DEVICE->SetSamplerState(i, D3DSAMP_MIPMAPLODBIAS, *((LPDWORD)(&mDesc.samplers[i].mipLODBias)));

      if (!oldState || oldState->mDesc.samplers[i].maxAnisotropy != mDesc.samplers[i].maxAnisotropy) 
		  D3D9DEVICE->SetSamplerState(i, D3DSAMP_MAXANISOTROPY, mDesc.samplers[i].maxAnisotropy);
      if (!oldState || oldState->mDesc.samplers[i].addressModeU != mDesc.samplers[i].addressModeU) 
		  D3D9DEVICE->SetSamplerState(i, D3DSAMP_ADDRESSU, GFXD3D9TextureAddress[mDesc.samplers[i].addressModeU]);
      if (!oldState || oldState->mDesc.samplers[i].addressModeV != mDesc.samplers[i].addressModeV) 
		  D3D9DEVICE->SetSamplerState(i, D3DSAMP_ADDRESSV, GFXD3D9TextureAddress[mDesc.samplers[i].addressModeV]);
      if (!oldState || oldState->mDesc.samplers[i].addressModeW != mDesc.samplers[i].addressModeW) 
		  D3D9DEVICE->SetSamplerState(i, D3DSAMP_ADDRESSW, GFXD3D9TextureAddress[mDesc.samplers[i].addressModeW]);
   }
}
