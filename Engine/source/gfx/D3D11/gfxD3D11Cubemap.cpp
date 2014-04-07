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

GFXD3D11Cubemap::GFXD3D11Cubemap() : m_pTexture(NULL), m_pShaderResourceView(NULL)
{
	mFaceFormat = GFXFormatR8G8B8A8;
}

GFXD3D11Cubemap::~GFXD3D11Cubemap()
{
	releaseSurfaces();
}

void GFXD3D11Cubemap::releaseSurfaces()
{
	SAFE_RELEASE(m_pShaderResourceView);
	SAFE_RELEASE(m_pTexture);
}

void GFXD3D11Cubemap::initStatic(GFXTexHandle *faces)
{
    AssertFatal(faces, "GFXD3D11Cubemap::initStatic(GFXTexHandle *faces) - Got null GFXTexHandle!");
	AssertFatal(*faces, "GFXD3D11Cubemap::initStatic(GFXTexHandle *faces) - empty texture passed to CubeMap::create");
  
	// NOTE - check tex sizes on all faces - they MUST be all same size
	mTexSize = faces->getWidth();
	mFaceFormat = faces->getFormat();

	D3D11_TEXTURE2D_DESC desc;

	desc.Width = mTexSize;
	desc.Height = mTexSize;
	desc.MipLevels = 1;
	desc.ArraySize = 6;
	desc.Format = GFXD3D11TextureFormat[mFaceFormat];
	desc.SampleDesc.Count = D3D11->getMultisampleType().Count;
	desc.SampleDesc.Quality = D3D11->getMultisampleType().Quality;
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

	D3D11_SUBRESOURCE_DATA pData[6];

	for(U32 i=0; i<6; i++)
	{
		GFXD3D11TextureObject *texObj = static_cast<GFXD3D11TextureObject*>((GFXTextureObject*)faces[i]);

		pData[i].pSysMem = texObj->getBitmap()->getBits();
		pData[i].SysMemPitch = texObj->getBitmap()->getBytesPerPixel() * texObj->getBitmap()->getHeight();
		pData[i].SysMemSlicePitch = texObj->getBitmap()->getBytesPerPixel() * texObj->getBitmap()->getHeight() * texObj->getBitmap()->getWidth();
	}

	HRESULT hr = D3D11DEVICE->CreateTexture2D(&desc, pData, &m_pTexture);

	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = GFXD3D11TextureFormat[mFaceFormat];
	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	SMViewDesc.TextureCube.MipLevels =  1;
	SMViewDesc.TextureCube.MostDetailedMip = 0;

	hr = D3D11DEVICE->CreateShaderResourceView(m_pTexture, &SMViewDesc, &m_pShaderResourceView);

	if(FAILED(hr))
	{
		AssertFatal(false, "GFXD3D11Cubemap::initStatic(GFXTexHandle *faces) - CreateTexture2D call failure");
	}
}

void GFXD3D11Cubemap::initStatic(DDSFile *dds)
{
    AssertFatal(dds, "GFXD3D11Cubemap::initStatic - Got null DDS file!");
    AssertFatal(dds->isCubemap(), "GFXD3D11Cubemap::initStatic - Got non-cubemap DDS file!");
    AssertFatal(dds->mSurfaces.size() == 6, "GFXD3D11Cubemap::initStatic - DDS has less than 6 surfaces!");  
   
    // NOTE - check tex sizes on all faces - they MUST be all same size
    mTexSize = dds->getWidth();
    mFaceFormat = dds->getFormat();

	D3D11_TEXTURE2D_DESC desc;

	desc.Width = mTexSize;
	desc.Height = mTexSize;
	desc.MipLevels = 1;
	desc.ArraySize = 6;
	desc.Format = GFXD3D11TextureFormat[mFaceFormat];
	desc.SampleDesc.Count = D3D11->getMultisampleType().Count;
	desc.SampleDesc.Quality = D3D11->getMultisampleType().Quality;
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

	D3D11_SUBRESOURCE_DATA pData[6];

	for(U32 i=0; i<6; i++)
	{
		pData[i].pSysMem = dds->mSurfaces[i]->mMips[0];
		pData[i].SysMemPitch = dds->getSurfacePitch();
		pData[i].SysMemSlicePitch = dds->getSurfaceSize();
	}

	HRESULT hr = D3D11DEVICE->CreateTexture2D(&desc, pData, &m_pTexture);

	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = GFXD3D11TextureFormat[mFaceFormat];
	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	SMViewDesc.TextureCube.MipLevels =  1;
	SMViewDesc.TextureCube.MostDetailedMip = 0;

	hr = D3D11DEVICE->CreateShaderResourceView(m_pTexture, &SMViewDesc, &m_pShaderResourceView);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D11Cubemap::initStatic(DDSFile *dds) - CreateTexture2D call failure");
	}
}

void GFXD3D11Cubemap::initDynamic(U32 texSize, GFXFormat faceFormat)
{
	mTexSize = texSize;
	mFaceFormat = faceFormat;

	D3D11_TEXTURE2D_DESC desc;

	desc.Width = mTexSize;
	desc.Height = mTexSize;
	desc.MipLevels = 1;
	desc.ArraySize = 6;
	desc.Format = GFXD3D11TextureFormat[mFaceFormat];
	desc.SampleDesc.Count = D3D11->getMultisampleType().Count;
	desc.SampleDesc.Quality = D3D11->getMultisampleType().Quality;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE | D3D11_RESOURCE_MISC_GENERATE_MIPS;

	HRESULT hr = D3D11DEVICE->CreateTexture2D(&desc, NULL, &m_pTexture);

	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = GFXD3D11TextureFormat[mFaceFormat];
	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	SMViewDesc.TextureCube.MipLevels =  1;
	SMViewDesc.TextureCube.MostDetailedMip = 0;

	hr = D3D11DEVICE->CreateShaderResourceView(m_pTexture, &SMViewDesc, &m_pShaderResourceView);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D11Cubemap::initDynamic - CreateTexture2D call failure");
	}

	D3D11DEVICECONTEXT->GenerateMips(m_pShaderResourceView);
}

//-----------------------------------------------------------------------------
// Set the cubemap to the specified texture unit num
//-----------------------------------------------------------------------------
void GFXD3D11Cubemap::setToTexUnit(U32 tuNum)
{
	D3D11DEVICECONTEXT->PSSetShaderResources(tuNum, 1, &m_pShaderResourceView);
}

void GFXD3D11Cubemap::zombify()
{
}

void GFXD3D11Cubemap::resurrect()
{
}
