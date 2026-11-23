#include "pch.h"
#include "CameraComponent.h"
#include "Core/Factory.h"
#include "StarFallEngine.h"

namespace STR_FALL
{
	FACTORY_REG(CameraComponent)

	void CameraComponent::Read(const rapidjson::Value& value)
	{
		Component::Read(value);

		JSON_READ(value, m_fov);
		JSON_READ(value, m_nearPlane);
		JSON_READ(value, m_farPlane);
	}

	void CameraComponent::Update(float dt)
	{
		m_view = glm::lookAtRH(m_owner->GetTransform().m_pos, m_owner->GetTransform().m_pos + m_owner->GetTransform().Forward(), m_owner->GetTransform().Up());
		m_projection = glm::perspective(glm::radians(m_fov), STR_Engine::Get().m_renderer.GetAspect(), m_nearPlane, m_farPlane);
	}

	void CameraComponent::UpdateGui()
	{
		ImGui::DragFloat("FOV", &m_fov, 0.1f);
		ImGui::DragFloat("near plane", &m_nearPlane, 0.1f);
		ImGui::DragFloat("far plane", &m_farPlane, 0.1f);
	}
}