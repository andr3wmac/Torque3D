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

#include "gfx/D3D11/gfxD3D11Cubemap.h"
#include "gfx/gfxCardProfile.h"
#include "gfx/gfxTextureManager.h"
#include "gfx/D3D11/gfxD3D11EnumTranslate.h"

GFXD3D11Cubemap::GFXD3D11Cubemap() : m_pTexture(NULL), m_pShaderResourceView(NULL), m_pDepthStencilSurfaces(NULL)
{
	mDynamic = false;
	mFaceFormat = GFXFormatR8G8B8A8;

	for(U32 i = 0; i < 6; i++)
	{
		m_pSurfaces[i] = NULL;
	}
}

GFXD3D11Cubemap::~GFXD3D11Cubemap()
{
	releaseSurfaces();
}

void GFXD3D11Cubemap::releaseSurfaces()
{
	if (mDynamic)
		GFXTextureManager::removeEventDelegate(this, &GFXD3D11Cubemap::_onTextureEvent);

	for (U32 i = 0; i < 6; i++)
	{
		SAFE_RELEASE(m_pSurfaces[i]);
	}

	SAFE_RELEASE(m_pDepthStencilSurfaces);
	SAFE_RELEASE(m_pShaderResourceView);
	SAFE_RELEASE(m_pTexture);
}

void GFXD3D11Cubemap::_onTextureEvent(GFXTexCallbackCode code)
{
    if (code == GFXZombify)
		releaseSurfaces();
    else if (code == GFXResurrect)
		initDynamic(mTexSize);
}

void GFXD3D11Cubemap::initStatic(GFXTexHandle *faces)
{
    AssertFatal( faces, "GFXD3D11Cubemap::initStatic - Got null GFXTexHandle!" );
	AssertFatal( *faces, "empty texture passed to CubeMap::create" );
  
	// NOTE - check tex sizes on all faces - they MUST be all same size
	mTexSize = faces->getWidth();
	mFaceFormat = faces->getFormat();

	D3D11_TEXTURE2D_DESC desc;

	desc.Width = mTexSize;
	desc.Height = mTexSize;
	desc.MipLevels = 0;
	desc.ArraySize = 6;
	desc.Format = GFXD3D11TextureFormat[mFaceFormat];
	desc.SampleDesc.Count = 0;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE | D3D11_RESOURCE_MISC_GENERATE_MIPS;

	D3D11_SUBRESOURCE_DATA pData[6];

	for(U32 i=0; i<6; i++)
	{
		GFXD3D11TextureObject *texObj = static_cast<GFXD3D11TextureObject*>((GFXTextureObject*)faces[i]);

		pData[i].pSysMem = texObj->getBitmap()->getBits();
		pData[i].SysMemPitch = texObj->getBitmap()->getBytesPerPixel() * texObj->getBitmap()->getHeight();
		pData[i].SysMemSlicePitch = texObj->getBitmap()->getBytesPerPixel() * texObj->getBitmap()->getHeight() * texObj->getBitmap()->getWidth();
	}

	HRESULT hr = static_cast<GFXD3D11Device*>(GFX)->getDevice()->CreateTexture2D(&desc, pData, &m_pTexture);

	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = GFXD3D11TextureFormat[mFaceFormat];
	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	SMViewDesc.TextureCube.MipLevels =  0;
	SMViewDesc.TextureCube.MostDetailedMip = 0;

	hr = static_cast<GFXD3D11Device*>(GFX)->getDevice()->CreateShaderResourceView(m_pTexture, &SMViewDesc, &m_pShaderResourceView);

	if(FAILED(hr))
	{
		AssertFatal(false, "GFXD3D11Cubemap::initStatic(GFXTexHandle *faces) - CreateTexture2D call failure");
	}

	static_cast<GFXD3D11Device*>(GFX)->getDeviceContext()->GenerateMips(m_pShaderResourceView);
}

