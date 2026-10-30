#pragma once

#define LIGHT_DIRECTIONAL 0
#define LIGHT_POINT 1
#define LIGHT_SPOT 2

#define MAX_LIGHTS 8

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
    uint type;
    float3 position;
    
    float4 color; // xyz -> rgb, w -> intensity
    
    float4 direction; // w -> range
    
    float innerCutoff;
    float outerCutoff;
    float2 padding1;
};

float calculateAttenuation(float distance, float range)
{
    return pow(saturate(1 - (distance / range)), 2);
}

float3 getLightVector(Light light, float3 pos, out float attenuation)
{
    float3 L;
    attenuation = 1.0f;
    
    if (light.type == LIGHT_DIRECTIONAL)
    {
        L = -normalize(light.direction.xyz);
    }
    else if (light.type == LIGHT_POINT)
    {
        float LL = length(light.position - pos);
        L = (light.position - pos) / LL;
        attenuation = calculateAttenuation(LL, light.direction.w);
    }
    else if (light.type == LIGHT_SPOT)
    {
        float LL = length(light.position - pos);
        L = (light.position - pos) / LL;
        attenuation = smoothstep(
            light.outerCutoff, light.innerCutoff,
            dot(normalize(light.direction.xyz), -L)
        ) * calculateAttenuation(LL, light.direction.w);
    }
    
    return L;
}