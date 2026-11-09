#include "pch.h"
#include "MaterialComponent.h"
#include "Core/Factory.h"
#include "LightComponent.h"
#include <Renderer/Light.h>

namespace STR_FALL
{
	FACTORY_REG(LightComponent)
	
	void STR_FALL::LightComponent::Read(const rapidjson::Value& value)
	{
	}

	Light LightComponent::GetLightData() const
	{
        return Light{
            .type = LightType::DIRECTIONAL,
            .position = glm::vec3(),
            .color = glm::vec4(), // xyz -> rgb, w -> intensity
            .direction = glm::vec4(), // w -> range
			.innerCutoff = 0.0f,
            .outerCutoff = 0.0f
        };
	}
}