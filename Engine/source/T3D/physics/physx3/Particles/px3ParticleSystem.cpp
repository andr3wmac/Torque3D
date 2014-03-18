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
#include "T3D/physics/physx3/Particles/px3ParticleSystem.h"
#include "T3D/physics/physx3/px3.h"
#include "T3D/physics/physx3/px3World.h"
#include "T3D/physics/physx3/px3Plugin.h"
#include "T3D/physics/physx3/px3Cast.h"
#include "T3D/physics/physx3/px3Stream.h"

#include "console/consoleTypes.h"
#include "scene/sceneManager.h"
#include "scene/sceneRenderState.h"
#include "renderInstance/renderPassManager.h"
#include "lighting/lightQuery.h"
#include "gfx/gfxDrawUtil.h"
#include "math/mathIO.h"
#include "core/stream/bitStream.h"
#include "materials/materialManager.h"
#include "materials/baseMatInstance.h"
#include "T3D/fx/particleEmitter.h"


Px3ParticleSystem::Px3ParticleSystem()
  : mWorld( NULL ),
    mScene( NULL )
{
   mParticleSystem = NULL;
	mNumParticles = 0;
	mMaxParticles = 0;
	mIndexPool = NULL;
	mCurrentIndex = 0;
}

Px3ParticleSystem::~Px3ParticleSystem()
{
	_releaseSystem();
}

bool Px3ParticleSystem::_createSystem()
{
   mWorld->releaseWriteLock();

	// Clear old data.
   _releaseSystem();

	// Attempt to create particle system.
	physx::PxParticleSystem* system = gPhysics3SDK->createParticleSystem(mMaxParticles);
   //enable GPU acceleration if supported
   system->setParticleBaseFlag(physx::PxParticleBaseFlag::eGPU,mWorld->isGpuSupported());
   if ( system )
   {
      // Add the system to the PhysX scene.
      mScene->addActor(*system);
      mParticleSystem = system;

		// Set properties.
      _updateProperties();
      return true;
    }
    return false;
}

void Px3ParticleSystem::_releaseSystem()
{
	if ( !mParticleSystem )    
		return;

	// Clear our particle information.
	mPosition.clear();
	mVelocity.clear();
	mIndex.clear();
	mUniqueIndex.clear();
	mNumParticles = 0;

	// Clear Index Pool
	if ( mIndexPool )
	{
		mIndexPool->release();
		mIndexPool = NULL;
	}

	// Release Particle System
	mParticleSystem->releaseParticles();
	mScene->removeActor( *mParticleSystem );
	mParticleSystem->release();
	mParticleSystem = NULL;
}

void Px3ParticleSystem::_updateProperties()
{
   if ( !mParticleSystem )
        return;

	// These are just temporary values,
	// will expose later.
	mParticleSystem->setGridSize(3.0f);
	mParticleSystem->setMaxMotionDistance(0.8f);
	mParticleSystem->setRestOffset(0.0143f);
	mParticleSystem->setContactOffset(0.0143f * 2);
	mParticleSystem->setDamping(0.0f);
	mParticleSystem->setRestitution(0.2f);
	mParticleSystem->setDynamicFriction(0.01f);
}

// Public Functions
bool Px3ParticleSystem::create(U32 maxParticles)
{
	mWorld = dynamic_cast<Px3World*>( PHYSICSMGR->getWorld( "client" ) );
   if ( !mWorld || !mWorld->getScene() )
   {
      Con::errorf( "[Px3ParticleSystem] Could not start. PhysX world not initialized." );
      return false;
   }
   mScene = mWorld->getScene();
	mIndexPool = physx::PxParticleExt::createIndexPool(maxParticles);

	_releaseSystem();
	mMaxParticles = maxParticles;
	return _createSystem();
}

void Px3ParticleSystem::release()
{
   _releaseSystem();
}

bool Px3ParticleSystem::addParticle(Point3F position, Point3F velocity)
{
   U32 dummy;
   return addParticle(position, velocity, dummy);
}

bool Px3ParticleSystem::addParticle(Point3F position, Point3F velocity, U32& uniqueIndex)
{
   Vector<Point3F> vel;
   vel.push_back(velocity);
   Vector<Point3F> pos;
   pos.push_back(position);
   Vector<U32> uniqueIndices = addParticles(pos, vel);
   if (uniqueIndices.size() > 0)
   {
      uniqueIndex = uniqueIndices[0];
      return true;
   }
   return false;
}


