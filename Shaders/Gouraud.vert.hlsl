#include "Lighting.hlsli"


cbuffer MatrixUniforms : register(b0, space1)
{
    float4x4 mvp;
    float4x4 model;
}
cbuffer VertexUniforms : register(b1, space1)
{
    float3 camPos;
    float padding;
}
cbuffer LightUniforms : register(b2, space1)
{
    Light lights[MAX_LIGHTS];
    uint numLights;
    float3 ambient;
}
cbuffer MatrerialUniforms : register(b3, space1)
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
    float3 diffuse : TEXCOORD1;
    float3 specular : TEXCOORD2;
};

Output main(Input input)
{
    Output output;
    output.position = mul(mvp, float4(input.position, 1.0f));
    output.texcoord = (input.texcoord * material.tiling) + material.offset;
    output.diffuse = ambient;
    output.specular = 0.0f;
    
    float3 N = normalize(mul((float3x3) model, input.normal));
    float3 worldPos = mul(model, float4(input.position, 1.0f)).xyz;
    float3 V = normalize(camPos - worldPos);
    
    for (uint i = 0; i < numLights; i++)
    {
        float3 radiance = lights[i].color.xyz * lights[i].color.w;
        float attenuation;
        float3 L = getLightVector(lights[i], worldPos, attenuation);
        float NdotL = saturate(dot(N, L));
    
        output.diffuse += radiance * NdotL * attenuation;
    
        if (NdotL > 0)
        {
            float3 H = normalize(V + L);
            float HdotN = saturate(dot(H, input.normal));
            output.specular += pow(HdotN, material.shininess) * radiance * attenuation;
        }
    }
    
    return output;
}