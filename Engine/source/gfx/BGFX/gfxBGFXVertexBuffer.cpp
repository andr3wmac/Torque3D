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
#include "gfx/BGFX/gfxBGFXVertexBuffer.h"
#include "gfx/BGFX/gfxBGFXDevice.h"
#include "gfx/BGFX/gfxBGFXTextureManager.h"
#include "gfx/BGFX/gfxBGFXStateBlock.h"

#include "core/strings/stringFunctions.h"
#include "gfx/gfxCubemap.h"
#include "gfx/screenshot.h"
#include "gfx/gfxPrimitiveBuffer.h"
#include "gfx/gfxCardProfile.h"
#include "gfx/gfxTextureManager.h"
#include "gfx/bitmap/gBitmap.h"
#include "core/util/safeDelete.h"
#include "windowManager/win32/win32Window.h"

#include <bgfx.h>
#include <bgfxplatform.h>

GFXBGFXVertexBuffer::GFXBGFXVertexBuffer( GFXDevice *device, U32 numVerts, const GFXVertexFormat *vertexFormat, U32 vertexSize, GFXBufferType bufferType ) :
      GFXVertexBuffer(device, numVerts, vertexFormat, vertexSize, bufferType) 
{ 
   // Constructor.
   tempBuf = NULL;
   vb.idx = bgfx::invalidHandle;
   dynamicVB.idx = bgfx::invalidHandle;
}

GFXBGFXVertexBuffer::~GFXBGFXVertexBuffer()
{
   delete[] tempBuf;
   if ( vb.idx != bgfx::invalidHandle )
      bgfx::destroyVertexBuffer(vb);
   if ( dynamicVB.idx != bgfx::invalidHandle )
      bgfx::destroyDynamicVertexBuffer(dynamicVB);
}

void GFXBGFXVertexBuffer::lock(U32 vertexStart, U32 vertexEnd, void **vertexPtr) 
{
   GFXBGFXDevice::BGFXVertexDecl* decl = static_cast<GFXBGFXDevice::BGFXVertexDecl*>(mVertexFormat.getDecl());
   delete[] tempBuf;

   lockedVertexStart = vertexStart;
   lockedVertexEnd   = vertexEnd;

   // Volatile : we use transient. don't need to worry about disposing them, it does that for us.
   if ( mBufferType == GFXBufferTypeVolatile )
   {
      if ( bgfx::checkAvailTransientVertexBuffer((lockedVertexEnd - lockedVertexStart), *decl->decl) )
      {
         bgfx::allocTransientVertexBuffer(&transientVB, (lockedVertexEnd - lockedVertexStart), *decl->decl);
         *vertexPtr = (void*) transientVB.data;
         return;
      } else {
         // We've got nothing else to give it.
         Con::printf("[BGFX] Ran out of transient vertex buffers.");
         tempBuf = new U8[(vertexEnd - vertexStart) * mVertexSize];
         *vertexPtr = (void*) tempBuf;
      }
      return;
   }

   // Used for everything but volatile.
   tempBuf = new U8[(vertexEnd - vertexStart) * mVertexSize];
   *vertexPtr = (void*) tempBuf;

   // Dynamic.
   if ( mBufferType == GFXBufferTypeDynamic && dynamicVB.idx == bgfx::invalidHandle )
   {
      dynamicVB = bgfx::createDynamicVertexBuffer((vertexEnd - vertexStart), *decl->decl);
   }
}

void GFXBGFXVertexBuffer::unlock() 
{
   GFXBGFXDevice::BGFXVertexDecl* decl = static_cast<GFXBGFXDevice::BGFXVertexDecl*>(mVertexFormat.getDecl());

   // Static should only be created once, but if someone invokes this it will work.
   if ( mBufferType == GFXBufferTypeStatic )
   {
      vb = bgfx::createVertexBuffer(
		  bgfx::makeRef(tempBuf, (lockedVertexEnd - lockedVertexStart) * mVertexSize ), 
        *decl->decl
		);
   }

   // Dynamic type uses update function.
   if ( mBufferType == GFXBufferTypeDynamic && dynamicVB.idx != bgfx::invalidHandle )
   {
      bgfx::updateDynamicVertexBuffer(dynamicVB, bgfx::makeRef(tempBuf, (lockedVertexEnd - lockedVertexStart) * mVertexSize ));
   }
}

void GFXBGFXVertexBuffer::prepare() 
{
   if ( mBufferType == GFXBufferTypeStatic && vb.idx != bgfx::invalidHandle )
   {
      bgfx::setVertexBuffer(vb, lockedVertexStart, lockedVertexEnd - lockedVertexStart );
   }

   if ( mBufferType == GFXBufferTypeDynamic && dynamicVB.idx != bgfx::invalidHandle )
   {
      bgfx::setVertexBuffer(dynamicVB, lockedVertexEnd - lockedVertexStart);
   }

   if ( mBufferType == GFXBufferTypeVolatile )
   {
      bgfx::setVertexBuffer(&transientVB, lockedVertexStart, lockedVertexEnd - lockedVertexStart);
   }
}

void GFXBGFXVertexBuffer::setActive(U32 vertexStart, U32 count)
{
   U32 vertCount = count;
   if ( vertCount > 0 )
   {
      Con::printf("VERT COUNT: %d", vertCount);
   }
   if ( vertCount < 1 ) vertCount = lockedVertexEnd - lockedVertexStart;

   if ( mBufferType == GFXBufferTypeStatic && vb.idx != bgfx::invalidHandle )
      bgfx::setVertexBuffer(vb, vertexStart, vertCount);

   if ( mBufferType == GFXBufferTypeDynamic && dynamicVB.idx != bgfx::invalidHandle )
      bgfx::setVertexBuffer(dynamicVB, vertCount);

   if ( mBufferType == GFXBufferTypeVolatile )
      bgfx::setVertexBuffer(&transientVB, vertexStart, vertCount);
}