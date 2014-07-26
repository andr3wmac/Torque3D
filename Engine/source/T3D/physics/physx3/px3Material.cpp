//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
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
#include "T3D/physics/physx3/px3Material.h"

//currently these map 1:1 but who knows if physx may change the value of their enum in the future? Best not to assume this
physx::PxCombineMode::Enum _convertMode(PhysicsMaterial::CombineMode mode)
{
   physx::PxCombineMode::Enum retMode;
   switch(mode)
   {
      case PhysicsMaterial::Average:
         retMode = physx::PxCombineMode::eAVERAGE;
         break;
      case PhysicsMaterial::Min:
         retMode = physx::PxCombineMode::eMIN;
         break;
      case PhysicsMaterial::Mulitply:
         retMode = physx::PxCombineMode::eMULTIPLY;
         break;
      case PhysicsMaterial::Max:
         retMode = physx::PxCombineMode::eMAX;
         break;
      default:
         retMode = physx::PxCombineMode::eAVERAGE;
         break;
   };

   return retMode;
}

Px3Material::Px3Material() : mMaterial(NULL)
{
}

// TODO: terrain material is freed after the physics plugin causing problems releasing the material here but physx will cleanup up anyway,
// still not very ideal at all
Px3Material::~Px3Material()
{
   //physx scene will clean up the PxMaterial - see above TODO
}

void Px3Material::update(const F32 restitution,const F32 staticFriction,const F32 dynamicFritction,CombineMode frictionMode,CombineMode restitutionMode)
{
   mMaterial->setDynamicFriction(dynamicFritction);
   mMaterial->setRestitution(restitution);
   mMaterial->setStaticFriction(staticFriction);
   mMaterial->setFrictionCombineMode(_convertMode(frictionMode));
   mMaterial->setRestitutionCombineMode(_convertMode(restitutionMode));
}

void Px3Material::create(const F32 restitution,const F32 staticFriction,const F32 dynamicFritction,CombineMode frictionMode,CombineMode restitutionMode)
{
   if(!mMaterial)
   {
      mMaterial = gPhysics3SDK->createMaterial(staticFriction,dynamicFritction,restitution);
      mMaterial->setFrictionCombineMode(_convertMode(frictionMode));
      mMaterial->setRestitutionCombineMode(_convertMode(restitutionMode));
   }
}

F32 Px3Material::getDynamicFriction() const
{
   return mMaterial->getDynamicFriction();
}

F32 Px3Material::getStaticFriction() const
{
   return mMaterial->getStaticFriction();
}

F32 Px3Material::getRestitution() const
{
   return mMaterial->getRestitution();
}


