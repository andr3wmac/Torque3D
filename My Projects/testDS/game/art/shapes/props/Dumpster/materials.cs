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

//--- dumpster.dae MATERIALS BEGIN ---
singleton Material(Dumpster)
{
   mapTo = "Dumpster";
  
   diffuseMap[0] = "art/shapes/props/Dumpster/Dumpster_diff.dds";
   normalMap[0] = "art/shapes/props/Dumpster/Dumpster_norm.dds";
   specularMap[0] = "art/shapes/props/Dumpster/Dumpster_spec.dds";
   
   specularPower[0] = "21";
   specular[0] = "1 1 1 0";
   pixelSpecular[0] = "0";
   constantCubemapGloss = "0.2";
   materialTag0 = "Untagged";
};

singleton Material(dumpster_DumpsterLOD)
{
	mapTo = "DumpsterLOD";

	diffuseMap[0] = "art/shapes/props/Dumpster/Dumpster_diff.dds";
	castShadows = "0";
   materialTag0 = "Untagged";
};

//--- dumpster.dae MATERIALS END ---

