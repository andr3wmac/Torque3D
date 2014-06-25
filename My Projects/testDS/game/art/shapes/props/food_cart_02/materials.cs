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

//--- food_cart.dae MATERIALS BEGIN ---
singleton Material(gas_cylinder)
{
   mapTo = "gas_cylinder";

   diffuseMap[0] = "art/shapes/props/food_cart_02/gas_cylinder_02_diff_GM.dds";
   specularMap[0] = "art/shapes/props/food_cart_02/gas_cylinder_02_spec_GM.dds";

   specular[0] = "1 1 1 0";
   specularPower[0] = 50;

   materialTag0 = "Untagged";
};

singleton Material(posters)
{
   mapTo = "posters";

   diffuseMap[0] = "art/shapes/props/food_cart_02/posters_diff_GM.dds";
   
   specular[0] = "1 1 1 0";
   specularPower[0] = 50;
   translucentBlendOp = "LerpAlpha";
   useAnisotropic[0] = true;
   materialTag0 = "Untagged";
};
singleton Material(foodcart)
{
   mapTo = "foodcart";
   
   diffuseMap[0] = "art/shapes/props/food_cart_02/food_cart_04_diff_GM.dds";
   normalMap[0] = "art/shapes/props/food_cart_02/food_cart_04_normals.dds";
   specularMap[0] = "art/shapes/props/food_cart_02/food_cart_04_spec_GM.dds";
   
   specular[0] = "1 1 1 1";
   specularPower[0] = "24";
   pixelSpecular[0] = "0";
   constantCubemapGloss = "0.2";
   useAnisotropic[0] = true;
   materialTag0 = "Untagged";
};

singleton Material(gas_cylinderLOD)
{
   mapTo = "gas_cylinderLOD";

   diffuseMap[0] = "art/shapes/props/food_cart_02/gas_cylinder_02_diff_GM.dds";
   castShadows = "0";
   materialTag0 = "Untagged";
};

singleton Material(postersLOD)
{
   mapTo = "postersLOD";

   diffuseMap[0] = "art/shapes/props/food_cart_02/posters_diff_GM.dds";
   castShadows = "0";
   materialTag0 = "Untagged";
};

singleton Material(foodcartLOD)
{
   mapTo = "foodcartLOD";

   diffuseMap[0] = "art/shapes/props/food_cart_02/food_cart_04_diff_GM.dds";
   castShadows = "0";
   specularMap[0] = "art/shapes/props/food_cart_02/food_cart_04_spec_GM.dds";
   materialTag0 = "Untagged";
};

//--- food_cart.dae MATERIALS END ---

singleton Material(FoodCart_Shadow)
{
   mapTo = "FoodCart_Shadow";
   diffuseMap[0] = "art/shapes/props/Car/Car_Shadow.dds";
   constantCubemapGloss = "0.2";
   castShadows = "0";
   translucent = "1";
   translucentZWrite = "0";
   materialTag0 = "Untagged";
   materialTag2 = "CT_Car";
   materialTag1 = "Prop";
};
