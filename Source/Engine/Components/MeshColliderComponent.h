#pragma once
#include <Core/Factory.h>
#include <Framework/Object.h>
#include <Serialization/Json.h>
#include <rapidjson/document.h>
#include "ColliderComponent.h"
#include <Renderer/Mesh.h>


namespace STR_FALL
{
	class MeshColliderComponent : public ColliderComponent
	{
	public:
		CLASS_PROTOTYPE(MeshColliderComponent)

		bool CheckCollision(const ColliderComponent& other) override;

		virtual void Read(const rapidjson::Value& value) override
		{
			ColliderComponent::Read(value);
		}

		Mesh3D m_mesh;
	};

	FACTORY_REG(MeshColliderComponent)
}