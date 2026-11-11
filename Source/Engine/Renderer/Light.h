#pragma once
#include <glm/glm.hpp>
#include <cstdint>

namespace STR_FALL
{
    constexpr uint32_t MAX_LIGHTS = 8;

    enum class LightType : uint32_t
    {
        DIRECTIONAL,
        POINT,
        SPOT
    };
    struct Light
    {
        LightType type;
        glm::vec3 position;

        glm::vec4 color; // xyz -> rgb, w -> intensity

        glm::vec4 direction; // w -> range

        float innerCutoff;
        float outerCutoff;
        glm::vec2 padding1;
    };
    struct LightsUniform
    {
        Light lights[MAX_LIGHTS];
        uint32_t num_lights;
        glm::vec3 ambient;
    };
}