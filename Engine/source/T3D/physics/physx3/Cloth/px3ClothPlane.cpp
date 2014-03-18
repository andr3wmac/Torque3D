//-----------------------------------------------------------------------------
// Authors: 
//        Andrew MacIntyre - Aldyre Studios - aldyre.com
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
#include "T3D/physics/physx3/Cloth/px3ClothPlane.h"
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

IMPLEMENT_CO_NETOBJECT_V1( Px3ClothPlane );

ConsoleDocClass( Px3ClothPlane,
   
   "@brief Rectangular patch of cloth simulated by PhysX.\n\n"   
   "@ingroup Physics"
);

enum Px3ClothPlaneAttachment {};
DefineBitfieldType( Px3ClothPlaneAttachment );

ImplementBitfieldType( Px3ClothPlaneAttachment,
   "Soon to be deprecated\n"
   "@internal" )
   { 0, "Bottom Right" },
   { 1, "Bottom Left" },
   { 2, "Top Right" },
   { 3, "Top Left" },
   { 4, "Top Center" },
   { 5, "Bottom Center" },
   { 6, "Right Center" },
   { 7, "Left Center" },
   { 8, "Top Edge" },
   { 9, "Bottom Edge" },
   { 10, "Right Edge" },
   { 11, "Left Edge" }
EndImplementBitfieldType;


Px3ClothPlane::Px3ClothPlane()
  : mWorld( NULL ),
    mScene( NULL ),
    mMatInst( NULL )
{
   mVertexRenderBuffer = NULL; 
   mIndexRenderBuffer = NULL;

   mClothMesh = NULL;
   mCloth = NULL;
   mVertices.clear();
   mPrimitives.clear();

   mPatchVerts.set( 8, 8 );
   mPatchSize.set( 8.0f, 8.0f );

   mNetFlags.set( Ghostable | ScopeAlways );
   mTypeMask |= StaticObjectType | StaticShapeObjectType;

   mCollisionEnabled = false;
   mWindEnabled = false;
   mGpuEnabled = true;

   mThickness = 0.1f;
   mSolverFrequency = 120.0f;
   mDampingCoef = 0.0f;
   mStretchVertical = 1.0f;
   mStretchHorizontal = 0.9f;
   mStretchShearing = 0.75f;
   mStretchBending = 0.5f;

   mAttachmentMask = 0;
}

Px3ClothPlane::~Px3ClothPlane()
{
}

bool Px3ClothPlane::onAdd()
{
   if ( !Parent::onAdd() )
      return false;

   // Cloth is only created on the client.
   if ( isClientObject() )
   {
      mWorld = dynamic_cast<Px3World*>( PHYSICSMGR->getWorld( "client" ) );
      
      if ( !mWorld || !mWorld->getScene() )
      {
         Con::errorf( "Px3ClothPlane::onAdd() - PhysXWorld not initialized... cloth disabled!" );
         return true;
      }

      mScene = mWorld->getScene();

      mResetXfm = getTransform();

      _createClothPatch();      

      PhysicsPlugin::getPhysicsResetSignal().notify( this, &Px3ClothPlane::onPhysicsReset, 1053.0f );
   }

   // On the server we use the static update
   // to setup the bounds of the cloth.
   if ( isServerObject() )
      _updateStaticCloth();

   addToScene();
   
   // Also the server object never ticks.
   if ( isServerObject() )
      setProcessTick( false );

   return true;
}

void Px3ClothPlane::onRemove()
{   
   SAFE_DELETE( mMatInst );
   if ( isClientObject() )
   {
      _releaseMesh();
      _releaseCloth();
      SAFE_DELETE(mVertexRenderBuffer);
      SAFE_DELETE(mIndexRenderBuffer);
      PhysicsPlugin::getPhysicsResetSignal().remove( this, &Px3ClothPlane::onPhysicsReset );
   }
   removeFromScene();
   Parent::onRemove();
}

