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

	void LightComponent::UpdateGui()
	{
		const char* types[3] = {"DIRECTIONAL", "POINT", "SPOT"};
		ImGui::ColorEdit4("color & intensity", glm::value_ptr(m_color));
		ImGui::Combo("Type", (int*)(&m_lightType), types, 3);
		if (m_lightType != LightType::DIRECTIONAL)
		{
			ImGui::SliderFloat("range", &m_range, 0.0f, 100.0f);
		}
	}
}