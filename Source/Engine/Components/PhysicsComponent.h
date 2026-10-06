#pragma once
#include "Component.h"
#include <Serialization/Json.h>

namespace STR_FALL
{
	class PhysicsComponent : public Component
	{
	public:
		virtual void ApplyForce(const Vector3& force) = 0;
		virtual void SetVelocity(const Vector3& velocity) = 0;
		virtual Vector3 GetVelocity() = 0;

		virtual void ApplyTorque(Vector3 torque) = 0;
		virtual void SetAngularVelocity(Vector3 angularVelocity) = 0;
		virtual Vector3 GetAngularVelocity() const = 0;

		virtual void SetPosition(const Vector3& position) = 0;
		virtual Vector3 GetPosition() const = 0;
		virtual void SetRotation(const Matrix3& rotation) = 0;
		virtual Matrix3 GetRotation() const = 0;

		virtual void Read(const rapidjson::Value& value);

	protected:
		float m_mass = 1.0f;
		float m_damping = 0.0f;
		float m_angularDamping = 0.0f;
		float m_gravityScale = 1.0f;
	};
}