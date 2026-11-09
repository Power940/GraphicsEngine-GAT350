#include "pch.h"
#include "Core/Factory.h"
#include "LightComponent.h"
#include <Renderer/Light.h>

namespace STR_FALL
{
	FACTORY_REG(LightComponent)
	
	void STR_FALL::LightComponent::Read(const rapidjson::Value& value)
	{
		Component::Read(value);

		std::string m_lightTypeName;
		JSON_READ(value, m_lightTypeName);

		if (m_lightTypeName == "directional") m_lightType = LightType::DIRECTIONAL;
		else if (m_lightTypeName == "spot") m_lightType = LightType::SPOT;
		else m_lightType = LightType::POINT;

		JSON_READ(value, m_color);
		JSON_READ(value, m_range);
		JSON_READ(value, m_innerCutoff);
		JSON_READ(value, m_outerCutoff);
	}

	Light LightComponent::GetLightData() const
	{
		const Transform3D& t = m_owner->GetTransform();

        return Light{
            .type = m_lightType,
            .position = t.m_pos,
            .color = m_color, // xyz -> rgb, w -> intensity
            .direction = glm::vec4(t.Forward(), m_range), // w -> range
			.innerCutoff = glm::cos(m_innerCutoff),
            .outerCutoff = glm::cos(m_outerCutoff)
        };
	}
}