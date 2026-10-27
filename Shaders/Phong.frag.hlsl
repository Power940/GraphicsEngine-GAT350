#include "Lighting.hlsli"

Texture2D<float4> u_texture : register(t0, space2);
SamplerState u_sampler : register(s0, space2);

cbuffer VertexUniforms : register(b0, space3)
{
    float3 camPos;
};
cbuffer LightUniforms : register(b1, space3)
{
    Light light;
}
cbuffer MatrerialUniforms : register(b2, space3)
{
    Material material;
}

struct Input
{
    float2 texcoord : TEXCOORD0;
    float3 worldPos : TEXCOORD1;
    float3 normal : TEXCOORD2;
};

struct Output
{
    float4 color : SV_Target0;
};

Output main(Input input)
{
    Output output;
    input.normal = normalize(input.normal);
    
    float3 radiance = light.color * light.intensity;
    float attenuation;
    float3 L = getLightVector(light, input.worldPos, attenuation);
    float NdotL = saturate(dot(input.normal, L));
    float3 diffuse = radiance * NdotL * attenuation + light.ambient;
    
    float3 specular = 0.0f;
    if (NdotL > 0)
    {
        float3 V = normalize(camPos - input.worldPos);
        float3 H = normalize(V + L);
        float HdotN = saturate(dot(H, input.normal));
        specular = pow(HdotN, material.shininess) * radiance * attenuation;
    }
    
    float4 albedo = u_texture.Sample(u_sampler, (input.texcoord * material.tiling) + material.offset) * material.color;
    output.color = float4(albedo.rgb * diffuse + specular, albedo.a);
    
    return output;
}