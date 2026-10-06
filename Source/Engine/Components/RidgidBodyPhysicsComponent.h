#pragma once
#include "PhysicsComponent.h"
#include <Math/Structs.h>

namespace STR_FALL
{
	class RidgidBodyPhysicsComponent : public PhysicsComponent
	{
	public:
		void ApplyForce(const Vector3& force) override;
		void SetVelocity(const Vector3& velocity) override;
		Vector3 GetVelocity() override;

		void ApplyTorque(Vector3 torque) override;
		void SetAngularVelocity(Vector3 angularVelocity) override;
		Vector3 GetAngularVelocity() const override;

		void SetPosition(const Vector3& position) override;
		Vector3 GetPosition() const override;
		void SetRotation(const Matrix3& position) override;
		Matrix3 GetRotation() const override;

		virtual void Update(float dt);
		virtual void Read(const rapidjson::Value& value);

	private:
		Vector3 m_acc = Vector3();
		Vector3 m_vel = Vector3();

		Vector3 m_angAcc = Vector3();
		Vector3 m_angVel = Vector3();
	};
}