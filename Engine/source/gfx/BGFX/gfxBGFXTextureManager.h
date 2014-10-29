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

#ifndef _GFXBGFXTextureManager_H_
#define _GFXBGFXTextureManager_H_

#ifndef _GFXTEXTUREOBJECT_H_
#include "gfx/gfxTextureObject.h"
#endif

#ifndef _GFXTEXTUREMANAGER_H_
#include "gfx/gfxTextureManager.h"
#endif

#ifndef BGFX_H_HEADER_GUARD
#include <bgfx.h>
#endif

#ifndef NANOVG_H
#include <nanovg.h>
#endif

class GFXBGFXTextureObject : public GFXTextureObject 
{
   GFXLockedRect* lockedRect;
   RectI* lockedArea;
   S32 nvgImage;

public:
   bgfx::UniformHandle u_texColor;
   U8* tempBuf;
   bgfx::TextureHandle mBGFXTexture;

   GFXBGFXTextureObject(GFXDevice * aDevice, GFXTextureProfile *profile); 
   ~GFXBGFXTextureObject();

   virtual void pureVirtualCrash() { };

   virtual GFXLockedRect * lock( U32 mipLevel = 0, RectI *inRect = NULL );
   virtual void unlock( U32 mipLevel = 0);
   virtual bool copyToBmp(GBitmap *) { return false; };

   virtual void release();
   virtual void zombify();
   virtual void resurrect();

   S32 getNVGImage(NVGcontext* context);
};

class GFXBGFXTextureManager : public GFXTextureManager
{

protected:
      virtual GFXTextureObject *_createTextureObject( U32 height, 
                                                      U32 width, 
                                                      U32 depth, 
                                                      GFXFormat format, 
                                                      GFXTextureProfile *profile, 
                                                      U32 numMipLevels, 
                                                      bool forceMips = false, 
                                                      S32 antialiasLevel = 0, 
                                                      GFXTextureObject *inTex = NULL );

      /// Load a texture from a proper DDSFile instance.
      virtual bool _loadTexture(GFXTextureObject *texture, DDSFile *dds);

      /// Load data into a texture from a GBitmap using the internal API.
      virtual bool _loadTexture(GFXTextureObject *texture, GBitmap *bmp);

      /// Load data into a texture from a raw buffer using the internal API.
      ///
      /// Note that the size of the buffer is assumed from the parameters used
      /// for this GFXTextureObject's _createTexture call.
      virtual bool _loadTexture(GFXTextureObject *texture, void *raw);

      /// Refresh a texture using the internal API.
      virtual bool _refreshTexture(GFXTextureObject *texture){ return true; };

      /// Free a texture (but do not delete the GFXTextureObject) using the internal
      /// API.
      ///
      /// This is only called during zombification for textures which need it, so you
      /// don't need to do any internal safety checks.
      virtual bool _freeTexture(GFXTextureObject *texture, bool zombify=false);

      virtual U32 _getTotalVideoMemory() { return 0; };
      virtual U32 _getFreeVideoMemory() { return 0; };
};

#endif