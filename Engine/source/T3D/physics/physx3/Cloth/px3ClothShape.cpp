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
#include "T3D/physics/physx3/Cloth/Px3ClothShape.h"
#include "T3D/physics/physx3/px3Casts.h"

//-----------------------------------------------------------------------------
// Constructor/Destructor
//-----------------------------------------------------------------------------
Px3ClothShape::Px3ClothShape()
{
    mShapeInstance = NULL;
    mWorld = NULL;
    mScene = NULL;
    mDebugTick=0;
}

Px3ClothShape::~Px3ClothShape()
{
}

//-----------------------------------------------------------------------------
// Cloth Management
//-----------------------------------------------------------------------------

void Px3ClothShape::_createFabric(ClothMesh* cMesh)
{
    // Generate list of triangles.
    Vector<U32>* indexData = cMesh->skinMesh->getIndices();
    cMesh->numTriangles = indexData->size();
    for(int a = 0; a < cMesh->numTriangles; a++)
    {
        U32 val = indexData->operator[](a);
        cMesh->triangles.push_back(val);
    }
        
    // Generate list of vertices.
    cMesh->vertexInfo = cMesh->skinMesh->getVertexInfo();
    for(int a = 0; a < cMesh->vertexInfo.size(); a++)
    {
        TSMesh::TSMeshVertexInfo* vert = &cMesh->vertexInfo[a];

        // Weight ( 0 = fixed, 1 = movable )
        // Bone 0 = Cloth Bone
        // Bone 1 = Rigid Bone
        F32 weight = vert->weight;
        if ( vert->bone == 1 ) weight = 0.0f;
        
        // Generate a list of cloth particles.
        Point3F point = vert->point;
        cMesh->vertices.push_back(physx::PxClothParticle(physx::PxVec3(point.x,
            point.y,
            point.z), weight));

        // Correct the Triangles list to remove duplicates
        // vertex references.
        for(int b = 0; b < cMesh->numTriangles; b++)
        {
            for (int c = 0; c < vert->mapsTo.size(); c++)
            {
                if ( vert->mapsTo[c] == cMesh->triangles[b] )
                    cMesh->triangles[b] = a;
            }
        }
    }

    // Set the number of verts for this cloth mesh.
    cMesh->numVertices = cMesh->vertices.size();

    // Create description of cloth to send to PhysX.
    physx::PxClothMeshDesc meshDesc;
    meshDesc.points.data = &cMesh->vertices[0];
    meshDesc.points.count = cMesh->numVertices;
    meshDesc.points.stride = sizeof(physx::PxClothParticle);

    meshDesc.invMasses.data = &cMesh->vertices[0].invWeight;
    meshDesc.invMasses.count = cMesh->numVertices;
    meshDesc.invMasses.stride = sizeof(physx::PxClothParticle);

    meshDesc.triangles.data = &cMesh->triangles[0];
    meshDesc.triangles.count = cMesh->numTriangles / 3;
    meshDesc.triangles.stride = sizeof(physx::PxU32) * 3;
    physx::PxClothFabric* clothFabric = physx::PxClothFabricCreate(*gPhysics3SDK, meshDesc, physx::PxVec3(0, 0, 0));

    // Store Fabric.
    if ( clothFabric )
        cMesh->fabric = clothFabric;
}

