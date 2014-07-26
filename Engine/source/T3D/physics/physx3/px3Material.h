//-----------------------------------------------------------------------------
// Copyright (c) 2014 NarivTech, www.narivtech.com
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

#ifndef _PX3MATERIAL_H_
#define _PX3MATERIAL_H_

#ifndef _PHYSX3_H_
#include "T3D/physics/physx3/px3.h"
#endif
#ifndef _T3D_PHYSICS_PHYSICSMATERIAL_H_
#include "T3D/physics/physicsMaterial.h"
#endif

class Px3Material : public PhysicsMaterial
{
public:
   Px3Material();
   virtual ~Px3Material();

   virtual void create(const F32 restitution,const F32 staticFriction,const F32 dynamicFritction,
                        CombineMode frictionMode=Average,CombineMode restitutionMode=Average);
   virtual void update(const F32 restitution,const F32 staticFriction,const F32 dynamicFritction,
                        CombineMode frictionMode=Average,CombineMode restitutionMode=Average);
   virtual F32 getDynamicFriction()const;
   virtual F32 getStaticFriction()const;
   virtual F32 getRestitution()const;

   physx::PxMaterial *getMaterial(){return mMaterial;}
private:
   physx::PxMaterial *mMaterial;
};

#endif // _PX3MATERIALH_
