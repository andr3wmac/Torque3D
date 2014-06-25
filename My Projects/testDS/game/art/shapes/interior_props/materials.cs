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

//--- Building_05_Int_Props.dae MATERIALS BEGIN ---
singleton Material(Building_05_Int_Props_Int_005_props_1)
{
	mapTo = "Int_005_props_1";

	diffuseMap[0] = "art/textures/Interior_props/Building_05_Int_Props_Diff.dds";
	normalMap[0] = "art/textures/Interior_props/Building_05_Int_Props_Norm.dds";
	specularMap[0] = "art/textures/Interior_props/Building_05_Int_Props_Spec.dds";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 8;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   materialTag0 = "RoadAndPath";
};

singleton Material(Building_05_Int_Props_collsions)
{
	mapTo = "collsions";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 8;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
};

singleton Material(Building_05_Int_Props_Int_005_props2)
{
	mapTo = "Int_005_props2";

	diffuseMap[0] = "art/textures/Interior_props/Building_05_Int_Props2_Diff.dds";
	normalMap[0] = "art/textures/Interior_props/Building_05_Int_Props2_norm.dds";
	specularMap[0] = "art/textures/Interior_props/Building_05_Int_Props2_Spec.dds";

	diffuseColor[0] = "0.996078 0.996078 0.996078 1";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 8;

	doubleSided = false;
	translucent = "1";
	translucentBlendOp = "None";
   materialTag0 = "RoadAndPath";
   diffuseColor[1] = "0.203922 0.219608 0.223529 1";
   diffuseMap[1] = "art/textures/Interior_props/Building_05_Int_Props2_Diff_GlowMask.dds";
   glow[1] = "1";
   emissive[1] = "1";
   constantCubemapGloss = "0.2";
};

//--- Building_05_Int_Props.dae MATERIALS END ---

//--- Building_01_Int_Props.dae MATERIALS BEGIN ---
singleton Material(Building_01_Int_Props_Int_001_props1)
{
	mapTo = "Int_001_props1";

	diffuseMap[0] = "art/textures/Interior_props/Building_01_Int_Props_Diff.dds";
	normalMap[0] = "art/textures/Interior_props/Building_01_Int_Props_norm.dds";
	specularMap[0] = "art/textures/Interior_props/Building_01_Int_Props_Spec.dds";

	diffuseColor[0] = "0.992157 0.992157 0.992157 1";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = "1";

	doubleSided = false;
	translucent = "1";
	translucentBlendOp = "None";
   materialTag0 = "RoadAndPath";
   constantCubemapGloss = "0.2";
   diffuseColor[1] = "0.168627 0.219608 0.223529 1";
   diffuseMap[1] = "art/textures/Interior_props/Building_001_Int_Props_GlowMask.dds";
   glow[1] = "1";
   emissive[1] = "1";
};

//--- Building_01_Int_Props.dae MATERIALS END ---

//--- Building_03_Int_Props.dae MATERIALS BEGIN ---

//--- Building_03_Int_Props.dae MATERIALS END ---

//--- Building_02_Int_Props.dae MATERIALS BEGIN ---



//--- Building_02_Int_Props.dae MATERIALS END ---

//--- Building_04_Int_Props.dae MATERIALS BEGIN ---
singleton Material(Building_06_Int_Props_building_06_int)
{
	mapTo = "building_06_int";

	diffuseMap[0] = "art/textures/Interior_props/Building_06_Int_Props_Diff";
	normalMap[0] = "art/textures/Interior_props/Building_06_Int_Props_norm.dds";
	specularMap[0] = "art/textures/Interior_props/Building_06_Int_Props_spec.dds";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 8;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   materialTag0 = "Chinatown";
   diffuseMap[1] = "art/textures/Interior_props/Building_006_Int_Props_GlowMask.dds";
   glow[1] = "1";
   emissive[1] = "1";
   diffuseColor[1] = "0.329412 0.329412 0.329412 1";
};

//--- Building_04_Int_Props.dae MATERIALS END ---

//--- Building_06_Int_Props.dae MATERIALS BEGIN ---
singleton Material(Building_06_Int_Props_building_06_int)
{
	mapTo = "building_06_int";

	diffuseMap[0] = "art/textures/Interior_props/Building_06_Int_Props_Diff";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 8;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
};

