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

//--- plaster.dae MATERIALS BEGIN ---
singleton Material(plaster_wallDecals)
{
   mapTo = "wallDecals";

   diffuseMap[0] = "wallDecals_diffuse.png";
   normalMap[0] = "wallDecals_normals.png";
   specularMap[0] = "art/textures/structures/specmask.dds";

   diffuseColor[0] = "1 1 1 0";
   specular[0] = "0.223529 0.223529 0.223529 1";
   specularPower[0] = 36;

   doubleSided = false;
   translucent = false;
   translucentBlendOp = "None";
   alphaTest = "1";
   alphaRef = "234";
   pixelSpecular[0] = "0";
   constantCubemapGloss = "0.2";
   materialTag0 = "Untagged";
};

//--- plaster.dae MATERIALS END ---

