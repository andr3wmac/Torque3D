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

#include "gfx/D3D9/gfxD3D9Cubemap.h"
#include "gfx/gfxCardProfile.h"
#include "gfx/gfxTextureManager.h"
#include "gfx/D3D9/gfxD3D9EnumTranslate.h"

static D3DCUBEMAP_FACES faceList[6] = 
{ 
	D3DCUBEMAP_FACE_POSITIVE_X, D3DCUBEMAP_FACE_NEGATIVE_X,
	D3DCUBEMAP_FACE_POSITIVE_Y, D3DCUBEMAP_FACE_NEGATIVE_Y,
	D3DCUBEMAP_FACE_POSITIVE_Z, D3DCUBEMAP_FACE_NEGATIVE_Z
};

GFXD3D9Cubemap::GFXD3D9Cubemap()
{
	mSupportsAutoMips = GFX->getCardProfiler()->queryProfile("autoMipMapLevel", true);
	mCubeTex = NULL;
	mFaceFormat = GFXFormatR8G8B8A8;
}

GFXD3D9Cubemap::~GFXD3D9Cubemap()
{
	releaseSurfaces();
}

void GFXD3D9Cubemap::releaseSurfaces()
{
	SAFE_RELEASE(mCubeTex);
}

void GFXD3D9Cubemap::initStatic(GFXTexHandle *faces)
{
    AssertFatal(faces, "GFXD3D9Cubemap::initStatic(GFXTexHandle *faces) - Got null GFXTexHandle!");
	AssertFatal(*faces, "GFXD3D9Cubemap::initStatic(GFXTexHandle *faces) - empty texture passed to CubeMap::create");
  
	// NOTE - check tex sizes on all faces - they MUST be all same size
	mTexSize = faces->getWidth();
	mFaceFormat = faces->getFormat();

	HRESULT hr = D3D9DEVICE->CreateCubeTexture(	mTexSize, 
												0, 
												mSupportsAutoMips ? D3DUSAGE_AUTOGENMIPMAP : 0, 
												GFXD3D9TextureFormat[mFaceFormat], 
												D3DPOOL_DEFAULT, 
												&mCubeTex, 
												NULL	);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D9Cubemap::initStatic(GFXTexHandle *faces) - CreateCubeTexture call failure");
	}

	if(mSupportsAutoMips) mCubeTex->GenerateMipSubLevels();

    for(U32 i = 0; i < 6; i++)
    {
		  // get cube face surface
		  IDirect3DSurface9 *cubeSurf;

		  hr = mCubeTex->GetCubeMapSurface(faceList[i], 0, &cubeSurf);

		  if(FAILED(hr)) 
		  {
	 		  AssertFatal(false, "GFXD3D9Cubemap::initStatic(GFXTexHandle *faces) - GetCubeMapSurface call failure");
		  }

		  GFXD3D9TextureObject *texObj = static_cast<GFXD3D9TextureObject*>((GFXTextureObject*)faces[i]);

		  IDirect3DSurface9 *inSurf;
		  hr = texObj->get2DTex()->GetSurfaceLevel(0, &inSurf);

		  if(FAILED(hr)) 
		  {
	 		  AssertFatal(false, "GFXD3D9Cubemap::initStatic(GFXTexHandle *faces) - GetSurfaceLevel call failure");
		  }

		  HRESULT hr = D3D9DEVICE->StretchRect(inSurf, NULL, cubeSurf, NULL, D3DTEXF_NONE);

		  if(FAILED(hr)) 
		  {
	 		  AssertFatal(false, "GFXD3D9Cubemap::initStatic(GFXTexHandle *faces) - StretchRect call failure");
		  }

		  cubeSurf->Release();
		  inSurf->Release();
    }
}

