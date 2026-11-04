#include "pch.h"
#include "CameraControllerComponent.h"
#include "Core/Factory.h"
#include "StarFallEngine.h"
#include <glm/gtx/norm.hpp>

namespace STR_FALL
{
	FACTORY_REG(CameraControllerComponent)
	
	void CameraControllerComponent::Update(float dt)
	{
		if (STR_Engine::Get().m_input.GetMouseDown(Input::RIGHT))
		{
			glm::vec2 axis = STR_Engine::Get().m_input.GetMouseDiff() * m_sensitivity;

			m_owner->IncrementTransformRotation(glm::vec3(-axis.y, -axis.x, 0.0f));
			m_owner->ClampTransformRotationX(-F_HPI + 0.01f, F_HPI - 0.01f);
		}

		//glm::quat q = glm::quat_cast(glm::eulerAngleYXZ(glm::radians(yaw), glm::radians(pitch), 0.0f));
		//owner->transform.SetRotationQuat(q);

		glm::vec3 dir = glm::vec3();
		dir += m_owner->GetTransform().Right() * static_cast<float>(STR_Engine::Get().m_input.GetKeyDiff(Input::KeyCodes::VK_D, Input::KeyCodes::VK_A));
		dir += m_owner->GetTransform().Up() * static_cast<float>(STR_Engine::Get().m_input.GetKeyDiff(Input::KeyCodes::VK_SPACE, Input::KeyCodes::VK_LCTRL));
		dir += m_owner->GetTransform().Forward() * static_cast<float>(STR_Engine::Get().m_input.GetKeyDiff(Input::KeyCodes::VK_W, Input::KeyCodes::VK_S));

		if (glm::length2(dir) > 0.0f) { dir = glm::normalize(dir); }
		m_owner->IncrementTransformPos(dir * (m_speed * dt));
	}

	void CameraControllerComponent::Read(const rapidjson::Value& value)
	{
		Component::Read(value);
		JSON_READ(value, m_speed);
		JSON_READ(value, m_sensitivity);
	}
}