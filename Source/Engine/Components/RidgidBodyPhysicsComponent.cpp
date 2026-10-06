#include "pch.h"
#include "RidgidBodyPhysicsComponent.h"
#include <Core/Factory.h>
#include <Math/Structs.h>
#include "PhysicsComponent.h"
#include <Serialization/Json.h>

namespace STR_FALL
{
	FACTORY_REG(RidgidBodyPhysicsComponent)

	void STR_FALL::RidgidBodyPhysicsComponent::ApplyForce(const Vector3& force)
	{
		m_acc = force / m_mass;
	}

	void RidgidBodyPhysicsComponent::SetVelocity(const Vector3& velocity)
	{
		m_vel = velocity;
	}

	Vector3 RidgidBodyPhysicsComponent::GetVelocity()
	{
		return m_vel;
	}

	void RidgidBodyPhysicsComponent::ApplyTorque(Vector3 torque)
	{
		m_angAcc += torque / m_mass;
	}

	void RidgidBodyPhysicsComponent::SetAngularVelocity(Vector3 angularVelocity)
	{
		m_angVel = angularVelocity;
	}

	Vector3 RidgidBodyPhysicsComponent::GetAngularVelocity() const
	{
		return m_angVel;
	}

	void RidgidBodyPhysicsComponent::SetPosition(const Vector3& position)
	{
		m_owner->SetTransformPos(position);
	}

	Vector3 RidgidBodyPhysicsComponent::GetPosition() const
	{
		return m_owner->GetTransform().m_pos;
	}

	void RidgidBodyPhysicsComponent::SetRotation(const Matrix3& rotation)
	{
		m_owner->SetTransformRotation(rotation);
	}

	Matrix3 RidgidBodyPhysicsComponent::GetRotation() const
	{
		return m_owner->GetTransform().m_rotMat;
	}

	void RidgidBodyPhysicsComponent::Update(float dt)
	{
		m_vel += m_acc * dt;
		m_vel *= 1.0f / (1.0f + m_damping * dt);

		m_angVel += m_angAcc * dt;
		m_angVel *= 1.0f / (1.0f + m_angularDamping * dt);

		m_owner->IncrementTransformPos(m_vel * dt);
		m_owner->IncrementTransformRotation(Matrix3::RotationXYZ(m_angVel));

		m_acc = Vector3();
		m_angAcc = Vector3();
	}

	void RidgidBodyPhysicsComponent::Read(const rapidjson::Value& value)
	{
		PhysicsComponent::Read(value);

		JSON_READ(value, m_vel);
		JSON_READ(value, m_angVel);
	}
}