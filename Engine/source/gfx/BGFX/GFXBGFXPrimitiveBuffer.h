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

#ifndef _GFXBGFXPrimitiveBuffer_H_
#define _GFXBGFXPrimitiveBuffer_H_

#ifndef _GFXPRIMITIVEBUFFER_H_
#include "gfx/gfxPrimitiveBuffer.h"
#endif

#ifndef BGFX_H_HEADER_GUARD
#include <bgfx.h>
#endif

class GFXBGFXPrimitiveBuffer : public GFXPrimitiveBuffer
{
private:
   U16* tempBuf;
   U32 mLockedStart;
   U32 mLockedEnd;

   bgfx::IndexBufferHandle ib;
   bgfx::DynamicIndexBufferHandle dynamicIB;
   bgfx::TransientIndexBuffer transientIB;

public:
   GFXBGFXPrimitiveBuffer( GFXDevice *device, U32 indexCount, U32 primitiveCount, GFXBufferType bufferType );
   ~GFXBGFXPrimitiveBuffer();

   virtual void lock(U32 indexStart, U32 indexEnd, void **indexPtr); ///< locks this primitive buffer for writing into
   virtual void unlock(); ///< unlocks this primitive buffer.
   virtual void prepare();  ///< prepares this primitive buffer for use on the device it was allocated on

   virtual void zombify() {}
   virtual void resurrect() {}

   void setActive(U32 startVertex, U32 minIndex, U32 numVerts, U32 startIndex, U32 primitiveCount);
};

#endif