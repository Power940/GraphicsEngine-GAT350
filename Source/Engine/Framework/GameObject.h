#pragma once
#include <Components/Component.h>
#include <Math/Structs.h>
#include "Object.h"
#include <Components/RendererComponent.h>
#include <concepts>
#include <rapidjson/document.h>
#include <Serialization/Json.h>
#include <memory>
#include <string>
#include <vector>
#include <unordered_set>
#include <Core/Factory.h>
#include <Renderer/Renderer.h>
#include <utility>


namespace STR_FALL
{
	class Scene;

	struct GameObject : public Object
	{ friend Scene;

	public:
		std::unordered_set<std::string> m_tags;
		Transform3D m_transform = Transform3D();
		std::vector<std::unique_ptr<Component>> m_components;
		Scene* m_scene = nullptr;
		bool m_toBeFreed = false;
		bool m_persistent = false;


		inline GameObject() = default;
		inline GameObject(const GameObject& other): Object(other), m_tags(other.m_tags), m_transform(other.m_transform), m_scene(other.m_scene)
		{
			for (const std::unique_ptr<Component>& component : other.m_components)
			{
				auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
				clone->m_owner = this;
				m_components.push_back(std::move(clone));
			}
		}

		CLASS_PROTOTYPE(GameObject)

		virtual void Start();
		virtual void Update(float dt);
		virtual void Draw(Renderer& r)
		{
			for (std::unique_ptr<Component>& component : m_components)
			{
				if (!component->m_active)
				{
					continue;
				}
				RendererComponent* rend = dynamic_cast<RendererComponent*>(component.get());
				if (rend)
				{
					rend->Draw(r);
				}
			}
		}
		virtual void OnCollision(GameObject* other) {}
		virtual void OnDestroy();

		inline Transform3D GetTransform() const { return m_transform; }
		void SetTransform(const Transform3D& transform)
		{
			m_transform = transform;
		}

		void SetTransformPos(const Vector3& pos)
		{
			m_transform.m_pos = pos;
		}
		void IncrementTransformPos(const Vector3& pos)
		{
			m_transform.m_pos += pos;
		}
		void SetTransformScale(const Vector3& scale)
		{
			m_transform.m_scale = scale;
		}
		void IncrementTransformScale(const Vector3& scale)
		{
			m_transform.m_scale += scale;
		}
		void SetTransformRotation(const Matrix3& rot)
		{
			m_transform.m_rotMat = rot;
		}
		void IncrementTransformRotation(const Matrix3& rot)
		{
			m_transform.m_rotMat = m_transform.m_rotMat * rot;
		}

		template<std::derived_from<Component> T>
		T* GetComponent()
		{
			T* result;
			for (std::unique_ptr<Component>& component : m_components)
			{
				result = dynamic_cast<T*>(component.get());
				if (result) { return result; }
			}

			return nullptr;
		}
		void AddComponent(std::unique_ptr<Component> component)
		{
			component->m_owner = this;
			m_components.push_back(std::move(component));
		}

		virtual void Read(const rapidjson::Value& value) override
		{
			Object::Read(value);

			JSON_READ(value, m_tags);
			JSON_READ(value, m_transform);
			JSON_READ(value, m_persistent);

			if (JSON_HAS(value, "m_components"))
			{
 				for (auto& componentValue : JSON_GET(value, "m_components").GetArray())
				{
					std::string m_typeName;
					JSON_READ(componentValue, m_typeName);

					auto component = Factory::Instance().Create<Component>(m_typeName);
					if (component)
					{
						component->Read(componentValue);
						AddComponent(std::move(component));
					}
				}
			}
		}
	};
}