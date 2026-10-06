#pragma once
#include "StarFallEngine.h"
#include "Components/MeshRenderer3DComponent.h"
#include <Core/Factory.h>
#include <Framework/Object.h>
#include <Components/MeshColliderComponent.h>

using namespace STR_FALL;

struct Platform : public GameObject
{
	Platform() = default;
	CLASS_PROTOTYPE(Platform)

	void Start() override
	{
		GetComponent<STR_FALL::MeshRenderer3DComponent>()->UpdateMesh(m_transform);
		GetComponent<STR_FALL::MeshColliderComponent>()->m_mesh = GetComponent<STR_FALL::MeshRenderer3DComponent>()->m_mesh;
	}
};

FACTORY_REG(Platform);