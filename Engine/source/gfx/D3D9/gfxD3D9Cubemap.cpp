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
   GFXD3D9Device *dev = static_cast<GFXD3D9Device *>(GFX);    

   mSupportsAutoMips = dev->getCardProfiler()->queryProfile("autoMipMapLevel", true);

   mCubeTex = NULL;
   mDynamic = false;
   mFaceFormat = GFXFormatR8G8B8A8;
}

GFXD3D9Cubemap::~GFXD3D9Cubemap()
{
   releaseSurfaces();
}

void GFXD3D9Cubemap::releaseSurfaces()
{
   if (!mCubeTex)
      return;

   if (mDynamic)
      GFXTextureManager::removeEventDelegate(this, &GFXD3D9Cubemap::_onTextureEvent);

   mCubeTex->Release();
   mCubeTex = NULL;
}

void GFXD3D9Cubemap::_onTextureEvent(GFXTexCallbackCode code)
{
   if (code == GFXZombify)
      releaseSurfaces();
   else if (code == GFXResurrect)
      initDynamic(mTexSize);
}

void GFXD3D9Cubemap::initStatic(GFXTexHandle *faces)
{
    AssertFatal( faces, "GFXD3D9Cubemap::initStatic - Got null GFXTexHandle!" );
	AssertFatal( *faces, "empty texture passed to CubeMap::create" );
  
	// NOTE - check tex sizes on all faces - they MUST be all same size
	mTexSize = faces->getWidth();
	mFaceFormat = faces->getFormat();

	HRESULT hr = static_cast<GFXD3D9Device*>(GFX)->getDevice()->CreateCubeTexture(	mTexSize, 
																					0, 
																					mSupportsAutoMips ? D3DUSAGE_AUTOGENMIPMAP : 0, 
																					GFXD3D9TextureFormat[mFaceFormat], 
																					D3DPOOL_MANAGED, 
																					&mCubeTex, 
																					NULL	);

	if(mSupportsAutoMips) mCubeTex->GenerateMipSubLevels();

	if(FAILED(hr)) 
	{
		AssertFatal(false, "CreateCubeTexture call failure");
	}

    for(U32 i=0; i<6; i++)
    {
      // get cube face surface
      IDirect3DSurface9 *cubeSurf = NULL;

      hr = mCubeTex->GetCubeMapSurface(faceList[i], 0, &cubeSurf);

	  if(FAILED(hr)) 
	  {
	 	  AssertFatal(false, "GetCubeMapSurface call failure");
	  }

      GFXD3D9TextureObject *texObj = static_cast<GFXD3D9TextureObject*>((GFXTextureObject*)faces[i]);
      IDirect3DSurface9 *inSurf;
      hr = texObj->get2DTex()->GetSurfaceLevel(0, &inSurf);

	  if(FAILED( hr )) 
	  {
	 	  AssertFatal(false, "GetSurfaceLevel call failure");
	  }

      // Lock the dest surface.
      D3DLOCKED_RECT lockedRect;
      cubeSurf->LockRect(&lockedRect, NULL, 0);
	  
	  D3DLOCKED_RECT lockedRect2;
      inSurf->LockRect(&lockedRect2, NULL, 0);

	  // Do a row-by-row copy.
	  U32 srcPitch = lockedRect2.Pitch;
	  U32 srcHeight = texObj->getBitmapHeight();
	  U8* srcBytes = (U8*)lockedRect2.pBits;
	  U8* dstBytes = (U8*)lockedRect.pBits;
	  
	  for (U32 j = 0; j<srcHeight; j++)          
	  {
		memcpy(dstBytes, srcBytes, srcPitch);
		dstBytes += lockedRect.Pitch;
		srcBytes += srcPitch;
	  }

	  cubeSurf->UnlockRect();
	  inSurf->UnlockRect();

      cubeSurf->Release();
      inSurf->Release();
    }
}

