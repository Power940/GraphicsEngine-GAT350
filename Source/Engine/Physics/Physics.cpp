#include "pch.h"
#include "Physics.h"
#include <Framework/GameObject.h>


namespace STR_FALL
{
	float const Physics::m_pixelsPerUnit = 48.0f;

	bool Physics::Initialize()
	{
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = b2Vec2{ 0.0f, 10.0f };
		m_worldId = b2CreateWorld(&worldDef);

		return true;
	}

	void Physics::Shutdown()
	{
		b2DestroyWorld(m_worldId);
	}

	void Physics::Update(float dt)
	{
		b2World_Step(m_worldId, 1.0f / 60.0f, 4);
		ProcessCollisionEvents();
	}

	void Physics::ProcessCollisionEvents()
	{
		b2ContactEvents contactEvents = b2World_GetContactEvents(m_worldId);

		for (int index = 0; index < contactEvents.beginCount; index++)
		{
			b2ContactBeginTouchEvent* contactEvent = contactEvents.beginEvents + index;

			if (!b2Shape_IsValid(contactEvent->shapeIdA) || !b2Shape_IsValid(contactEvent->shapeIdB)) { continue; }

			b2BodyId bodyA = b2Shape_GetBody(contactEvent->shapeIdA);
			b2BodyId bodyB = b2Shape_GetBody(contactEvent->shapeIdB);

			GameObject* gameObjectA = (GameObject*)b2Body_GetUserData(bodyA);
			GameObject* gameObjectB = (GameObject*)b2Body_GetUserData(bodyB);

			if (!gameObjectA || !gameObjectB || !gameObjectA->m_toBeFreed || !gameObjectB->m_toBeFreed || !gameObjectA->m_active || !gameObjectB->m_active) { continue; }

			gameObjectA->OnCollision(gameObjectB);
			gameObjectB->OnCollision(gameObjectA);
		}
		
		
		b2SensorEvents sensorEvents = b2World_GetSensorEvents(m_worldId);

		for (int index = 0; index < sensorEvents.beginCount; index++)
		{
			b2SensorBeginTouchEvent* sensorEvent = sensorEvents.beginEvents + index;

			if (!b2Shape_IsValid(sensorEvent->sensorShapeId) || !b2Shape_IsValid(sensorEvent->visitorShapeId)) { continue; }

			b2BodyId bodyA = b2Shape_GetBody(sensorEvent->sensorShapeId);
			b2BodyId bodyB = b2Shape_GetBody(sensorEvent->visitorShapeId);

			GameObject* gameObjectA = (GameObject*)b2Body_GetUserData(bodyA);
			GameObject* gameObjectB = (GameObject*)b2Body_GetUserData(bodyB);

			if (!gameObjectA || !gameObjectB || !gameObjectA->m_toBeFreed || !gameObjectB->m_toBeFreed || !gameObjectA->m_active || !gameObjectB->m_active) { continue; }

			gameObjectA->OnCollision(gameObjectB);
			gameObjectB->OnCollision(gameObjectA);
		}
	}
}