//--- Building_06_Int_Props.dae MATERIALS END ---


singleton Material(interiorProps_005)
{
   mapTo = "MaterialLibrary5.Int_005_props";
   diffuseMap[0] = "art/textures/Interior_props/Building_05_Int_Props_Diff.dds";
   normalMap[0] = "art/textures/Interior_props/Building_05_Int_Props_Norm.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/Interior_props/Building_05_Int_Props_Spec.dds";
   constantCubemapGloss = "0.2";
   materialTag0 = "RoadAndPath";
   specularPower[0] = "1";
};
//--- Building_07_Int_Props.dae MATERIALS BEGIN ---
singleton Material(Building_07_Int_Props_restuarant)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
};

singleton Material(Building_07_Int_Props_Kitchen)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   materialTag0 = "RoadAndPath";
   constantCubemapGloss = "0.2";
};

//--- Building_07_Int_Props.dae MATERIALS END ---

//--- Building_07_Int_Props_SecondSet.dae MATERIALS BEGIN ---
singleton Material(Building_07_Int_Props_SecondSet_int_07_props2Glass)
{
	mapTo = "int_07_props2Glass";

	diffuseMap[0] = "art/textures/Interior_props/int07_props_secondSetGlass_diffuse.dds";
	normalMap[0] = "art/textures/Interior_props/int07_props_secondSetGlass_normals.dds";
	specularMap[0] = "art/textures/Interior_props/int07_props_secondSetGlass_specular.dds";

	diffuseColor[0] = "0.470588 0.694118 0.745098 1";
	specular[0] = "0.996078 0.996078 0.996078 0.162";
	specularPower[0] = 29;

	doubleSided = false;
	translucent = 1;
	translucentBlendOp = "LerpAlpha";
   constantCubemapGloss = "0.2";
   materialTag0 = "RoadAndPath";
   translucentZWrite = "0";
   castShadows = "0";
};

//--- Building_07_Int_Props_SecondSet.dae MATERIALS END ---


singleton Material(Building_07_Int_Props_SecondSet_int_07_props2)
{
   mapTo = "int_07_props2";
   diffuseMap[0] = "art/textures/Interior_props/int07_props_secondSet_diffuse.dds";
   normalMap[0] = "art/textures/Interior_props/int07_props_secondSet_normals.dds";
   specular[0] = "1 1 1 0";
   specularPower[0] = "91";
   specularMap[0] = "art/textures/Interior_props/int07_props_secondSet_specular.dds";
   castShadows = "0";
   alphaRef = "0";
   constantCubemapGloss = "0.2";
   materialTag0 = "RoadAndPath";
};
//--- Building_03_Int_Props_SecondSet.dae MATERIALS BEGIN ---

//--- Building_03_Int_Props_SecondSet.dae MATERIALS END ---




singleton Material(building04_int01)
{
   mapTo = "Building_004_int1";
   diffuseMap[0] = "art/textures/Interior_props/Building_04_Int_Props1_diff.dds";
   translucentBlendOp = "None";
   materialTag0 = "RoadAndPath";
   constantCubemapGloss = "0.2";
   normalMap[0] = "";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/Interior_props/Building_04_Int_Props1_spec.dds";
   castShadows = "0";
   alphaTest = "1";
   alphaRef = "107";
   diffuseMap[1] = "art/textures/Interior_props/Building_004_Int_Props2_GlowMask.dds";
   glow[1] = "1";
   emissive[1] = "1";
   translucent = "1";
   diffuseColor[1] = "0.419608 0.388235 0.301961 1";
};

singleton Material(building04_int02)
{
   mapTo = "Building_004_int2";
   diffuseMap[0] = "art/textures/Interior_props/Building_04_Int_Props2_diff.dds";
   translucentBlendOp = "None";
   materialTag0 = "RoadAndPath";
   constantCubemapGloss = "0.2";
   //normalMap[0] = "art/textures/Interior_props/Building_04_Int_Props2_norm.dds";
   specularMap[0] = "art/textures/Interior_props/Building_04_Int_Props2_spec.dds";
   castShadows = "0";
   diffuseMap[1] = "art/textures/Interior_props/Building_04_Int_Props2_GlowMask.dds";
   glow[1] = "1";
   emissive[1] = "1";
   glow[0] = "0";
   translucent = "1";
   diffuseColor[1] = "0.14902 0.145098 0.133333 1";
};








