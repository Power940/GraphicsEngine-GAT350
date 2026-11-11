#include "pch.h"
#include "CameraControllerComponent.h"
#include "Core/Factory.h"
#include "StarFallEngine.h"
#include <glm/gtx/norm.hpp>
#include <glm/glm.hpp>

namespace STR_FALL
{
	FACTORY_REG(CameraControllerComponent)
	
	void CameraControllerComponent::Update(float dt)
	{
		glm::vec2 axis = STR_Engine::Get().m_input.GetMouseRelative() * m_sensitivity;

		m_yaw -= axis.x;
		m_pitch -= axis.y;
		if (m_pitch < (-F_HPI + 0.01f)) { m_pitch = -F_HPI + 0.01f; }
		if (m_pitch < (F_HPI - 0.01f)) { m_pitch = F_HPI - 0.01f; }

		glm::quat q = glm::quat_cast(glm::eulerAngleYXZ(m_yaw, m_pitch, 0.0f));
		m_owner->SetTransformRotation(q);

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