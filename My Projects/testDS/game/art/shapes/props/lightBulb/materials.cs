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

//--- lightBulb.dae MATERIALS BEGIN ---
singleton Material(lightsStringDay)
{
   mapTo = "lightsString";
   diffuseMap[0] = "art/shapes/props/lightBulb/lightbulbs.dds";
   diffuseColor[0] = "0 0 0 1";
   materialTag0 = "Untagged";
};

//--- lightBulb.dae MATERIALS END ---


singleton Material(lightBulb_lightBulb)
{
   mapTo = "lightBulb";
   diffuseColor[0] = "0.996078 0.996078 0.996078 1";
   diffuseColor[1] = "0.32549 0.32549 0.32549 1";
   diffuseMap[0] = "art/shapes/props/lightBulb/lightbulbs.dds";
   diffuseMap[1] = "art/shapes/props/lightBulb/lightbulbs.dds";
   diffuseMap[2] = "art/shapes/props/lightBulb/lightbulbs.dds";
   specular[0] = "1 1 1 0";
   specularPower[0] = "16";
   glow[1] = "1";
   emissive[0] = "1";
   translucentBlendOp = "None";
   emissive[1] = "1";
   glow[0] = "1";
   glow[2] = "1";
   materialTag0 = "Untagged";
};
//--- lightBulbday.dae MATERIALS BEGIN ---
singleton Material(lightBulbday_lightBulbDay)
{
	mapTo = "lightBulbDay";

	diffuseMap[0] = "art/shapes/props/lightBulb/lightbulbs.dds";

	diffuseColor[0] = "0.737255 0.67451 0.509804 1";
	specular[0] = "0.0705882 0.0705882 0.0705882 1";
	specularPower[0] = "1";

	doubleSided = false;
	translucent = "0";
	translucentBlendOp = "LerpAlpha";
   pixelSpecular[0] = "0";
   glow[0] = "1";
   emissive[0] = "1";
   materialTag0 = "Untagged";
   castShadows = "0";
};

//--- lightBulbday.dae MATERIALS END ---
