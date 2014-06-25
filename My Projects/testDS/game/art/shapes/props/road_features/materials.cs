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

//--- Cobble_concrete_damage.dae MATERIALS BEGIN ---

//--- Cobble_concrete_damage.dae MATERIALS END ---



singleton Material(Cobble_concrete_damage_road_features)
{
   mapTo = "road_features";
   diffuseColor[0] = "1 1 1 0";
   diffuseMap[0] = "art/shapes/props/road_features/road_features_2.dds";
   normalMap[0] = "art/shapes/props/road_features/road_features_norm.dds";
   alphaTest = "1";
   alphaRef = "120";
   castShadows = "0";
   translucent = "0";
   translucentZWrite = "0";
   translucentBlendOp = "None";
   materialTag0 = "Untagged";
};

//--- trash_corners.dae MATERIALS BEGIN ---
singleton Material(trash_corners_trash_corner)
{
	mapTo = "trash_corner";

	diffuseMap[0] = "art/shapes/props/road_features/trash_diffuse.tga";
	normalMap[0] = "art/shapes/props/road_features/trash_normals_NRM.tga";
	specularMap[0] = "art/shapes/props/road_features/trash_spec.tga";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 1;
	pixelSpecular[0] = false;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   alphaTest = "1";
   alphaRef = "26";
   materialTag0 = "Untagged";
};

//--- trash_corners.dae MATERIALS END ---

//--- Gen_pothole_side.dae MATERIALS BEGIN ---
singleton Material(Gen_pothole_side_Material_road_features)
{
	mapTo = "Material-road_features";

	diffuseMap[0] = "art/shapes/props/road_features/road_features_2.dds";
	normalMap[0] = "art/shapes/props/road_features/road_features_norm.dds";
	specularMap[0] = "art/textures/structures/specmask.dds";

	diffuseColor[0] = "0.403922 0.403922 0.403922 1";
	specular[0] = "0.705882 0.705882 0.705882 1";
	specularPower[0] = 128;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   alphaTest = "1";
   alphaRef = "120";
   pixelSpecular[0] = "0";
   constantCubemapGloss = "0.2";
   materialTag0 = "Untagged";
};

//--- Gen_pothole_side.dae MATERIALS END ---