Vector<U32> Px3ParticleSystem::addParticles(Vector<Point3F> position, Vector<Point3F> velocity)
{
	if ( mNumParticles == mMaxParticles )
	{
		Con::errorf("[Px3ParticleSystem] Maximum number of particles reached.");
		return 0;
	}

	Vector<physx::PxU32> indexList;
	Vector<U32> uniqueIndexList;
	Vector<physx::PxVec3> posList;
	Vector<physx::PxVec3> velList;

	// See how many particles we can create.
	U32 count = position.size();
	indexList.setSize(count);
	count = mIndexPool->allocateIndices(count, physx::PxStrideIterator<physx::PxU32>(&indexList[0]));
	indexList.setSize(count);
   if (count < 1)
      return 0;
	// Add as many as we can to the list. Hopefully all of them.
	for(int a = 0; a < count; a++)
	{
		posList.push_back(physx::PxVec3(position[a].x, position[a].y, position[a].z));
		velList.push_back(physx::PxVec3(velocity[a].x, velocity[a].y, velocity[a].z));
		uniqueIndexList.push_back(mCurrentIndex++);
	}

	// Setup creation data.
	physx::PxParticleCreationData particleCreationData;
	particleCreationData.numParticles = count;
	particleCreationData.positionBuffer = physx::PxStrideIterator<const physx::PxVec3>(&posList[0]);
	particleCreationData.velocityBuffer = physx::PxStrideIterator<const physx::PxVec3>(&velList[0]);
	particleCreationData.indexBuffer = physx::PxStrideIterator<const physx::PxU32>(&indexList[0]);

	// Attempt to create them all.
	if ( mParticleSystem->createParticles(particleCreationData) )
	{
		// If successfull, store data and return the amount.
		mIndex.merge(indexList);
		mPosition.merge(posList);
		mVelocity.merge(velList);
		mUniqueIndex.merge(uniqueIndexList);
		mNumParticles += count;
	}

	return uniqueIndexList;
}

U32 Px3ParticleSystem::getParticleCount()
{
	return mNumParticles;
}

U32 Px3ParticleSystem::getUniqueParticleIndex(U32 index)
{
	return mUniqueIndex[index];
}

U32 Px3ParticleSystem::getIndexFromUniqueIndex(U32 index)
{
	for (U32 i = 0; i < mUniqueIndex.size(); i++)
	   if (mUniqueIndex[i] == index)
		   return i;

	AssertWarn(false, "The requested index does not exist.");
	return 0;
}

bool Px3ParticleSystem::removeParticle(U32 index)
{
	return (removeParticles(index, 1) > 0);
}

U32 Px3ParticleSystem::removeParticles(U32 index, U32 count)
{
	if ( !mParticleSystem )
		return 0;

	// Ensure we aren't removing past what we have.
	if ( (index + count) > mNumParticles )
		count = mNumParticles - index;

   if ( count < 1 ) return 0;

	// Free their indicies.
	mIndexPool->freeIndices(count, physx::PxStrideIterator<const physx::PxU32>(&mIndex[index]));
	mParticleSystem->releaseParticles(count, physx::PxStrideIterator<const physx::PxU32>(&mIndex[index]));

	for ( U32 i = 0; i < count; i++ )
	{
		mPosition.erase(mPosition.begin() + index);
		mVelocity.erase(mVelocity.begin() + index);
		mIndex.erase(mIndex.begin() + index);
      mUniqueIndex.erase(mUniqueIndex.begin() + index);
	}
	mNumParticles -= count;
	return count;
}

void Px3ParticleSystem::applyForce(Point3F force)
{
	if ( mNumParticles < 1 )
		return;

	Vector<physx::PxVec3> forces;
	for(U32 i = 0; i < mNumParticles; i++)
		forces.push_back(physx::PxVec3(force.x, force.y, force.z));

	// Apply force to all particles in the system.
	mParticleSystem->addForces(mNumParticles, 
		physx::PxStrideIterator<const physx::PxU32>(&mIndex[0]), 
		physx::PxStrideIterator<const physx::PxVec3>(&forces[0]), 
		physx::PxForceMode::eFORCE);
}

bool Px3ParticleSystem::lock()
{
	if ( !mParticleSystem )
		return false;

	// System must be locked before it can be read.
	mParticleReadData = mParticleSystem->lockParticleReadData();
	if ( !mParticleReadData )
		return false;

	return true;
}

void Px3ParticleSystem::unlock()
{
	if ( !mParticleSystem && !mParticleReadData )
		return; 
	mParticleReadData->unlock();
}

Vector<Point3F> Px3ParticleSystem::readParticles()
{
   Vector<Point3F> results;

	if ( !mParticleSystem )
		return results;

	if ( !mParticleReadData )
		return results;

	// Read Flags + Positions from PhysX
	physx::PxStrideIterator<const physx::PxParticleFlags> flagsIt(mParticleReadData->flagsBuffer);
	physx::PxStrideIterator<const physx::PxVec3> positionIt(mParticleReadData->positionBuffer);

	for (unsigned i = 0; i < mParticleReadData->validParticleRange; ++i, ++flagsIt, ++positionIt)
	{
		// Checks to make sure the particle is valid.
		if (*flagsIt & physx::PxParticleFlag::eVALID)
		{
			const physx::PxVec3& position = *positionIt;
			results.push_back(Point3F(position.x, position.y, position.z));
		}

		// Should add more checks for flags here, could be used to trigger events
		// like onParticleCollision or something.
		/* 
			eCOLLISION_WITH_STATIC
				Marks a particle that has collided with a static actor shape.

			eCOLLISION_WITH_DYNAMIC
				Marks a particle that has collided with a dynamic actor shape.

			eCOLLISION_WITH_DRAIN
				Marks a particle that has collided with a shape that has been flagged as a drain
				Explanation:  Drains are objects that destroy particles when they touch them.

			eSPATIAL_DATA_STRUCTURE_OVERFLOW
				Marks a particle that had to be ignored for simulation ie outside of grid.
		*/
	}

	return results;
}