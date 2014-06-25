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

//--- machineGunAmmo.dae MATERIALS BEGIN ---
singleton Material(machineGunAmmo_AmmoCrate)
{
	mapTo = "AmmoCrate";

	diffuseMap[0] = "art/shapes/items/ammo/Ammo_Crate_DIFF";
	normalMap[0] = "art/shapes/items/ammo/Ammo_Crate_Norm";
	specularMap[0] = "art/shapes/items/ammo/Ammo_Crate_Spec";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 1";
	specularPower[0] = 50;
	glow[0] = "0";

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
};

//--- machineGunAmmo.dae MATERIALS END ---

//--- pistolAmmo.dae MATERIALS BEGIN ---
singleton Material(pistolAmmo_Material_DE_ammo)
{
	mapTo = "Material-DE_ammo";

	diffuseMap[0] = "art/shapes/items/ammo/DE_Ammo_Diff.dds";
	normalMap[0] = "art/shapes/items/ammo/DE_Ammo_norm.dds";
	specularMap[0] = "art/shapes/items/ammo/DE_Ammo_Spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "8 4.23227e-033 1.4013e-045 1";
	specularPower[0] = 1;
	glow[0] = "0";

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "0";
};

//--- pistolAmmo.dae MATERIALS END ---

//--- grenade.dae MATERIALS BEGIN ---
singleton Material(grenade_grenade)
{
	mapTo = "grenade";

	diffuseMap[0] = "art/shapes/items/ammo/Grenade2_Diff";
	normalMap[0] = "art/shapes/items/ammo/Grenade2_Norm";
	specularMap[0] = "art/shapes/items/ammo/Grenade2_Spec";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;
	pixelSpecular[0] = false;
	emissive[0] = false;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
    glow[0] = "0";
   planarReflection = "0";
   dynamicCubemap = "0";
};

//--- grenade.dae MATERIALS END ---

//--- grenadeAmmo.dae MATERIALS BEGIN ---
singleton Material(grenadeAmmo_Material_grenade)
{
	mapTo = "Material-grenade";

	diffuseMap[0] = "Grenade2_Diff";
	normalMap[0] = "Grenade2_Norm";
	specularMap[0] = "Grenade2_Spec";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
};

//--- grenadeAmmo.dae MATERIALS END ---

