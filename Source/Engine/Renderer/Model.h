#pragma once
#include "Resources/Resource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>
#include "MaterialInstance.h"

struct aiNode;
struct aiMesh;
struct aiScene;

namespace STR_FALL
{
	class Model : public Resource
	{
	public:
		struct Vertex
		{
			glm::vec3 position;
			glm::vec2 texcoord;
			glm::vec3 normal;
			glm::vec3 tangent;
		};

		struct Mesh
		{
			std::unique_ptr<VertexBuffer> vertexBuffer;
			std::unique_ptr<IndexBuffer> indexBuffer;
			uint32_t materialIndex = 0;
		};

	public:
		bool Load(const std::string& filename, const class Renderer& renderer);
		void Draw(class Renderer& renderer, const std::vector<res_t<MaterialInstance>>& overrides = {}) const;

		void UpdateGui()
		{
			ImGui::Text("Meshes");
			ImGui::Separator();
			for (size_t i = 0; i < m_meshes.size(); i++)
			{
				ImGui::Text("Mesh [%d]: Material [%d]", i, m_meshes[i].materialIndex);
			}

			ImGui::Text("Materials");
			ImGui::Separator();
			for (size_t i = 0; i < m_materials.size(); i++)
			{
				ImGui::Text("Material [%d]: %s", i, m_materials[i].m_name.c_str());
			}
		}

	private:
		void ProcessNode(aiNode* node, const aiScene* scene, const class Renderer& renderer);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene, const class Renderer& renderer);

		void LoadMaterials(const aiScene* scene, const std::string& directory, const class Renderer& renderer);

	private:
		std::vector<Mesh> m_meshes;
		std::vector<MaterialInstance> m_materials;
	};
}
