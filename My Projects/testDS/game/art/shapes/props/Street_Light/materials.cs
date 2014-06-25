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

//--- street_light.dae MATERIALS BEGIN ---
singleton Material(street_light_Street_Light)
{
	mapTo = "Street_Light";

	diffuseMap[0] = "art/shapes/props/Street_Light/streetlight_diff.dds";
	normalMap[0] = "art/shapes/props/Street_Light/StreetLight_norm.dds";
	specularMap[0] = "art/shapes/props/Street_Light/streetlight_spec.dds";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = "1";
	translucentBlendOp = "None";
   pixelSpecular[0] = "0";
   constantCubemapGloss = "0.2";
   diffuseMap[1] = "art/shapes/props/Street_Light/streetlight_GlowMask.dds";
   glow[1] = "1";
   emissive[1] = "1";
   diffuseColor[1] = "0.45098 0.431373 0.364706 1";
   materialTag0 = "Untagged";
};

//--- street_light.dae MATERIALS END ---




singleton Material(streetLightLOD)
{
   mapTo = "Street_LightLOD";
   diffuseMap[0] = "art/shapes/props/Street_Light/streetlight_diff.dds";
   translucentBlendOp = "None";
   diffuseMap[1] = "art/shapes/props/Street_Light/streetlight_GlowMask.dds";
   glow[1] = "1";
   emissive[1] = "1";
   translucent = "1";
   constantCubemapGloss = "0.2";
   diffuseColor[1] = "0.45098 0.431373 0.364706 1";
   materialTag0 = "Untagged";
};
