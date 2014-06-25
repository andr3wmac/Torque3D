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

//--- PoliceBaracade_01.dae MATERIALS BEGIN ---

//--- PoliceBaracade_01.dae MATERIALS END ---


singleton Material(policeBaracades)
{
   mapTo = "baracades";
   specular[0] = "1 1 1 0";
   specularPower[0] = "50";
   translucentBlendOp = "None";
   diffuseMap[0] = "art/shapes/props/Baracades/Baracades_diff.dds";
   normalMap[0] = "art/shapes/props/Baracades/Baracades_normals.dds";
   pixelSpecular[0] = "0";
   specularMap[0] = "art/shapes/props/Baracades/Baracades_spec.dds";
   constantCubemapGloss = "0.2";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
};

singleton Material(policeBaracadesLOD)
{
   mapTo = "baracadesLOD";
   translucentBlendOp = "None";
   diffuseMap[0] = "art/shapes/props/Baracades/Baracades_diff.dds";
   materialTag0 = "Chinatown";
   materialTag1 = "Prop";
   materialTag2 = "LOD";
};
