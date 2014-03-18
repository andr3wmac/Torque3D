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

#ifndef _Px3ClothPlane_H
#define _Px3ClothPlane_H

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

using namespace physx;

class Px3ClothPlane : public GameBase
{
    typedef GameBase Parent;

    enum MaskBits 
    {
        TransformMask  = Parent::NextFreeMask << 0,
        ClothMask      = Parent::NextFreeMask << 1,
        MaterialMask   = Parent::NextFreeMask << 3,
        NextFreeMask   = Parent::NextFreeMask << 4
    };  

public:

    Px3ClothPlane();
    virtual ~Px3ClothPlane();

    DECLARE_CONOBJECT( Px3ClothPlane );

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
    virtual void interpolateTick( F32 delta );

protected:

    Px3World *mWorld;
    PxScene *mScene;
    PxClothFabric *mClothMesh;
    PxCloth *mCloth;

    bool mCollisionEnabled;
    bool mWindEnabled;
    //GPU hardware acceleration for supported GPU's
    bool mGpuEnabled;

    F32 mThickness;
    F32 mSolverFrequency;
    F32 mDampingCoef;
    F32 mStretchVertical; // 1.0f
    F32 mStretchHorizontal; // 0.9f
    F32 mStretchShearing; // 0.75f
    F32 mStretchBending; // 0.5f

    U32 mAttachmentMask;
    static EnumTable mAttachmentFlagTable;

    String mMaterialName;
    SimObjectPtr<Material> mMaterial;
    BaseMatInstance *mMatInst;

    /// 
    GFXVertexPNTT *mVertexRenderBuffer;
    U16 *mIndexRenderBuffer;
    U32 mNumIndices;
    U32 mNumVertices;
    U32 mNumPrimitives;
    Vector<physx::PxClothParticle> mVertices;
    Vector<physx::PxU32> mPrimitives;

    U32 mMeshDirtyFlags;
    bool mIsVBDirty;
    GFXPrimitiveBufferHandle mPrimBuffer;
    GFXVertexBufferHandle<GFXVertexPNTT> mVB;

    Point2I mPatchVerts; 
    Point2F mPatchSize;
    MatrixF mResetXfm;

    bool _createClothPatch();
	void _generateVertices();
	void _initMaterial();
	void _initBuffers();
    void _recreateCloth( const MatrixF &transform );
	void _releaseCloth();
	void _releaseMesh();
    void _updateClothProperties();
    void _updateStaticCloth();
    void _updateVBIB();
};

#endif