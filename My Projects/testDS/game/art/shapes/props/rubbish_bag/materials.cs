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

//--- rub_bag.dae MATERIALS BEGIN ---
singleton Material(rub_bag_rubbishBag)
{
	mapTo = "rubbishBag";

	diffuseMap[0] = "art/shapes/props/rubbish_bag/rubbish_bag_diff_GM.dds";
	normalMap[0] = "art/shapes/props/rubbish_bag/rubbish_bag_norm_GM.dds";
	specularMap[0] = "art/shapes/props/rubbish_bag/rubbish_bag_spec_GM.dds";

	diffuseColor[0] = "0.8 0.8 0.8 0";
	specularPower[0] = 31;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Untagged";
};

//--- rub_bag.dae MATERIALS END ---

