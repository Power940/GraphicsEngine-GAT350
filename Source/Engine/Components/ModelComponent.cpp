#include "pch.h"
#include "ModelComponent.h"
#include "Core/Factory.h"
#include <Renderer/Uniforms.h>
#include "Renderer/Model.h"
#include "StarFallEngine.h"

namespace STR_FALL
{
	FACTORY_REG(ModelComponent)

	void ModelComponent::Draw(Renderer& r)
	{
		ObjectUniform objectUniform
		{
			.model = m_owner->GetTransform().GetMatrix(),
			.normalMatrix = m_owner->GetTransform().GetMatrix()
		};

		r.SetVertexUniforms(UniformSlot::Object, &objectUniform, sizeof(objectUniform));
		r.SetFragmentUniforms(UniformSlot::Object, &objectUniform, sizeof(objectUniform));

		m_model->Draw(r, m_materials);
	}

	void ModelComponent::Read(const rapidjson::Value& value)
	{
		RendererComponent::Read(value);

		std::string m_modelName;
		JSON_READ(value, m_modelName);

		m_model = ResourceManager().Get<Model>(m_modelName, STR_Engine::Get().m_renderer);
		 //"materials": [ "materials/brick.instance.json", null ] - one entry per slot, null keeps the model's material

		if (JSON_HAS(value, "m_materials"))
		{
			for (const auto& entry : JSON_GET(value, "m_materials").GetArray())
			{
				if (entry.IsString())
				{
					auto material = ResourceManager().Get<MaterialInstance>(entry.GetString(), STR_Engine::Get().m_renderer);
					if (!material) { std::cerr << "Could not load material: " << entry.GetString() << std::endl; }
					m_materials.push_back(material);
				}
				else
				{
					m_materials.push_back(nullptr);
				}
			}
		}

	}
}