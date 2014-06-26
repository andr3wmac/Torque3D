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

//--- ChinaTownInts.dae MATERIALS BEGIN ---


singleton Material(ChinaTownInts_interiors_floor_003)
{
	mapTo = "interiors.floor_003";

	diffuseMap[0] = "art/textures/structures/floors/WoodenFloor_diffuse";
	normalMap[0] = "art/textures/structures/floors/WoodenFloor_normals.dds";
	specularMap[0] = "art/textures/structures/floors/WoodenFloor_spec.dds";

	diffuseColor[0] = "0.670588 0.670588 0.670588 1";
	specular[0] = "0.34902 0.34902 0.34902 1";
	specularPower[0] = 59;
	pixelSpecular[0] = 0;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   detailScale[0] = "4 4";
   detailNormalMap[0] = "art/textures/structures/detail_normal.dds";
   detailNormalMapStrength[0] = "-1";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(ChinaTownInts_interiors_ceiling_001)
{
	mapTo = "interiors.ceiling_001";

	diffuseMap[0] = "art/textures/structures/ceilings/ceiling_diffuse_001";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.584314 0.584314 0.584314 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;
	pixelSpecular[0] = false;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(ChinaTownInts_interiors_ceiling_002)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;
	pixelSpecular[0] = false;
	emissive[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};






singleton Material(ChinaTownInts_interiors_intWall_005)
{
	mapTo = "interiors.intWall_005";

	diffuseMap[0] = "art/textures/structures/interiorWalls/intWall05_Diffuse.dds";
	normalMap[0] = "art/textures/structures/interiorWalls/intWall05_normals.dds";
	specularMap[0] = "art/textures/structures/interiorWalls/intWall05_Specular.dds";

	diffuseColor[0] = "0.729412 0.729412 0.729412 1";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	pixelSpecular[0] = 0;
	emissive[0] = 0;

	doubleSided = 1;
	translucent = false;
	translucentBlendOp = "None";
   detailMap[0] = "art/textures/structures/detail.dds";
   detailScale[0] = "10 10";
   detailNormalMap[0] = "art/textures/structures/detail_normal.dds";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(ChinaTownInts_interiors_stairs)
{
	mapTo = "interiors.stairs";

	diffuseMap[0] = "art/textures/structures/stairs/stairs_diffuse.dds";
	normalMap[0] = "art/textures/structures/stairs/stairs_normal.dds";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 46;
	pixelSpecular[0] = 0;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(ChinaTownInts_brick_002)
{
	mapTo = "brick_002";

	diffuseMap[0] = "art/textures/structures/walls/brick_002_diffuse.dds";
	normalMap[0] = "art/textures/structures/walls/brick_002_normal.dds";
	specularMap[0] = "art/textures/structures/walls/brick_002_spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	pixelSpecular[0] = false;
	emissive[0] = 0;
	useAnisotropic[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};







singleton Material(ChinaTownInts_interiors_IntWallCon)
{
	mapTo = "interiors.IntWallCon";

	diffuseMap[0] = "art/textures/structures/concrete/interiorWall_concrete_diffuse.dds";
	normalMap[0] = "art/textures/structures/concrete/interiorWall_concrete_norm.dds";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0.345098 0.345098 0.345098 1";
	specularPower[0] = 1;
	pixelSpecular[0] = 0;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(ChinaTownInts_interiors_confloor_001)
{
	mapTo = "interiors.confloor_001";

	diffuseMap[0] = "art/textures/structures/concrete/conFloor_001_diffuse.dds";
	normalMap[0] = "art/textures/structures/concrete/conFloor_001_norm.dds";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0.443137 0.443137 0.443137 1";
	specularPower[0] = 1;
	pixelSpecular[0] = 0;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(ChinaTownInts_plaster_003)
{
	mapTo = "plaster_003";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	pixelSpecular[0] = false;
	emissive[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};



singleton Material(ChinaTownInts_intwall_7)
{
	mapTo = "intwall_7";

	diffuseMap[0] = "art/textures/structures/interiorWalls/intWall06_Diffuse.dds";
	normalMap[0] = "art/textures/structures/interiorWalls/intWall06_normals.dds";
	specularMap[0] = "art/textures/structures/interiorWalls/intWall06_Spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	pixelSpecular[0] = false;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- ChinaTownInts.dae MATERIALS END ---

//--- ChinaTown.dae MATERIALS BEGIN ---


singleton Material(ChinaTown_concrete_001)
{
	mapTo = "concrete_001";

	diffuseMap[0] = "art/textures/structures/concrete/concrete_001_diffuse.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	pixelSpecular[0] = false;
	emissive[0] = 0;
	useAnisotropic[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};


singleton Material(ChinaTown_windows_windowsDoors)
{
	mapTo = "windows.windowsDoors";

	diffuseMap[0] = "art/textures/structures/windowsDoors/windowsDoors_diffuse.dds";
	normalMap[0] = "art/textures/structures/windowsDoors/windowsDoors_normal.dds";
	specularMap[0] = "art/textures/structures/windowsDoors/windowsDoors_spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	pixelSpecular[0] = 0;
	emissive[0] = 0;
	useAnisotropic[0] = true;

	doubleSided = 1;
	translucent = false;
	translucentBlendOp = "LerpAlpha";
   cubemap = "";
   alphaTest = "1";
   alphaRef = "40";
   detailScale[0] = "30 30";
   materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_ground_pavement)
{
	mapTo = "ground.pavement";

	diffuseMap[0] = "art/textures/structures/ground/pavement_diffuse.dds";
	normalMap[0] = "art/textures/structures/ground/pavement_normal.dds";
	specularMap[0] = "art/textures/structures/ground/pavement_spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	pixelSpecular[0] = 1;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   detailMap[0] = "";
   detailScale[0] = "3 3";
   detailNormalMap[0] = "art/textures/structures/detail_normal.dds";
   detailNormalMapStrength[0] = "1";
   waveFreq[0] = "3.75";
   waveAmp[0] = "0.313";
   materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_railings_railings)
{
	mapTo = "railings.railings";

	diffuseMap[0] = "art/textures/structures/railings/railingsNew_diffuse.dds";
	normalMap[0] = "art/textures/structures/railings/railingsNew_normals";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0.996078 0.996078 0.996078 1";
	specularPower[0] = 11;
	pixelSpecular[0] = 1;
	emissive[0] = 0;

	doubleSided = 1;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_shadeCloths_shadeCloth_002)
{
	mapTo = "shadeCloths.shadeCloth_002";

	diffuseMap[0] = "art/textures/structures/shadeCloths/shadeCloth02_Diffuse.dds";
	normalMap[0] = "art/textures/structures/shadeCloths/shadeCloth01_normals.dds";
	specularMap[0] = "art/textures/structures/shadeCloths/shadeCloth01_Spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 24;
	pixelSpecular[0] = 1;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};


singleton Material(ChinaTown_props_ShopSigns)
{
	mapTo = "props.ShopSigns";

	diffuseMap[0] = "art/textures/structures/shopSigns/shopSigns_diffuse.dds";
	normalMap[0] = "art/textures/structures/shopSigns/shopSigns_normal.dds";
	specularMap[0] = "art/textures/structures/shopSigns/shopSigns_spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;
	pixelSpecular[0] = 1;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};



singleton Material(ChinaTown_rooftiles_roofTiles)
{
	mapTo = "rooftiles.roofTiles";

	diffuseMap[0] = "art/textures/structures/roofs/roofs_diffuse.dds";
	normalMap[0] = "art/textures/structures/roofs/roofs_normal.dds";
	specularMap[0] = "art/textures/structures/roofs/roofs_spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 29;
	pixelSpecular[0] = 1;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   alphaTest = "1";
   materialTag0 = "Chinatown";
};







singleton Material(ChinaTown_railings_fireEscape)
{
	mapTo = "railings.fireEscape";

	diffuseMap[0] = "art/textures/structures/railings/fireEscape_diffuse.dds";
	normalMap[0] = "art/textures/structures/railings/fireEscape_normals.dds";
	specularMap[0] = "art/textures/structures/railings/fireEscape_Spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	pixelSpecular[0] = 1;
	emissive[0] = 0;

	doubleSided = 1;
	translucent = false;
	translucentBlendOp = "None";
   alphaTest = "1";
   alphaRef = "114";
   materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_null_nolight)
{
	mapTo = "null.nolight";

	diffuseMap[0] = "art/textures/structures/NOLIGHT/noLight.JPG";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0 0 0 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	pixelSpecular[0] = false;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};


singleton Material(ChinaTown_interiors_floor_001)
{
	mapTo = "interiors.floor_001";

	diffuseMap[0] = "art/textures/structures/floors/tiles_001.dds";
	normalMap[0] = "art/textures/structures/floors/tiles_001_normals.dds";
	specularMap[0] = "art/textures/structures/floors/tiles_001_specular.dds";

	diffuseColor[0] = "0.435294 0.435294 0.435294 1";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	pixelSpecular[0] = 0;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_interiors_intWall_001)
{
	mapTo = "interiors.intWall_001";

	diffuseMap[0] = "art/textures/structures/interiorWalls/intWall01_Diffuse.dds";
	normalMap[0] = "art/textures/structures/interiorWalls/intWall01_normals.dds";
	specularMap[0] = "art/textures/structures/interiorWalls/intWall01_Specular.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	pixelSpecular[0] = 0;
	emissive[0] = 0;

	doubleSided = 1;
	translucent = false;
	translucentBlendOp = "None";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_interiors_intWall_002)
{
	mapTo = "interiors.intWall_002";

	diffuseMap[0] = "art/textures/structures/interiorWalls/intWall02_Diffuse.dds";
	normalMap[0] = "art/textures/structures/interiorWalls/intWall02_normals.dds";
	specularMap[0] = "art/textures/structures/interiorWalls/intWall02_Specular.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 41;
	pixelSpecular[0] = 0;
	emissive[0] = 0;

	doubleSided = 1;
	translucent = false;
	translucentBlendOp = "None";
   castShadows = "0";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};




singleton Material(ChinaTown_rooftiles_metalRoof)
{
	mapTo = "rooftiles.metalRoof";

	diffuseMap[0] = "art/textures/structures/roofs/metalroof_diffuse.dds";
	normalMap[0] = "art/textures/structures/roofs/metalroof_normal.dds";
	specularMap[0] = "art/textures/structures/roofs/metalroof_spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0.992157 0.992157 0.992157 1";
	specularPower[0] = 1;
	pixelSpecular[0] = 1;
	emissive[0] = 0;

	doubleSided = 1;
	translucent = false;
	translucentBlendOp = "None";
   alphaTest = "1";
   alphaRef = "114";
   materialTag0 = "Chinatown";
};


singleton Material(ChinaTown_interiors_intWall_004)
{
	mapTo = "interiors.intWall_004";

	diffuseMap[0] = "art/textures/structures/interiorWalls/intWall04_Diffuse.dds";
	normalMap[0] = "art/textures/structures/interiorWalls/intWall04_normals.dds";
	specularMap[0] = "art/textures/structures/interiorWalls/intWall04_Specular.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	pixelSpecular[0] = 1;
	emissive[0] = 0;

	doubleSided = 1;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_interiors_intWall_006)
{
	mapTo = "interiors.intWall_006";

	diffuseMap[0] = "art/textures/structures/interiorWalls/intWall06_Diffuse.dds";
	normalMap[0] = "art/textures/structures/interiorWalls/intWall06_normals.dds";
	specularMap[0] = "art/textures/structures/interiorWalls/intWall06_Spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	pixelSpecular[0] = 0;
	emissive[0] = 0;

	doubleSided = 1;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_gravel)
{
	mapTo = "gravel";

	diffuseMap[0] = "art/textures/structures/concrete/concrete_001_diffuse.dds";
	normalMap[0] = "";
	specularMap[0] = "art/textures/structures/concrete/concrete_001_specular.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	pixelSpecular[0] = false;
	emissive[0] = 0;
	useAnisotropic[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_interiors_intWall_003)
{
	mapTo = "interiors.intWall_003";

	diffuseMap[0] = "art/textures/structures/interiorWalls/intWall03_Diffuse.dds";
	normalMap[0] = "art/textures/structures/interiorWalls/intWall03_normals.dds";
	specularMap[0] = "art/textures/structures/interiorWalls/intWall03_Specular.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 34;
	pixelSpecular[0] = 0;
	emissive[0] = 0;

	doubleSided = 1;
	translucent = false;
	translucentBlendOp = "None";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_interiors_floor_002)
{
	mapTo = "interiors.floor_002";

	diffuseMap[0] = "art/textures/structures/floors/tiles_002.dds";
	normalMap[0] = "art/textures/structures/floors/tiles_002_normals.dds";
	specularMap[0] = "art/textures/structures/detail.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0.996078 0.996078 0.996078 1";
	specularPower[0] = 51;
	pixelSpecular[0] = 0;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   detailMap[0] = "art/textures/structures/detail.dds";
   detailScale[0] = "5 5";
   detailNormalMap[0] = "art/textures/structures/detail_normal.dds";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_props_dragonPillar)
{
	mapTo = "props.dragonPillar";

	diffuseMap[0] = "art/shapes/props/dragonPillar/DragonPillar_Diffuse.dds";
	normalMap[0] = "art/shapes/props/dragonPillar/DragonPillar_normals.dds";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0.996078 0.843137 0.184314 0";
	specularPower[0] = 1;
	pixelSpecular[0] = 1;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- ChinaTown.dae MATERIALS END ---

//--- ChinaTown_Ground.dae MATERIALS BEGIN ---
singleton Material(ChinaTown_Ground_ground_paving)
{
	mapTo = "ground.paving";

	diffuseMap[0] = "art/textures/structures/ground/paving_diffuse.dds";
	normalMap[0] = "art/textures/structures/ground/paving_norm.dds";
	specularMap[0] = "art/textures/structures/ground/paving_spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 26;
	pixelSpecular[0] = 1;
	emissive[0] = 0;
	useAnisotropic[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   detailScale[0] = "4 4";
   detailNormalMap[0] = "art/textures/structures/detail_normal.dds";
   materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_Ground_ground_pavement_edge)
{
	mapTo = "ground.pavement_edge";

	diffuseMap[0] = "art/textures/structures/ground/pavement_edge_diffuse";
	normalMap[0] = "art/textures/structures/ground/pavement_edge_normal";
	specularMap[0] = "art/textures/structures/ground/pavement_edge_spec";

	diffuseColor[0] = "0.996078 0.996078 0.996078 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	pixelSpecular[0] = 1;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};


singleton Material(ChinaTown_Ground_ground_cobble)
{
	mapTo = "ground.cobble";

	diffuseMap[0] = "art/textures/structures/ground/cobble_diffuse.dds";
	normalMap[0] = "art/textures/structures/ground/cobble_normal.dds";
	specularMap[0] = "art/textures/structures/ground/cobble_specular.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 21;
	pixelSpecular[0] = 1;
	emissive[0] = 0;
	useAnisotropic[0] = true;
	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   parallaxScale[0] = "0.00559441";
   materialTag0 = "Chinatown";
};


singleton Material(ChinaTown_Ground_ground_road)
{
	mapTo = "ground.road";

	diffuseMap[0] = "art/textures/structures/ground/road.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	pixelSpecular[0] = 1;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   detailMap[0] = "art/textures/structures/detail.dds";
   detailScale[0] = "5 5";
   detailNormalMap[0] = "art/textures/structures/detail_normal.dds";
   materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_Ground_ground_brokenWall)
{
	mapTo = "ground.brokenWall";

	diffuseMap[0] = "art/textures/structures/brokenWall/brokenWalls_diffuse.dds";
	normalMap[0] = "art/textures/structures/brokenWall/brokenWals_nomrals.dds";
	specularMap[0] = "art/textures/structures/brokenWall/brokenWalls_spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 24;
	pixelSpecular[0] = 1;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   detailScale[0] = "20 20";
   detailNormalMap[0] = "art/textures/structures/detail_normal.dds";
   detailNormalMapStrength[0] = "-2";
   materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_Ground_props_temple)
{
	mapTo = "props.temple";

	diffuseMap[0] = "art/shapes/props/Temple/Temple_Diff.dds";
	normalMap[0] = "art/shapes/props/Temple/Temple_Norm.dds";
	specularMap[0] = "art/shapes/props/Temple/Temple_Spec.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 24;
	pixelSpecular[0] = 1;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_Ground_ground_ground_cobble_edge)
{
	mapTo = "ground.ground_cobble_edge";

	diffuseMap[0] = "art/textures/structures/ground/cobble_Edge_diffuse.dds";
	normalMap[0] = "";
	specularMap[0] = "art/textures/structures/ground/cobble_Edge_specular.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 41;
	pixelSpecular[0] = 1;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_Ground_ground_ground_crakedTiles)
{
	mapTo = "ground.ground_crakedTiles";

	diffuseMap[0] = "art/textures/structures/ground/crakedTiles2_diffuse.dds";
	normalMap[0] = "art/textures/structures/ground/crakedTiles2_normals.dds";
	specularMap[0] = "art/textures/structures/ground/crakedTiles2_specular.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 64;
	pixelSpecular[0] = 1;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   detailScale[0] = "8 8";
   detailNormalMap[0] = "art/textures/structures/detail_normal.dds";
   materialTag0 = "Chinatown";
};

singleton Material(ChinaTown_Ground_ground_ground_grass)
{
	mapTo = "ground.ground_grass";

	diffuseMap[0] = "art/textures/structures/ground/grass2_diffuse.dds";
	normalMap[0] = "art/textures/structures/ground/grass2_normals.dds";
	specularMap[0] = "art/textures/structures/ground/grass2_specular.dds";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 1;
	pixelSpecular[0] = false;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   detailMap[0] = "art/textures/structures/detail.dds";
   detailScale[0] = "10 10";
   detailNormalMap[0] = "art/textures/structures/detail_normal.dds";
   detailNormalMapStrength[0] = "5";
   materialTag0 = "Chinatown";
};

//--- ChinaTown_Ground.dae MATERIALS END ---


singleton Material(tramTracks)
{
   mapTo = "railings_tramTracks";
   diffuseMap[0] = "core/art/warnmat";
   specularPower[0] = "8";
   pixelSpecular[0] = "0";
   normalMap[0] = "";
   specular[0] = "1 1 1 1";
   materialTag0 = "Chinatown";
};
//--- ChinaTown_CrashSite.dae MATERIALS BEGIN ---
singleton Material(ChinaTown_CrashSite_Debri_crakedEarth)
{
	mapTo = "Debri.crakedEarth";

	diffuseMap[0] = "art/textures/structures/crashSite/paving_Crash_Decal_03";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   alphaTest = "1";
   alphaRef = "114";
   materialTag0 = "Chinatown";
};

//--- ChinaTown_CrashSite.dae MATERIALS END ---


singleton Material(ChinaTown_CrashSite_Debri_blownUpCar02)
{
   mapTo = "Debri.blownUpCar02";
   diffuseMap[0] = "art/shapes/props/Car/CarDestroyed_D.dds";
   normalMap[0] = "art/shapes/props/Car/CarDestroyed_N.dds";
   specularMap[0] = "art/shapes/props/Car/CarDestroyed_D.dds";
   specular[0] = "1 1 1 0";
   specularPower[0] = "1";
   pixelSpecular[0] = "1";
   translucentBlendOp = "None";
   materialTag0 = "Chinatown";
};


singleton Material(newMaterial5)
{
   mapTo = "Debri.brokenPavement";
   diffuseMap[0] = "art/textures/structures/crashSite/Pavement_Diff";
   normalMap[0] = "art/textures/structures/crashSite/Pavement_normals";
   specularPower[0] = "96";
   pixelSpecular[0] = "1";
   specularMap[0] = "art/textures/structures/crashSite/Pavement_Diff.tga";
   materialTag0 = "Chinatown";
};

singleton Material(newMaterial9)
{
   mapTo = "Debri.blownUpCar";
   diffuseMap[0] = "art/textures/structures/crashSite/BlownUpCar_Col";
   normalMap[0] = "art/textures/structures/crashSite/BlownUpCar_Normal.png";
   specularPower[0] = "1";
   pixelSpecular[0] = "1";
   specularMap[0] = "art/textures/structures/crashSite/BlownUpCar_spec";
   materialTag0 = "Chinatown";
};

singleton Material(newMaterial11)
{
   mapTo = "Debri.brokenBrickRoad";
   diffuseMap[0] = "art/textures/structures/crashSite/BrokenBrickRoad_Col";
   normalMap[0] = "art/textures/structures/crashSite/BrokenBrickRoad_normal";
   specularPower[0] = "39";
   pixelSpecular[0] = "1";
   specularMap[0] = "art/textures/structures/crashSite/BrokenBrickRoad_Spec";
   materialTag0 = "Chinatown";
};


singleton Material(glass)
{
   mapTo = "windows.GlassPanes";
   diffuseMap[0] = "art/shapes/props/Glass/glass_Diffuse.dds";
   doubleSided = "0";
   translucent = "1";
   constantCubemapGloss = 0.2; 
   cubemap = "refNightSkyCubemap";
   detailScale[0] = "5 5";
   detailNormalMapStrength[0] = "5";
   specular[0] = "0.184314 0.184314 0.184314 1";
   specularPower[0] = "31";
   pixelSpecular[0] = "1";
   diffuseColor[0] = "1 1 1 0";

   materialTag0 = "Chinatown";
};


singleton Material(grass_grass)
{
	mapTo = "grass";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- grass.dae MATERIALS END ---

//--- CT_building_001.dae MATERIALS BEGIN ---
singleton Material(CT_building_001_allBorders)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	useAnisotropic[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_001_props_allProps)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;
	useAnisotropic[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_001_allBordersLOD)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	useAnisotropic[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_001_props_allPropsLOD)
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
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_001_LOD__001_buildingLOD3)
{
	mapTo = "LOD._001_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_001_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_001.dae MATERIALS END ---

//--- CT_building_002.dae MATERIALS BEGIN ---
singleton Material(CT_building_002_LOD__002_buildingLOD3)
{
	mapTo = "LOD._002_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_002_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   castShadows = "1";
   materialTag0 = "Chinatown";
};

//--- CT_building_002.dae MATERIALS END ---

//--- CT_building_003.dae MATERIALS BEGIN ---
singleton Material(CT_building_003_LOD__003_buildingLOD3)
{
	mapTo = "LOD._003_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_003_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   castShadows = "1";
   materialTag0 = "Chinatown";
};

//--- CT_building_003.dae MATERIALS END ---

//--- CT_building_004.dae MATERIALS BEGIN ---
singleton Material(CT_building_004_LOD__004_buildingLOD3)
{
	mapTo = "LOD._004_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_004_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   castShadows = "1";
   materialTag0 = "Chinatown";
};

//--- CT_building_004.dae MATERIALS END ---

//--- CT_building_005.dae MATERIALS BEGIN ---
singleton Material(CT_building_005_LOD__005_buildingLOD3)
{
	mapTo = "LOD._005_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_005_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   castShadows = "1";
   materialTag0 = "Chinatown";
};

//--- CT_building_005.dae MATERIALS END ---

//--- CT_building_006.dae MATERIALS BEGIN ---
singleton Material(CT_building_006_LOD__006_buildingLOD3)
{
	mapTo = "LOD._006_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_006_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   castShadows = "1";
   materialTag0 = "Chinatown";
};

//--- CT_building_006.dae MATERIALS END ---

//--- CT_building_007.dae MATERIALS BEGIN ---
singleton Material(CT_building_007_LOD__007_buildingLOD3)
{
	mapTo = "LOD._007_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_007_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   castShadows = "1";
   materialTag0 = "Chinatown";
};

//--- CT_building_007.dae MATERIALS END ---

//--- CT_building_008.dae MATERIALS BEGIN ---
singleton Material(CT_building_008_LOD__008_buildingLOD3)
{
	mapTo = "LOD._008_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_008_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   castShadows = "1";
   materialTag0 = "Chinatown";
};

//--- CT_building_008.dae MATERIALS END ---

//--- CT_building_009.dae MATERIALS BEGIN ---
singleton Material(CT_building_009_LOD__009_buildingLOD3)
{
	mapTo = "LOD._009_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_009_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_009.dae MATERIALS END ---

//--- CT_building_010.dae MATERIALS BEGIN ---
singleton Material(CT_building_010_props_dragonStatue)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_010_props_dragonStatueLOD)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_010.dae MATERIALS END ---

//--- CT_building_011.dae MATERIALS BEGIN ---
singleton Material(CT_building_011_windows_GlassPanesLOD)
{
	mapTo = "windows.GlassPanesLOD";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_011.dae MATERIALS END ---

//--- CT_building_012.dae MATERIALS BEGIN ---
singleton Material(CT_building_012_LODS__012_buildingLOD3)
{
	mapTo = "LODS._012_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_012_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_012.dae MATERIALS END ---

//--- CT_building_013.dae MATERIALS BEGIN ---
singleton Material(CT_building_013_interiors_floor_2)
{
	mapTo = "interiors.floor_2";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "0 0 0 0";
	specularPower[0] = 128;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_013.dae MATERIALS END ---

//--- CT_building_014.dae MATERIALS BEGIN ---
singleton Material(CT_building_014_LOD__014_buildingLOD3)
{
	mapTo = "LOD._014_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_014_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_014.dae MATERIALS END ---

//--- CT_building_015.dae MATERIALS BEGIN ---
singleton Material(CT_building_015_LODS__015_buildingLOD3)
{
	mapTo = "LODS._015_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_015_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 1";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_015.dae MATERIALS END ---

//--- CT_building_038.dae MATERIALS BEGIN ---


//--- CT_building_038.dae MATERIALS END ---

//--- CT_building_016.dae MATERIALS BEGIN ---
singleton Material(CT_building_016_walls_brick_005)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_016_walls_brick_005LOD)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_016_LOD__016_buildingLOD3)
{
	mapTo = "LOD._016_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_016_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.819608 0.819608 0.819608 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   castShadows = "1";
   materialTag0 = "Chinatown";
};

//--- CT_building_016.dae MATERIALS END ---

//--- CT_building_017.dae MATERIALS BEGIN ---
singleton Material(CT_building_017_walls_brick_002)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_017_walls_plaster_004)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_017_walls_plaster_004LOD)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_017_walls_brick_002LOD)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_017_LODS__017_buildingLOD3)
{
	mapTo = "LODS._017_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_017_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   castShadows = "1";
   materialTag0 = "Chinatown";
};

//--- CT_building_017.dae MATERIALS END ---

//--- CT_building_018.dae MATERIALS BEGIN ---
singleton Material(CT_building_018_walls_plaster_005)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_018_walls_brick_004)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_018_walls_brick_004LOD)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_018_walls_plaster_005LOD)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_018_LODS__018_buildingLOD3)
{
	mapTo = "LODS._018_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_018_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.72549 0.72549 0.72549 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   castShadows = "1";
   materialTag0 = "Chinatown";
};

//--- CT_building_018.dae MATERIALS END ---

//--- CT_building_019.dae MATERIALS BEGIN ---
singleton Material(CT_building_019_LODS__019_buildingLOD3)
{
	mapTo = "LODS._019_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_019_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   castShadows = "1";
   materialTag0 = "Chinatown";
};

//--- CT_building_019.dae MATERIALS END ---

//--- CT_building_020.dae MATERIALS BEGIN ---


singleton Material(CT_building_020_LODS__020_buildingLOD3)
{
	mapTo = "LODS._020_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_020_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_020.dae MATERIALS END ---

//--- CT_building_021.dae MATERIALS BEGIN ---
singleton Material(CT_building_021_LODS__021_buildingLOD3)
{
	mapTo = "LODS._021_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_021_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_021.dae MATERIALS END ---

//--- CT_building_022.dae MATERIALS BEGIN ---
singleton Material(CT_building_022_LODS__022_buildingLOD3)
{
	mapTo = "LODS._022_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_022_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_022.dae MATERIALS END ---

//--- CT_building_023.dae MATERIALS BEGIN ---
singleton Material(CT_building_023_walls_plaster_003)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_023_walls_brick_003)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_023_walls_brick_003LOD)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_023_walls_plaster_003LOD)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_023_LODS__023_buildingLOD3)
{
	mapTo = "LODS._023_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_023_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_023.dae MATERIALS END ---

//--- CT_building_024.dae MATERIALS BEGIN ---
singleton Material(CT_building_024_LODS__024_buildingLOD3)
{
	mapTo = "LODS._024_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_024_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_024.dae MATERIALS END ---

//--- CT_building_025.dae MATERIALS BEGIN ---


singleton Material(CT_building_025_LODS__025_buildingLOD3)
{
	mapTo = "LODS._025_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_025_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_025.dae MATERIALS END ---

//--- CT_building_026.dae MATERIALS BEGIN ---
singleton Material(CT_building_026_LODS__026_buildingLOD3)
{
	mapTo = "LODS._026_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_026_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_026.dae MATERIALS END ---

//--- CT_building_027.dae MATERIALS BEGIN ---
singleton Material(CT_building_027_LODS__027_buildingLOD3)
{
	mapTo = "LODS._027_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_027_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_027.dae MATERIALS END ---

//--- CT_building_028.dae MATERIALS BEGIN ---
singleton Material(CT_building_028_walls_plaster_002)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_028_walls_plaster_002LOD)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};


singleton Material(CT_building_028_LODS__028_buildingLOD3)
{
	mapTo = "LODS._028_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_028_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_028.dae MATERIALS END ---

//--- CT_building_029.dae MATERIALS BEGIN ---
singleton Material(CT_building_029_LODS__029_buildingLOD3)
{
	mapTo = "LODS._029_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_029_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   castShadows = "1";
   materialTag0 = "Chinatown";
};

//--- CT_building_029.dae MATERIALS END ---

//--- CT_building_030.dae MATERIALS BEGIN ---
singleton Material(CT_building_030_LODS__30_buildingLOD3)
{
	mapTo = "LODS._30_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_030_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.666667 0.647059 0.623529 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_030.dae MATERIALS END ---

//--- CT_building_031.dae MATERIALS BEGIN ---
singleton Material(CT_building_031_LODS__031_buildingLOD3)
{
	mapTo = "LODS._031_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_031_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_031.dae MATERIALS END ---

//--- CT_building_032.dae MATERIALS BEGIN ---


singleton Material(CT_building_032_LODS__032_buildingLOD3)
{
	mapTo = "LODS._032_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_032_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_032.dae MATERIALS END ---

//--- CT_building_034.dae MATERIALS BEGIN ---
singleton Material(CT_building_034_LODS__034_buildingLOD3)
{
	mapTo = "LODS._034_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_034_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_034.dae MATERIALS END ---

//--- CT_building_035.dae MATERIALS BEGIN ---
singleton Material(CT_building_035_LODS__035_buildingLOD3)
{
	mapTo = "LODS._035_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_035_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_035.dae MATERIALS END ---

//--- CT_building_036.dae MATERIALS BEGIN ---
singleton Material(CT_building_036_LODS__036_buildingLOD3)
{
	mapTo = "LODS._036_buildingLOD3";

	diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_036_buildingLOD3_albedo.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_036.dae MATERIALS END ---

//--- CT_building_033.dae MATERIALS BEGIN ---
singleton Material(CT_building_033_debri_blownUpBuilding)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_033_debri_blownUpBuildingLOD)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_033.dae MATERIALS END ---


singleton Material(allProps)
{
   mapTo = "props.allProps";
   diffuseMap[0] = "art/textures/structures/buildingProps/allProps_diffuse.dds";
   translucent = "1";
   alphaTest = "1";
   normalMap[0] = "art/textures/structures/buildingProps/allProps_norm.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/buildingProps/allPropss_spec.dds";
   alphaRef = "107";
   useAnisotropic[0] = true;
   diffuseColor[0] = "0.639216 0.639216 0.639216 1";
   constantCubemapGloss = "0.2";
   specularPower[0] = "6";
   castShadows = "1";
   translucentBlendOp = "None";
   //diffuseMap[1] = "art/textures/structures/buildingProps/allProps_glow_mask.dds";
   //glow[1] = "0";
   //emissive[1] = "1";
   //diffuseColor[1] = "1.25 1.25 1.25 1";
   materialTag0 = "Chinatown";
};

singleton Material(allBorders)
{
   mapTo = "allBorders";
   diffuseMap[0] = "art/textures/structures/borders/allBorders_diffuse.dds";
   alphaTest = "1";
   alphaRef = "26";
   normalMap[0] = "art/textures/structures/borders/allBorders_norm.dds";
   specularPower[0] = "14";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/borders/allBorders_spec.dds";
   useAnisotropic[0] = true;
   detailMap[0] = "";
   detailScale[0] = "30 30";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(brick_001)
{
   mapTo = "walls.brick_001";
   diffuseMap[0] = "art/textures/structures/walls/brick_001_diffuse.dds";
   normalMap[0] = "art/textures/structures/walls/brick_001_normal.dds";
   specularPower[0] = "1";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/walls/brick_001_spec.dds";
   overlayMap[0] = "art/textures/structures/walls/brickDirt02.dds";
   useAnisotropic[0] = true;
   diffuseColor[0] = "0.917647 0.917647 0.917647 1";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};


singleton Material(brick_004)
{
   mapTo = "walls.brick_004";
   diffuseMap[0] = "art/textures/structures/walls/brick_004_diffuse.dds";
   normalMap[0] = "art/textures/structures/walls/brick_004_normal.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/walls/brick_004_spec.dds";
   overlayMap[0] = "art/textures/structures/walls/brickDirt02.dds";
   useAnisotropic[0] = true;
   specularPower[0] = "34";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};



singleton Material(plaster_003)
{
   mapTo = "walls.plaster_003";
   diffuseMap[0] = "art/textures/structures/walls/plaster_003_diffuse.dds";
   normalMap[0] = "art/textures/structures/walls/plaster_all_normal.dds";
   specularMap[0] = "art/textures/structures/walls/plaster_all_specular.dds";
   overlayMap[0] = "art/textures/structures/walls/plasterDirt02.dds";
   diffuseColor[0] = "0.788235 0.788235 0.788235 1";
   specularPower[0] = "14";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(brick_005)
{
   mapTo = "walls.brick_005";
   diffuseMap[0] = "art/textures/structures/walls/brick_005_diffuse.dds";
   normalMap[0] = "art/textures/structures/walls/brick_005_normal.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/walls/brick_005_spec.dds";
   specularPower[0] = "16";
   overlayMap[0] = "art/textures/structures/walls/brickDirt02.dds";
   useAnisotropic[0] = true;
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(brick_002)
{
   mapTo = "walls.brick_002";
   diffuseMap[0] = "art/textures/structures/walls/brick_002_diffuse.dds";
   normalMap[0] = "art/textures/structures/walls/brick_002_normal.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/walls/brick_002_spec.dds";
   overlayMap[0] = "art/textures/structures/walls/brickDirt02.dds";
   useAnisotropic[0] = true;
   diffuseColor[0] = "0.00392157 0.00392157 0.00392157 0";
   specularPower[0] = "1";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(plaster_002)
{
   mapTo = "walls.plaster_002";
   diffuseMap[0] = "art/textures/structures/walls/plaster_002_diffuse.dds";
   normalMap[0] = "art/textures/structures/walls/plaster_all_normal.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/walls/plaster_all_specular.dds";
   overlayMap[0] = "art/textures/structures/walls/plasterDirt02.dds";
   specularPower[0] = "1";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(plaster_004)
{
   mapTo = "walls.plaster_004";
   diffuseMap[0] = "art/textures/structures/walls/plaster_004_diffuse.dds";
   normalMap[0] = "art/textures/structures/walls/plaster_all_normal.dds";
   specularMap[0] = "art/textures/structures/walls/plaster_all_specular.dds";
   overlayMap[0] = "art/textures/structures/walls/plasterDirt02.dds";
   materialTag0 = "Chinatown";
};

singleton Material(plaster_005)
{
   mapTo = "walls.plaster_005";
   diffuseMap[0] = "art/textures/structures/walls/plaster_005_diffuse.dds";
   overlayMap[0] = "art/textures/structures/walls/plasterDirt02.dds";
   normalMap[0] = "art/textures/structures/walls/plaster_all_normal.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/walls/plaster_all_specular.dds";
   specularPower[0] = "21";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};


singleton Material(brick_003)
{
   mapTo = "walls.brick_003";
   diffuseMap[0] = "art/textures/structures/walls/brick_003_diffuse.dds";
   normalMap[0] = "art/textures/structures/walls/brick_003_normal.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/walls/brick_003_specular.dds";
   overlayMap[0] = "art/textures/structures/walls/brickDirt02.dds";
   useAnisotropic[0] = true;
   diffuseColor[0] = "0.772549 0.772549 0.772549 1";
   constantCubemapGloss = "0.2";
   specularPower[0] = "16";
   materialTag0 = "Chinatown";
};

singleton Material(allBordersLOD)
{
   mapTo = "allBordersLOD";
   diffuseMap[0] = "art/textures/structures/borders/allBorders_diffuse.dds";
   alphaTest = "1";
   alphaRef = "26";
   useAnisotropic[0] = true;
   detailMap[0] = "";
   detailScale[0] = "30 30";
   useAnisotropic[0] = true;
   materialTag0 = "Chinatown";
};

singleton Material(plaster_003LOD)
{
   mapTo = "walls.plaster_003LOD";
   diffuseMap[0] = "art/textures/structures/walls/plaster_003_diffuse.dds";
   overlayMap[0] = "art/textures/structures/walls/plasterDirt02.dds";
   useAnisotropic[0] = true;
   diffuseColor[0] = "0.603922 0.603922 0.603922 1";
   materialTag0 = "Chinatown";
};

singleton Material(allPropsLOD)
{
   mapTo = "props.allPropsLOD";
   diffuseMap[0] = "art/textures/structures/buildingProps/allProps_diffuse.dds";
   alphaTest = "1";
   alphaRef = "107";
   useAnisotropic[0] = 0;
   translucentBlendOp = "None";
   constantCubemapGloss = "0.2";
   castShadows = "0";
   translucent = "0";
   diffuseColor[0] = "0.64 0.64 0.64 1";
   specularPower[0] = "1";
   materialTag0 = "Chinatown";
};

singleton Material(brick_001LOD)
{
   mapTo = "walls.brick_001LOD";
   diffuseMap[0] = "art/textures/structures/walls/brick_001_diffuse.dds";
   overlayMap[0] = "art/textures/structures/walls/brickDirt01.dds";
   useAnisotropic[0] = true;
   useAnisotropic[0] = true;
   diffuseColor[0] = "0.784314 0.784314 0.784314 1";
   materialTag0 = "Chinatown";
};

singleton Material(brick_004LOD)
{
   mapTo = "walls.brick_004LOD";
   diffuseMap[0] = "art/textures/structures/walls/brick_004_diffuse.dds";
   diffuseColor[0] = "1 1 1 0";
   overlayMap[0] = "art/textures/structures/walls/brickDirt02.dds";
   useAnisotropic[0] = true;
   materialTag0 = "Chinatown";
};

singleton Material(concrete_001LOD)
{
   mapTo = "walls.concrete_001LOD";
   diffuseMap[0] = "art/textures/structures/concrete/concrete_001.dds";
   useAnisotropic[0] = true;
   materialTag0 = "Chinatown";
};



singleton Material(brick_002LOD)
{
   mapTo = "walls.brick_002LOD";
   diffuseMap[0] = "art/textures/structures/walls/brick_002_diffuse.dds";
   useAnisotropic[0] = true;
   overlayMap[0] = "art/textures/structures/walls/brickDirt02.dds";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(brick_005LOD)
{
   mapTo = "walls.brick_005LOD";
   diffuseMap[0] = "art/textures/structures/walls/brick_005_diffuse.dds";
   useAnisotropic[0] = true;
   materialTag0 = "Chinatown";
};

singleton Material(plaster_002LOD)
{
   mapTo = "walls.plaster_002LOD";
   diffuseMap[0] = "art/textures/structures/walls/plaster_002_diffuse.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "";
   normalMap[0] = "";
   overlayMap[0] = "art/textures/structures/walls/plasterDirt02.dds";
   useAnisotropic[0] = true;
   diffuseColor[0] = "0.996078 0.996078 0.996078 1";
   materialTag0 = "Chinatown";
};


singleton Material(concrete_001)
{
   mapTo = "walls.concrete_001";
   diffuseMap[0] = "art/textures/structures/concrete/concrete_001.dds";
   normalMap[0] = "art/textures/structures/walls/concrete_normal.dds";
   specularPower[0] = "61";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/walls/concrete_spec.dds";
   useAnisotropic[0] = true;
   detailScale[0] = "6 6";
   detailNormalMap[0] = "art/textures/structures/concreteDetail_normal.dds";
   detailNormalMapStrength[0] = "2";
   materialTag0 = "Chinatown";
};

singleton Material(plaster_004LOD)
{
   mapTo = "walls.plaster_004LOD";
   diffuseMap[0] = "art/textures/structures/walls/plaster_004_diffuse.dds";
   useAnisotropic[0] = true;
   materialTag0 = "Chinatown";
};

singleton Material(brick_003LOD)
{
   mapTo = "walls.brick_003LOD";
   diffuseMap[0] = "art/textures/structures/walls/brick_003_diffuse.dds";
   overlayMap[0] = "art/textures/structures/walls/brickDirt02.dds";
   useAnisotropic[0] = true;
   diffuseColor[0] = "0.768628 0.768628 0.768628 1";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(plaster_001LOD)
{
   mapTo = "walls.plaster_001LOD";
   diffuseMap[0] = "art/textures/structures/walls/plaster_001_diffuse.dds";
   useAnisotropic[0] = true;
   materialTag0 = "Chinatown";
};


singleton Material(plaster_005LOD)
{
   mapTo = "walls.plaster_005LOD";
   diffuseMap[0] = "art/textures/structures/walls/plaster_005_diffuse.dds";
   useAnisotropic[0] = true;
   materialTag0 = "Chinatown";
};

singleton Material(interiorWall_003LOD)
{
   mapTo = "interiors.intWall_003LOD";
   diffuseMap[0] = "art/textures/structures/interiorWalls/intWall03_Diffuse.dds";
   useAnisotropic[0] = true;
   doubleSided = "1";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(interiorWall_001LOD)
{
   mapTo = "interiors.intWall_001LOD";
   diffuseMap[0] = "art/textures/structures/interiorWalls/intWall01_Diffuse.dds";
   useAnisotropic[0] = true;
   materialTag0 = "Chinatown";
};

singleton Material(interiorWall_002LOD)
{
   mapTo = "interiors.intWall_002LOD";
   diffuseMap[0] = "art/textures/structures/interiorWalls/intWall02_Diffuse.dds";
   useAnisotropic[0] = true;
   materialTag0 = "Chinatown";
};

singleton Material(interiorWall_004LOD)
{
   mapTo = "interiors.intWall_004LOD";
   diffuseMap[0] = "art/textures/structures/interiorWalls/intWall04_Diffuse.dds";
   overlayMap[0] = "art/textures/structures/walls/brickDirt02.dds";
   useAnisotropic[0] = true;
   materialTag0 = "Chinatown";
};

singleton Material(interiorWall_005LOD)
{
   mapTo = "interiors.intWall_005LOD";
   diffuseMap[0] = "art/textures/structures/interiorWalls/intWall05_Diffuse.dds";
   materialTag0 = "Chinatown";
};

singleton Material(interiorWall_006LOD)
{
   mapTo = "interiors.intWall_006LOD";
   diffuseMap[0] = "art/textures/structures/interiorWalls/intWall06_Diffuse.dds";
   materialTag0 = "Chinatown";
};

singleton Material(Floor_001LOD)
{
   mapTo = "interiors.floor_001LOD";
   diffuseMap[0] = "art/textures/structures/floors/tiles_001.dds";
   diffuseColor[0] = "0.435294 0.435294 0.435294 1";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(floor_002LOD)
{
   mapTo = "interiors.floor_002LOD";
   diffuseMap[0] = "art/textures/structures/floors/tiles_002.dds";
   materialTag0 = "Chinatown";
};

singleton Material(ceiling_002LOD)
{
   mapTo = "interiors.ceiling_002LOD";
   diffuseMap[0] = "art/textures/structures/ceilings/ceiling_diffuse_002.dds";
   materialTag0 = "Chinatown";
};

singleton Material(_037_buildingLOD3)
{
   mapTo = "LODS._037_buildingLOD3";
   diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_037_buildingLOD3_albedo.dds";
   materialTag0 = "Chinatown";
};

singleton Material(blownUpBuilding)
{
   mapTo = "debri.blownUpBuilding";
   diffuseMap[0] = "art/textures/structures/blownUpBuilding/blownUpBuilding_diffuse.dds";
   normalMap[0] = "art/textures/structures/blownUpBuilding/blownUpBuilding_normals.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/blownUpBuilding/blownUpBuilding_spec.dds";
   specularPower[0] = "49";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(blownUpBuildingLOD)
{
   mapTo = "debri.blownUpBuildingLOD";
   diffuseMap[0] = "art/textures/structures/blownUpBuilding/blownUpBuilding_diffuse.dds";
   materialTag0 = "Chinatown";
};

singleton Material(_033_buildingLOD3)
{
   mapTo = "LODS._033_buildingLOD3";
   diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_033_buildingLOD3_albedo.dds";
   materialTag0 = "Chinatown";
};

singleton Material(dragonPillar)
{
   mapTo = "props.dragonStatue";
   diffuseMap[0] = "art/shapes/props/dragonPillar/DragonPillar_Diffuse.dds";
   normalMap[0] = "art/shapes/props/dragonPillar/DragonPillar_normals.dds";
   specularMap[0] = "art/shapes/props/dragonPillar/DragonPillar_Specular.dds";
   doubleSided = "1";
   alphaTest = "1";
   alphaRef = "0";
   pixelSpecular[0] = "0";
   specularPower[0] = "16";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(dragonPillarLOD)
{
   mapTo = "props.dragonStatueLOD";
   diffuseMap[0] = "art/shapes/props/dragonPillar/DragonPillar_Diffuse.dds";
   castShadows = "0";
   materialTag0 = "Chinatown";
};

singleton Material(_010_buildingLOD3)
{
   mapTo = "LODS._010_buildingLOD3";
   diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_010_buildingLOD3_albedo.dds";
   materialTag0 = "Chinatown";
};
//--- ChinaTown_heliBuilding.dae MATERIALS BEGIN ---
singleton Material(ChinaTown_heliBuilding_Debri_blownUpBuilding02)
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
	materialTag0 = "Chinatown";
};

//--- ChinaTown_heliBuilding.dae MATERIALS END ---

//--- CT_Interior_001.dae MATERIALS BEGIN ---
singleton Material(CT_Interior_001_floor_001)
{
	mapTo = "floor_001";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_001_intWall_006)
{
	mapTo = "intWall_006";

	diffuseMap[0] = "art/textures/structures/interiorWalls/intWall06_Diffuse.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_001_stairs)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_001_ceiling_001)
{
	mapTo = "ceiling_001";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_001_floor_002)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 0 0.5";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_001_ceiling_002)
{
	mapTo = "ceiling_002";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_001_intWall_001)
{
	mapTo = "intWall_001";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_Interior_001.dae MATERIALS END ---

//--- CT_Interior_002.dae MATERIALS BEGIN ---
singleton Material(CT_Interior_002_windows_windowsDoors)
{
	mapTo = "windows_windowsDoors";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	useAnisotropic[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_002_interiors_ceiling_001)
{
	mapTo = "interiors_ceiling_001";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_002_interiors_intWall_002)
{
	mapTo = "interiors_intWall_002";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_002_interiors_floor_001)
{
	mapTo = "interiors_floor_001";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_002_interiors_intWall_003)
{
	mapTo = "interiors_intWall_003";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_002_interiors_intWall_006)
{
	mapTo = "interiors_intWall_006";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_002_interiors_floor_002)
{
	mapTo = "interiors_floor_002";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_Interior_002.dae MATERIALS END ---

//--- CT_Interior_006.dae MATERIALS BEGIN ---
singleton Material(CT_Interior_006_intWall_005)
{
	mapTo = "intWall_005";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_006_floor_003)
{
	mapTo = "floor_003";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_006_intWall_003)
{
	mapTo = "intWall_003";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_Interior_006.dae MATERIALS END ---

//--- CS_BackPropeller03.dae MATERIALS BEGIN ---
singleton Material(CS_BackPropeller03_BrokenPave)
{
	mapTo = "unmapped_mat";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CS_BackPropeller03.dae MATERIALS END ---

//--- CS_brokenPavment.dae MATERIALS BEGIN ---
singleton Material(CS_brokenPavment_BrokenTiles)
{
	mapTo = "BrokenTiles";

	diffuseMap[0] = "art/textures/structures/crashSite/Pavement_Diff.dds";
	normalMap[0] = "art/textures/structures/crashSite/Pavement_normals.dds";
	specularMap[0] = "art/textures/structures/specmask.dds";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 31;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "0";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

//--- CS_brokenPavment.dae MATERIALS END ---

//--- CS_cars.dae MATERIALS BEGIN ---
singleton Material(CS_cars_BurntCars)
{
	mapTo = "BurntCars";

	diffuseMap[0] = "art/shapes/props/Car/CarDestroyed_D.dds";
	normalMap[0] = "art/shapes/props/Car/CarDestroyed_N.dds";
	specularMap[0] = "art/shapes/props/Car/CarDestroyed_D.dds";

	diffuseColor[0] = "1.0 1.0 1.0 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "0";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "CT_Car";
};

singleton Material(CS_cars_Bakie)
{
	mapTo = "Bakie";

	diffuseMap[0] = "art/textures/structures/crashSite/BlownUpCar_Col.dds";
	normalMap[0] = "art/textures/structures/crashSite/BlownUpCar_Normal.dds";
	specularMap[0] = "art/textures/structures/crashSite/BlownUpCar_spec.dds";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "1";
   materialTag0 = "Chinatown";
};

//--- CS_cars.dae MATERIALS END ---

//--- CT_MainSquare.dae MATERIALS BEGIN ---
singleton Material(CT_MainSquare_ground_ground_crakedTiles)
{
	mapTo = "ground_ground_crakedTiles";

	diffuseMap[0] = "art/textures/structures/ground/crakedTiles_diffuse.dds";
	normalMap[0] = "art/textures/structures/ground/crakedTiles_normals.dds";
	specularMap[0] = "art/textures/structures/ground/crakedTiles_specular.dds";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 51;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "1";
   materialTag0 = "Chinatown";
};

singleton Material(CT_MainSquare_ground_ground_grass)
{
	mapTo = "ground_ground_grass";

	diffuseMap[0] = "art/textures/structures/ground/grass2_diffuse.dds";
	normalMap[0] = "art/textures/structures/ground/grass_002_normals.dds";
	specularMap[0] = "art/textures/structures/ground/grass_002_specular.dds";

	diffuseColor[0] = "0.4 0.4 0.4 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 39;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "0";
   detailScale[0] = "5 5";
   detailNormalMapStrength[0] = "0.5";
   materialTag0 = "Chinatown";
};

singleton Material(CT_MainSquare_ground_brokenWall)
{
	mapTo = "ground_brokenWall";

	diffuseMap[0] = "art/textures/structures/brokenWall/brokenWalls_diffuse.dds";
	normalMap[0] = "art/textures/structures/brokenWall/brokenWals_nomrals.dds";
	specularMap[0] = "art/textures/structures/brokenWall/brokenWalls_spec.dds";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "0";
   materialTag0 = "Chinatown";
};

singleton Material(CT_MainSquare_props_temple)
{
	mapTo = "props_temple";

	diffuseMap[0] = "art/shapes/props/Temple/Temple_Diff.dds";
	normalMap[0] = "art/shapes/props/Temple/Temple_Norm.dds";
	specularMap[0] = "art/shapes/props/Temple/Temple_Spec.dds";

	diffuseColor[0] = "0.866667 0.866667 0.866667 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "0";
   materialTag0 = "Chinatown";
};

singleton Material(CT_MainSquare_walls_concrete_001)
{
	mapTo = "walls_concrete_001";

	diffuseMap[0] = "art/textures/structures/concrete/concrete_001.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;
	useAnisotropic[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_MainSquare_ground_ground_cobble_edge)
{
	mapTo = "ground_ground_cobble_edge";

	diffuseMap[0] = "art/textures/structures/ground/cobble_Edge_diffuse.dds";
	normalMap[0] = "art/textures/structures/ground/cobble_Edge_normal.dds";
	specularMap[0] = "art/textures/structures/ground/cobble_Edge_specular.dds";

	diffuseColor[0] = "0.396078 0.396078 0.396078 1";
	specular[0] = "0 0 0 0";
	specularPower[0] = 46;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "0";
   emissive[0] = "0";
   materialTag0 = "Chinatown";
};

//--- CT_MainSquare.dae MATERIALS END ---



singleton Material(ceiling_002)
{
   mapTo = "interiors.ceiling_002";
   diffuseMap[0] = "art/textures/structures/ceilings/ceiling_diffuse_002.dds";
   materialTag0 = "Chinatown";
};

singleton Material(_011_buildingLOD3)
{
   mapTo = "LODS._011_buildingLOD3";
   diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_011_buildingLOD3_albedo.dds";
   materialTag0 = "Chinatown";
};

singleton Material(heli_building)
{
   mapTo = "Debri.blownUpBuilding02";
   diffuseMap[0] = "art/textures/structures/crashSite/CrashedBuilding_Col.dds";
   normalMap[0] = "art/textures/structures/crashSite/CrashedBuilding_Normal.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/crashSite/CrashedBuilding_Spec.dds";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(heli_paving)
{
   mapTo = "BrokenPave";
   diffuseMap[0] = "art/textures/structures/crashSite/BrokenBrickRoad_Col.dds";
   normalMap[0] = "art/textures/structures/crashSite/BrokenBrickRoad_normal.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/crashSite/BrokenBrickRoad_Spec.dds";
   specularPower[0] = "34";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};
//--- CS_rubble.dae MATERIALS BEGIN ---
singleton Material(CS_rubble_allProps)
{
	mapTo = "allProps";

	diffuseMap[0] = "art/textures/structures/buildingProps/allProps_diffuse";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CS_rubble.dae MATERIALS END ---

//--- CT_Ground.dae MATERIALS BEGIN ---
singleton Material(CT_Ground_ground_paving)
{
	mapTo = "ground_paving";

	diffuseMap[0] = "art/textures/structures/ground/paving_diffuse.dds";
	normalMap[0] = "art/textures/structures/ground/paving_norm.dds";
	specularMap[0] = "art/textures/structures/ground/paving_spec.dds";

	diffuseColor[0] = "0.592157 0.592157 0.592157 1";
	specular[0] = "0 0 0 0";
	specularPower[0] = 14;
	useAnisotropic[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "0";
   detailScale[0] = "1 1";
   detailNormalMap[0] = "art/textures/structures/ground/paving_norm.dds";
   detailNormalMapStrength[0] = "0.5";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(CT_Ground_ground_pavement)
{
	mapTo = "ground_pavement";

	diffuseMap[0] = "art/textures/structures/ground/pavement_diffuse.dds";
	normalMap[0] = "art/textures/structures/ground/pavement_normal.dds";
	specularMap[0] = "art/textures/structures/ground/pavement_spec.dds";

	diffuseColor[0] = "0.870588 0.870588 0.870588 1";
	specular[0] = "0 0 0 0";
	specularPower[0] = 6;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "0";
   detailScale[0] = "1 1";
   detailNormalMap[0] = "art/textures/structures/ground/pavement_normal.dds";
   detailNormalMapStrength[0] = "0.2";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(CT_Ground_ground_cobble)
{
	mapTo = "ground_cobble";

	diffuseMap[0] = "art/textures/structures/ground/cobble_diffuse.dds";
	normalMap[0] = "art/textures/structures/ground/cobble_normal.dds";
	specularMap[0] = "art/textures/structures/ground/cobble_specular.dds";

	diffuseColor[0] = "0.494118 0.494118 0.494118 1";
	specular[0] = "0 0 0 0";
	specularPower[0] = 4;
	useAnisotropic[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "0";
   constantCubemapGloss = "0.2";
   parallaxScale[0] = "0.0555556";
   customFootstepSound = "playerFootstepPlaylist";
   materialTag0 = "Chinatown";
};

singleton Material(CT_Ground_ground_road)
{
	mapTo = "ground_road";

	diffuseMap[0] = "art/textures/structures/ground/road.dds";
	//normalMap[0] = "art/textures/structures/ground/road_normal.dds";
	//specularMap[0] = "art/textures/structures/ground/road_spec.dds";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "0.243137 0.243137 0.243137 1";
	specularPower[0] = 41;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "1";
   detailScale[0] = "3 3";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(CT_Ground_ground_pavement_edge)
{
	mapTo = "ground_pavement_edge";

	diffuseMap[0] = "art/textures/structures/ground/pavement_edge_diffuse.dds";
	normalMap[0] = "art/textures/structures/ground/pavement_edge_normal.dds";
	specularMap[0] = "art/textures/structures/ground/pavement_edge_spec.dds";

	diffuseColor[0] = "0.615686 0.615686 0.615686 1";
	specular[0] = "0 0 0 0";
	specularPower[0] = 19;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "0";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

//--- CT_Ground.dae MATERIALS END ---



//--- CT_TramTracks.dae MATERIALS END ---



//--- CT_Interior_003.dae MATERIALS BEGIN ---
singleton Material(CT_Interior_003_interiors_intWall_005)
{
	mapTo = "interiors_intWall_005";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_Interior_003.dae MATERIALS END ---


singleton Material(Tracks)
{
   mapTo = "railings_tramTracks";
   diffuseMap[0] = "art/textures/structures/tramTracks/Rails.dds";
   pixelSpecular[0] = "1";
   materialTag0 = "Chinatown";
};

singleton Material(CrashBuilding)
{
   mapTo = "blownUpBuilding02";
   diffuseMap[0] = "art/textures/structures/crashSite/CrashedBuilding_Col.dds";
   normalMap[0] = "art/textures/structures/crashSite/CrashedBuilding_Normal.dds";
   specularMap[0] = "art/textures/structures/crashSite/CrashedBuilding_Spec.dds";
   parallaxScale[0] = "0";
   pixelSpecular[0] = "1";
   materialTag0 = "Chinatown";
};

singleton Material(Rubble)
{
   mapTo = "Rubble";
   diffuseMap[0] = "art/textures/structures/blownUpBuilding/blownUpBuilding_diffuse.dds";
   normalMap[0] = "art/textures/structures/blownUpBuilding/blownUpBuilding_normals.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/blownUpBuilding/blownUpBuilding_spec.dds";
   specularPower[0] = "1";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(newMaterial13)
{
   mapTo = "unmapped_mat";
   diffuseMap[0] = "tools/materialeditor/gui/matEd_mappedMat";
   castShadows = "1";
   translucent = "0";
   translucentZWrite = "0";
   translucentBlendOp = "LerpAlpha";
   materialTag0 = "Chinatown";
};

singleton Material(newMaterial16)
{
   mapTo = "BigRoadCracks";
   diffuseMap[0] = "art/textures/structures/RoadCracks.dds";
   specularPower[0] = "8";
   castShadows = "0";
   translucent = "1";
   translucentZWrite = "0";
   translucentBlendOp = "LerpAlpha";
   materialTag0 = "Chinatown";
   alphaRef = "0";
};

singleton Material(ConcreteBoarders)
{
   mapTo = "concreteBorders";
   diffuseMap[0] = "art/textures/structures/borders/concreteborders_diff.dds";
   normalMap[0] = "art/textures/structures/borders/concreteborders_norm.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/borders/concreteborders_spec.dds";
   detailScale[0] = "6 6";
   detailNormalMap[0] = "art/textures/structures/concreteDetail_normal.dds";
   specularPower[0] = "56";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};



singleton Material(plaster_001)
{
   mapTo = "walls.plaster_001";
   diffuseMap[0] = "art/textures/structures/walls/plaster_001_diffuse.dds";
   overlayMap[0] = "art/textures/structures/walls/plasterDirt02.dds";
   normalMap[0] = "art/textures/structures/walls/plaster_all_normal.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/walls/plaster_all_specular.dds";
   specularPower[0] = "1";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
};

singleton Material(building38_LOD3)
{
   mapTo = "LODS._038_buildingLOD3";
   diffuseMap[0] = "art/textures/structures/BuildingsLOD3/_038_buildingLOD3_albedo.dds";
   materialTag0 = "Chinatown";
};
//--- CT_building_013_Int.dae MATERIALS BEGIN ---
singleton Material(CT_building_013_Int_interiors_ceiling_002)
{
	mapTo = "interiors_ceiling_002";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_013_Int_interiors_intWall_001)
{
	mapTo = "interiors_intWall_001";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_building_013_Int_interiors_stairs)
{
	mapTo = "interiors_stairs";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_building_013_Int.dae MATERIALS END ---

//--- CT_Interior_001_3.dae MATERIALS BEGIN ---
singleton Material(CT_Interior_001_3_interiors_ceiling_3)
{
	mapTo = "interiors.ceiling_3";

	diffuseMap[0] = "art/textures/structures/ceilings/ceiling_diffuse_002.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_001_3_interiors_windows_windowsDoors)
{
	mapTo = "interiors.windows_windowsDoors";

	diffuseMap[0] = "art/textures/structures/windowsDoors/windowsDoors_diffuse.dds";
	normalMap[0] = "art/textures/structures/windowsDoors/windowsDoors_normal.dds";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_Interior_001_3.dae MATERIALS END ---

//--- CT_Interior_004.dae MATERIALS BEGIN ---
singleton Material(CT_Interior_004_MaterialLibrary19_Knives)
{
	mapTo = "MaterialLibrary19.Knives";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = true;
	translucentBlendOp = "LerpAlpha";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary22_shelves)
{
	mapTo = "MaterialLibrary22.shelves";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary23_MaterialLibrary1_Restaurant_Furniture)
{
	mapTo = "MaterialLibrary23.MaterialLibrary1_Restaurant_Furniture";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary24_Restaurant_Furniture)
{
	mapTo = "MaterialLibrary24.Restaurant_Furniture";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary3_filing_cabinet)
{
	mapTo = "MaterialLibrary3.filing_cabinet";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary4_Paintings)
{
	mapTo = "MaterialLibrary4.Paintings";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary5_chandelier)
{
	mapTo = "MaterialLibrary5.chandelier";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = true;
	translucentBlendOp = "LerpAlpha";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary6_kitchen_interior)
{
	mapTo = "MaterialLibrary6.kitchen_interior";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary25_Paintings)
{
	mapTo = "MaterialLibrary25.Paintings";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary26_MaterialLibrary_Plugs_Switches)
{
	mapTo = "MaterialLibrary26.MaterialLibrary_Plugs_Switches";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary27_interior_light_02)
{
	mapTo = "MaterialLibrary27.interior_light_02";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary28_MaterialLibrary_Plugs_Switches)
{
	mapTo = "MaterialLibrary28.MaterialLibrary_Plugs_Switches";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary11_kitchen_interior)
{
	mapTo = "MaterialLibrary11.kitchen_interior";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary12_Material)
{
	mapTo = "MaterialLibrary12.Material";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary13_kitchen_interior)
{
	mapTo = "MaterialLibrary13.kitchen_interior";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary14_kitchen_interior)
{
	mapTo = "MaterialLibrary14.kitchen_interior";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary16_oven)
{
	mapTo = "MaterialLibrary16.oven";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary16_ovenLOD)
{
	mapTo = "MaterialLibrary16.ovenLOD";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary1_desk)
{
	mapTo = "MaterialLibrary1.desk";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 67.2;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary_couch)
{
	mapTo = "MaterialLibrary.couch";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "0 0 0 0";
	specularPower[0] = 1;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary2_desk)
{
	mapTo = "MaterialLibrary2.desk";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 67.2;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary16_oven_glassLOD)
{
	mapTo = "MaterialLibrary16.oven_glassLOD";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary18_kitchen_interior)
{
	mapTo = "MaterialLibrary18.kitchen_interior";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary20_rubbishBag)
{
	mapTo = "MaterialLibrary20.rubbishBag";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.8 0.8 0.8 1";
	specular[0] = "0.2 0.2 0.2 1";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

singleton Material(CT_Interior_004_MaterialLibrary21_CardboardBoxes)
{
	mapTo = "MaterialLibrary21.CardboardBoxes";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Chinatown";
};

//--- CT_Interior_004.dae MATERIALS END ---

singleton Material(CT_building_013_LODS__013_buildingLOD3)
{
   mapTo = "LODS._013_buildingLOD3";
   specular[0] = "1 1 1 0";
   specularPower[0] = "50";
   translucentBlendOp = "None";
   materialTag0 = "Chinatown";
};

singleton Material(CT_building_013_floor_2)
{
   mapTo = "floor_2";
   specular[0] = "0 0 0 0";
   specularPower[0] = "128";
   translucentBlendOp = "None";
   materialTag0 = "Chinatown";
};

singleton Material(CT_building_027_CollisionMesh_AllowStep)
{
   mapTo = "CollisionMesh_AllowStep";
   diffuseColor[0] = "0.8 0.8 0 0.5";
   specular[0] = "0.2 0.2 0.2 1";
   translucent = "1";
   materialTag0 = "Chinatown";
};

singleton Material(CT_building_027_CollisionMesh)
{
   mapTo = "CollisionMesh";
   diffuseColor[0] = "0.8 0 0 0.5";
   specular[0] = "0.2 0.2 0.2 1";
   translucent = "1";
   materialTag0 = "Chinatown";
};

singleton Material(CT_Signs)
{
   mapTo = "CT_Signs";
   diffuseMap[0] = "art/textures/structures/buildingProps/allProps_diffuse.dds";
   translucent = "1";
   alphaTest = "1";
   normalMap[0] = "art/textures/structures/buildingProps/allProps_norm.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/textures/structures/buildingProps/allPropss_spec.dds";
   alphaRef = "107";
   useAnisotropic[0] = true;
   diffuseColor[0] = "0.639216 0.639216 0.639216 1";
   constantCubemapGloss = "0.2";
   specularPower[0] = "6";
   castShadows = "1";
   translucentBlendOp = "None";
   diffuseMap[1] = "art/textures/structures/buildingProps/allProps_glow_mask.dds";
   glow[1] = "0";
   emissive[1] = "1";
   diffuseColor[1] = "1.25 1.25 1.25 1";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
};

singleton Material(CT_building_012_Material_)
{
   mapTo = "Material-";
   translucentBlendOp = "None";
};
