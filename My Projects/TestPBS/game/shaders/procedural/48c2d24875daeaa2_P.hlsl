//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "shaders/common/torque.hlsl"

// Features:
// Vert Position
// Deferred Shading: Diffuse Map
// Deferred Shading: Specular Map
// Deferred Shading: Specular Power
// Deferred Shading: Specular Strength
// Deferred Shading: Mat Info Flags
// Bumpmap [Deferred]
// Visibility
// Eye Space Depth (Out)
// GBuffer Conditioner
// DXTnm

struct ConnectData
{
   float2 texCoord        : TEXCOORD0;
   float3x3 viewToTangent   : TEXCOORD1;
   float2 vpos            : VPOS;
   float4 wsEyeVec        : TEXCOORD4;
};


struct Fragout
{
   float4 col : COLOR0;
   float4 col1 : COLOR1;
   float4 col2 : COLOR2;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
Fragout main( ConnectData IN,
              uniform sampler2D diffuseMap      : register(S0),
              uniform sampler2D specularMap     : register(S1),
              uniform float     specularPower   : register(C0),
              uniform float     specularStrength : register(C1),
              uniform float     matInfoFlags    : register(C2),
              uniform sampler2D bumpMap         : register(S2),
              uniform float     visibility      : register(C3),
              uniform float3    vEye            : register(C4),
              uniform float4    oneOverFarplane : register(C5)
)
{
   Fragout OUT;

   // Vert Position
   
   // Deferred Shading: Diffuse Map
   OUT.col1 = tex2DLinear(diffuseMap, IN.texCoord);
   
   // Deferred Shading: Specular Map
   OUT.col1.a = dot(tex2D(specularMap, IN.texCoord).rgb, float3(0.3, 0.59, 0.11));
   
   // Deferred Shading: Specular Power
   OUT.col2 = float4(0.0, 0.0, specularPower / 128.0, 0.0);
   
   // Deferred Shading: Specular Strength
   OUT.col2.a = specularStrength / 5.0;
   
   // Deferred Shading: Mat Info Flags
   OUT.col2.r = matInfoFlags;
   
   // Bumpmap [Deferred]
   float4 bumpNormal = float4( tex2D(bumpMap, IN.texCoord).ag * 2.0 - 1.0, 0.0, 0.0 ); // DXTnm
   bumpNormal.z = sqrt( 1.0 - dot( bumpNormal.xy, bumpNormal.xy ) ); // DXTnm
   half3 gbNormal = (half3)mul( bumpNormal.xyz, IN.viewToTangent );
   
   // Visibility
   fizzle( IN.vpos, visibility );
   
   // Eye Space Depth (Out)
#ifndef CUBE_SHADOW_MAP
   float eyeSpaceDepth = dot(vEye, (IN.wsEyeVec.xyz / IN.wsEyeVec.w));
#else
   float eyeSpaceDepth = length( IN.wsEyeVec.xyz / IN.wsEyeVec.w ) * oneOverFarplane.x;
#endif
   
   // GBuffer Conditioner
   float4 normal_depth = float4(normalize(gbNormal), eyeSpaceDepth);

   // output buffer format: GFXFormatR16G16B16A16F
   // g-buffer conditioner: float4(normal.X, normal.Y, depth Hi, depth Lo)
   float4 _gbConditionedOutput = float4(sqrt(half(2.0/(1.0 - normal_depth.y))) * half2(normal_depth.xz), 0.0, normal_depth.a);
   
   // Encode depth into hi/lo
   float2 _tempDepth = frac(normal_depth.a * float2(1.0, 65535.0));
   _gbConditionedOutput.zw = _tempDepth.xy - _tempDepth.yy * float2(1.0/65535.0, 0.0);

   OUT.col = _gbConditionedOutput;
   
   // DXTnm
   

   return OUT;
}
