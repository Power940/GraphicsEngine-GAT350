#pragma once

#define LIGHT_DIRECTIONAL 0
#define LIGHT_POINT 1
#define LIGHT_SPOT 2

struct Material
{
    float4 color;
    
    float2 tiling;
    float2 offset;
    
    float shininess;
    float3 padding1;
};

struct Light
{
    float3 position;
    uint type;
    
    float3 direction;
    float innerCutoff;
    
    float3 color;
    float intensity;
    
    float3 ambient;
    float outerCutoff;
    
};

float3 getLightVector(Light light, float3 pos, out float attenuation)
{
    float3 L;
    attenuation = 1.0f;
    
    if (light.type == LIGHT_DIRECTIONAL)
    {
        L = -normalize(light.direction);
    }
    else if (light.type == LIGHT_POINT)
    {
        L = normalize(light.position - pos);
    }
    else if (light.type == LIGHT_SPOT)
    {
        L = normalize(light.position - pos);
        attenuation = smoothstep(light.outerCutoff, light.innerCutoff, dot(-L, light.position));

    }
    
    return L;
}