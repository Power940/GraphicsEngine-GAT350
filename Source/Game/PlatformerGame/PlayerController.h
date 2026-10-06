#pragma once
#include <StarFallEngine.h>
#include <Core/Factory.h>
#include <Components/MeshColliderComponent.h>
#include <Framework/GameObject.h>
#include <Framework/Object.h>
#include <Input/Input.h>
#include <Math/Structs.h>
#include <Renderer/Mesh.h>
#include <Serialization/Json.h>
#include <rapidjson/document.h>
#include <iostream>
#include <ostream>


struct PlayerController : public STR_FALL::GameObject
{
	STR_FALL::Camera3D m_cam = STR_FALL::Camera3D::Empty;
	STR_FALL::Mesh3D m_mesh;
	STR_FALL::Vector2 m_dir = STR_FALL::Vector2(0.0f, 0.0f);
	STR_FALL::Vector3 m_vel = STR_FALL::Vector3();
	STR_FALL::MeshColliderComponent* collider = nullptr;

	PlayerController() = default;
	CLASS_PROTOTYPE(PlayerController)

	void Start() override
	{
		collider = GetComponent<STR_FALL::MeshColliderComponent>();
		collider->m_mesh = m_mesh;
		collider->m_mesh *= m_transform.m_rotMat;
		collider->m_mesh *= m_transform.m_scale;
		collider->m_mesh += m_transform.m_pos;
	}

	void Update(float dt) override
	{
		m_dir = STR_FALL::STR_Engine::Get().m_input.GetKeyDir(
			STR_FALL::Input::VK_D, STR_FALL::Input::VK_A,
			STR_FALL::Input::VK_W, STR_FALL::Input::VK_S
		).Normalize();

		m_vel.m_x = -m_dir.m_x;
		m_vel.m_z = m_dir.m_y;
		if (STR_FALL::STR_Engine::Get().m_input.GetKeyPressed(STR_FALL::Input::VK_SPACE))
		{
			m_vel.m_y = -1.0f;
		}

		IncrementTransformPos(m_vel * 50.0f * dt);

		collider->m_mesh = m_mesh;
		collider->m_mesh *= m_transform.m_rotMat;
		collider->m_mesh *= m_transform.m_scale;
		collider->m_mesh += m_transform.m_pos;

		m_cam.m_transform = m_transform;
		m_cam.m_transform.m_pos += (m_transform.m_rotMat.Up() * -20.0f) + (m_transform.m_rotMat.Forward() * -30.0f);

		m_vel.m_y += 0.05f;
	}


	void OnCollision(GameObject* other) override
	{
		if (other->m_tags.contains("platform"))
		{
			m_vel.m_y = 0;
		}
	}


	virtual void Read(const rapidjson::Value& value) override
	{
		GameObject::Read(value);

		JSON_READ(value, m_cam);
		JSON_READ(JSON_GET(value, "m_mesh"), m_mesh);
	}
};

FACTORY_REG(PlayerController);