#pragma once
#include <StarFallEngine.h>
#include <Core/Factory.h>

using namespace STR_FALL;

struct Marker : public GameObject
{
	bool m_canBeHit = false;

	Marker() = default;
	CLASS_PROTOTYPE(Marker)

	void Update(float dt) override { }

	virtual void Read(const rapidjson::Value& value) override
	{
		GameObject::Read(value);

		JSON_READ(value, m_canBeHit);
	}
};

FACTORY_REG(Marker)