void Px3ClothPlane::onPhysicsReset( PhysicsResetEvent reset )
{
   // Store the reset transform for later use.
   if ( reset == PhysicsResetEvent_Store )
      mResetXfm = getTransform();

   // Recreate the cloth at the last reset position.
   _recreateCloth( mResetXfm );
}

void Px3ClothPlane::initPersistFields()
{
   Parent::initPersistFields();

   addField( "material", TypeMaterialName, Offset( mMaterialName, Px3ClothPlane ),
        "@brief Name of the material to render.\n\n" );

   addField( "size", TypePoint2F, Offset( mPatchSize, Px3ClothPlane ),
        "@brief The width and height of the cloth.\n\n" );

   addField( "attachments", TYPEID< Px3ClothPlaneAttachment >(), Offset( mAttachmentMask, Px3ClothPlane ),
      "@brief Optional way to specify cloth verts that will be attached to the world position "
      "it is created at.\n\n" );

   addGroup( "Simulation" );
      addField( "frequency", TypeF32, Offset( mSolverFrequency, Px3ClothPlane ),
         "@brief Iterations per second of cloth simulation.\n\n" );

      addField( "samples", TypePoint2I, Offset( mPatchVerts, Px3ClothPlane ),
         "@brief The number of cloth vertices in width and length.\n\n"
         "At least two verts should be defined.\n\n");
   endGroup( "Simulation" );

   addGroup( "Stretching" );
      addField( "damping_coef", TypeF32, Offset( mDampingCoef, Px3ClothPlane ),
         "@brief Value between 0 and 1\n\n" );
      addField( "stretch_vertical", TypeF32, Offset( mStretchVertical, Px3ClothPlane ),
         "@brief Value between 0 and 1\n\n" );
      addField( "stretch_horizontal", TypeF32, Offset( mStretchHorizontal, Px3ClothPlane ),
         "@brief Value between 0 and 1\n\n" );
      addField( "stretch_shearing", TypeF32, Offset( mStretchShearing, Px3ClothPlane ),
         "@brief Value between 0 and 1\n\n" );
      addField( "stretch_bending", TypeF32, Offset( mStretchBending, Px3ClothPlane ),
         "@brief Value between 0 and 1\n\n" );
   endGroup( "Stretching" );

   addField( "Collision", TypeBool, Offset( mCollisionEnabled, Px3ClothPlane ),
      "@brief Enables or disables collision with the rest of the world.\n\n" );

   addField( "Wind", TypeBool, Offset( mWindEnabled, Px3ClothPlane ),
      "@brief Enables or disables wind driven by forest wind emitter.\n\n" );

   addField( "Gpu", TypeBool, Offset( mGpuEnabled, Px3ClothPlane ),
      "@brief Enables or Disables GPU acceleration of the cloth.\n\n"
      "This feature only works with NVidia GPU's and on Windows Operating Systems.\n\n");

   // Cloth doesn't support scale.
   removeField( "scale" );
}

void Px3ClothPlane::inspectPostApply()
{
   Parent::inspectPostApply();

   // Must have at least 2 verts.
   mPatchVerts.x = getMax( 2, mPatchVerts.x );
   mPatchVerts.y = getMax( 2, mPatchVerts.y );
   if ( isServerObject() )
      _updateStaticCloth();

   setMaskBits( TransformMask | MaterialMask | ClothMask );
}

U32 Px3ClothPlane::packUpdate( NetConnection *conn, U32 mask, BitStream *stream )
{
   U32 retMask = Parent::packUpdate( conn, mask, stream );

   if ( stream->writeFlag( mask & TransformMask ) )
      mathWrite( *stream, getTransform() );

   if ( stream->writeFlag( mask & MaterialMask ) )
      stream->write( mMaterialName );

   if ( stream->writeFlag( mask & ClothMask ) )
   {
      mathWrite( *stream, mPatchVerts );
      mathWrite( *stream, mPatchSize );

      stream->write( mAttachmentMask );

      stream->writeFlag( mCollisionEnabled );
      stream->writeFlag( mWindEnabled );
      stream->writeFlag( mGpuEnabled );

      stream->write( mSolverFrequency );
      stream->write( mDampingCoef );
      stream->write( mStretchVertical );
      stream->write( mStretchHorizontal ); 
      stream->write( mStretchShearing );
      stream->write( mStretchBending );
   }

   return retMask;
}

