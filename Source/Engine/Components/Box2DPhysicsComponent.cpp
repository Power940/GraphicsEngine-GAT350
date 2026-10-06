#include "pch.h"
#include "Box2DPhysicsComponent.h"
#include <Core/Factory.h>
#include <Math/Structs.h>
#include <memory>
#include "PhysicsComponent.h"
#include <Core/StringUtils.h>
#include <Physics/PhysicsBody.h>
#include <Serialization/Json.h>
#include <string>
#include <StarFallEngine.h>

namespace STR_FALL
{
	FACTORY_REG(Box2DPhysicsComponent)

	Box2DPhysicsComponent::Box2DPhysicsComponent(const Box2DPhysicsComponent& other)
	{
		m_bodyDef = other.m_bodyDef;
		m_size = other.m_size;
		m_scale = other.m_scale;
	}

	void Box2DPhysicsComponent::Start()
	{
		m_bodyDef.owner = m_owner;
		m_physicsBody = std::make_unique<PhysicsBody>(
			m_owner->m_transform,
			m_owner->m_transform.m_scale,
			m_bodyDef,
			STR_Engine::m_phys
		);
	}

	void Box2DPhysicsComponent::Update(float dt)
	{
		m_owner->SetTransformPos(GetPosition());
		m_owner->SetTransformRotation(GetRotation());
	}

	void Box2DPhysicsComponent::Read(const rapidjson::Value& value)
	{
		PhysicsComponent::Read(value);

		JSON_READ_NAME(value, "size", m_size);
		JSON_READ_NAME(value, "scale", m_scale);

		JSON_READ_NAME(value, "m_gravityScale", m_bodyDef.gravityScale);
		JSON_READ_NAME(value, "m_linearDamping", m_bodyDef.linearDamping);
		JSON_READ_NAME(value, "m_angularDamping", m_bodyDef.angularDamping);
		JSON_READ_NAME(value, "m_constrainAngle", m_bodyDef.constrainAngle);
		JSON_READ_NAME(value, "m_isDynamic", m_bodyDef.isDynamic);
		JSON_READ_NAME(value, "m_friction", m_bodyDef.friction);
		JSON_READ_NAME(value, "m_restitution", m_bodyDef.restitution);
		JSON_READ_NAME(value, "m_density", m_bodyDef.density);
		JSON_READ_NAME(value, "m_isSensor", m_bodyDef.isSensor);

		std::string shapeName;
		JSON_READ_NAME(value, "m_shape", shapeName);

		if (!shapeName.empty())
		{
			if (EqualsIgnoreCase(shapeName, "box")) m_bodyDef.shape = PhysicsBody::Shape::Box;
			else if (EqualsIgnoreCase(shapeName, "capsule")) m_bodyDef.shape = PhysicsBody::Shape::Capsule;
			else if (EqualsIgnoreCase(shapeName, "circle")) m_bodyDef.shape = PhysicsBody::Shape::Circle;
		}
	}

	void Box2DPhysicsComponent::ApplyForce(const Vector3& force)
	{
		m_physicsBody->ApplyForce(force);
	}

	void Box2DPhysicsComponent::SetVelocity(const Vector3& velocity)
	{
		m_physicsBody->SetVelocity(velocity);
	}

	Vector3 Box2DPhysicsComponent::GetVelocity()
	{
		return m_physicsBody->GetVelocity();
	}

	void Box2DPhysicsComponent::ApplyTorque(Vector3 torque)
	{
		m_physicsBody->ApplyTorque(torque.m_x);
	}

	void Box2DPhysicsComponent::SetAngularVelocity(Vector3 angularVelocity)
	{
		m_physicsBody->SetAngularVelocity(angularVelocity.m_x);
	}

	Vector3 Box2DPhysicsComponent::GetAngularVelocity() const
	{
		return m_physicsBody->GetAngularVelocity();
	}

	void Box2DPhysicsComponent::SetPosition(const Vector3& position)
	{
		m_physicsBody->SetPosition(position);
	}

	Vector3 Box2DPhysicsComponent::GetPosition() const
	{
		return m_physicsBody->GetPosition();
	}

	void Box2DPhysicsComponent::SetRotation(const Matrix3& rotation)
	{
		m_physicsBody->SetRotation(rotation[0][0]);
	}

	Matrix3 Box2DPhysicsComponent::GetRotation() const
	{
		return m_physicsBody->GetRotation();
	}
}