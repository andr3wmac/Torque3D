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

//--- outdoor_wall_light.dae MATERIALS BEGIN ---
singleton Material(outdoor_wall_light_outDoorLight)
{
	mapTo = "outDoorLight";

	diffuseMap[0] = "art/shapes/props/outdoor_wall_light/outdoor_wall_light_diff_GM.dds";
	normalMap[0] = "art/shapes/props/outdoor_wall_light/outdoor_wall_light_norm_GM.dds";
	specularMap[0] = "art/shapes/props/outdoor_wall_light/outdoor_wall_light_spec_GM.dds";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = "1";
	translucentBlendOp = "None";
   glow[0] = "0";
   diffuseMap[1] = "art/shapes/props/outdoor_wall_light/outdoor_wall_light_diff_GM_GlowMask.dds";
   glow[1] = "1";
   emissive[1] = "1";
   diffuseColor[1] = "0.482353 0.435294 0.317647 1";
   materialTag0 = "Untagged";
};

//--- outdoor_wall_light.dae MATERIALS END ---