void Px3ClothPlane::unpackUpdate( NetConnection *conn, BitStream *stream )
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

   // ClothMask
   if ( stream->readFlag() )
   {
      Point2I patchVerts;
      Point2F patchSize;
      mathRead( *stream, &patchVerts );
      mathRead( *stream, &patchSize );

   if (  patchVerts != mPatchVerts ||
         !patchSize.equal( mPatchSize ) )
   {
      mPatchVerts = patchVerts;
      mPatchSize = patchSize;
      _releaseMesh();
   }

   U32 attachMask;
   stream->read( &attachMask );
   if ( attachMask != mAttachmentMask )
   {
      mAttachmentMask = attachMask;
      _releaseCloth();
   }

   mCollisionEnabled = stream->readFlag();
   mWindEnabled = stream->readFlag();
   mGpuEnabled = stream->readFlag();

   stream->read( &mSolverFrequency );
   stream->read( &mDampingCoef );
   stream->read( &mStretchVertical );
   stream->read( &mStretchHorizontal ); 
   stream->read( &mStretchShearing );
   stream->read( &mStretchBending );

   if (  isClientObject() && 
      isProperlyAdded() &&
      mWorld && !mCloth )
   {
      _createClothPatch();
   }

   _updateClothProperties();
   }
}

void Px3ClothPlane::_recreateCloth( const MatrixF &transform )
{
   if ( !mWorld )
   {
      _updateStaticCloth();
      return;
   }

   mWorld->getPhysicsResults();
   Parent::setTransform( transform );

   _createClothPatch();
}

void Px3ClothPlane::setTransform( const MatrixF &mat )
{
   Parent::setTransform( mat );
   setMaskBits( TransformMask );

   // Only need to do this if we're on the server
   // or if we're not currently ticking physics.
   if ( !mWorld || !mWorld->isEnabled() )
      _updateStaticCloth();
}

void Px3ClothPlane::setScale( const VectorF &scale )
{
   // Cloth doesn't support scale as it has plenty
   // of complications... sharing meshes, thickness,
   // transform origin, etc.
   return;
}

void Px3ClothPlane::prepRenderImage( SceneRenderState *state )
{  
   if ( mIsVBDirty )
      _updateVBIB();

   // Recreate the material if we need to.
   if ( !mMatInst )
      _initMaterial();

   // If we don't have a material instance after the override then 
   // we can skip rendering all together.
   BaseMatInstance *matInst = state->getOverrideMaterial( mMatInst );
   if ( !matInst )
      return;

   MeshRenderInst *ri = state->getRenderPass()->allocInst<MeshRenderInst>();

    // If we need lights then set them up.
   if ( matInst->isForwardLit() )
   {
      LightQuery query;
      query.init( getWorldSphere() );
        query.getLights( ri->lights, 8 );
   }

   ri->projection = state->getRenderPass()->allocSharedXform(RenderPassManager::Projection);
   ri->objectToWorld = &MatrixF::Identity;

   ri->worldToCamera = state->getRenderPass()->allocSharedXform(RenderPassManager::View);   
   ri->type = RenderPassManager::RIT_Mesh;

   ri->primBuff = &mPrimBuffer;
   ri->vertBuff = &mVB;

   ri->matInst = matInst;
   ri->prim = state->getRenderPass()->allocPrim();
   ri->prim->type = GFXTriangleList;
   ri->prim->minIndex = 0;
   ri->prim->startIndex = 0;
   ri->prim->numPrimitives = mNumIndices / 3;

   ri->prim->startVertex = 0;
   ri->prim->numVertices = mNumVertices;

   ri->defaultKey = matInst->getStateHint();
   ri->defaultKey2 = (U32)ri->vertBuff;

   state->getRenderPass()->addInst( ri );
}