void Px3ClothShape::_createCloth(ClothMesh* cMesh)
{
    // Make sure we can change the world.
    mWorld->lockScene();

    // Create fabric if it doesn't exist.
    if ( cMesh->fabric == NULL )
        _createFabric(cMesh);

    // Apply transform
    physx::PxTransform out;
    QuatF q;
    q.set(mTransform);
    out.q = px3Cast<physx::PxQuat>(q);
    out.p = px3Cast<physx::PxVec3>(mTransform.getPosition());

    // Clear old cloth
    if ( cMesh->cloth )
        _releaseCloth(cMesh);

    // Attempt to create 
    physx::PxCloth* cloth = gPhysics3SDK->createCloth(out, *cMesh->fabric, &cMesh->vertices[0], physx::PxClothFlags());
    if ( cloth )
    {
        // Add cloth to the scene.
        mScene->addActor(*cloth);

        // Store cloth information.
        cMesh->cloth = cloth;

        // Duplicate the mesh vertex array for our own personal use.
        TSMesh::TSMeshVertexArray* meshVertexData = cMesh->skinMesh->getVertexData();
        cMesh->meshVertexData = new TSMesh::TSMeshVertexArray();
        cMesh->meshVertexData->set( NULL, 0, 0, false );
        void *aligned_mem = dMalloc_aligned( meshVertexData->vertSize() * meshVertexData->size(), 16 );
        dMemcpy( aligned_mem, meshVertexData->address(), meshVertexData->mem_size() );
        cMesh->meshVertexData->set( aligned_mem, meshVertexData->vertSize(), meshVertexData->size() );
        cMesh->meshVertexData->setReady( true );

        // Override the vertices in the instance with our new vertex array.
        cMesh->meshInstance->setVertexOverride(cMesh->meshVertexData);

        // Setup default cloth properties.
        // This will later be replaced with per-cloth properties from datablock.
        cMesh->cloth->setClothFlag(physx::PxClothFlag::eSCENE_COLLISION, true);
        cMesh->cloth->setSolverFrequency(120.0f);
        cMesh->cloth->setDampingCoefficient(physx::PxVec3(0.0f));
        cMesh->cloth->setStretchConfig(physx::PxClothFabricPhaseType::eVERTICAL, physx::PxClothStretchConfig(1.0f)); //1.0f
        cMesh->cloth->setStretchConfig(physx::PxClothFabricPhaseType::eHORIZONTAL, physx::PxClothStretchConfig(0.9f)); //0.9f
        cMesh->cloth->setStretchConfig(physx::PxClothFabricPhaseType::eSHEARING, physx::PxClothStretchConfig(0.75f)); // 0.75f
        cMesh->cloth->setStretchConfig(physx::PxClothFabricPhaseType::eBENDING, physx::PxClothStretchConfig(0.5f)); // 0.5f
    }

    mWorld->unlockScene();
}

void Px3ClothShape::_releaseCloth(ClothMesh* cMesh)
{
    if ( cMesh->cloth )
    {
        if ( mScene )
            mScene->removeActor( *cMesh->cloth );

        cMesh->cloth->release();
        cMesh->cloth = NULL;
    }

    if ( cMesh->meshInstance )
        cMesh->meshInstance->setVertexOverride(NULL);

    SAFE_DELETE(cMesh->meshVertexData);
}

void Px3ClothShape::_findClothMeshes()
{
    if ( !mShapeInstance )
        return;

    // Clear any data we have.
    _clearClothMeshes();

    // Populate cloth mesh vector with all meshes we find that start with
    // the word cloth. They aren't actually created until after Torque
    // skins them. This is handled in ProcessTick().
    if ( mClothMeshes.size() == 0 )
    {
        //Vector<TSMesh*> data = mShape->findAllMeshes("cloth");
        Vector<TSShapeInstance::MeshObjectInstance*> data = mShapeInstance->findMeshInstances("Cloth");
        
        for (int i = 0; i < data.size(); i++)
        {
            TSSkinMesh* skinMesh = dynamic_cast<TSSkinMesh*>(data[i]->getMesh(0));
            if ( skinMesh )
            {
                ClothMesh cMesh;
                cMesh.cloth = NULL;
                cMesh.fabric = NULL;
                cMesh.numTriangles = 0;
                cMesh.numVertices = 0;
                cMesh.skinMesh = skinMesh;
                cMesh.meshVertexData = NULL;
                cMesh.meshInstance = data[i];
                mClothMeshes.push_back(cMesh);
            }
        }
    }
}

