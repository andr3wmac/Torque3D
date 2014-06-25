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

//--- Van_01.dae MATERIALS BEGIN ---

//--- Van_01.dae MATERIALS END ---




//--- Van_02.dae MATERIALS BEGIN ---
singleton Material(Van_02_Material_Van_02LOD)
{
	mapTo = "Material-Van_02LOD";

	diffuseMap[0] = "art/shapes/props/Van/Van_Diff_02.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
    cubemap = "refDaySkyCubemap";
    materialTag0 = "Untagged";
};

//--- Van_02.dae MATERIALS END ---



singleton Material(Van_02)
{
   mapTo = "Van_01";
   diffuseMap[0] = "art/shapes/props/Van/Van_Diff_01";
   normalMap[0] = "art/shapes/props/Van/Van_Norm";
   specularMap[0] = "art/shapes/props/Van/Van_Spec";
   
   	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	cubemap = "refDaySkyCubemap";
	useAnisotropic[0] = true;
   materialTag0 = "Untagged";
};
//--- Van_03.dae MATERIALS BEGIN ---
singleton Material(Van_03_Material_Van_03LOD)
{
	mapTo = "Material-Van_03LOD";

	diffuseMap[0] = "art/shapes/props/Van/Van_Diff_03.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	cubemap = "refDaySkyCubemap";
   materialTag0 = "Untagged";
};

//--- Van_03.dae MATERIALS END ---



//--- Van_04.dae MATERIALS BEGIN ---
singleton Material(Van_04_Van_Shadow)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.5 0.5 0.5 0";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   materialTag0 = "Untagged";
};

//--- Van_04.dae MATERIALS END ---


//--- policevan.dae MATERIALS BEGIN ---
singleton Material(policevan_Material_Van_police1)
{
	mapTo = "Material-Van_police1";

	diffuseMap[0] = "art/shapes/props/Van/Van_Diff_04.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   useAnisotropic[0] = true;
   materialTag0 = "Untagged";
};

//--- policevan.dae MATERIALS END ---



singleton Material(policevan_policeVan)
{
   mapTo = "Material-Van_police";
   diffuseColor[0] = "0.701961 0.701961 0.701961 1";
   diffuseMap[0] = "art/shapes/props/Van/Van_Diff_04.dds";
   normalMap[0] = "art/shapes/props/Van/Van_Norm.dds";
   specular[0] = "0.2 0.2 0.2 1";
   specularPower[0] = "1";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/shapes/props/Van/Van_Spec.dds";
   translucentBlendOp = "None";
   cubemap = "refDaySkyCubemap";
   constantCubemapGloss = "0.2";
   useAnisotropic[0] = true;
   materialTag0 = "Untagged";
};

singleton Material(Van_Van_Shadow)
{
   mapTo = "Material-Van_Shadow";
   diffuseColor[0] = "0 0 0 1";
   diffuseMap[0] = "art/shapes/props/Van/Van_Shadow_Diff2";
   specular[0] = "0.2 0.2 0.2 1";
   translucent = "1";
   alphaRef = "0";
   materialTag0 = "Untagged";
   castShadows = "0";
   constantCubemapGloss = "0.2";
};

singleton Material(Van_02_Van_02)
{
   mapTo = "Material-Van_02";
   diffuseColor[0] = "0.545098 0.545098 0.545098 1";
   diffuseMap[0] = "art/shapes/props/Van/Van_Diff_02";
   normalMap[0] = "art/shapes/props/Van/Van_Norm";
   specular[0] = "0.2 0.2 0.2 1";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/shapes/props/Van/Van_Spec";
   translucentBlendOp = "None";
   cubemap = "refDaySkyCubemap";
   specularPower[0] = "61";
   useAnisotropic[0] = true;
   materialTag0 = "Untagged";
};

singleton Material(Van_03_Van_03)
{
   mapTo = "Material-Van_03";
   diffuseColor[0] = "0.8 0.8 0.8 0";
   diffuseMap[0] = "art/shapes/props/Van/Van_Diff_03";
   normalMap[0] = "art/shapes/props/Van/Van_Norm";
   specular[0] = "0.2 0.2 0.2 1";
   specularPower[0] = "11";
   specularMap[0] = "art/shapes/props/Van/Van_Spec";
   translucentBlendOp = "None";
   cubemap = "refDaySkyCubemap";
   useAnisotropic[0] = true;
   materialTag0 = "Untagged";
};



singleton Material(Van_01_VanGlass)
{
   mapTo = "VanGlass";
   specular[0] = "0.368627 0.368627 0.368627 0";
   specularPower[0] = "50";
   translucentBlendOp = "LerpAlpha";
   constantCubemapGloss = "0.2";
   diffuseMap[0] = "art/shapes/props/Van/Van_Diff_01.dds";
   specularMap[0] = "art/shapes/props/Van/Van_Spec.dds";
   translucent = "1";
   cubemap = "CTDaySkyCubemap";
   materialTag0 = "Untagged";
};

singleton Material(Van_01_Material_Van_01)
{
   mapTo = "unmapped_mat";
   specular[0] = "0.2 0.2 0.2 1";
   specularPower[0] = "50";
   translucentBlendOp = "None";
   constantCubemapGloss = "0.2";
   materialTag0 = "Untagged";
};



singleton Material(Van_Van)
{
   mapTo = "Material-Van_01";
   diffuseMap[0] = "art/shapes/props/Van/Van_Diff_01";
   normalMap[0] = "art/shapes/props/Van/Van_Norm";
   specularPower[0] = "46";
   specularMap[0] = "art/shapes/props/Van/Van_Spec";
   translucentBlendOp = "None";
   cubemap = "refDaySkyCubemap";
   constantCubemapGloss = "0.2";
   useAnisotropic[0] = true;
   materialTag0 = "Untagged";
};

singleton Material(van01LOD)
{
   mapTo = "Material-Van_01LOD";
   diffuseMap[0] = "art/shapes/props/Van/Van_Diff_01.dds";
   constantCubemapGloss = "0.2";
   materialTag0 = "Untagged";
};