void Px3ClothPlane::_releaseMesh()
{
   if ( !mClothMesh )
      return;

   mClothMesh->release();
}

void Px3ClothPlane::_releaseCloth()
{
   if ( !mCloth )    
      return;

   mScene->removeActor( *mCloth );
   mCloth->release();
   mCloth = NULL;
}

void Px3ClothPlane::_initBuffers()
{
   // Allocate Render Buffer for Vertices if it hasn't been done before+
   int maxVertices = mNumVertices * 3;
   int maxIndicies = mNumIndices * 3;
   mVertexRenderBuffer = new GFXVertexPNTT[maxVertices];
   mIndexRenderBuffer = new U16[maxIndicies];

   // Set up texture coords.
   F32 dx = 1.0f / (F32)(mPatchVerts.x-1);
   F32 dy = 1.0f / (F32)(mPatchVerts.y-1);

   F32 *coord = (F32*)&mVertexRenderBuffer[0].texCoord;
   for ( U32 i = 0; i < mPatchVerts.y; i++) 
   {
      for ( U32 j = 0; j < mPatchVerts.x; j++) 
      {
         coord[0] = j*dx;
         coord[1] = i*-dy;
         coord += sizeof( GFXVertexPNTT ) / sizeof( F32 );
      }
   }

   mMeshDirtyFlags = 0;
}

void Px3ClothPlane::_generateVertices()
{
   // Must have at least 2 verts.
   mPatchVerts.x = getMax( 2, mPatchVerts.x );
   mPatchVerts.y = getMax( 2, mPatchVerts.y );

   // Generate a uniform cloth patch, 
   // w and h are the width and height, 
   // d is the distance between vertices.  
   mNumVertices = mPatchVerts.x * mPatchVerts.y;
   mNumIndices = (mPatchVerts.x-1) * (mPatchVerts.y-1) * 2;
   
   F32 patchWidth = mPatchSize.x / (F32)( mPatchVerts.x - 1 );
   F32 patchHeight = mPatchSize.y / (F32)( mPatchVerts.y - 1 );

   // Set up attachments
   // Bottom right = bit 0
   // Bottom left = bit 1
   // Top right = bit 2
   // Top left = bit 3
   bool bRight = mAttachmentMask & BIT( 0 );
   bool bLeft = mAttachmentMask & BIT( 1 );
   bool tRight = mAttachmentMask & BIT( 2 );
   bool tLeft =  mAttachmentMask & BIT( 3 );

   // Generate list of vertices
   mVertices.clear();
   for (U32 i = 0; i < mPatchVerts.y; i++) 
   {        
      for (U32 j = 0; j < mPatchVerts.x; j++) 
      {            
         // Attachments handled with inverse weighting.
         float weight = 0.8f;
         if ( i == 0 && j == 0 && bLeft )
            weight = 0.0f;
         if ( i == 0 && j == (mPatchVerts.x - 1) && bRight )
            weight = 0.0f;
         if ( i == (mPatchVerts.y - 1) && j == 0 && tLeft )
            weight = 0.0f;
         if ( i == (mPatchVerts.y - 1) && j == (mPatchVerts.x - 1) && tRight )
            weight = 0.0f;

         mVertices.push_back(PxClothParticle(PxVec3(patchWidth * j, 0.0f, patchHeight * i), weight));
      }    
   }

   int width = mPatchVerts.x;
   int height = mPatchVerts.y;

   // Generate list of primitives
   mNumPrimitives = 0;
   mPrimitives.clear();
   for (U32 y = 0; y < height - 1; y++)
   {
      for (U32 x = 0; x < width - 1; x++)
      {
         U32 x1 = x + (y * width);
         mPrimitives.push_back(x1);
         mPrimitives.push_back(x1 + 1);
         U32 y1 = x1 + width;
         mPrimitives.push_back(y1);
         mPrimitives.push_back(y1 + 1);
         mNumPrimitives++;
      }
   }

   _initBuffers();
}

