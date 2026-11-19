#pragma once
#include "Resources/Resource.h"
#include "Material.h"
#include "Texture.h"

namespace STR_FALL
{
	class Texture;

	class MaterialInstance : public Resource
	{
	public:
		MaterialInstance() = default;
		explicit MaterialInstance(const res_t<Material> material);

		void Initialize(const res_t<Material>& material);
		bool Load(const std::string& filename, const class Renderer& renderer);

		void Bind(SDL_GPUCommandBuffer* commandBuffer, SDL_GPURenderPass* renderPass) const;

		void SetTexture(size_t slot, res_t<Texture> texture);
		bool SetTexture(const std::string& name, res_t<Texture> texture);

		MaterialData& GetData() { return m_data; }
		const MaterialData& GetData() const { return m_data; }
		const Material& GetMaterial() const { return *m_material; }

		std::string m_materialName = "";

		void UpdateGui() override
		{
			ImGui::Text("Material Name: %s", m_materialName.c_str());

			ImGui::ColorEdit4("Base Color", glm::value_ptr(m_data.baseColor));
			ImGui::ColorEdit3("Specular Color", glm::value_ptr(m_data.specularColor));
			ImGui::ColorEdit3("Emissive Color", glm::value_ptr(m_data.emissiveColor));
			ImGui::SliderFloat("Shininess", &m_data.shininess, 0, 256);
			ImGui::DragFloat2("Tiling", glm::value_ptr(m_data.tiling), 0.1f);
			ImGui::DragFloat2("Offset", glm::value_ptr(m_data.offset), 0.1f);

			for (auto& Texture : m_textures)
			{
				if (Texture) { Texture->UpdateGui(); }
			}
		}

	private:
		res_t<Material> m_material;
		MaterialData m_data;
		std::vector<res_t<Texture>> m_textures;
	};
}