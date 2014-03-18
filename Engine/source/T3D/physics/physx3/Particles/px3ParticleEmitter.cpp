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

IMPLEMENT_CONOBJECT( Px3ParticleEmitter );

ConsoleDocClass( Px3ParticleEmitter,
   
    "@brief Emitter for PhysX Particles\n\n"   
    "@ingroup Physics"
);

Px3ParticleEmitter::Px3ParticleEmitter()
  : mMatInst( NULL )
{
    mParticleSystem = NULL;

    //mNetFlags.set( Ghostable | ScopeAlways );
    //mTypeMask |= StaticObjectType | StaticShapeObjectType;

    emitterTick = 0;
    emitterRemoveTick = 0;
    timeSinceTick = 0;
}

Px3ParticleEmitter::~Px3ParticleEmitter()
{
}

bool Px3ParticleEmitter::onAdd()
{
    if ( !GameBase::onAdd() )
        return false;

    // On the server we use the static update
    // to setup the bounds of the cloth.
    if ( isServerObject() )
        _updateStaticSystem();

    addToScene();
   
    // Also the server object never ticks.
    if ( isServerObject() )
        setProcessTick( false );

    return true;
}

void Px3ParticleEmitter::onRemove()
{   
    SAFE_DELETE( mMatInst );
    if ( isClientObject() )
    {
        if ( mParticleSystem != NULL )
		    mParticleSystem->release();

        PhysicsPlugin::getPhysicsResetSignal().remove( this, &Px3ParticleEmitter::onPhysicsReset );
    }

    removeFromScene();
    Parent::onRemove();
}

void Px3ParticleEmitter::onPhysicsReset( PhysicsResetEvent reset )
{
    // Store the reset transform for later use.
    if ( reset == PhysicsResetEvent_Store )
        mResetXfm = getTransform();

    // Recreate the cloth at the last reset position.
    _recreateSystem( mResetXfm );
}

void Px3ParticleEmitter::initPersistFields()
{
    Parent::initPersistFields();

    addField( "material", TypeMaterialName, Offset( mMaterialName, Px3ParticleEmitter ),
        "@brief Name of the material to render.\n\n" );

   // Cloth doesn't support scale.
   removeField( "scale" );
}

void Px3ParticleEmitter::inspectPostApply()
{
   Parent::inspectPostApply();
   //
   // if ( isServerObject() )
   //    _updateStaticSystem();

   setMaskBits( TransformMask | MaterialMask | ClothMask );
}

U32 Px3ParticleEmitter::packUpdate( NetConnection *conn, U32 mask, BitStream *stream )
{
   U32 retMask = Parent::packUpdate( conn, mask, stream );

   if ( stream->writeFlag( mask & TransformMask ) )
      mathWrite( *stream, getTransform() );

   if ( stream->writeFlag( mask & MaterialMask ) )
      stream->write( mMaterialName );

   if ( stream->writeFlag( mask & ClothMask ) )
   {
        //stream->writeFlag( mCollisionEnabled );
        //stream->writeFlag( mWindEnabled );
   }

   return retMask;
}

void Px3ParticleEmitter::unpackUpdate( NetConnection *conn, BitStream *stream )
{
    Parent::unpackUpdate( conn, stream );

    // TransformMask
    if ( stream->readFlag() )
    {
        MatrixF mat;
        mathRead( *stream, &mat );
        setTransform( mat );
    }

    // MaterialMask
    if ( stream->readFlag() )
    {
        stream->read( &mMaterialName );
        SAFE_DELETE( mMatInst );
    }

    // ParticleMask
    if ( stream->readFlag() )
    {
        // mCollisionEnabled = stream->readFlag();
        // mWindEnabled = stream->readFlag();

        if (  isClientObject() && isProperlyAdded() && !mParticleSystem )
        {
            //_createSystem();
        }

        _updateProperties();
    }
}

void Px3ParticleEmitter::_recreateSystem( const MatrixF &transform )
{
    if ( !mParticleSystem )
    {
        _updateStaticSystem();
        return;
    }

    Parent::setTransform( transform );
}

void Px3ParticleEmitter::setTransform( const MatrixF &mat )
{
    Parent::setTransform( mat );
    setMaskBits( TransformMask );

    // Only need to do this if we're on the server
    // or if we're not currently ticking physics.
    if ( !mParticleSystem )
        _updateStaticSystem();
}