bool Px3ClothPlane::_createClothPatch()
{
   // Make sure we can change the world.
   mWorld->releaseWriteLock();

   // Generate Vert/Prim data.
   _generateVertices();

   // Create Cloth Mesh Description.
   PxClothMeshDesc meshDesc;
   meshDesc.points.data = &mVertices[0];
   meshDesc.points.count = mNumVertices;
   meshDesc.points.stride = sizeof(PxClothParticle);

   meshDesc.invMasses.data = &mVertices[0].invWeight;
   meshDesc.invMasses.count = mNumVertices;
   meshDesc.invMasses.stride = sizeof(PxClothParticle);

   meshDesc.quads.data = &mPrimitives[0];
   meshDesc.quads.count = mNumPrimitives;
   meshDesc.quads.stride = sizeof(PxU32) * 4;
   PxClothFabric* clothFabric = PxClothFabricCreate(*gPhysics3SDK, meshDesc, PxVec3(0, 0, 0));

   // Apply transform
   PxTransform out;
   QuatF q;
   q.set(getTransform());
   out.q = px3Cast<PxQuat>(q);
   out.p = px3Cast<PxVec3>(getTransform().getPosition());

   // Delete old cloth, create new cloth.
   _releaseCloth();
   PxCloth* cloth = gPhysics3SDK->createCloth(out, *clothFabric, &mVertices[0], PxClothFlags());
   if ( cloth )
   {
      mScene->addActor(*cloth);
      mCloth = cloth;

      _updateClothProperties();
      mIsVBDirty = true;
   }
        
   _updateStaticCloth();
   return true;
}

void Px3ClothPlane::_updateClothProperties()
{
   if ( !mCloth )
      return;

   mCloth->setClothFlag(PxClothFlag::eSCENE_COLLISION, mCollisionEnabled);
   bool gpuSupport = (mGpuEnabled && mWorld->isGpuSupported()) ? true : false;
   mCloth->setClothFlag(PxClothFlag::eGPU, gpuSupport);
   mCloth->setSolverFrequency(mSolverFrequency);
   mCloth->setDampingCoefficient(PxVec3(mDampingCoef));

   // Stretch Config
   mCloth->setStretchConfig(PxClothFabricPhaseType::eVERTICAL, PxClothStretchConfig(mStretchVertical)); //1.0f
   mCloth->setStretchConfig(PxClothFabricPhaseType::eHORIZONTAL, PxClothStretchConfig(mStretchHorizontal)); //0.9f
   mCloth->setStretchConfig(PxClothFabricPhaseType::eSHEARING, PxClothStretchConfig(mStretchShearing)); // 0.75f
   mCloth->setStretchConfig(PxClothFabricPhaseType::eBENDING, PxClothStretchConfig(mStretchBending)); // 0.5f
}

void Px3ClothPlane::_initMaterial()
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

void Px3ClothPlane::_updateVBIB()
{
   if ( !mCloth )
      return;

   PROFILE_SCOPE( Px3ClothPlane_UpdateVBIB );

   mIsVBDirty = false;

   // Don't set the VB if the vertex count is the same!
   if ( mVB.isNull() || mVB->mNumVerts < mNumVertices )
      mVB.set( GFX, mNumVertices, GFXBufferTypeDynamic );

   GFXVertexPNTT *vpPtr = mVB.lock();
   dMemcpy( vpPtr, mVertexRenderBuffer, sizeof( GFXVertexPNTT ) * mNumVertices );
   mVB.unlock();

   if ( mPrimBuffer.isNull() || mPrimBuffer->mIndexCount < mNumIndices )
      mPrimBuffer.set( GFX, mNumIndices, 0, GFXBufferTypeDynamic );

   U16 *pbPtr;
   mPrimBuffer.lock( &pbPtr );
   dMemcpy( pbPtr, mIndexRenderBuffer, sizeof( U16 ) * mNumIndices );
   mPrimBuffer.unlock();
}

