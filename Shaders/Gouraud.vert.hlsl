#include "Lighting.hlsli"

cbuffer VertexUniforms : register(b0, space1)
{
    float4x4 mvp;
    float4x4 model;
    float3 camPos;
    float padding;
}
cbuffer LightUniforms : register(b1, space1)
{
    Light light;
}
cbuffer MatrerialUniforms : register(b2, space1)
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
    float3 radiance = light.color * light.intensity;
    float3 worldPos = mul(model, float4(input.position, 1.0f)).xyz;
    float3 N = normalize(mul((float3x3) model, input.normal));
    float attenuation;
    float3 L = getLightVector(light, worldPos, attenuation);
    
    float NdotL = saturate(dot(N, L));
    
    output.position = mul(mvp, float4(input.position, 1.0f));
    output.texcoord = (input.texcoord * material.tiling) + material.offset;
    output.diffuse = radiance * NdotL + light.ambient * attenuation;
    output.specular = float3(0.0f, 0.0f, 0.0f);
    
    if (NdotL > 0)
    {
        float3 V = normalize(camPos - worldPos);
        float3 H = normalize(V + L);
        float HdotN = saturate(dot(H, N));
        output.specular = pow(HdotN, material.shininess) * radiance * attenuation;
    }
    
    return output;
}