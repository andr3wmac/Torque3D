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

//--- chinese_lantern.dae MATERIALS BEGIN ---
singleton Material(chinese_lantern_Misc_rope)
{
	mapTo = "Misc.rope";

	diffuseMap[0] = "";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;
	pixelSpecular[0] = false;
	emissive[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Untagged";
};



//--- chinese_lantern.dae MATERIALS END ---



singleton Material(CT_paperLantern)
{
   mapTo = "Misc.Paper_lantern";
   diffuseMap[0] = "art/shapes/props/lantern/lamp_diff_GM.dds";
   normalMap[0] = "art/shapes/props/lantern/lamp_normals.dds";
   alphaTest = "1";
   alphaRef = "73";
   specularPower[0] = "66";
   pixelSpecular[0] = "1";
   glow[0] = "1";
   doubleSided = "1";
   diffuseMap[1] = "art/shapes/props/lantern/lamp_glow.dds";
   glow[1] = "1";
   specular[0] = "1 0.396078 0 1";
   materialTag0 = "Untagged";
};

