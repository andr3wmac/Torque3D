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

//--- dragonPillar.dae MATERIALS BEGIN ---
singleton Material(dragonPillar_ChinaTown_props_dragonPillar)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   constantCubemapGloss = "0.2";
   materialTag0 = "Untagged";
};

//--- dragonPillar.dae MATERIALS END ---


singleton Material(ChinaTown_props_dragonPillar)
{
   mapTo = "ChinaTown_props_dragonPillar";
   diffuseColor[0] = "1 1 1 0";
   diffuseMap[0] = "art/shapes/props/dragonPillar/DragonPillar_Diffuse.dds";
   normalMap[0] = "art/shapes/props/dragonPillar/DragonPillar_normals.dds";
   specular[0] = "0.470588 0.564706 0.619608 1";
   specularPower[0] = "31";
   pixelSpecular[0] = "0";
   translucentBlendOp = "None";
   constantCubemapGloss = "0.2";
   specularMap[0] = "art/shapes/props/dragonPillar/DragonPillar_Specular.dds";
   translucent = "1";
   alphaTest = "1";
   alphaRef = "20";
   materialTag0 = "Untagged";
};
