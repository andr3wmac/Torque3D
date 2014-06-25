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

//--- trash_can.dae MATERIALS BEGIN ---
singleton Material(trash_can_trash_canLOD)
{
	mapTo = "trash_canLOD";

	diffuseMap[0] = "art/shapes/props/trash_can/trash_can_diff_GM.dds";
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

//--- trash_can.dae MATERIALS END ---


singleton Material(trash_can_Phong_Preset)
{
   mapTo = "trash_can";
   diffuseColor[0] = "1 1 1 0";
   diffuseMap[0] = "art/shapes/props/trash_can/trash_can_diff_GM.dds";
   normalMap[0] = "art/shapes/props/trash_can/trash_can_norm_GM.dds";
   specularPower[0] = "21";
   specularMap[0] = "art/shapes/props/trash_can/trash_can_spec_GM.dds";
   translucentBlendOp = "None";
   materialTag0 = "Untagged";
};
