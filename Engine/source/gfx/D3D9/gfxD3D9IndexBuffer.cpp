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

#include "gfx/D3D9/gfxD3D9Device.h"
#include "gfx/D3D9/gfxD3D9EnumTranslate.h"
#include "gfx/D3D9/gfxD3D9IndexBuffer.h"
#include "core/util/safeRelease.h"

void GFXD3D9PrimitiveBuffer::prepare()
{
	static_cast<GFXD3D9Device*>(GFX)->_setPrimitiveBuffer(this);
}

void GFXD3D9PrimitiveBuffer::lock(U32 indexStart, U32 indexEnd, void **indexPtr)
{
   AssertFatal(!mLocked, "GFXD3D9PrimitiveBuffer::lock - Can't lock a primitive buffer more than once!");

   mLocked = true;
   U32 flags=0;

   switch(mBufferType)
   {
   case GFXBufferTypeStatic:
   case GFXBufferTypeDynamic:
      flags |= D3DLOCK_DISCARD;
      break;

   case GFXBufferTypeVolatile:
      // Get our range now...
      AssertFatal(indexStart == 0,                "Cannot get a subrange on a volatile buffer.");
      AssertFatal(indexEnd < MAX_DYNAMIC_INDICES, "Cannot get more than MAX_DYNAMIC_INDICES in a volatile buffer. Up the constant!");

      // Get the primtive buffer
      mVolatileBuffer = static_cast<GFXD3D9Device*>(GFX)->mDynamicPB;

      AssertFatal( mVolatileBuffer, "GFXD3D9PrimitiveBuffer::lock - No dynamic primitive buffer was available!");

      // We created the pool when we requested this volatile buffer, so assume it exists...
      if(mVolatileBuffer->mIndexCount + indexEnd > MAX_DYNAMIC_INDICES) 
      {
         flags |= D3DLOCK_DISCARD;
         mVolatileStart = indexStart  = 0;
         indexEnd       = indexEnd;
      }
      else 
      {
         flags |= D3DLOCK_NOOVERWRITE;
         mVolatileStart = indexStart  = mVolatileBuffer->mIndexCount;
         indexEnd                    += mVolatileBuffer->mIndexCount;
      }

      mVolatileBuffer->mIndexCount = indexEnd + 1;
      ib = mVolatileBuffer->ib;

      break;
   }

    HRESULT hr = ib->Lock(indexStart * sizeof(U16), (indexEnd - indexStart) * sizeof(U16), indexPtr, flags);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D9PrimitiveBuffer::lock - Could not lock primitive buffer.");
	}

   #ifdef TORQUE_DEBUG
   
      // Allocate a debug buffer large enough for the lock
      // plus space for over and under run guard strings.
      mLockedSize = (indexEnd - indexStart) * sizeof(U16);
      const U32 guardSize = sizeof( _PBGuardString );
      mDebugGuardBuffer = new U8[mLockedSize+(guardSize*2)];

      // Setup the guard strings.
      dMemcpy( mDebugGuardBuffer, _PBGuardString, guardSize ); 
      dMemcpy( mDebugGuardBuffer + mLockedSize + guardSize, _PBGuardString, guardSize ); 

      // Store the real lock pointer and return our debug pointer.
      mLockedBuffer = *indexPtr;
      *indexPtr = (U16*)( mDebugGuardBuffer + guardSize );

   #endif // TORQUE_DEBUG
}

void GFXD3D9PrimitiveBuffer::unlock()
{
   #ifdef TORQUE_DEBUG
   
      if ( mDebugGuardBuffer )
      {
         const U32 guardSize = sizeof( _PBGuardString );

         // First check the guard areas for overwrites.
         AssertFatal( dMemcmp( mDebugGuardBuffer, _PBGuardString, guardSize ) == 0,
            "GFXD3D9PrimitiveBuffer::unlock - Caught lock memory underrun!" );
         AssertFatal( dMemcmp( mDebugGuardBuffer + mLockedSize + guardSize, _PBGuardString, guardSize ) == 0,
            "GFXD3D9PrimitiveBuffer::unlock - Caught lock memory overrun!" );

         // Copy the debug content down to the real PB.
         dMemcpy( mLockedBuffer, mDebugGuardBuffer + guardSize, mLockedSize );

         // Cleanup.
         delete [] mDebugGuardBuffer;
         mDebugGuardBuffer = NULL;
         mLockedBuffer = NULL;
         mLockedSize = 0;
      }

   #endif // TORQUE_DEBUG

   ib->Unlock();
   mLocked = false;
   mIsFirstLock = false;
   mVolatileBuffer = NULL;
}

GFXD3D9PrimitiveBuffer::~GFXD3D9PrimitiveBuffer() 
{
   if( mBufferType != GFXBufferTypeVolatile )
   {
      SAFE_RELEASE( ib );
   }
}

void GFXD3D9PrimitiveBuffer::zombify()
{
   if(mBufferType == GFXBufferTypeStatic)
      return;
            
   AssertFatal(!mLocked, "GFXD3D9PrimitiveBuffer::zombify - Cannot zombify a locked buffer!");

   if (mBufferType == GFXBufferTypeVolatile)
   {
      // We must null the volatile buffer else we're holding
      // a dead pointer which can be set on the device.      
      ib = NULL;
      return;
   }

   // Dynamic buffers get released.
   SAFE_RELEASE(ib);
}

void GFXD3D9PrimitiveBuffer::resurrect()
{
	if(mBufferType != GFXBufferTypeDynamic)
		return;
      
	U32 usage = D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC;

	HRESULT hr = (static_cast<GFXD3D9Device*>(GFX)->getDevice()->CreateIndexBuffer(sizeof(U16) * mIndexCount ,  usage, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ib, 0));

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D9PrimitiveBuffer::resurrect - Failed to allocate an index buffer.");
	}
}
