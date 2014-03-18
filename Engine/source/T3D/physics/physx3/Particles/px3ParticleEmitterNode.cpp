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

#include "platform/platform.h"
#include "T3D/physics/physx3/Particles/px3ParticleEmitter.h"
#include "T3D/physics/physx3/Particles/px3ParticleEmitterNode.h"

IMPLEMENT_CO_NETOBJECT_V1(Px3ParticleEmitterNode);

//-----------------------------------------------------------------------------
// ParticleEmitterNode
//-----------------------------------------------------------------------------
Px3ParticleEmitterNode::Px3ParticleEmitterNode()
{
   // Todo: ScopeAlways?
   mNetFlags.set(Ghostable);
   mTypeMask |= EnvironmentObjectType;

   mNodeTick = 0;
   timeSinceTick = 0;
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
Px3ParticleEmitterNode::~Px3ParticleEmitterNode()
{
   //
}

void Px3ParticleEmitterNode::initPersistFields()
{
   Parent::initPersistFields();
}

void Px3ParticleEmitterNode::setEmitterDataBlock(ParticleEmitterData* data)
{
   if (isServerObject())
   {
      setMaskBits(EmitterDBMask);
   }
   else
   {
      Px3ParticleEmitter* pEmitter = NULL;
      if (data)
      {
         // Create emitter with new datablock
         pEmitter = new Px3ParticleEmitter;
         pEmitter->onNewDataBlock(data, false);
         if (pEmitter->registerObject() == false)
         {
            Con::warnf(ConsoleLogEntry::General, "Could not register base emitter for particle of class: %s", data->getName() ? data->getName() : data->getIdString());
            delete pEmitter;
            return;
         }
      }

      // Replace emitter
      if (mEmitter)
         mEmitter->deleteWhenEmpty();

      mEmitter = pEmitter;
   }

   mEmitterDatablock = data;
}

void Px3ParticleEmitterNode::processTick(const Move* move)
{
   Parent::processTick(move);

   if (!mActive || mEmitter.isNull() || !mDataBlock)
      return;
   Point3F emitPoint, emitVelocity;
   Point3F emitAxis(0, 0, 1);
   getTransform().mulV(emitAxis);
   getTransform().getColumn(3, &emitPoint);
   emitVelocity = emitAxis * mVelocity;

   mEmitter->emitParticles(emitPoint, emitPoint,
      emitAxis,
      emitVelocity, (U32)(timeSinceTick * mDataBlock->timeMultiple));
   timeSinceTick = 0;
}

void Px3ParticleEmitterNode::advanceTime(F32 dt)
{
   GameBase::advanceTime(dt);

   U32 numMSToUpdate = (U32)(dt * 1000.0f);
   if (numMSToUpdate == 0) return;

   timeSinceTick += numMSToUpdate;
}