void GFXD3D11Cubemap::initStatic(DDSFile *dds)
{
    AssertFatal(dds, "GFXD3D11Cubemap::initStatic - Got null DDS file!");
    AssertFatal(dds->isCubemap(), "GFXD3D11Cubemap::initStatic - Got non-cubemap DDS file!");
    AssertFatal(dds->mSurfaces.size() == 6, "GFXD3D11Cubemap::initStatic - DDS has less than 6 surfaces!");  
   
    // NOTE - check tex sizes on all faces - they MUST be all same size
    mTexSize = dds->getWidth();
    mFaceFormat = dds->getFormat();
    U32 levels = dds->getMipLevels();

	D3D11_TEXTURE2D_DESC desc;

	desc.Width = mTexSize;
	desc.Height = mTexSize;
	desc.MipLevels = levels;
	desc.ArraySize = 6;
	desc.Format = GFXD3D11TextureFormat[mFaceFormat];
	desc.SampleDesc.Count = 0;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE | D3D11_RESOURCE_MISC_GENERATE_MIPS;

	D3D11_SUBRESOURCE_DATA* pData = new D3D11_SUBRESOURCE_DATA[6 + levels];

	for(U32 i=0; i<6; i++)
	{
		if (!dds->mSurfaces[i])
			continue;

		for(U32 j = 0; j < levels; j++)
		{
			pData[i + j].pSysMem = dds->mSurfaces[i]->mMips[j];
			pData[i + j].SysMemPitch = dds->getSurfacePitch(j);
			pData[i + j].SysMemSlicePitch = dds->getSurfaceSize(j);
		}
	}

	HRESULT hr = static_cast<GFXD3D11Device*>(GFX)->getDevice()->CreateTexture2D(&desc, pData, &m_pTexture);

	delete [] pData;

	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = GFXD3D11TextureFormat[mFaceFormat];
	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	SMViewDesc.TextureCube.MipLevels =  levels;
	SMViewDesc.TextureCube.MostDetailedMip = 0;

	hr = static_cast<GFXD3D11Device*>(GFX)->getDevice()->CreateShaderResourceView(m_pTexture, &SMViewDesc, &m_pShaderResourceView);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D11Cubemap::initStatic(DDSFile *dds) - CreateTexture2D call failure");
	}
}

