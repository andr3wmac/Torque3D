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

//--- Planter.dae MATERIALS BEGIN ---

//--- Planter.dae MATERIALS END ---

//--- Pavement_Tree.dae MATERIALS BEGIN ---
singleton Material(Pavement_Tree_PlanterLeavesLOD)
{
	mapTo = "PlanterLeavesLOD";

	diffuseMap[0] = "art/shapes/props/Planter/Ceramic_Planter_Diff.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.337255 0.337255 0.337255 1";
	specular[0] = "0 0 0 1";
	specularPower[0] = 50;

	doubleSided = 1;
	translucent = false;
	translucentBlendOp = "None";
   alphaTest = "1";
   alphaRef = "67";
   castShadows = "0";
   materialTag0 = "Untagged";
};

singleton Material(Pavement_Tree_PlanterLOD)
{
	mapTo = "PlanterLOD";

	diffuseMap[0] = "art/shapes/props/Planter/Ceramic_Planter_Diff.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.588235 0.588235 0.588235 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   materialTag0 = "Untagged";
};

//--- Pavement_Tree.dae MATERIALS END ---

//--- Pavement_planter.dae MATERIALS BEGIN ---

//--- Pavement_planter.dae MATERIALS END ---

//--- Ferns.dae MATERIALS BEGIN ---
singleton Material(Ferns_Fern)
{
	diffuseMap[0] = "art/shapes/props/Planter/Pavement_planter_Diff";
	mapTo = "Fern";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;
	pixelSpecular[0] = false;
	emissive[0] = false;

	doubleSided = 1;
	translucent = false;
	translucentBlendOp = "LerpAlpha";
   normalMap[0] = "art/shapes/props/Planter/Pavement_planter_Norm.dds";
   specularMap[0] = "art/shapes/props/Planter/Pavement_planter_Spec.dds";
   alphaTest = "1";
   alphaRef = "127";
   materialTag0 = "Untagged";
};

//--- Ferns.dae MATERIALS END ---

//--- Ceramic_Planter.dae MATERIALS BEGIN ---

//--- Ceramic_Planter.dae MATERIALS END ---

//--- Pavement_planter_Railing.dae MATERIALS BEGIN ---

//--- Pavement_planter_Railing.dae MATERIALS END ---


singleton Material(CTP_plantPot_001)
{
   mapTo = "Lores";
   diffuseMap[0] = "art/shapes/props/Planter/Planter_Diff.dds";
   normalMap[0] = "art/shapes/props/Planter/Planter_Norm.dds";
   specularMap[0] = "art/shapes/props/Planter/Planter_Spec.dds";
   doubleSided = "1";
   alphaTest = "1";
   alphaRef = "140";
   materialTag0 = "Untagged";
};


singleton Material(Pavement_planter_Railing_planter_Pavement)
{
   mapTo = "planter_Pavement";
   diffuseColor[0] = "1 1 1 0";
   diffuseMap[0] = "art/shapes/props/Planter/Pavement_planter_Diff";
   specularMap[0] = "art/shapes/props/Planter/Pavement_planter_Spec";
   translucentBlendOp = "LerpAlpha";
   normalMap[0] = "art/shapes/props/Planter/Pavement_planter_Norm.dds";
   doubleSided = "1";
   translucent = "1";
   alphaRef = "0";
   materialTag0 = "Untagged";
};
//--- planter_plants.dae MATERIALS BEGIN ---
singleton Material(planter_plants_PlanterLeaves)
{
	mapTo = "PlanterLeaves";

	diffuseMap[0] = "art/shapes/props/Planter/Planter_Tree_Diff.dds";
	

	diffuseColor[0] = "0.364706 0.364706 0.364706 1";
	specular[0] = "0.568627 0.780392 0.560784 1";
	specularPower[0] = 56;

	doubleSided = 1;
	translucent = 0;
	translucentBlendOp = "None";
   pixelSpecular[0] = "0";
   alphaTest = "1";
   alphaRef = "100";
   constantCubemapGloss = "0.2";
   materialTag0 = "Untagged";
};

//--- planter_plants.dae MATERIALS END ---


singleton Material(Planter)
{
   mapTo = "Planter";
   diffuseMap[0] = "art/shapes/props/Planter/Ceramic_Planter_Diff.dds";
   normalMap[0] = "art/shapes/props/Planter/Ceramic_Planter_Norm.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/shapes/props/Planter/Ceramic_Planter_Spec.dds";
   diffuseColor[0] = "0.513726 0.513726 0.513726 1";
   constantCubemapGloss = "0.2";
   materialTag0 = "Untagged";
};
//--- ReatPlanters.dae MATERIALS BEGIN ---
singleton Material(ReatPlanters_CeramicPlanter)
{
	mapTo = "CeramicPlanter";

	diffuseMap[0] = "art/shapes/props/Planter/Ceramic_Planter_Diff.dds";
	normalMap[0] = "art/shapes/props/Planter/Ceramic_Planter_Norm.dds";
	specularMap[0] = "art/shapes/props/Planter/Ceramic_Planter_Spec.dds";

	diffuseColor[0] = "0.443137 0.443137 0.443137 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   alphaTest = "1";
   alphaRef = "5";
   materialTag0 = "Untagged";
};

singleton Material(ReatPlanters_CeramicPlanterLOD)
{
	mapTo = "CeramicPlanterLOD";

	diffuseMap[0] = "art/shapes/props/Planter/Ceramic_Planter_Diff.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.537255 0.537255 0.537255 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   materialTag0 = "Untagged";
};

//--- ReatPlanters.dae MATERIALS END ---

//--- MSPlanters.dae MATERIALS BEGIN ---
singleton Material(MSPlanters_MaterialLibrary_CeramicPlanter)
{
	mapTo = "MaterialLibrary_CeramicPlanter";

	diffuseMap[0] = "art/shapes/props/Planter/Ceramic_Planter_Diff.dds";
	normalMap[0] = "art/shapes/props/Planter/Ceramic_Planter_Norm.dds";
	specularMap[0] = "art/shapes/props/Planter/Pavement_planter_Spec.dds";

	diffuseColor[0] = "0.443137 0.443137 0.443137 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = 1;
	translucent = false;
	translucentBlendOp = "None";
   alphaTest = "1";
   alphaRef = "167";
   materialTag0 = "Untagged";
};

singleton Material(MSPlanters_MaterialLibrary_CeramicPlanterLOD)
{
	mapTo = "MaterialLibrary_CeramicPlanterLOD";

	diffuseMap[0] = "art/shapes/props/Planter/Ceramic_Planter_Diff.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.54902 0.54902 0.54902 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   constantCubemapGloss = "0.2";
   materialTag0 = "Untagged";
};

//--- MSPlanters.dae MATERIALS END ---

