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

//--- Car_01.dae MATERIALS BEGIN ---
singleton Material(Car_01)
{
	mapTo = "Car_01";

	diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_white_diff.dds";
	normalMap[0] = "";
	specularMap[0] = "art/shapes/props/Car/CAR_NEW_spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";	
   cubemap = "refnightSkyCubemap";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "CT_Car";
};
singleton Material(Car_01LOD)
{
	mapTo = "Car_01LOD";

	diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_white_diff.dds";
	diffuseColor[0] = "1 1 1 0";
	castShadows = "0";
   constantCubemapGloss = "0.2";
   doubleSided = "1";
   customFootstepSound = "playerFootstepPlaylist";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "LOD";
   materialTag3 = "CT_Car";
};


//--- Car_01.dae MATERIALS END ---


//--- Car_02.dae MATERIALS BEGIN ---
singleton Material(Car_02)
{
	mapTo = "Car_02";

	diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_white_diff.dds";
	normalMap[0] = "";
	specularMap[0] = "art/shapes/props/Car/CAR_NEW_spec.dds";

	diffuseColor[0] = "0.396078 0.396078 0.396078 1";
	specular[0] = "0.25098 0.25098 0.25098 1";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";	
   cubemap = "refnightSkyCubemap";
   pixelSpecular[0] = "1";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "CT_Car";
};
singleton Material(Car_02LOD)
{
	mapTo = "Car_02LOD";

	diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_white_diff.dds";
	diffuseColor[0] = "0.27451 0.27451 0.27451 1";
	castShadows = "0";
   specularMap[0] = "art/shapes/props/Car/CAR_NEW_spec.dds";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "LOD";
   materialTag3 = "CT_Car";
};

//--- Car_02.dae MATERIALS END ---



//--- Car_03.dae MATERIALS BEGIN ---
singleton Material(Car_03)
{
	mapTo = "Car_03";

	diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_black_diff.dds";
	normalMap[0] = "";
	specularMap[0] = "art/shapes/props/Car/CAR_NEW_spec.dds";

	diffuseColor[0] = "0.717647 0.717647 0.717647 1";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 16;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";	
   pixelSpecular[0] = "1";
   cubemap = "refnightSkyCubemap";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag3 = "CT_Car";
};
singleton Material(Car_03LOD)
{
	mapTo = "Car_03LOD";

	diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_black_diff.dds";
	diffuseColor[0] = "0.71 0.71 0.71 1";
	castShadows = "0";
   specularPower[0] = "1";
   cubemap = "";
   pixelSpecular[0] = "0";
   specularMap[0] = "";
   constantCubemapGloss = "0.2";
   doubleSided = "1";
   customFootstepSound = "playerFootstepPlaylist";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "LOD";
   materialTag3 = "CT_Car";
};
//--- Car_03.dae MATERIALS END ---



//--- Car_04.dae MATERIALS BEGIN ---


singleton Material(Car_04)
{
	mapTo = "Car_04";

	diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_red.dds";
	normalMap[0] = "";
	specularMap[0] = "art/shapes/props/Car/CAR_NEW_spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 41;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";	
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "CT_Car";
};
singleton Material(Car_04LOD)
{
	mapTo = "Car_04LOD";

	diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_red.dds";
	diffuseColor[0] = "1 1 1 0";
	castShadows = "0";
   constantCubemapGloss = "0.2";
   doubleSided = "1";
   customFootstepSound = "playerFootstepPlaylist";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "LOD";
   materialTag3 = "CT_Car";
};
//--- Car_04.dae MATERIALS END ---



//--- Car_05.dae MATERIALS BEGIN ---
singleton Material(Car_05)
{
	mapTo = "Car_05";

	diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_green_diff.dds";
	normalMap[0] = "";
	specularMap[0] = "art/shapes/props/Car/CAR_NEW_spec.dds";

	diffuseColor[0] = "0.992157 0.992157 0.992157 0";
	specular[0] = "0.992157 0.992157 0.992157 1";
	specularPower[0] = 44;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";	
   cubemap = "refnightSkyCubemap";
   pixelSpecular[0] = "1";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "CT_Car";
};
singleton Material(Car_05LOD)
{
	mapTo = "Car_05LOD";

	diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_green_diff.dds";
	diffuseColor[0] = "1 1 1 0";
	castShadows = "0";
   specularPower[0] = "1";
   pixelSpecular[0] = "0";
   specularMap[0] = "";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "LOD";
   materialTag3 = "CT_Car";
};

//--- Car_05.dae MATERIALS END ---


