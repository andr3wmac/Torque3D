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

//--- streetLamp.dae MATERIALS BEGIN ---
singleton Material(streetLamp_streetLamp)
{
	mapTo = "streetLamp";

	diffuseMap[0] = "art/shapes/props/streetLamp/streetLamp_diffuse.dds";
	normalMap[0] = "art/shapes/props/streetLamp/streetLamp_normals.dds";
	specularMap[0] = "art/shapes/props/streetLamp/streetLamp_spec.dds";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "1 1 1 1";
	specularPower[0] = 4;

	doubleSided = false;
	translucent = "1";
	translucentBlendOp = "None";
   pixelSpecular[0] = "0";
   alphaTest = "1";
   alphaRef = "33";
   constantCubemapGloss = "0.2";
   diffuseMap[1] = "art/shapes/props/streetLamp/streetLamp_GlowMask.dds";
   glow[1] = "1";
   emissive[1] = "1";
   diffuseColor[1] = "0.215686 0.172549 0.0941177 1";
   materialTag0 = "Untagged";
};

//--- streetLamp.dae MATERIALS END ---


singleton Material(streetLampLOD)
{
   mapTo = "streetLampLOD";
   diffuseMap[0] = "art/shapes/props/streetLamp/streetLamp_diffuse.dds";
   diffuseColor[0] = "1 1 1 0";
   alphaTest = "1";
   alphaRef = "87";
   materialTag0 = "Untagged";
};
