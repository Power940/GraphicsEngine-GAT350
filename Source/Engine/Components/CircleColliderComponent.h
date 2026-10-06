#pragma once
#include <Core/Factory.h>
#include <Framework/Object.h>
#include <Serialization/Json.h>
#include <rapidjson/document.h>
#include "ColliderComponent.h"


namespace STR_FALL
{
	class CircleColliderComponent : public ColliderComponent
	{
	public:
		CLASS_PROTOTYPE(CircleColliderComponent)

		bool CheckCollision(const ColliderComponent& other) override;

		virtual void Read(const rapidjson::Value& value) override
		{
			ColliderComponent::Read(value);

			JSON_READ(value, m_radius);
		}

		float m_radius = 0.0f;
	};

	FACTORY_REG(CircleColliderComponent)
}