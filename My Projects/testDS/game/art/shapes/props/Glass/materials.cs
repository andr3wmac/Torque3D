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

//--- glassPlane.dae MATERIALS BEGIN ---

//--- glassPlane.dae MATERIALS END ---



singleton Material(glassPlane_Glass_Plane)
{
   mapTo = "Glass_Plane";
   diffuseMap[0] = "art/shapes/props/Glass/glass_Diffuse_forBuildings.TGA";
   specular[0] = "0.870588 0.870588 0.870588 0.402";
   specular[1] = "0.996078 0.92549 0.74902 1";
   specularPower[0] = "9";
   specularPower[1] = "128";
   pixelSpecular[0] = "1";
   specularMap[0] = "";
   doubleSided = "1";
   castShadows = "0";
   translucent = "1";
   alphaRef = "0";
   cubemap = "refDaySkyCubemap";
   materialTag0 = "Untagged";
};