void GFXD3D9Cubemap::initStatic(DDSFile *dds)
{
   AssertFatal(dds, "GFXD3D9Cubemap::initStatic - Got null DDS file!");
   AssertFatal(dds->isCubemap(), "GFXD3D9Cubemap::initStatic - Got non-cubemap DDS file!");
   AssertFatal(dds->mSurfaces.size() == 6, "GFXD3D9Cubemap::initStatic - DDS has less than 6 surfaces!");  
   
   // NOTE - check tex sizes on all faces - they MUST be all same size
   mTexSize = dds->getWidth();
   mFaceFormat = dds->getFormat();
   U32 levels = dds->getMipLevels();

   if(levels > 0) mSupportsAutoMips = false;

   HRESULT hr = static_cast<GFXD3D9Device*>(GFX)->getDevice()->CreateCubeTexture(	mTexSize, 
																					levels, 
																					mSupportsAutoMips ? D3DUSAGE_AUTOGENMIPMAP : 0, 
																					GFXD3D9TextureFormat[mFaceFormat], 
																					D3DPOOL_MANAGED, 
																					&mCubeTex, 
																					NULL);

   if(FAILED(hr)) 
   {
	   AssertFatal(false, "CreateCubeTexture call failure");
   }

   if(mSupportsAutoMips) mCubeTex->GenerateMipSubLevels();

   for(U32 i=0; i<6; i++)
   {
      if (!dds->mSurfaces[i]) 
		  continue;

      for(U32 j = 0; j < levels; j++)
      {
         IDirect3DSurface9 *cubeSurf = NULL;
         hr = mCubeTex->GetCubeMapSurface(faceList[i], j, &cubeSurf);

		 if(FAILED(hr)) 
		 {
			AssertFatal(false, "GFXD3D9Cubemap::initStatic - Get cubemap surface failed!");
		 }

         D3DLOCKED_RECT lockedRect;
         hr = cubeSurf->LockRect(&lockedRect, NULL, 0);

		 if(FAILED(hr)) 
		 {
			AssertFatal(false, "GFXD3D9Cubemap::initStatic - Failed to lock surface level for load!");
		 }

         memcpy(lockedRect.pBits, dds->mSurfaces[i]->mMips[j], dds->getSurfaceSize(j));

         cubeSurf->UnlockRect();
         cubeSurf->Release();
      }
   }
}

void GFXD3D9Cubemap::initDynamic(U32 texSize, GFXFormat faceFormat)
{
   if(mCubeTex)
      return;

   if(!mDynamic)
      GFXTextureManager::addEventDelegate( this, &GFXD3D9Cubemap::_onTextureEvent);

   mDynamic = true;
   mTexSize = texSize;
   mFaceFormat = faceFormat;

   HRESULT hr = static_cast<GFXD3D9Device*>(GFX)->getDevice()->CreateCubeTexture(	texSize,
																					0,
																					mSupportsAutoMips ? (D3DUSAGE_AUTOGENMIPMAP | D3DUSAGE_RENDERTARGET) : D3DUSAGE_RENDERTARGET,
																					GFXD3D9TextureFormat[faceFormat],
																					D3DPOOL_DEFAULT, 
																					&mCubeTex, 
																					NULL);

    if(mSupportsAutoMips) mCubeTex->GenerateMipSubLevels();

	if(FAILED(hr)) 
	{
		AssertFatal(false, "CreateCubeTexture call failure");
	}
}

//-----------------------------------------------------------------------------
// Set the cubemap to the specified texture unit num
//-----------------------------------------------------------------------------
void GFXD3D9Cubemap::setToTexUnit(U32 tuNum)
{
   static_cast<GFXD3D9Device *>(GFX)->getDevice()->SetTexture( tuNum, mCubeTex );
}

void GFXD3D9Cubemap::zombify()
{
   // Static cubemaps are handled by D3D
   if( mDynamic )
      releaseSurfaces();
}

void GFXD3D9Cubemap::resurrect()
{
   // Static cubemaps are handled by D3D
   if( mDynamic )
      initDynamic( mTexSize, mFaceFormat );
}
