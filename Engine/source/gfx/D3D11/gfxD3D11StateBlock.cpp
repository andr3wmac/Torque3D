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

#include "gfx/gfxDevice.h"
#include "gfx/D3D11/gfxD3D11StateBlock.h"
#include "gfx/D3D11/gfxD3D11EnumTranslate.h"

inline D3D11_FILTER GetD3D11TextureFilter(const GFXTextureFilterType minFilter, const GFXTextureFilterType magFilter, const GFXTextureFilterType mipFilter, const bool comparison)
{
	bool anisotropic = false;

	D3D11_FILTER_TYPE min, mag, mip;

	switch(mipFilter)
	{
	case GFXTextureFilterNone:
	case GFXTextureFilterPoint:
		mip = D3D11_FILTER_TYPE_POINT;
		break;

	default:
		mip = D3D11_FILTER_TYPE_LINEAR;
		break;
	}

	switch(minFilter)
	{
	case GFXTextureFilterNone:
	case GFXTextureFilterPoint:
		min = D3D11_FILTER_TYPE_POINT;
		break;

	case GFXTextureFilterLinear:
		min = D3D11_FILTER_TYPE_LINEAR;
		break;

	default:
		min = D3D11_FILTER_TYPE_LINEAR;
		anisotropic = true;
		break;
	}

	switch (magFilter)
	{
	case GFXTextureFilterNone:
	case GFXTextureFilterPoint:
		mag = D3D11_FILTER_TYPE_POINT;
		break;

	case GFXTextureFilterLinear:
		mag = D3D11_FILTER_TYPE_LINEAR;
		break;

	default:
		mag = D3D11_FILTER_TYPE_LINEAR;
		anisotropic = true;
		break;
	}

	D3D11_FILTER filter = anisotropic ? D3D11_ENCODE_ANISOTROPIC_FILTER(comparison) : D3D11_ENCODE_BASIC_FILTER(min, mag, mip, comparison);

	return filter;
}

