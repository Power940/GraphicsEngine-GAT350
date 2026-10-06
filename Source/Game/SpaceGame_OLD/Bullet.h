#pragma once
#include "StarFallEngine.h"
#include "Components/MeshRenderer3DComponent.h"
#include <Core/Factory.h>
#include <Framework/Object.h>
#include "Marker.h"

using namespace STR_FALL;

struct Bullet : public GameObject
{
	Vector3 m_dir = Vector3();

	Bullet() = default;
	CLASS_PROTOTYPE(Bullet)

	void Update(float dt) override
	{
		IncrementTransformPos(m_dir * dt * 500);

		GetComponent<MeshRenderer3DComponent>()->UpdateMesh(m_transform);
	}

	void OnCollision(GameObject* other) override
	{
		if (other->m_tags.contains("marker") && dynamic_cast<Marker*>(other)->m_canBeHit)
		{
			other->m_toBeFreed = true;
			m_toBeFreed = true;
		}
	}
};

FACTORY_REG(Bullet);