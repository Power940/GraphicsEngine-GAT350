#include "Lighting.hlsli"

cbuffer MatrixUniforms : register(b0, space1)
{
    float4x4 mvp;
    float4x4 model;
}

struct Input
{
    float3 position : TEXCOORD0;
    float2 texcoord : TEXCOORD1;
    float3 normal : TEXCOORD2;
    float3 tangent : TEXCOORD3;
};

struct Output
{
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD0;
    float3 worldPos : TEXCOORD1;
    float3 normal : TEXCOORD2;
};

Output main(Input input)
{
    Output output;
    output.position = mul(mvp, float4(input.position, 1.0f));
    output.texcoord = input.texcoord;
    output.worldPos = mul(model, float4(input.position, 1.0f)).xyz;
    output.normal = normalize(mul((float3x3) model, input.normal));
    return output;
}