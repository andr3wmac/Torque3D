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
#include "gfx/BGFX/gfxBGFXPrimitiveBuffer.h"
#include "gfx/BGFX/gfxBGFXDevice.h"
#include "gfx/BGFX/gfxBGFXTextureManager.h"
#include "gfx/BGFX/gfxBGFXVertexBuffer.h"
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

GFXBGFXPrimitiveBuffer::GFXBGFXPrimitiveBuffer( GFXDevice *device, U32 indexCount, U32 primitiveCount, GFXBufferType bufferType )
   : GFXPrimitiveBuffer(device, indexCount, primitiveCount, bufferType), tempBuf( NULL )
{
   ib.idx = bgfx::invalidHandle;
   dynamicIB.idx = bgfx::invalidHandle;
}

GFXBGFXPrimitiveBuffer::~GFXBGFXPrimitiveBuffer()
{
   delete[] tempBuf;
   if ( ib.idx != bgfx::invalidHandle )
      bgfx::destroyIndexBuffer(ib);
   if ( dynamicIB.idx != bgfx::invalidHandle )
      bgfx::destroyDynamicIndexBuffer(dynamicIB);
}

void GFXBGFXPrimitiveBuffer::lock(U32 indexStart, U32 indexEnd, void **indexPtr)
{
   delete[] tempBuf;

   mLockedStart = indexStart;
   mLockedEnd   = indexEnd;

   // Volatile : we use transient. don't need to worry about disposing them, it does that for us.
   if ( mBufferType == GFXBufferTypeVolatile )
   {
      bgfx::allocTransientIndexBuffer(&transientIB, (indexEnd - indexStart) * sizeof(U16));
      *indexPtr = (void*) transientIB.data;
      return;
   }

   // Used for everything but volatile.
   tempBuf = new U16[(indexEnd - indexStart) * sizeof(U16)];
   *indexPtr = (void*) tempBuf;

   // Dynamic.
   if ( mBufferType == GFXBufferTypeDynamic && dynamicIB.idx == bgfx::invalidHandle )
   {
      dynamicIB = bgfx::createDynamicIndexBuffer(indexEnd - indexStart);
   }
}

void GFXBGFXPrimitiveBuffer::unlock() 
{
   // Static should only be created once, but if someone invokes this it will work.
   if ( mBufferType == GFXBufferTypeStatic )
   {
      ib = bgfx::createIndexBuffer( bgfx::makeRef(tempBuf, (mLockedEnd - mLockedStart) * sizeof(U16)) );
   }

   // Dynamic type uses update function.
   if ( mBufferType == GFXBufferTypeDynamic && dynamicIB.idx != bgfx::invalidHandle )
   {
      bgfx::updateDynamicIndexBuffer(dynamicIB, bgfx::makeRef(tempBuf, (mLockedEnd - mLockedStart) * sizeof(U16) ));
   }
}

void GFXBGFXPrimitiveBuffer::prepare()
{
	static_cast<GFXBGFXDevice *>( mDevice )->_setPrimitiveBuffer(this);
}

void GFXBGFXPrimitiveBuffer::setActive(U32 startVertex, 
                                       U32 minIndex, 
                                       U32 numVerts, 
                                       U32 startIndex, 
                                       U32 primitiveCount)
{
   if ( mBufferType == GFXBufferTypeStatic && ib.idx != bgfx::invalidHandle )
      bgfx::setIndexBuffer(ib);

   if ( mBufferType == GFXBufferTypeDynamic && dynamicIB.idx != bgfx::invalidHandle )
      bgfx::setIndexBuffer(dynamicIB);

   if ( mBufferType == GFXBufferTypeVolatile )
      bgfx::setIndexBuffer(&transientIB);
}