void Px3ParticleEmitter::setScale( const VectorF &scale )
{
    // Cloth doesn't support scale as it has plenty
    // of complications... sharing meshes, thickness,
    // transform origin, etc.
    return;
}

void Px3ParticleEmitter::prepRenderImage( SceneRenderState *state )
{  
    Parent::prepRenderImage(state);
}

void Px3ParticleEmitter::_updateProperties()
{
    if ( !mParticleSystem )
        return;
}

void Px3ParticleEmitter::_initMaterial()
{
    SAFE_DELETE( mMatInst );

    Material *material = NULL;
    if (mMaterialName.isNotEmpty() )
        Sim::findObject( mMaterialName, material );

    if ( material )
        mMatInst = material->createMatInstance();
    else
        mMatInst = MATMGR->createMatInstance( "WarningMaterial" );

    GFXStateBlockDesc desc;
    desc.setCullMode( GFXCullNone );
    mMatInst->addStateBlockDesc( desc );

    mMatInst->init( MATMGR->getDefaultFeatures(), getGFXVertexFormat<GFXVertexPNTT>() );
}

void Px3ParticleEmitter::_updateVBIB()
{
    if ( !mParticleSystem )
        return;

    // Not used at the moment.
}

void Px3ParticleEmitter::_updateStaticSystem()
{
    mObjBox.set( 0, 5, 0, 5, 5, 5 );
    resetWorldBox();
}

void Px3ParticleEmitter::addParticle(const Point3F &pos, const Point3F &axis, const Point3F &vel, const Point3F &axisx)
{
    Point3F ejectionAxis = axis;
    F32 theta = (mDataBlock->thetaMax - mDataBlock->thetaMin) * gRandGen.randF() +
        mDataBlock->thetaMin;

    F32 ref = (F32(mInternalClock) / 1000.0) * mDataBlock->phiReferenceVel;
    F32 phi = ref + gRandGen.randF() * mDataBlock->phiVariance;

    // Both phi and theta are in degs.  Create axis angles out of them, and create the
    //  appropriate rotation matrix...
    AngAxisF thetaRot(axisx, theta * (M_PI / 180.0));
    AngAxisF phiRot(axis, phi   * (M_PI / 180.0));

    MatrixF temp(true);
    thetaRot.setMatrix(&temp);
    temp.mulP(ejectionAxis);
    phiRot.setMatrix(&temp);
    temp.mulP(ejectionAxis);

    F32 initialVel = mDataBlock->ejectionVelocity;
    initialVel += (mDataBlock->velocityVariance * 2.0f * gRandGen.randF()) - mDataBlock->velocityVariance;

    Point3F newPos = pos + (ejectionAxis * (mDataBlock->ejectionOffset + mDataBlock->ejectionOffsetVariance* gRandGen.randF()));
    Point3F newVel = ejectionAxis * initialVel;
    U32 index;

    // Attempt to create particle. If this fuction returns false there isn't
    // enough room for another particle. Exit.
    bool particleWereAdded = mParticleSystem->addParticle(newPos, newVel, index);
    if (!particleWereAdded)
        return;

    n_parts++;
    if (n_parts > n_part_capacity || n_parts > mDataBlock->partListInitSize)
    {
        // In an emergency we allocate additional particles in blocks of 16.
        // This should happen rarely.
        Particle* store_block = new Particle[16];
        part_store.push_back(store_block);
        n_part_capacity += 16;
        for (S32 i = 0; i < 16; i++)
        {
            store_block[i].next = part_freelist;
            part_freelist = &store_block[i];
        }
        mDataBlock->allocPrimBuffer(n_part_capacity); // allocate larger primitive buffer or will crash 
    }

    // Add to particle linked list.
    Particle* pNew = part_freelist;
    part_freelist = pNew->next;
    pNew->next = part_list_head.next;
    part_list_head.next = pNew;

    // 
    pNew->pos = newPos;
    pNew->vel = newVel;
    pNew->orientDir = ejectionAxis;
    pNew->acc.set(0, 0, 0);
    pNew->currentAge = 0;

    // Choose a new particle datablack randomly from the list
    U32 dBlockIndex = gRandGen.randI() % mDataBlock->particleDataBlocks.size();
    mDataBlock->particleDataBlocks[dBlockIndex]->initializeParticle(pNew, vel);
    updateKeyData(pNew);
    if (index <= 0)
        return;

    mParticleIndexTable.insertUnique(pNew, index);
}

