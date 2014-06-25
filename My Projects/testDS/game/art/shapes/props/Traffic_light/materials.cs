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

//--- Traffic_light.dae MATERIALS BEGIN ---
singleton Material(Traffic_light_Traffic_light)
{
	mapTo = "Traffic_light";

	diffuseMap[0] = "art/shapes/props/Traffic_light/Traffic_Light_Diff.dds";
	normalMap[0] = "art/shapes/props/Traffic_light/Traffic_Light_Norm.dds";
	specularMap[0] = "art/shapes/props/Traffic_light/Traffic_Light_Spec.dds";

	diffuseColor[0] = "0.545098 0.545098 0.545098 1";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "0";
   constantCubemapGloss = "0.2";
   materialTag0 = "Untagged";
};

singleton Material(Traffic_light_Traffic_lightLOD)
{
	mapTo = "Traffic_lightLOD";

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

//--- Traffic_light.dae MATERIALS END ---

//--- Traffic_light2.dae MATERIALS BEGIN ---
singleton Material(Traffic_light2_Phong_Preset)
{
	mapTo = "Phong_Preset";

	diffuseMap[0] = "art/shapes/props/Traffic_light/WlakSign.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   emissive[0] = "1";
   materialTag0 = "Untagged";
};

//--- Traffic_light2.dae MATERIALS END ---


singleton Material(Traffic_light_Material_Traffic_light)
{
   mapTo = "Material-Traffic_lightLOD";
   diffuseMap[0] = "art/shapes/props/Traffic_light/Traffic_Light_Diff.dds";
   specular[0] = "1 1 1 0";
   specularPower[0] = "50";
   translucentBlendOp = "None";
   materialTag0 = "Untagged";
};
//--- Traffic_walk.dae MATERIALS BEGIN ---
singleton Material(Traffic_walk_Trafficwalk)
{
	mapTo = "Trafficwalk";

	diffuseMap[0] = "art/shapes/props/Traffic_light/WalkSign.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.996078 0.996078 0.996078 0";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   emissive[0] = "1";
   constantCubemapGloss = "0.2";
   glow[0] = "1";
   animFlags[0] = "0x00000010";
   sequenceFramePerSec[0] = "1";
   sequenceSegmentSize[0] = "0.5";
   materialTag0 = "Untagged";
};

//--- Traffic_walk.dae MATERIALS END ---

//--- Traffic_light_amber.dae MATERIALS BEGIN ---
singleton Material(Traffic_light_amber_Traffic_light_amber)
{
	mapTo = "Traffic_light_amber";

	diffuseMap[0] = "tools/materialeditor/gui/matEd_mappedMat";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   glow[0] = "0";
   emissive[0] = "0";
   animFlags[0] = "0x00000000";
   sequenceFramePerSec[0] = "0";
   sequenceSegmentSize[0] = "0";
   materialTag0 = "Untagged";
};

//--- Traffic_light_amber.dae MATERIALS END ---

