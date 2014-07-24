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

#ifndef _GFXD3D9STATEBLOCK_H_
#define _GFXD3D9STATEBLOCK_H_

#include "gfx/D3D9/gfxD3D9Device.h"
#include "gfx/gfxStateBlock.h"

class GFXD3D9StateBlock : public GFXStateBlock
{   
public:

   GFXD3D9StateBlock(const GFXStateBlockDesc& desc);
   virtual ~GFXD3D9StateBlock();

   /// Called by D3D9 device to active this state block.
   /// @param oldState  The current state, used to make sure we don't set redundant states on the device.  Pass NULL to reset all states.
   void activate(GFXD3D9StateBlock* oldState);


   // 
   // GFXStateBlock interface
   //

   /// Returns the hash value of the desc that created this block
   virtual U32 getHashValue() const;

   /// Returns a GFXStateBlockDesc that this block represents
   virtual const GFXStateBlockDesc& getDesc() const;

   //
   // GFXResource
   //
   virtual void zombify() { }
   /// When called the resource should restore all device sensitive information destroyed by zombify()
   virtual void resurrect() { }
private:
   GFXStateBlockDesc mDesc;
   U32 mCachedHashValue;
   U32 mColorMask; 
};

typedef StrongRefPtr<GFXD3D9StateBlock> GFXD3D9StateBlockRef;

#endif