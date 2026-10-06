#include "pch.h"
#include "Scene.h"
#include <Components/ColliderComponent.h>
#include <Core/Factory.h>
#include "GameObject.h"
#include <Renderer/Renderer.h>
#include <Serialization/Json.h>
#include <rapidjson/document.h>
#include <memory>
#include <string>
#include <utility>
#include <vector>


namespace STR_FALL
{
	bool Scene::Load(std::string filePath)
	{
		rapidjson::Document doc;
		if (Json::Load(filePath, doc))
		{
			if (JSON_HAS(doc, "GameObjects"))
			{
				for (auto& gameObjectValue : JSON_GET(doc, "GameObjects").GetArray())
				{
					std::string m_typeName;
					JSON_READ(gameObjectValue, m_typeName);

					auto gameObject = Factory::Instance().Create<GameObject>(m_typeName);
					gameObject->Read(gameObjectValue);

					bool m_prototype = false;
					JSON_READ(gameObjectValue, m_prototype);

					if (m_prototype)
					{
						std::string m_name;
						JSON_READ(gameObjectValue, m_name);
						Factory::Instance().PrototypeRegister<GameObject>(m_name, std::move(gameObject));
					}
					else
					{
						AddObject(std::move(gameObject));
					}
				}
			}
		}

		return true;
	}

	void Scene::Update(float dt)
	{
		m_safeToAddObject = false;
		for (auto& object : m_objects) { object->Update(dt); }
		m_safeToAddObject = true;

		UpdateCollisions();

		std::erase_if(m_objects, [](auto& object) { object->OnDestroy(); return object->m_toBeFreed; });

		for (std::unique_ptr<GameObject>& gameObject : m_pendingObjects)
		{
			m_objects.push_back(std::move(gameObject));
			m_objects.back()->Start();
		}
		m_pendingObjects.clear();
	}

	void Scene::Draw(Renderer& r)
	{
		for (auto& object : m_objects) { object->Draw(r); }
	}

	void Scene::UpdateCollisions()
	{
		float dist = -1.0f;
		GameObject* ObjectA;
		GameObject* ObjectB;
		ColliderComponent* colliderA;
		ColliderComponent* colliderB;

		for (int indexA = 0; indexA < m_objects.size(); indexA++)
		{
			ObjectA = m_objects[indexA].get();
			if (ObjectA->m_toBeFreed) { continue; }
			colliderA = ObjectA->GetComponent<ColliderComponent>();
			if (!colliderA) { continue; }

			for (int indexB = indexA + 1; indexB < m_objects.size(); indexB++)
			{
				ObjectB = m_objects[indexB].get();
				if (ObjectB->m_toBeFreed) { continue; }
				colliderB = ObjectB->GetComponent<ColliderComponent>();
				if (!colliderB) { continue; }


				if (colliderA->m_collisionMask.AnyMatch(colliderB->m_collisionLayer) && colliderA->CheckCollision(*colliderB))
				{
					ObjectA->OnCollision(ObjectB);
				}
				if (colliderA->m_collisionLayer.AnyMatch(colliderB->m_collisionMask) && colliderB->CheckCollision(*colliderA))
				{
					ObjectB->OnCollision(ObjectA);
				}
			}
		}
	}
}