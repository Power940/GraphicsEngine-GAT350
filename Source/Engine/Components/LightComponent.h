#pragma once
#include "Component.h"
#include "Renderer/Light.h"

namespace STR_FALL
{
	class LightComponent : public Component
	{
	public:
		CLASS_PROTOTYPE(LightComponent)

		void Read(const rapidjson::Value& value) override;

		struct Light GetLightData() const;
		 
	private:
		LightType m_lightType = LightType::POINT;
		glm::vec4 m_color = glm::vec4(1.0f);
		float m_range = 20.0f;
		float m_innerCutoff = 20.0f;
		float m_outerCutoff = 30.0f;
	};
}