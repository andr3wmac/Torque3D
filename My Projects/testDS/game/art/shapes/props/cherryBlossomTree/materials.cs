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

//--- cherryBlossomTree_001.dae MATERIALS BEGIN ---



singleton Material(cherryBlossomTree_001_Branches)
{
	mapTo = "Branches";

	diffuseMap[0] = "art/shapes/props/MainSquareProps/leavesDiff.tga";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "0.972549 0.862745 0.972549 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = 1;
	translucent = false;
	translucentBlendOp = "None";
   alphaTest = "1";
   alphaRef = "214";
   materialTag0 = "Untagged";
};

singleton Material(cherryBlossomTree_001_BranchesLOD)
{
	mapTo = "BranchesLOD";

	diffuseMap[0] = "art/shapes/props/cherryBlossomTree/Cherry_Blossoms.dds";
	normalMap[0] = "";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;

	doubleSided = 1;
	translucent = false;
	translucentBlendOp = "None";
   alphaTest = "1";
   alphaRef = "221";
   materialTag0 = "Untagged";
};




singleton Material(cherryBlossomTree_001_Tree)
{
   mapTo = "Tree";
   diffuseColor[0] = "1 1 1 0";
   diffuseMap[0] = "art/shapes/props/cherryBlossomTree/diff";
   normalMap[0] = "art/shapes/props/cherryBlossomTree/Cherry_Blossoms_Norm.dds";
   specular[0] = "0.02 0.02 0.02 1";
   specularPower[0] = "1";
   specularMap[0] = "art/shapes/props/cherryBlossomTree/Cherry_Blossoms_Spec.dds";
   translucentBlendOp = "None";
   pixelSpecular[0] = "1";
   materialTag0 = "Untagged";
};

singleton Material(cherryBlossomTree_treeLOD)
{
   mapTo = "TreeLOD";
   diffuseMap[0] = "art/shapes/props/cherryBlossomTree/diff";
   materialTag0 = "Untagged";
};
