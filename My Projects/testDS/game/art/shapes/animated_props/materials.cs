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

//--- flags.dae MATERIALS BEGIN ---


//--- flags.dae MATERIALS END ---


singleton Material(ChinaTown_props_ShopSigns)
{
   mapTo = "props.ShopSigns";
   diffuseMap[0] = "art/textures/structures/borders/borders_diffuse.dds";
   normalMap[0] = "art/textures/structures/borders/borders_001_normals.dds";
   specular[0] = "1 1 1 0";
   specularPower[0] = "50";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/borders/borders_001_spec.dds";
   translucentBlendOp = "None";
   doubleSided = "0";
   materialTag0 = "Untagged";
};
//--- flags3.dae MATERIALS BEGIN ---
singleton Material(flags3_borders)
{
	mapTo = "borders";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.129412 0.129412 0.129412 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Untagged";
};

//--- flags3.dae MATERIALS END ---

//--- lanterns01.dae MATERIALS BEGIN ---

//--- lanterns01.dae MATERIALS END ---

//--- lanterns02.dae MATERIALS BEGIN ---
singleton Material(lanterns02_lanterns2)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Untagged";
};

//--- lanterns02.dae MATERIALS END ---


singleton Material(lanterns02_borders1)
{
   mapTo = "borders1";
   diffuseMap[0] = "art/textures/structures/border/borders_diffuse.dds";
   specular[0] = "0 0 0 0";
   specularPower[0] = "1";
   doubleSided = "1";
   translucentBlendOp = "None";
   alphaTest = "1";
   alphaRef = "181";
   materialTag0 = "Untagged";
};

//--- flags4.dae MATERIALS BEGIN ---
singleton Material(flags4_null)
{
	mapTo = "null";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Untagged";
};

//--- flags4.dae MATERIALS END ---

//--- lanterns03.dae MATERIALS BEGIN ---
singleton Material(lanterns03_lanterns)
{
	mapTo = "lanterns";

	diffuseMap[0] = "art/shapes/props/lantern/lamp_diff_GM.dds";
	//diffuseColor[0] = "7 0.5 0.5 1";
	diffuseMap[1] = "art/shapes/props/lantern/lamp_glow.dds";
	diffuseColor[1] = "1.5 1.25 1 1";
	doubleSided = 1;
	emissive[1] = 1;
	materialTag0 = "Untagged";
};

//--- lanterns03.dae MATERIALS END ---

//--- Propeller05.dae MATERIALS BEGIN ---
singleton Material(Propeller05_Apachi)
{
	mapTo = "Apachi";

	diffuseMap[0] = "art/textures/structures/crashSite/Apachi_2048_Col.dds";
	normalMap[0] = "art/textures/structures/crashSite/Apachi_2048_normals.dds";
	specularMap[0] = "art/textures/structures/crashSite/Apachi_2048_Spec.dds";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "0";
   constantCubemapGloss = "0.2";
   materialTag0 = "Untagged";
};

//--- Propeller05.dae MATERIALS END ---



singleton Material(ChinaTown_props_lanterns)
{
   mapTo = "unmapped_mat";
   diffuseMap[0] = "art/shapes/props/lantern/lamp_diff_GM.dds";
   normalMap[0] = "art/shapes/props/lantern/lamp_normals.dds";
   specular[0] = "1 1 1 0";
   specularPower[0] = "29";
   glow[0] = "1";
   doubleSided = "1";
   translucentBlendOp = "None";
   alphaTest = "1";
   alphaRef = "33";
   customFootstepSound = "playerFootstepPlaylist";
   constantCubemapGloss = "0.2";
   materialTag0 = "Untagged";
};

//--- lanterns07.dae MATERIALS BEGIN ---
singleton Material(lanterns07_MaterialLibrary2_Apachi)
{
	mapTo = "MaterialLibrary2.Apachi";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Untagged";
};

//--- lanterns07.dae MATERIALS END ---