void Px3ParticleEmitter::processTick( const Move *move )
{
    // Make sure particle system exists
    if ( !mParticleSystem )
        return;

	// These are temp arbitrary values.
	mObjBox.set( 0, 5, 0, 5, 5, 5 );
    resetWorldBox();

    // Read back the data from the particles.
    S32 particleCount = mParticleSystem->getParticleCount();
    if (mParticleSystem->lock())
    {
        Vector<Point3F> positions = mParticleSystem->readParticles();
        if (positions.size() > 0)
        {
            int index = particleCount - 1;
            for (Particle* part = part_list_head.next; part != NULL; part = part->next)
            {
                // Update particle position if we're still here.
                if ( index < positions.size() && index >= 0 )
				    part->pos = positions[index];

                index--;
            }
        }
        mParticleSystem->unlock();
    }

    // Remove expired particles.
    int index = particleCount - 1;
    Particle* last_part = &part_list_head;
    for (Particle* part = part_list_head.next; part != NULL; part = part->next)
    {
        if ( index < 0 ) break;

        part->currentAge += timeSinceTick;
        if (part->currentAge > part->totalLifetime)
        {
            // Delete particle from PhysX.
            mParticleSystem->removeParticle(index);

            // Delete particle from Torque.
            n_parts--;
            last_part->next = part->next;
            part->next = part_freelist;
            part_freelist = part;
            part = last_part;
        } else {
            // only decrease index if we didn't delete a particle.
            last_part = part;
            index--;
        }
    }

   if (timeSinceTick != 0 && n_parts > 0)
   {
      update(timeSinceTick);
   }
   timeSinceTick = 0;
}

void Px3ParticleEmitter::interpolateTick( F32 delta )
{
   // Nothing to do for now!
}

bool Px3ParticleEmitter::onNewDataBlock( GameBaseData *dptr, bool reload )
{
	if(!Parent::onNewDataBlock(dptr, reload))
		return false;
	
   // ParticleSystem is only created on the client.
   if ( isClientObject() )
   {
      mResetXfm = getTransform();
      PhysicsPlugin::getPhysicsResetSignal().notify( this, &Px3ParticleEmitter::onPhysicsReset, 1053.0f );

	  mParticleSystem = new Px3ParticleSystem();
     //U32 ParticlesPerSecond = 1000 / (mDataBlock->ejectionPeriodMS - mDataBlock->periodVarianceMS);
     //F32 MaxParticleLifetimeInSeconds = (mDataBlock->particleDataBlocks[0]->lifetimeMS + mDataBlock->particleDataBlocks[0]->lifetimeVarianceMS) / 1000;
     mParticleSystem->create(250);
   }
   return true;
}

//-----------------------------------------------------------------------------
// advanceTime
//-----------------------------------------------------------------------------
void Px3ParticleEmitter::advanceTime(F32 dt)
{
   if (dt < 0.00001) return;

   GameBase::advanceTime(dt);

   // Make sure particle system exists
   if (!mParticleSystem)
   {
      if (mDeleteWhenEmpty)
         mDeleteOnTick = true;
      return;
   }

   if (dt > 0.5) dt = 0.5;

   if (mDead) return;

   mElapsedTimeMS += (S32)(dt * 1000.0f);

   U32 numMSToUpdate = (U32)(dt * 1000.0f);
   if (numMSToUpdate == 0) return;

   timeSinceTick += numMSToUpdate;

   // TODO: Prefetch
   AssertFatal(n_parts >= 0, "ParticleEmitter: negative part count!");

   if (n_parts < 1 && mDeleteWhenEmpty)
   {
      mDeleteOnTick = true;
      return;
   }
}

//-----------------------------------------------------------------------------
// Update particles
//-----------------------------------------------------------------------------
void Px3ParticleEmitter::update(U32 ms)
{
   for (Particle* part = part_list_head.next; part != NULL; part = part->next)
      updateKeyData(part);
}