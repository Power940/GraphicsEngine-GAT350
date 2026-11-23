#include "Lighting.hlsli"
#include "Uniforms.hlsli"


cbuffer ObjectUniforms : register(OBJECT_SLOT, VERTEX_UNIFORM_SPACE)
{
    Object object;
}
cbuffer FrameUniforms : register(FRAME_SLOT, VERTEX_UNIFORM_SPACE)
{
    Frame frame;
}
cbuffer LightUniforms : register(LIGHT_SLOT, VERTEX_UNIFORM_SPACE)
{
    Lights lights;
}
cbuffer MatrerialUniforms : register(MATERIAL_SLOT, VERTEX_UNIFORM_SPACE)
{
    Material material;
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
};

Output main(Input input)
{
    Output output;
    output.texcoord = (input.texcoord * material.tiling) + material.offset;
    output.position = mul(frame.viewProjection, float4(mul(object.model, float4(input.position, 1.0f)).xyz, 1.0));
    return output;
}