void GFXD3D9Cubemap::initStatic(DDSFile *dds)
{
	AssertFatal(dds, "GFXD3D9Cubemap::initStatic(DDSFile *dds) - Got null DDS file!");
	AssertFatal(dds->isCubemap(), "GFXD3D9Cubemap::initStatic(DDSFile *dds) - Got non-cubemap DDS file!");
	AssertFatal(dds->mSurfaces.size() == 6, "GFXD3D9Cubemap::initStatic(DDSFile *dds) - DDS has less than 6 surfaces!");  
   
	// NOTE - check tex sizes on all faces - they MUST be all same size
	mTexSize = dds->getWidth();
	mFaceFormat = dds->getFormat();
	U32 levels = dds->getMipLevels();

	if(levels > 1) mSupportsAutoMips = false; // anis -> already have mipmaps. don't ask to generate it for us from d3d driver.

	HRESULT hr = D3D9DEVICE->CreateCubeTexture(	mTexSize, 
												levels, 
												mSupportsAutoMips ? D3DUSAGE_AUTOGENMIPMAP : 0, 
												GFXD3D9TextureFormat[mFaceFormat], 
												D3DPOOL_DEFAULT, 
												&mCubeTex, 
												NULL);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D9Cubemap::initStatic(DDSFile *dds) - CreateCubeTexture call failure");
	}

	if(mSupportsAutoMips) mCubeTex->GenerateMipSubLevels();

	for(U32 i = 0; i < 6; i++)
	{
		if(!dds->mSurfaces[i])
		{
			// TODO: The DDS can skip surfaces, but i'm unsure what i should
			// do here when creating the cubemap. Ignore it for now.
			continue;
		}

		for(U32 j = 0; j < levels; j++)
		{
			IDirect3DSurface9 *cubeSurf;
			hr = mCubeTex->GetCubeMapSurface(faceList[i], j, &cubeSurf);

			if(FAILED(hr)) 
			{
				AssertFatal(false, "GFXD3D9Cubemap::initStatic(DDSFile *dds) - GetCubeMapSurface call failure");
			}

			IDirect3DTexture9 *tempText;
			hr = D3D9DEVICE->CreateTexture(	mTexSize,
											mTexSize,
											0, 
											0, 
											GFXD3D9TextureFormat[mFaceFormat], 
											D3DPOOL_SYSTEMMEM, 
											&tempText, 
											NULL );

			if(FAILED(hr)) 
			{
				AssertFatal(false, "GFXD3D9Cubemap::initStatic(DDSFile *dds) - CreateTexture call failure");
			}

			IDirect3DSurface9 *inSurf;
			hr = tempText->GetSurfaceLevel(0, &inSurf);

			if(FAILED(hr)) 
			{
	 			AssertFatal(false, "GFXD3D9Cubemap::initStatic(DDSFile *dds) - GetSurfaceLevel call failure");
			}

			D3DLOCKED_RECT lockedRect;
			hr = inSurf->LockRect(&lockedRect, NULL, 0);

			if(FAILED(hr))
			{
				AssertFatal(false, "GFXD3D9Cubemap::initStatic(DDSFile *dds) - LockRect call failure");
			}

			if(dds->getSurfacePitch(j) != lockedRect.Pitch)
			{
				// Do a row-by-row copy.
				U32 srcPitch = dds->getSurfacePitch(j);
				U32 srcHeight = dds->getHeight(j);
				U8* srcBytes = dds->mSurfaces[i]->mMips[j];
				U8* dstBytes = (U8*)lockedRect.pBits;
				for (U32 i = 0; i < srcHeight; ++i)          
				{
					dMemcpy(dstBytes, srcBytes, srcPitch);
					dstBytes += lockedRect.Pitch;
					srcBytes += srcPitch;
				}           
			}

			else
			{
				dMemcpy(lockedRect.pBits, dds->mSurfaces[i]->mMips[j], dds->getSurfaceSize(j));
			}

			hr = inSurf->UnlockRect();

			if(FAILED(hr))
			{
				AssertFatal(false, "GFXD3D9Cubemap::initStatic(DDSFile *dds) - UnlockRect call failure");
			}

			hr = D3D9DEVICE->UpdateSurface(inSurf, NULL, cubeSurf, NULL);

			if(FAILED(hr))
			{
				AssertFatal(false, "GFXD3D9Cubemap::initStatic(DDSFile *dds) - UpdateSurface call failure");
			}

			inSurf->Release();
			tempText->Release();
			cubeSurf->Release();
		}
	}
}

void GFXD3D9Cubemap::initDynamic(U32 texSize, GFXFormat faceFormat)
{
	mTexSize = texSize;
	mFaceFormat = faceFormat;

	HRESULT hr = D3D9DEVICE->CreateCubeTexture(	mTexSize,
												0,
												(mSupportsAutoMips ? D3DUSAGE_AUTOGENMIPMAP : 0) | D3DUSAGE_RENDERTARGET,
												GFXD3D9TextureFormat[mFaceFormat],
												D3DPOOL_DEFAULT, 
												&mCubeTex, 
												NULL);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D9Cubemap::initDynamic - CreateCubeTexture call failure");
	}

    if(mSupportsAutoMips) mCubeTex->GenerateMipSubLevels();
}

//-----------------------------------------------------------------------------
// Set the cubemap to the specified texture unit num
//-----------------------------------------------------------------------------
void GFXD3D9Cubemap::setToTexUnit(U32 tuNum)
{
	D3D9DEVICE->SetTexture(tuNum, mCubeTex);
}

void GFXD3D9Cubemap::zombify()
{
}

void GFXD3D9Cubemap::resurrect()
{
}