//--- Car_07.dae MATERIALS BEGIN ---
singleton Material(Car_07)
{
	mapTo = "Car_07";

	diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_yellowcab_DIFF.dds";
	normalMap[0] = "";
	specularMap[0] = "art/shapes/props/Car/CAR_NEW_spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 14;
	useAnisotropic[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";	
   cubemap = "refnightSkyCubemap";
   pixelSpecular[0] = "1";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "CT_Car";
};
singleton Material(Car_07LOD)
{
	mapTo = "Car_07LOD";

	diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_yellowcab_DIFF.dds";
	diffuseColor[0] = "1 1 1 0";
	castShadows = "0";
   doubleSided = "1";
   customFootstepSound = "playerFootstepPlaylist";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "LOD";
   materialTag3 = "CT_Car";
};
//--- Car_07.dae MATERIALS END ---



//--- Car_08.dae MATERIALS BEGIN ---
singleton Material(Car_08)
{
	mapTo = "Car_08";

	diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_Blue_diff.dds";
	normalMap[0] = "";
	specularMap[0] = "art/shapes/props/Car/CAR_NEW_spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";	
   cubemap = "refnightSkyCubemap";
   pixelSpecular[0] = "1";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "CT_Car";
};
singleton Material(Car_08LOD)
{
	mapTo = "Car_08LOD";

	diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_Blue_diff.dds";
	diffuseColor[0] = "1 1 1 0";
	castShadows = "1";
   constantCubemapGloss = "0.2";
   doubleSided = "1";
   customFootstepSound = "playerFootstepPlaylist";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "LOD";
   materialTag3 = "CT_Car";
};

//--- Car_08.dae MATERIALS END ---



//--- Car_09.dae MATERIALS BEGIN ---
singleton Material(car_police)
{
	mapTo = "Car_09";

   diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_police_diff.dds";
   normalMap[0] = "";
   specularMap[0] = "art/shapes/props/Car/CAR_NEW_spec.dds";

   diffuseColor[0] = "0.517647 0.517647 0.517647 1";
   specular[0] = "0.2 0.2 0.2 1";
   specularPower[0] = 19;

   doubleSided = false;
   translucent = false;
   translucentBlendOp = "None";	
   pixelSpecular[0] = "1";
   cubemap = "refnightSkyCubemap";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "CT_Car";
};
singleton Material(car_policeLOD)
{
   mapTo = "Car_09LOD";
   doubleSided = "1";
   customFootstepSound = "playerFootstepPlaylist";
   constantCubemapGloss = "0.2";

   diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_police_diff.dds";
   diffuseColor[0] = "0.505882 0.505882 0.505882 1";
   castShadows = "0";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "LOD";
   materialTag3 = "CT_Car";
};

//--- Car_09.dae MATERIALS END ---



singleton Material(Car_Shadow)
{
   mapTo = "Car_Shadow";
   diffuseMap[0] = "art/shapes/props/Car/Car_Shadow";
   castShadows = "0";
   translucent = "1";
   translucentZWrite = "0";
   alphaTest = "0";
   alphaRef = "0";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "CT_Car";
   constantCubemapGloss = "0.2";
};

singleton Material(car_Glass)
{
   mapTo = "Car_Glass";
   diffuseColor[0] = "0.8 0.8 0.8 0";
   diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_black_diff.dds";
   specular[0] = "0.25098 0.25098 0.254902 0.444";
   specularPower[0] = "56";
   specularMap[0] = "";
   translucent = "1";
   translucentBlendOp = "LerpAlpha";
   translucentZWrite = "0";
   cubemap = "refDaySkyCubemap";
   alphaRef = "0";
   constantCubemapGloss = "0.2";
   pixelSpecular[0] = "0";
   doubleSided = "1";
   customFootstepSound = "playerFootstepPlaylist";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "CT_Car";
};
singleton Material(car_GlassLOD)
{
	mapTo = "car_GlassLOD";

   diffuseMap[0] = "art/shapes/props/Car/CAR_NEW_black_diff.dds";
	diffuseColor[0] = "1 1 1 0";
	castShadows = "1";
   translucent = "1";
   translucentZWrite = "0";
   constantCubemapGloss = "0.2";
   cubemap = "refDaySkyCubemap";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "LOD";
   materialTag3 = "CT_Car";
};

singleton Material(CarDestroyed)
{
   mapTo = "CarDestroyed";

   diffuseMap[0] = "art/shapes/props/Car/CarDestroyed_D.dds";
   specularMap[0] = "art/shapes/props/Car/CarDestroyed_D.dds";
   normalMap[0] = "art/shapes/props/Car/CarDestroyed_N.dds";
   diffuseColor[0] = "1 1 1 0";
   castShadows = "1";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag3 = "CT_Car";
   showFootprints = "0";
   customFootstepSound = "DeathCrySound";
};

singleton Material(CollisionMesh_CarMetal)
{
   mapTo = "CollisionMesh_CarMetal";
   diffuseColor[0] = "1 0 0 0.75";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   translucent = "1";
   customFootstepSound = "FootLightMetalSound";
   showFootprints = "0";
   customImpactSound = "BulletImpactSound";
   materialTag1 = "Collision";
};
