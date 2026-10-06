#pragma once
#include "RendererComponent.h"
#include <Core/Factory.h>
#include <Framework/Object.h>
#include <Math/Structs.h>
#include <Renderer/Mesh.h>
#include <Renderer/Renderer.h>
#include <Serialization/Json.h>
#include <rapidjson/document.h>


namespace STR_FALL
{
	class MeshRenderer3DComponent : public RendererComponent
	{
	public:
		MultiMesh3D m_baseMesh;
		MultiMesh3D m_mesh;

		MeshRenderer3DComponent() = default;

		CLASS_PROTOTYPE(MeshRenderer3DComponent)

		virtual void Draw(Renderer& r) override
		{
			for (Mesh3D& mesh : m_mesh.m_meshes)
			{
				if (mesh.m_texture)
				{
					r.Render3DCustomTexture(mesh.m_points, mesh.m_indices, mesh.m_texture.get());
				}
				else
				{
					r.SetColor(mesh.m_color);
					r.Render3DCustomOutline(mesh.m_points, mesh.m_indices);
				}
			}
		}

		virtual void Read(const rapidjson::Value& value) override
		{
			RendererComponent::Read(value);

			Mesh3D mesh;
			for (auto& meshValue : JSON_GET(value, "Meshes").GetArray())
			{
				JSON_READ(meshValue, mesh);
				m_baseMesh.m_meshes.push_back(mesh);
			}
			m_mesh = m_baseMesh;
		}

		void UpdateMesh(const Transform3D& newTransform)
		{
			m_mesh = m_baseMesh;
			m_mesh *= newTransform.m_rotMat;
			m_mesh *= newTransform.m_scale;
			m_mesh += newTransform.m_pos;
		}
	};

	FACTORY_REG(MeshRenderer3DComponent)
}