void Px3ClothPlane::_updateStaticCloth()
{
   // Setup the unsimulated world bounds.
   mObjBox.set(   0, mThickness * -0.5f, 0, 
               mPatchSize.x, mThickness * 0.5f, mPatchSize.y );
   resetWorldBox();

   // If we don't have render buffers then we're done.
   if ( !mVertexRenderBuffer || !mIndexRenderBuffer )
      return;

   // Make sure the VBs are updated.
   mIsVBDirty = true;

   F32 patchWidth = mPatchSize.x / (F32)(mPatchVerts.x-1);
   F32 patchHeight = mPatchSize.y / (F32)(mPatchVerts.y-1);

   Point3F normal( 0, 1, 0 );
   getTransform().mulV( normal );

   GFXVertexPNTT *vert = mVertexRenderBuffer;

   for (U32 y = 0; y < mPatchVerts.y; y++) 
   {        
      for (U32 x = 0; x < mPatchVerts.x; x++) 
      {            
         vert->point.set( patchWidth * x, 0.0f, patchHeight * y );
         getTransform().mulP( vert->point );
         vert->normal = normal;
         vert++;
      }
   }

   U16 *index = mIndexRenderBuffer;
   mNumIndices = (mPatchVerts.x-1) * (mPatchVerts.y-1) * 6;
   U16 yOffset = mPatchVerts.x;

   for (U32 y = 0; y < mPatchVerts.y-1; y++) 
   {   
      for (U32 x = 0; x < mPatchVerts.x-1; x++) 
      {       
         U16 base = x + ( yOffset * y );

         index[0] = base;
         index[1] = base + 1;
         index[2] = base + 1 + yOffset;

         index[3] = base + 1 + yOffset;
         index[4] = base + yOffset;
         index[5] = base;

         index += 6;
      }
   }
}

void Px3ClothPlane::processTick( const Move *move )
{
   // Make sure the cloth is created.
   if ( !mCloth )
   return;

   // Update bounds.
   if ( mWorld->isEnabled() )
   {
      Point3F vel = ParticleEmitter::mWindVelocity;
      physx::PxVec3 windVec( vel.x, vel.y, vel.z );
      mCloth->setExternalAcceleration(windVec);

      // This is where the magic happens. We read back the vertex positions from PhysX
      // and alter the positions in the vertex buffer.
   physx::PxClothParticleData* pData = mCloth->lockParticleData(PxDataAccessFlag::eREADABLE);
   if ( pData != NULL )
   {
      for(int i = 0; i < mNumVertices; i++)
      {
         physx::PxClothParticle* particle = &pData->particles[i];
         mVertexRenderBuffer[i].point.set(particle->pos.x, particle->pos.y, particle->pos.z);
         getTransform().mulP( mVertexRenderBuffer[i].point );
      }
      pData->unlock();
   }

   // Update Bounding Box : Currently seems a little broken.
   physx::PxBounds3 box;
   box = mCloth->getWorldBounds(); 

   Point3F min = px3Cast<Point3F>( box.minimum );
   Point3F max = px3Cast<Point3F>( box.minimum );

   mWorldBox.set( min, max );
   mObjBox = mWorldBox;

   getWorldTransform().mul( mObjBox );
   }
   else
   {
      mObjBox.set( 0, mThickness * -0.5f, 0, 
                  mPatchSize.x, mThickness * 0.5f, mPatchSize.y );
   }

   resetWorldBox();

   // Update the VB on the next render.
   mIsVBDirty = true;
}

void Px3ClothPlane::interpolateTick( F32 delta )
{
   // Nothing to do for now!
}

bool Px3ClothPlane::onNewDataBlock( GameBaseData *dptr, bool reload )
{
   return false;
}