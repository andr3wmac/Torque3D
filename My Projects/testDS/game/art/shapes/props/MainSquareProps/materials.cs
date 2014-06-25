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

//--- MSProps.dae MATERIALS BEGIN ---
singleton Material(MSProps_MS_leaves)
{
	mapTo = "MS_leaves";

	diffuseMap[0] = "art/shapes/props/MainSquareProps/leavesDiff.dds";
	normalMap[0] = "art/shapes/props/MainSquareProps/leavesNorm.dds";
	

	diffuseColor[0] = "0.74902 0.647059 0.772549 1";
	specular[0] = "0.541176 0.537255 0.537255 1";
	specularPower[0] = 99;

	doubleSided = 1;
	translucent = false;
	translucentBlendOp = "None";
   alphaTest = "1";
   alphaRef = "208";
   toneMap[0] = "art/shapes/props/MainSquareProps/leavesDiffLight.dds";
   emissive[0] = "0";
   pixelSpecular[0] = "0";
   parallaxScale[0] = "0";
   constantCubemapGloss = "0.2";
   planarReflection = "0";
   dynamicCubemap = "0";
   glow[0] = "0";
   materialTag0 = "Untagged";
};

//--- MSProps.dae MATERIALS END ---


singleton Material(MSProps_MS_Diff)
{
   mapTo = "MS_Diff";
   diffuseColor[0] = "0.454902 0.454902 0.454902 1";
   diffuseMap[0] = "art/shapes/props/MainSquareProps/MSTextures.dds";
   normalMap[0] = "";
   specular[0] = "1 1 1 1";
   specularPower[0] = "8";
   pixelSpecular[0] = "0";
   specularMap[0] = "";
   doubleSided = "0";
   translucent = "0";
   translucentBlendOp = "None";
   translucentZWrite = "0";
   alphaTest = "0";
   alphaRef = "1";
   materialTag0 = "Untagged";
};
//--- shrub.dae MATERIALS BEGIN ---
singleton Material(shrub_shrubery)
{
	mapTo = "shrubery";

	diffuseMap[0] = "art/shapes/props/MainSquareProps/leavesDiff.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.196078 0.192157 0.133333 1";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;

	doubleSided = 0;
	translucent = false;
	translucentBlendOp = "None";
   alphaTest = "1";
   alphaRef = "80";
   materialTag0 = "Untagged";
};

//--- shrub.dae MATERIALS END ---

