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
#include "gfx/BGFX/gfxBGFXShader.h"

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

GFXBGFXShader::GFXBGFXShader()
{
   mVertexShader.idx = bgfx::invalidHandle;
   mPixelShader.idx = bgfx::invalidHandle;
   mShaderProgram.idx = bgfx::invalidHandle;
   mPixelShaderFile = NULL;
   mVertexShaderFile = NULL;
}

GFXBGFXShader::~GFXBGFXShader()
{
   if ( mPixelShaderFile )
   {
      mPixelShaderFile->close();
      SAFE_DELETE(mPixelShaderFile);
   }
   if ( mVertexShaderFile )
   {
      mVertexShaderFile->close();
      SAFE_DELETE(mVertexShaderFile);
   }
}

bool GFXBGFXShader::_init()
{
   // TODO: Multiplatform support.

   if ( mVertexShader.idx == bgfx::invalidHandle )
   {
      String compiledPath = mVertexFile.getFullPath() + ".bin";
      bgfx::compileShader(0, mVertexFile.getFullPath().c_str(), compiledPath.c_str(), "v", "windows", "vs_3_0", NULL, "shaders/includes/", "shaders/includes/varying.def.sc");

      SAFE_DELETE(mVertexShaderFile);
      mVertexShaderFile = new FileObject();
      if ( mVertexShaderFile->readMemory(compiledPath.c_str()) )
      {
         const bgfx::Memory* mem = bgfx::makeRef(mVertexShaderFile->buffer(), mVertexShaderFile->getBufferSize());
         mVertexShader = bgfx::createShader(mem);
         //mVertexShaderFile->close();
      }
   }

   if ( mPixelShader.idx == bgfx::invalidHandle )
   {
      String compiledPath = mPixelFile.getFullPath() + ".bin";
      bgfx::compileShader(0, mPixelFile.getFullPath().c_str(), compiledPath.c_str(), "f", "windows", "ps_3_0", NULL, "shaders/includes/", "shaders/includes/varying.def.sc");

      SAFE_DELETE(mPixelShaderFile);
      mPixelShaderFile = new FileObject();
      if ( mPixelShaderFile->readMemory(compiledPath.c_str()) )
      {
         const bgfx::Memory* mem = bgfx::makeRef(mPixelShaderFile->buffer(), mPixelShaderFile->getBufferSize());
         mPixelShader = bgfx::createShader(mem);
         //mPixelShaderFile->close();
      }
   }

   // This should be moved asap.
   if ( mShaderProgram.idx == bgfx::invalidHandle && mVertexShader.idx != bgfx::invalidHandle && mPixelShader.idx != bgfx::invalidHandle )
      mShaderProgram = bgfx::createProgram(mVertexShader, mPixelShader);

   //if ( mVertexShaderFile )
   //   mVertexShaderFile->close();
   //if ( mPixelShaderFile )
    //  mPixelShaderFile->close();
   return (mShaderProgram.idx != bgfx::invalidHandle);
}