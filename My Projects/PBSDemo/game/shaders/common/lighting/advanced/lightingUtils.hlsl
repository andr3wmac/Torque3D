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


float attenuate( float4 lightColor, float lightRadius, float dist )
{
   // andrewmac: Physical Based Shading
   // Replaced with falloff equation based on Unreal Engine 4
   // https://de45xmedrsdbp.cloudfront.net/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf
   return pow(saturate(1.0 - pow(dist / lightRadius, 4)), 2) / (pow(dist, 2) + 1);
}

float3 getDistanceVectorToPlane( float3 origin, float3 direction, float4 plane )
{
   float denum = dot( plane.xyz, direction.xyz );
   float num = dot( plane, float4( origin, 1.0 ) );
   float t = -num / denum;

   return direction.xyz * t;
}

float3 getDistanceVectorToPlane( float negFarPlaneDotEye, float3 direction, float4 plane )
{
   float denum = dot( plane.xyz, direction.xyz );
   float t = negFarPlaneDotEye / denum;

   return direction.xyz * t;
}
