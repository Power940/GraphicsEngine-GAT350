#pragma once
#include "Resources/Resource.h"
#include "Shader.h"
#include "Pipeline.h"
#include <glm/glm.hpp>
#include "Texture.h"

namespace STR_FALL
{
	struct MaterialData
	{
		glm::vec4 baseColor = glm::vec4(1.0f);

		glm::vec3 specularColor = glm::vec3(1.0f);
		float shininess = 32.0f;

		glm::vec3 emissiveColor = glm::vec3(0.0f);
		float padding1;

		glm::vec2 tiling = glm::vec2(1.0f);
		glm::vec2 offset = glm::vec2(0.0f);

		void UpdateGui()
		{
			ImGui::DragFloat4("Base Color", glm::value_ptr(baseColor));
			ImGui::DragFloat3("Specular Color", glm::value_ptr(specularColor));
			ImGui::DragFloat3("Emissive Color", glm::value_ptr(emissiveColor));
			ImGui::DragFloat("Shininess", &shininess);
			ImGui::DragFloat2("Tiling", glm::value_ptr(tiling));
			ImGui::DragFloat2("Offset", glm::value_ptr(offset));
		}
	};

	class Material : public Resource
	{
	public:
		bool Load(const std::string& filename, const class Renderer& renderer);

		const MaterialData& GetDefaults() const { return m_defaults; }

		size_t GetTextureSlotCount() const { return m_textureSlots.size(); }
		int GetTextureSlot(const std::string& name) const;

		const Pipeline& GetPipeline() const { return m_pipeline; }
		const res_t<Texture>& GetDefaultTexture() const { return m_defaultTexture; }

		void UpdateGui()
		{
			if (ImGui::CollapsingHeader("Vertex Shader", ImGuiTreeNodeFlags_CollapsingHeader))
			{
				m_vertexShader->UpdateGui();
			}

			if (ImGui::CollapsingHeader("Fragment Shader", ImGuiTreeNodeFlags_CollapsingHeader))
			{
				m_fragmentShader->UpdateGui();
			}

			if (ImGui::CollapsingHeader("Pipeline", ImGuiTreeNodeFlags_CollapsingHeader))
			{
				m_pipeline.UpdateGui();
			}

			if (ImGui::CollapsingHeader("Texture Slots", ImGuiTreeNodeFlags_CollapsingHeader))
			{
				for (std::string& textureSlot : m_textureSlots)
				{
					ImGui::Text(textureSlot.c_str());
				}
			}

			if (ImGui::CollapsingHeader("Defaults", ImGuiTreeNodeFlags_CollapsingHeader))
			{
				m_defaults.UpdateGui();
			}

			if (ImGui::CollapsingHeader("Default Texture", ImGuiTreeNodeFlags_CollapsingHeader))
			{
				m_defaultTexture->UpdateGui();
			}
		}

	private:
		res_t<Shader> m_vertexShader;
		res_t<Shader> m_fragmentShader;
		Pipeline m_pipeline;

		MaterialData m_defaults;
		std::vector<std::string> m_textureSlots;
		res_t<Texture> m_defaultTexture;
	};
}