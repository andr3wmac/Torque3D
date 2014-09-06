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

//--- cube.dae MATERIALS BEGIN ---
singleton Material(cube_GridMaterial)
{
	mapTo = "GridMaterial";

	diffuseMap[0] = "art/shapes/cube/grid.dds";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "1 1 1 1";
	specularPower[0] = "21";
	pixelSpecular[0] = false;
	emissive[0] = "0";

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "LerpAlpha";
   materialTag0 = "Miscellaneous";
   subSurface[0] = "0";
   cubemap = "DesertSkyCubemap";
   specularStrength[0] = "0";
};

//--- cube.dae MATERIALS END ---


singleton Material(rounded_cube_TestCubeMaterial)
{
   mapTo = "TestCubeMaterial";
   diffuseColor[0] = "0.348135 0.64 0.3072 1";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "50";
   translucentBlendOp = "None";
   diffuseMap[0] = "art/grey_block.png";
   translucencyMap[0] = "art/test_translucency_middle.png";
   glow[0] = "1";
   materialTag0 = "Miscellaneous";
};

singleton Material(rounded_cube_TestCubeCenterMaterial)
{
   mapTo = "TestCubeCenterMaterial";
   diffuseColor[0] = "0.996078 0.992157 0.992157 1";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "50";
   translucentBlendOp = "None";
   diffuseMap[0] = "art/grey_block.png";
   translucencyMap[0] = "art/test_translucency_center.png";
   materialTag0 = "Miscellaneous";
};