singleton Material(Building_02_Int_Props_int02_props02)
{
   mapTo = "int02_props02";
   diffuseMap[0] = "art/textures/Interior_props/Building_02_Int_Props3_diff.dds";
   normalMap[0] = "art/textures/Interior_props/Building_02_Int_Props3_norm.dds";
   specular[0] = "1 1 1 0";
   specularPower[0] = "50";
   specularMap[0] = "art/textures/Interior_props/Building_02_Int_Props3_spec.dds";
   castShadows = "0";
   translucentBlendOp = "None";
   materialTag0 = "RoadAndPath";
   constantCubemapGloss = "0.2";
};

singleton Material(Building_03_Int_Props_building_03_int)
{
   mapTo = "building_03_int";
   diffuseMap[0] = "art/textures/Interior_props/Building_03_Int_Props_Diff.dds";
   translucentBlendOp = "None";
   materialTag0 = "RoadAndPath";
   constantCubemapGloss = "0.2";
   normalMap[0] = "art/textures/Interior_props/Building_03_Int_Props_norm.dds";
   specularMap[0] = "art/textures/Interior_props/Building_03_Int_Props_spec.dds";
   castShadows = "0";
   diffuseColor[1] = "0.227451 0.262745 0.266667 1";
   diffuseMap[1] = "art/textures/Interior_props/Building_003_Int_Props_GlowMask.dds";
   glow[1] = "1";
   emissive[1] = "1";
   translucent = "1";
};

singleton Material(Building_03_Int_Props_SecondSet_int03_props_SecondSet)
{
   mapTo = "int03_props_SecondSet";
   diffuseMap[0] = "art/textures/Interior_props/int03_props_secondSet_diffuse.dds";
   normalMap[0] = "art/textures/Interior_props/int03_props_secondSet_normals.dds";
   specular[0] = "1 1 1 0";
   specularPower[0] = "50";
   specularMap[0] = "art/textures/Interior_props/int03_props_secondSet_specular.dds";
   castShadows = "0";
   translucentBlendOp = "None";
   materialTag0 = "RoadAndPath";
   constantCubemapGloss = "0.2";
};



singleton Material(Building_02_Int_Props_MaterialLibrary_MaterialLibrary_Kitchen)
{
   mapTo = "MaterialLibrary_MaterialLibrary_Kitchen";
   diffuseMap[0] = "art/textures/Interior_props/Building_02_Int_Props1_Diff.dds";
   normalMap[0] = "art/textures/Interior_props/Building_02_Int_Props1_norm.dds";
   specular[0] = "0.2 0.2 0.2 1";
   specularPower[0] = "50";
   specularMap[0] = "art/textures/Interior_props/Building_02_Int_Props1_spec.dds";
   castShadows = "1";
   translucentBlendOp = "None";
   materialTag0 = "RoadAndPath";
   constantCubemapGloss = "0.2";
};

singleton Material(Building_02_Int_Props_MaterialLibrary_MaterialLibrary_restuarant)
{
   mapTo = "MaterialLibrary_MaterialLibrary_restuarant";
   diffuseMap[0] = "art/textures/Interior_props/Building_02_Int_Props2_Diff.dds";
   normalMap[0] = "art/textures/Interior_props/Building_02_Int_Props2_norm.dds";
   specular[0] = "0.2 0.2 0.2 1";
   specularPower[0] = "50";
   specularMap[0] = "art/textures/Interior_props/Building_02_Int_Props2_spec.dds";
   castShadows = "0";
   translucentBlendOp = "None";
   materialTag0 = "RoadAndPath";
   constantCubemapGloss = "0.2";
   diffuseColor[1] = "0.282353 0.227451 0.160784 1";
   diffuseMap[1] = "art/textures/Interior_props/Building_02_Int_Props2_GlowMask.dds";
   glow[1] = "1";
   emissive[1] = "1";
   translucent = "1";
};

singleton Material(Building_08_Int_Props_CollisionMesh_NoStep)
{
   mapTo = "CollisionMesh_NoStep";
   diffuseColor[0] = "1 0 0 0.75";
   specular[0] = "0.2 0.2 0.2 1";
   translucent = "1";
};
