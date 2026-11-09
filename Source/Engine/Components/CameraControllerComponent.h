#pragma once
#include "Component.h"
#include <Framework/Object.h>

namespace STR_FALL
{
	class CameraControllerComponent : public Component
	{
	public:
		CLASS_PROTOTYPE(CameraControllerComponent)

		void Update(float dt) override;
		void Read(const rapidjson::Value& value) override;

	private:
		float m_speed = 1.0f;
		float m_sensitivity = 1.0f;
		float m_yaw = 0.0f;
		float m_pitch = 0.0f;
	};
}