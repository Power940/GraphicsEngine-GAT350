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
			if (ImGui::CollapsingHeader("Meshes", ImGuiTreeNodeFlags_CollapsingHeader))
			{
				for (Mesh& mesh : m_meshes)
				{
					ImGui::PushID(&mesh);

					int i = mesh.materialIndex;
					ImGui::InputInt("Material Index", &i);
					if (i < 0) { i = 0; }
					mesh.materialIndex = i;

					mesh.vertexBuffer->UpdateGui();
					mesh.indexBuffer->UpdateGui();

					ImGui::PopID();
				}
			}

			if (ImGui::CollapsingHeader("Materials", ImGuiTreeNodeFlags_CollapsingHeader))
			{
				for (MaterialInstance& mat : m_materials)
				{
					ImGui::PushID(&mat);

					mat.UpdateGui();

					ImGui::PopID();
				}
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
