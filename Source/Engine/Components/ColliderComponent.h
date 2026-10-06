#pragma once
#include "Component.h"
#include <Math/Structs.h>
#include <Serialization/Json.h>
#include <rapidjson/document.h>


namespace STR_FALL
{
	class ColliderComponent : public Component
	{
	public:
		BitMaskInt m_collisionMask;
		BitMaskInt m_collisionLayer;


		virtual bool CheckCollision(const ColliderComponent& other) = 0;


		virtual void Read(const rapidjson::Value& value) override
		{
			Component::Read(value);

			JSON_READ(value, m_collisionMask);
			JSON_READ(value, m_collisionLayer);
		}
	};
}