GFXD3D11StateBlock::GFXD3D11StateBlock(const GFXStateBlockDesc& desc)
{
	mDesc = desc;
	mCachedHashValue = desc.getHashValue();

	// Color writes
	mColorMask = 0; 
    mColorMask |= ( mDesc.colorWriteRed   ? D3D11_COLOR_WRITE_ENABLE_RED   : 0 );
    mColorMask |= ( mDesc.colorWriteGreen ? D3D11_COLOR_WRITE_ENABLE_GREEN : 0 );
    mColorMask |= ( mDesc.colorWriteBlue  ? D3D11_COLOR_WRITE_ENABLE_BLUE  : 0 );
    mColorMask |= ( mDesc.colorWriteAlpha ? D3D11_COLOR_WRITE_ENABLE_ALPHA : 0 );

	mBlendDesc.AlphaToCoverageEnable = false;
	mBlendDesc.IndependentBlendEnable = false;

	mBlendDesc.RenderTarget[0].BlendEnable = mDesc.blendEnable;
	mBlendDesc.RenderTarget[0].BlendOp = GFXD3D11BlendOp[mDesc.blendOp];
	mBlendDesc.RenderTarget[0].BlendOpAlpha = GFXD3D11BlendOp[mDesc.separateAlphaBlendOp];
	mBlendDesc.RenderTarget[0].DestBlend = GFXD3D11Blend[mDesc.blendDest];
	mBlendDesc.RenderTarget[0].DestBlendAlpha = GFXD3D11Blend[mDesc.separateAlphaBlendDest];
	mBlendDesc.RenderTarget[0].SrcBlend = GFXD3D11Blend[mDesc.blendSrc];
	mBlendDesc.RenderTarget[0].SrcBlendAlpha = GFXD3D11Blend[mDesc.separateAlphaBlendSrc];
	mBlendDesc.RenderTarget[0].RenderTargetWriteMask = mColorMask;

	HRESULT hr = D3D11DEVICE->CreateBlendState(&mBlendDesc, &mBlendState);

	if(FAILED(hr))
	{
		AssertFatal(false, "GFXD3D11StateBlock::GFXD3D11StateBlock - CreateBlendState call failure.");
	}

	mDepthStencilDesc.DepthWriteMask = mDesc.zWriteEnable ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
	mDepthStencilDesc.DepthEnable = mDesc.zEnable;
	mDepthStencilDesc.DepthFunc = GFXD3D11CmpFunc[mDesc.zFunc];
	mDepthStencilDesc.StencilWriteMask = mDesc.stencilWriteMask;
	mDepthStencilDesc.StencilReadMask = mDesc.stencilMask;
	mDepthStencilDesc.StencilEnable = mDesc.stencilEnable;

	mDepthStencilDesc.FrontFace.StencilFunc = GFXD3D11CmpFunc[mDesc.stencilFunc];
	mDepthStencilDesc.FrontFace.StencilFailOp = GFXD3D11StencilOp[mDesc.stencilFailOp];
	mDepthStencilDesc.FrontFace.StencilDepthFailOp = GFXD3D11StencilOp[mDesc.stencilZFailOp];
	mDepthStencilDesc.FrontFace.StencilPassOp = GFXD3D11StencilOp[mDesc.stencilPassOp];
	mDepthStencilDesc.BackFace = mDepthStencilDesc.FrontFace;

	hr = D3D11DEVICE->CreateDepthStencilState(&mDepthStencilDesc, &mDepthStencilState);

	if(FAILED(hr))
	{
		AssertFatal(false, "GFXD3D11StateBlock::GFXD3D11StateBlock - CreateDepthStencilState call failure.");
	}

	mRasterizerDesc.CullMode = GFXD3D11CullMode[mDesc.cullMode];
	mRasterizerDesc.FillMode = GFXD3D11FillMode[mDesc.fillMode];
	mRasterizerDesc.DepthBias = mDesc.zBias;
	mRasterizerDesc.SlopeScaledDepthBias = mDesc.zSlopeBias;
	mRasterizerDesc.AntialiasedLineEnable = FALSE;
	mRasterizerDesc.MultisampleEnable = FALSE;
	mRasterizerDesc.ScissorEnable = FALSE;
	mRasterizerDesc.DepthClipEnable = TRUE;
	mRasterizerDesc.FrontCounterClockwise = TRUE;
	mRasterizerDesc.DepthBiasClamp = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;

	hr = D3D11DEVICE->CreateRasterizerState(&mRasterizerDesc, &mRasterizerState);

	if(FAILED(hr))
	{
		AssertFatal(false, "GFXD3D11StateBlock::GFXD3D11StateBlock - CreateDepthStencilState call failure.");
	}

	for (U32 i = 0; i < getOwningDevice()->getNumSamplers(); i++)
	{
		static const bool comparison = false; // unused

		mSamplerDesc[i].AddressU = GFXD3D11TextureAddress[mDesc.samplers[i].addressModeU];
		mSamplerDesc[i].AddressV = GFXD3D11TextureAddress[mDesc.samplers[i].addressModeV];
		mSamplerDesc[i].AddressW = GFXD3D11TextureAddress[mDesc.samplers[i].addressModeW];

		mSamplerDesc[i].MaxAnisotropy = mDesc.samplers[i].maxAnisotropy;
		mSamplerDesc[i].MipLODBias = mDesc.samplers[i].mipLODBias;
		mSamplerDesc[i].MinLOD = 0.0f;
		mSamplerDesc[i].MaxLOD = D3D11_FLOAT32_MAX;

		mSamplerDesc[i].Filter = GetD3D11TextureFilter(mDesc.samplers[i].minFilter, mDesc.samplers[i].magFilter, mDesc.samplers[i].mipFilter, comparison);
		mSamplerDesc[i].BorderColor[0] = D3D11_DEFAULT_BORDER_COLOR_COMPONENT;
		mSamplerDesc[i].BorderColor[1] = D3D11_DEFAULT_BORDER_COLOR_COMPONENT;
		mSamplerDesc[i].BorderColor[2] = D3D11_DEFAULT_BORDER_COLOR_COMPONENT;
		mSamplerDesc[i].BorderColor[3] = D3D11_DEFAULT_BORDER_COLOR_COMPONENT;
		mSamplerDesc[i].ComparisonFunc = D3D11_COMPARISON_NEVER;

		hr = D3D11DEVICE->CreateSamplerState(&mSamplerDesc[i], &mSamplerStates[i]);

		if(FAILED(hr))
		{
			AssertFatal(false, "GFXD3D11StateBlock::GFXD3D11StateBlock - CreateSamplerState call failure.");
		}
	}
}

GFXD3D11StateBlock::~GFXD3D11StateBlock()
{
   SAFE_RELEASE(mBlendState)
   SAFE_RELEASE(mRasterizerState);
   SAFE_RELEASE(mDepthStencilState);

   for(U32 i = 0; i < getOwningDevice()->getNumSamplers(); ++i)
       SAFE_RELEASE(mSamplerStates[i]);
}

/// Returns the hash value of the desc that created this block
U32 GFXD3D11StateBlock::getHashValue() const
{
   return mCachedHashValue;
}

/// Returns a GFXStateBlockDesc that this block represents
const GFXStateBlockDesc& GFXD3D11StateBlock::getDesc() const
{
   return mDesc;
}