void GFXD3D11Cubemap::initDynamic(U32 texSize, GFXFormat faceFormat)
{
	if(!mDynamic)
		GFXTextureManager::addEventDelegate(this, &GFXD3D11Cubemap::_onTextureEvent);

	mDynamic = true;
	mTexSize = texSize;
	mFaceFormat = faceFormat;

	D3D11_TEXTURE2D_DESC desc;

	desc.Width = mTexSize;
	desc.Height = mTexSize;
	desc.MipLevels = 0;
	desc.ArraySize = 6;
	desc.Format = GFXD3D11TextureFormat[mFaceFormat];
	desc.SampleDesc.Count = 0;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE | D3D11_RESOURCE_MISC_GENERATE_MIPS;

	HRESULT hr = static_cast<GFXD3D11Device*>(GFX)->getDevice()->CreateTexture2D(&desc, NULL, &m_pTexture);

	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = GFXD3D11TextureFormat[mFaceFormat];
	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	SMViewDesc.TextureCube.MipLevels =  0;
	SMViewDesc.TextureCube.MostDetailedMip = 0;

	hr = static_cast<GFXD3D11Device*>(GFX)->getDevice()->CreateShaderResourceView(m_pTexture, &SMViewDesc, &m_pShaderResourceView);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D11Cubemap::initDynamic - CreateTexture2D call failure");
	}

	static_cast<GFXD3D11Device*>(GFX)->getDeviceContext()->GenerateMips(m_pShaderResourceView);

	D3D11_RENDER_TARGET_VIEW_DESC viewDesc;
	viewDesc.Format = desc.Format;
	viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
	viewDesc.Texture2DArray.ArraySize = 1;
	viewDesc.Texture2DArray.MipSlice = 0;

	for (U32 i = 0; i < 6; i++)
	{
		viewDesc.Texture2DArray.FirstArraySlice = i;
		hr = static_cast<GFXD3D11Device*>(GFX)->getDevice()->CreateRenderTargetView(m_pTexture, &viewDesc, &m_pSurfaces[i]);

		if(FAILED(hr)) 
		{
			AssertFatal(false, "GFXD3D11Cubemap::initDynamic - CreateRenderTargetView call failure");
		}
	}

    D3D11_TEXTURE2D_DESC depthTexDesc;
    depthTexDesc.Width = mTexSize;
    depthTexDesc.Height = mTexSize;
    depthTexDesc.MipLevels = 1;
    depthTexDesc.ArraySize = 1;
    depthTexDesc.SampleDesc.Count = 0;
    depthTexDesc.SampleDesc.Quality = 0;
    depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
    depthTexDesc.Usage = D3D11_USAGE_DYNAMIC;
    depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthTexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    depthTexDesc.MiscFlags = 0;

    ID3D11Texture2D* depthTex = 0;
    hr = static_cast<GFXD3D11Device*>(GFX)->getDevice()->CreateTexture2D(&depthTexDesc, 0, &depthTex);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D11Cubemap::initDynamic - CreateTexture2D for depth stencil call failure");
	}

    // Create the depth stencil view for the entire cube
    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
    dsvDesc.Format = GFXD3D11TextureFormat[mFaceFormat];
    dsvDesc.Flags  = 0;
    dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsvDesc.Texture2D.MipSlice = 0;
    hr = static_cast<GFXD3D11Device*>(GFX)->getDevice()->CreateDepthStencilView(depthTex, &dsvDesc, &m_pDepthStencilSurfaces);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D11Cubemap::initDynamic - CreateDepthStencilView call failure");
	}
}

//-----------------------------------------------------------------------------
// Set the cubemap to the specified texture unit num
//-----------------------------------------------------------------------------
void GFXD3D11Cubemap::setToTexUnit(U32 tuNum)
{
	if(mDynamic)
	{
		float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		ID3D11RenderTargetView*	pSurfaces;
		ID3D11DepthStencilView*	pDepthStencilSurfaces;

		static_cast<GFXD3D11Device*>(GFX)->getDeviceContext()->PSSetShaderResources(tuNum, 1, &m_pShaderResourceView);

		static_cast<GFXD3D11Device*>(GFX)->getDeviceContext()->OMGetRenderTargets(1, &pSurfaces, &pDepthStencilSurfaces);

		for(U32 i = 0; i < 6; i++)
		{
			static_cast<GFXD3D11Device*>(GFX)->getDeviceContext()->OMSetRenderTargets(1, &m_pSurfaces[i], m_pDepthStencilSurfaces);
			static_cast<GFXD3D11Device*>(GFX)->getDeviceContext()->ClearRenderTargetView(m_pSurfaces[i], ClearColor);
			static_cast<GFXD3D11Device*>(GFX)->getDeviceContext()->ClearDepthStencilView(m_pDepthStencilSurfaces, D3D11_CLEAR_DEPTH, 1.0f, 0);
		}

		static_cast<GFXD3D11Device*>(GFX)->getDeviceContext()->OMSetRenderTargets(1, &pSurfaces, pDepthStencilSurfaces);
	}

	else
	{
		static_cast<GFXD3D11Device*>(GFX)->getDeviceContext()->PSSetShaderResources(tuNum, 1, &m_pShaderResourceView);
	}
}

void GFXD3D11Cubemap::zombify()
{
   // Static cubemaps are handled by D3D
   if( mDynamic )
      releaseSurfaces();
}

void GFXD3D11Cubemap::resurrect()
{
   // Static cubemaps are handled by D3D
   if( mDynamic )
      initDynamic( mTexSize, mFaceFormat );
}
