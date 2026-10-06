#pragma once
#include <box2d/id.h>
#include <Math/Structs.h>
#include <box2d/math_functions.h>


namespace STR_FALL
{
	class Physics
	{
	friend class PhysicsBody;
	public:
		Physics() = default;

		bool Initialize();
		void Shutdown();

		void Update(float dt);

		static const float m_pixelsPerUnit;

		static b2Vec2 ToB2(const Vector2& v) { return b2Vec2(v.m_x, v.m_y); }
		static Vector2 ToVector2(const b2Vec2& v) { return Vector2(v.x, v.y); }

		static Vector2 PixelToWorld(const Vector2& pixel) { return pixel / m_pixelsPerUnit; }
		static Vector2 WorldToPixel(const Vector2& world) { return world * m_pixelsPerUnit; }

	private:
		b2WorldId m_worldId;

		void ProcessCollisionEvents();
	};
}
