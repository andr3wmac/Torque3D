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

//--- Large_light.dae MATERIALS BEGIN ---
singleton Material(Large_light_CarLights)
{
	mapTo = "CarLights";

	diffuseMap[0] = "art/shapes/props/Car/police_lights/lights_diff.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.992157 0.992157 0.992157 0";
	specular[0] = "1 1 1 1";
	specularPower[0] = 50;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   glow[0] = "1";
   diffuseMap[1] = "art/shapes/props/Car/police_lights/lights_diff.dds";
   pixelSpecular[0] = "0";
   glow[1] = "1";
   diffuseColor[1] = "0.509804 0.509804 0.509804 1";
   emissive[0] = "0";
   emissive[1] = "0";
   diffuseMap[2] = "";
   glow[2] = "0";
   diffuseColor[2] = "0.992157 0.992157 0.992157 0";
   emissive[2] = "0";
   animFlags[2] = "0x00000000";
   scrollDir[2] = "0.241 0";
   rotSpeed[2] = "1.294";
   rotPivotOffset[2] = "-1 -1";
   sequenceSegmentSize[2] = "2";
   animFlags[3] = "0x00000001";
   scrollSpeed[3] = "1.412";
   sequenceFramePerSec[2] = "1";
   animFlags[1] = "0x00000000";
   sequenceFramePerSec[1] = "1";
   sequenceSegmentSize[1] = "2";
   animFlags[0] = "0x00000000";
   sequenceFramePerSec[0] = "10.31";
   sequenceSegmentSize[0] = "0";
};

//--- Large_light.dae MATERIALS END ---

