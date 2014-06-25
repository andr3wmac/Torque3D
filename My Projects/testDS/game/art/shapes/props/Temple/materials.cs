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

//--- Temple.dae MATERIALS BEGIN ---
singleton Material(Temple_Default_Material)
{
	mapTo = "Default_Material";

	diffuseMap[0] = "art/shapes/props/Temple/Temple_Diff.dds";
	normalMap[0] = "art/shapes/props/Temple/Temple_Norm.jpg";
	specularMap[0] = "art/shapes/props/Temple/Temple_Spec.dds";

	diffuseColor[0] = "0.7 0.7 0.7 0";
	specular[0] = "1 1 1 0";
	specularPower[0] = 50;
	pixelSpecular[0] = false;
	emissive[0] = 0;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Untagged";
};

//--- Temple.dae MATERIALS END ---


//--- TempleLow.dae MATERIALS BEGIN ---

//--- TempleLow.dae MATERIALS END ---


singleton Material(Temple_MaterialLibrary_Temple)
{
   mapTo = "temple";
   diffuseColor[0] = "0.7 0.7 0.7 0";
   diffuseMap[0] = "art/shapes/props/Temple/Temple_Diff.dds";
   detailMap[0] = "detail.dds";
   detailScale[0] = "5 5";
   normalMap[0] = "art/shapes/props/Temple/Temple_Norm.jpg";
   specular[0] = "0 0.509804 1 0";
   specularPower[0] = "1";
   pixelSpecular[0] = "0";
   translucentBlendOp = "None";
   specularMap[0] = "art/shapes/props/Temple/Temple_Spec.dds";
   materialTag0 = "Untagged";
};