void Px3ClothShape::_clearClothMeshes()
{
    for ( U32 i = 0; i < mClothMeshes.size(); i++ )
    {
        ClothMesh* cMesh = &mClothMeshes[i];

        // Release Cloth.
        _releaseCloth(cMesh);

        // Release Fabric.
		if(cMesh->fabric)
		{
			cMesh->fabric->release();
			cMesh->fabric = NULL;
		}
    }
    mClothMeshes.clear();
}

void Px3ClothShape::setTransform( const MatrixF &mat )
{
    mTransform = mat;
}

void Px3ClothShape::onPhysicsReset( PhysicsResetEvent reset )
{
    // Recreate each cloth at the last reset position.
    mWorld->getPhysicsResults();
    for ( int i = 0; i < mClothMeshes.size(); i++ )
        _createCloth(&mClothMeshes[i]);
}

bool Px3ClothShape::create(TSShapeInstance* shapeInst, const MatrixF &transform)
{
    mWorld = dynamic_cast<Px3World*>( PHYSICSMGR->getWorld( "client" ) );
      
    if ( !mWorld || !mWorld->getScene() )
    {
        Con::errorf( "Px3Cloth::onAdd() - PhysXWorld not initialized... cloth disabled!" );
        return false;
    }

    mScene = mWorld->getScene();
    PhysicsPlugin::getPhysicsResetSignal().notify( this, &Px3ClothShape::onPhysicsReset, 1053.0f );

    // Save shape and transform data.
    mShapeInstance = shapeInst;
    mTransform = transform;

    // Find all cloth meshes within the shape.
    _findClothMeshes();
    return true;
}

void Px3ClothShape::release()
{
    // Clear any cloth meshes + fabric.
    _clearClothMeshes();

    // Remove physics plugin callback.
    PhysicsPlugin::getPhysicsResetSignal().remove( this, &Px3ClothShape::onPhysicsReset );
}

void Px3ClothShape::processTick()
{
    if ( !mShapeInstance )
        return;

    // Update bounds.
    if ( mWorld->isEnabled() )
    {
        // Temporary Wind Vector Hack.
        physx::PxVec3 windVec( 5.0f, 2.0f, 1.0f );
      
        bool displayDebug = false;
        mDebugTick++;
        if ( mDebugTick > 32 )
        {
            displayDebug = true;
            mDebugTick = 0;
        }

        // Loop through each cloth mesh we have listed.
        for ( int i = 0; i < mClothMeshes.size(); i++ )
        {
            // Check if it's actualy physx representation has 
            // been made yet.
            ClothMesh* cMesh = &mClothMeshes[i];
            if ( cMesh->cloth == NULL ) 
            {
                if ( cMesh->skinMesh->hasSkinned() )
                    _createCloth(cMesh);
                continue;
            }

            // Read the latest updates from PhysX.
            physx::PxClothParticleData* pData = cMesh->cloth->lockParticleData(physx::PxDataAccessFlag::eREADABLE);
            if ( pData != NULL )
            {
                for(int a = 0; a < cMesh->numVertices; a++)
                {
                    // The particle represents a single vertex of the cloth.
                    physx::PxClothParticle* particle = &pData->particles[a];

                    // Unfortunately there are a number of duplicate vertices
                    // and they all have to be updated.
                    Vector<U32> vertMap = cMesh->vertexInfo[a].mapsTo;
                    for(int b = 0; b < vertMap.size(); b++)
                    {
                        TSMesh::__TSMeshVertexBase* vert = &(*cMesh->meshVertexData)[vertMap[b]];
                        vert->vert(Point3F(particle->pos.x, particle->pos.y, particle->pos.z));
                    }
                }
            }
            // Unlock PhysX particle data.
            pData->unlock();

            // Add Wind Acceleration, and updated vertex buffer.
            cMesh->cloth->setExternalAcceleration(windVec);
        }
   }
}
