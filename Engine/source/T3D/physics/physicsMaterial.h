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

#ifndef _T3D_PHYSICS_PHYSICSMATERIAL_H_
#define _T3D_PHYSICS_PHYSICSMATERIAL_H_

class PhysicsMaterial
{
public:
   enum CombineMode
   {
      Average = 0,
      Min = 1,
      Mulitply = 2,
      Max = 3
   };

   virtual ~PhysicsMaterial() {}

   virtual void create(const F32 restitution,const F32 staticFriction,const F32 dynamicFritction,
                        CombineMode frictionMode=Average,CombineMode restitutionMode=Average)=0;
   virtual void update(const F32 restitution,const F32 staticFriction,const F32 dynamicFritction,
                        CombineMode frictionMode=Average,CombineMode restitutionMode=Average)=0;

   virtual F32 getDynamicFriction()const=0;
   virtual F32 getStaticFriction()const=0;
   virtual F32 getRestitution()const=0;
};


#endif // _T3D_PHYSICS_PHYSICSMATERIAL_H_