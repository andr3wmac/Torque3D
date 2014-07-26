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

#ifndef _PX3PARTICLE_SYSTEM_H_
#define _PX3PARTICLE_SYSTEM_H_

#ifndef _PHYSX3_H_
#include "T3D/physics/physx3/px3.h"
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

class Material;
class BaseMatInstance;
class Px3World;

class Px3ParticleSystem
{

public:
   Px3ParticleSystem();
   virtual ~Px3ParticleSystem(); 

   bool create(U32 maxParticles);
   void release();

   bool addParticle(Point3F position, Point3F velocity);
   bool addParticle(Point3F position, Point3F velocity, U32& uniqueIndex);
   Vector<U32> addParticles(Vector<Point3F> position, Vector<Point3F> velocity);
   bool removeParticle(U32 index);
   U32 removeParticles(U32 index, U32 count);

   bool lock();
   void unlock();
   Vector<Point3F> readParticles();

   void applyForce(Point3F force);
   U32 getParticleCount();
   U32 getUniqueParticleIndex(U32 index);
   U32 getIndexFromUniqueIndex(U32 index);

protected:
   Px3World *mWorld;
   physx::PxScene *mScene;

   physx::PxParticleExt::IndexPool* mIndexPool;
   physx::PxParticleSystem* mParticleSystem;
   physx::PxParticleReadData* mParticleReadData;

   U32 mNumParticles;
   U32 mMaxParticles;

   Vector<physx::PxVec3> mPosition;
   Vector<physx::PxVec3> mVelocity;
   Vector<physx::PxU32> mIndex;
   Vector<U32> mUniqueIndex;

   MatrixF mResetXfm;
   void _releaseSystem();
   bool _createSystem();
   bool _createParticles();
   void _updateProperties();

   U32 mCurrentIndex;
};

#endif // _PX3PARTICLE_SYSTEM_H_
