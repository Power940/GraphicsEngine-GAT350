#include "pch.h"
#include "Scene.h"
#include <Core/Factory.h>
#include "GameObject.h"
#include <Renderer/Renderer.h>
#include <Serialization/Json.h>
#include <rapidjson/document.h>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <Components/CameraComponent.h>
#include "Renderer/Light.h"
#include <Components/LightComponent.h>
#include "StarFallEngine.h"


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
					if (JSON_HAS(gameObjectValue, "COMMENT"))
					{
						continue;
					}

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
		FrameUniform frameUniform{};

		auto camera = GetObjectName<GameObject>("camera");
		if (camera)
		{
			auto cameraComponent = camera->GetComponent<CameraComponent>();
			if (cameraComponent)
			{
				frameUniform.cameraPosition = camera->GetTransform().m_pos;
				frameUniform.view = cameraComponent->GetView();
				frameUniform.projection = cameraComponent->GetProjection();
				frameUniform.viewProjection = frameUniform.projection * frameUniform.view;

				r.SetVertexUniforms(UniformSlot::Frame, &frameUniform, sizeof(frameUniform));
				r.SetFragmentUniforms(UniformSlot::Frame, &frameUniform, sizeof(frameUniform));
			}
		}

		LightsUniform lightsUniform{};
		lightsUniform.ambient = m_ambient;

		auto lights = GetObjectsTag<GameObject>("light");
		for (auto light : lights)
		{
			if (!light->m_active) { continue; }

			auto lightComponent = light->GetComponent<LightComponent>();
			if (lightComponent && lightComponent->m_active)
			{
				lightsUniform.lights[lightsUniform.num_lights++] = lightComponent->GetLightData();
			}
		}

		r.SetVertexUniforms(UniformSlot::Light, &lightsUniform, sizeof(lightsUniform));
		r.SetFragmentUniforms(UniformSlot::Light, &lightsUniform, sizeof(lightsUniform));

		for (auto& object : m_objects) { object->Draw(r); }
	}

	void Scene::UpdateGui()
	{
		glm::vec3 clearColor = STR_Engine::Get().m_renderer.GetClearColor();
		ImGui::ColorEdit3("clear light", glm::value_ptr(clearColor));
		STR_Engine::Get().m_renderer.SetClearColor(clearColor);
		ImGui::ColorEdit3("ambient light", glm::value_ptr(m_ambient));
	}
}