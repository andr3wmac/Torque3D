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

uniform sampler2D diffuseMap : register(S0);

struct ShadowVert
{
   float4 pos        : POSITION;
   float2 uv0        : TEXCOORD0;
};

float4 main( ShadowVert IN ) : COLOR
{
    float4 OUT = 0;
    float TextelScale = 1.0 / 2048.0;
    float2 Value = float2(0.0, 0.0);

    float Coefficients[9] = 
        {0.077847, 0.123317, 0.077847,
         0.123317, 0.195346, 0.123317,
         0.077847, 0.123317, 0.077847};

    for(int Index = 0; Index < 9; Index++)
    {
        Value += tex2D(diffuseMap, float2(IN.uv0.x + (Index - 4) * TextelScale, IN.uv0.y)).xy * Coefficients[Index];
    }

    OUT = float4(Value.x, Value.y, 0.0, 1.0);
    return OUT;
}
