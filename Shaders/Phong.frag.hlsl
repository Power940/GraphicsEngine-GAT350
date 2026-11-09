#include "Lighting.hlsli"
#include "Uniforms.hlsli"


Texture2D<float4> u_texture : register(t0, space2);
SamplerState u_sampler : register(s0, space2);


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
    
    float3 V = normalize(frame.cameraPosition - input.worldPos);
    float3 diffuse = lights.ambient;
    float3 specular = 0.0f;
    
    for (uint i = 0; i < lights.numLights; i++)
    {
        float3 radiance = lights.lights[i].color.xyz * lights.lights[i].color.w;
        float attenuation;
        float3 L = getLightVector(lights.lights[i], input.worldPos, attenuation);
        float NdotL = saturate(dot(input.normal, L));
        diffuse += radiance * NdotL * attenuation;
    
        if (NdotL > 0)
        {
            float3 H = normalize(V + L);
            float HdotN = saturate(dot(H, input.normal));
            specular += pow(HdotN, material.shininess) * radiance * attenuation;
        }
    }
    
    float4 albedo = u_texture.Sample(u_sampler, input.texcoord) * material.color;
    output.color = float4(albedo.rgb * diffuse + specular, albedo.a);
    
    return output;
}