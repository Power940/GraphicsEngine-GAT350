#include "pch.h"
#include "PhysicsComponent.h"
#include <rapidjson/document.h>

namespace STR_FALL
{
	void PhysicsComponent::Read(const rapidjson::Value& value)
	{
		Component::Read(value);

		JSON_READ(value, m_mass);
		JSON_READ(value, m_damping);
		JSON_READ(value, m_angularDamping);
		JSON_READ(value, m_gravityScale);
	}
}