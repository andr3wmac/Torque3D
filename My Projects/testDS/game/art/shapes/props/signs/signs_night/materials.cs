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

//--- ChiTownRestaurant_Sign.dae MATERIALS BEGIN ---
singleton Material(ChiTownRestaurant_Sign_ShopSigns)
{
	mapTo = "ShopSigns";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Untagged";
};

//--- ChiTownRestaurant_Sign.dae MATERIALS END ---

//--- 27_19_nightSigns.dae MATERIALS BEGIN ---
singleton Material(_27_19_nightSigns_nightSigns)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Untagged";
};

//--- 27_19_nightSigns.dae MATERIALS END ---


singleton Material(ngihtSigns)
{
   mapTo = "nightSigns";
   diffuseMap[0] = "art/shapes/props/signs/signs_night/NeonNight_diff.dds";
   diffuseMap[1] = "art/shapes/props/signs/signs_night/NeonNight_diff.dds";
   diffuseMap[2] = "";
   glow[2] = "0";
   diffuseColor[2] = "0.996078 0.996078 0.996078 0";
   emissive[0] = "1";
   diffuseColor[1] = "0.592157 0.592157 0.592157 1";
   emissive[1] = "1";
   diffuseColor[0] = "0.227451 0.227451 0.227451 1";
   glow[1] = "1";
   emissive[2] = "0";
   glow[0] = "1";
   materialTag0 = "Untagged";
};
//--- 32_24_nightSigns.dae MATERIALS BEGIN ---
singleton Material(_32_24_nightSigns_Scene_Material)
{
	mapTo = "Scene_Material";

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

//--- 32_24_nightSigns.dae MATERIALS END ---

