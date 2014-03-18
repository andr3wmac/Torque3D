//-----------------------------------------------------------------------------
// Authors: 
//		Andrew MacIntyre - Aldyre Studios - aldyre.com
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

#ifndef _PX3CLOTHSHAPE_H_
#define _PX3CLOTHSHAPE_H_

#include "T3D/physics/physx3/px3.h"
#include "T3D/physics/physx3/px3World.h"
#include "T3D/physics/physx3/px3Plugin.h"
#include "ts/tsShapeInstance.h"

#ifndef _ITICKABLE_H_
    #include "core/iTickable.h"
#endif

class Px3World;

//-----------------------------------------------------------------------------
// Px3Px3ClothShape provides the ability to load a shape into torque and have 
// individual mesh pieces appear as cloth in the world. The mesh must meet
// the following criteria:
//  1) Each mesh must be named Cloth-x or cloth-x where x is any positive
//     integer.
//  2) Every vertex must be weighted to either bone 0 or bone 1. Meaning two
//     bones have to be created that each cloth mesh is weighed to. The
//     vertices on bone 0 are treated as loose cloth, the ones on bone 1 are
//     treated as fixed points.
//-----------------------------------------------------------------------------

class Px3ClothShape : public PhysicsCloth
{
   TSShapeInstance*		mShapeInstance;

   U32 mDebugTick;
   
   // Data for each cloth mesh found in the shape.
   struct ClothMesh
   {
		physx::PxCloth *cloth;
		physx::PxClothFabric* fabric;
		TSSkinMesh* skinMesh;
		TSMesh::TSMeshVertexArray* meshVertexData;
		TSShapeInstance::MeshObjectInstance* meshInstance;
		U32 numVertices;
		U32 numTriangles;
		Vector<physx::PxClothParticle> vertices;
		Vector<TSMesh::TSMeshVertexInfo> vertexInfo;
		Vector<physx::PxU32> triangles;
   };

protected:
	// PhysX 3.3 Variables.
	Px3World *mWorld;
	physx::PxScene *mScene;

	// Vector of all the cloth meshes found within
	// this shape.
	Vector<ClothMesh> mClothMeshes;

	// Used to track last physics reset position.
	MatrixF mTransform;

	// Cloth management functions.
	void _createCloth(ClothMesh* cMesh);
	void _releaseCloth(ClothMesh* cMesh);
	void _createFabric(ClothMesh* cMesh);
	void _findClothMeshes();
	void _clearClothMeshes();

public:
   Px3ClothShape();
   virtual ~Px3ClothShape();
   
   // Physics Reset Callback Function.
   void onPhysicsReset( PhysicsResetEvent reset );

   bool create(TSShapeInstance* shapeInst, const MatrixF &transform);
   void release();
   void processTick();
   void setTransform( const MatrixF &mat );
};

#endif // _PX3CLOTHSHAPE_H_