/// Called by D3D11 device to active this state block.
void GFXD3D11StateBlock::activate(GFXD3D11StateBlock* oldState)
{
	PROFILE_SCOPE(GFXD3D11StateBlock_Activate);

	mBlendDesc.AlphaToCoverageEnable = false;
	mBlendDesc.IndependentBlendEnable = false;

	mBlendDesc.RenderTarget[0].BlendEnable = mDesc.blendEnable;
	mBlendDesc.RenderTarget[0].BlendOp = GFXD3D11BlendOp[mDesc.blendOp];
	mBlendDesc.RenderTarget[0].BlendOpAlpha = GFXD3D11BlendOp[mDesc.separateAlphaBlendOp];
	mBlendDesc.RenderTarget[0].DestBlend = GFXD3D11Blend[mDesc.blendDest];
	mBlendDesc.RenderTarget[0].DestBlendAlpha = GFXD3D11Blend[mDesc.separateAlphaBlendDest];
	mBlendDesc.RenderTarget[0].SrcBlend = GFXD3D11Blend[mDesc.blendSrc];
	mBlendDesc.RenderTarget[0].SrcBlendAlpha = GFXD3D11Blend[mDesc.separateAlphaBlendSrc];
	mBlendDesc.RenderTarget[0].RenderTargetWriteMask = mColorMask;

	static const float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	D3D11DEVICECONTEXT->OMSetBlendState(mBlendState, blendFactor , 0xFFFFFFFF);

	mDepthStencilDesc.DepthWriteMask = mDesc.zWriteEnable ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
	mDepthStencilDesc.DepthEnable = mDesc.zEnable;
	mDepthStencilDesc.DepthFunc = GFXD3D11CmpFunc[mDesc.zFunc];
	mDepthStencilDesc.StencilWriteMask = mDesc.stencilWriteMask;
	mDepthStencilDesc.StencilReadMask = mDesc.stencilMask;
	mDepthStencilDesc.StencilEnable = mDesc.stencilEnable;

	mDepthStencilDesc.FrontFace.StencilFunc = GFXD3D11CmpFunc[mDesc.stencilFunc];
	mDepthStencilDesc.FrontFace.StencilFailOp = GFXD3D11StencilOp[mDesc.stencilFailOp];
	mDepthStencilDesc.FrontFace.StencilDepthFailOp = GFXD3D11StencilOp[mDesc.stencilZFailOp];
	mDepthStencilDesc.FrontFace.StencilPassOp = GFXD3D11StencilOp[mDesc.stencilPassOp];
	mDepthStencilDesc.BackFace = mDepthStencilDesc.FrontFace;

	D3D11DEVICECONTEXT->OMSetDepthStencilState(mDepthStencilState, mDesc.stencilRef);

	mRasterizerDesc.CullMode = GFXD3D11CullMode[mDesc.cullMode];
	mRasterizerDesc.FillMode = GFXD3D11FillMode[mDesc.fillMode];
	mRasterizerDesc.DepthBias = mDesc.zBias;
	mRasterizerDesc.SlopeScaledDepthBias = mDesc.zSlopeBias;
	mRasterizerDesc.AntialiasedLineEnable = FALSE;
	mRasterizerDesc.MultisampleEnable = FALSE;
	mRasterizerDesc.ScissorEnable = FALSE;
	mRasterizerDesc.DepthClipEnable = TRUE;
	mRasterizerDesc.FrontCounterClockwise = TRUE;
	mRasterizerDesc.DepthBiasClamp = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;

    D3D11DEVICECONTEXT->RSSetState(mRasterizerState);

	for (U32 i = 0; i < getOwningDevice()->getNumSamplers(); i++)
	{
		static const bool comparison = false; // unused

		mSamplerDesc[i].AddressU = GFXD3D11TextureAddress[mDesc.samplers[i].addressModeU];
		mSamplerDesc[i].AddressV = GFXD3D11TextureAddress[mDesc.samplers[i].addressModeV];
		mSamplerDesc[i].AddressW = GFXD3D11TextureAddress[mDesc.samplers[i].addressModeW];

		mSamplerDesc[i].MaxAnisotropy = mDesc.samplers[i].maxAnisotropy;
		mSamplerDesc[i].MipLODBias = mDesc.samplers[i].mipLODBias;
		mSamplerDesc[i].MinLOD = 0.0f;
		mSamplerDesc[i].MaxLOD = D3D11_FLOAT32_MAX;

		mSamplerDesc[i].Filter = GetD3D11TextureFilter(mDesc.samplers[i].minFilter, mDesc.samplers[i].magFilter, mDesc.samplers[i].mipFilter, comparison);
		mSamplerDesc[i].BorderColor[0] = D3D11_DEFAULT_BORDER_COLOR_COMPONENT;
		mSamplerDesc[i].BorderColor[1] = D3D11_DEFAULT_BORDER_COLOR_COMPONENT;
		mSamplerDesc[i].BorderColor[2] = D3D11_DEFAULT_BORDER_COLOR_COMPONENT;
		mSamplerDesc[i].BorderColor[3] = D3D11_DEFAULT_BORDER_COLOR_COMPONENT;
		mSamplerDesc[i].ComparisonFunc = D3D11_COMPARISON_NEVER;

		D3D11DEVICECONTEXT->PSSetSamplers(i, 1, &mSamplerStates[i]);
	}
}
