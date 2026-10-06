#pragma once
#include "PhysicsComponent.h"
#include <Framework/Object.h>
#include <Math/Structs.h>
#include <Physics/PhysicsBody.h>
#include <Serialization/Json.h>
#include <memory>

namespace STR_FALL
{
	class Box2DPhysicsComponent : public PhysicsComponent
	{
	public:
		Box2DPhysicsComponent() = default;
		Box2DPhysicsComponent(const Box2DPhysicsComponent& other);

		CLASS_PROTOTYPE(Box2DPhysicsComponent)

		void Start() override;
		void Update(float dt) override;
		void Read(const rapidjson::Value& value) override;

		void ApplyForce(const Vector3& force) override;
		void SetVelocity(const Vector3& velocity) override;
		Vector3 GetVelocity() override;
		void ApplyTorque(Vector3 torque) override;
		void SetAngularVelocity(Vector3 angularVelocity) override;
		Vector3 GetAngularVelocity() const override;
		void SetPosition(const Vector3& position) override;
		Vector3 GetPosition() const override;
		void SetRotation(const Matrix3& rotation) override;
		Matrix3 GetRotation() const override;

	private:
		Vector2 m_size = Vector2();
		Vector2 m_scale = Vector2(1.0f, 1.0f);

		PhysicsBody::PhysicsBodyDef m_bodyDef;
		std::unique_ptr<PhysicsBody> m_physicsBody;

	};
}