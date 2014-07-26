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

#ifndef _PX3PARTICLE_EMITTER_H
#define _PX3PARTICLE_EMITTER_H

#ifndef _PHYSX3_H_
#include "T3D/physics/physx3/px3.h"
#endif
#ifndef _PX3PARTICLE_SYSTEM_H_
#include "T3D/physics/physx3/Particles/px3ParticleSystem.h"
#endif
#ifndef _T3D_PHYSICSCOMMON_H_
#include "T3D/physics/physicsCommon.h"
#endif
#ifndef _GAMEBASE_H_
#include "T3D/gameBase/gameBase.h"
#endif
#ifndef _GFXPRIMITIVEBUFFER_H_
#include "gfx/gfxPrimitiveBuffer.h"
#endif
#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif
#ifndef _H_PARTICLE_EMITTER
#include "T3D/fx/ParticleEmitter.h"
#endif
#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif

class Material;
class BaseMatInstance;
class Px3World;

class Px3ParticleEmitter : public ParticleEmitter
{
   typedef ParticleEmitter Parent;

   enum MaskBits 
   {
      TransformMask  = Parent::NextFreeMask << 0,
      ClothMask      = Parent::NextFreeMask << 1,
      MaterialMask   = Parent::NextFreeMask << 3,
      NextFreeMask   = Parent::NextFreeMask << 4
   };  

public:

   Px3ParticleEmitter();
   virtual ~Px3ParticleEmitter();

   DECLARE_CONOBJECT( Px3ParticleEmitter );      

   // SimObject
   virtual bool onAdd();
   virtual void onRemove();
   static void initPersistFields();
   virtual void inspectPostApply();
   void onPhysicsReset( PhysicsResetEvent reset );

   // NetObject
   virtual U32 packUpdate( NetConnection *conn, U32 mask, BitStream *stream );
   virtual void unpackUpdate( NetConnection *conn, BitStream *stream );

   // SceneObject
   virtual void setTransform( const MatrixF &mat );
   virtual void setScale( const VectorF &scale );
   virtual void prepRenderImage( SceneRenderState *state );

   // GameBase
   virtual bool onNewDataBlock( GameBaseData *dptr, bool reload );
   virtual void processTick( const Move *move );
   virtual void interpolateTick(F32 delta);
   virtual void advanceTime(F32 dt);
   virtual void update(U32 ms);

   // ParticleEmitter
   virtual void addParticle(const Point3F &pos, const Point3F &axis, const Point3F &vel, const Point3F &axisx);

protected:
   Px3ParticleSystem* mParticleSystem;

   U32 emitterTick;
   U32 emitterRemoveTick;
   U32 timeSinceTick;

   String mMaterialName;
   SimObjectPtr<Material> mMaterial;
   BaseMatInstance *mMatInst;
   MatrixF mResetXfm;

   void _initMaterial();
   void _recreateSystem( const MatrixF &transform );
   void _updateProperties();
   void _updateStaticSystem();
   void _updateVBIB();

    HashTable<Particle*, int> mParticleIndexTable;
};

#endif // _PX3PARTICLE_EMITTER_H_
