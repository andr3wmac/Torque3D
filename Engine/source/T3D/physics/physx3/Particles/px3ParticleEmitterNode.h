//-----------------------------------------------------------------------------
// Authors: 
//      Andrew MacIntyre - Aldyre Studios - aldyre.com
//      Lukas Joergensen - WinterLeaf Entertainment - winterleafentertainment.com
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

#ifndef _PX3PARTICLE_EMITTER_NODE_H_
#define _PX3PARTICLE_EMITTER_NODE_H_

#ifndef _GAMEBASE_H_
#include "T3D/gameBase/gameBase.h"
#endif
#ifndef _PARTICLEEMITTERDUMMY_H_
#include "T3D/fx/particleEmitterNode.h"
#endif
#ifndef _PX3PARTICLE_EMITTER_H_
#include "T3D/physics/physx3/Particles/px3ParticleEmitter.h"
#endif

//*****************************************************************************
// ParticleEmitterNode
//*****************************************************************************
class Px3ParticleEmitterNode : public ParticleEmitterNode
{
   typedef ParticleEmitterNode Parent;

public:
   Px3ParticleEmitterNode();
   ~Px3ParticleEmitterNode();

   static void initPersistFields();

   DECLARE_CONOBJECT(Px3ParticleEmitterNode);

   virtual void setEmitterDataBlock(ParticleEmitterData* data);

   bool onAdd() { return Parent::onAdd(); };
   void onRemove() { Parent::onRemove(); };
   U32  packUpdate(NetConnection *conn, U32 mask, BitStream* stream) { return Parent::packUpdate(conn, mask, stream); };
   void unpackUpdate(NetConnection *conn, BitStream* stream) { Parent::unpackUpdate(conn, stream); };

   void advanceTime(F32 dt);
   void processTick(const Move* move);

   U32 mNodeTick;
   U32 timeSinceTick;
};

#endif //_PX3PARTICLE_EMITTER_NODE_H_
