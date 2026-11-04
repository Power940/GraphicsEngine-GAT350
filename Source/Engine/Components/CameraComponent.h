#pragma once
#include "Component.h"
#include <Framework/Object.h>

namespace STR_FALL
{
	class CameraComponent : public Component
	{
	public:
		CLASS_PROTOTYPE(CameraComponent)

		void Read(const rapidjson::Value& value) override;

		void Update(float dt) override;

		float m_fov = 70.0f;
		float m_nearPlane = 0.001f;
		float m_farPlane = 1000.0f;

		inline const glm::mat4x4& GetView() const { return m_view; }
		inline const glm::mat4x4& GetProjection() const { return m_projection; }

	private:
		glm::mat4x4 m_view;
		glm::mat4x4 m_projection;
	};
}