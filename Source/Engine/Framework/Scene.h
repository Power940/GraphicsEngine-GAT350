#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Object.h"
#include <memory>
#include <string>
#include <utility>
#include <vector>


namespace STR_FALL
{
	class Scene
	{
	private:
		std::vector<std::unique_ptr<GameObject>> m_objects = {};
		std::vector<std::unique_ptr<GameObject>> m_pendingObjects = {};
		bool m_safeToAddObject = true;

	public:
		class Game* m_game = nullptr;

		void AddObject(std::unique_ptr<GameObject> object)
		{
			if (object->m_scene == nullptr) { object->m_scene = this; }

			if (m_safeToAddObject) { m_objects.push_back(std::move(object)); m_objects.back()->Start(); }
			else { m_pendingObjects.push_back(std::move(object)); }
		}
		inline Object* GetObjectIndex(const int element) const { return m_objects[element].get(); }
		template<typename T> inline T* GetObjectName(const std::string& name)
		{
			for (auto& object : m_objects)
			{
				T* objectT = dynamic_cast<T*>(object.get());
				if (objectT != nullptr && objectT->m_name == name) { return objectT; }
			}
			return nullptr;
		}

		bool Load(std::string filePath);

		void Update(float dt);
		void Draw(Renderer& r);

		void UpdateCollisions();

		void RemoveAllObjects(bool ignorePersistant = false)
		{
			if (ignorePersistant)
			{
				m_objects.clear();
				m_pendingObjects.clear();
			}
			else
			{
				std::erase_if(m_objects, [](auto& object) { return object->m_persistent; });
				std::erase_if(m_pendingObjects, [](auto& object) { return object->m_persistent; });
			}
		}
	};
}