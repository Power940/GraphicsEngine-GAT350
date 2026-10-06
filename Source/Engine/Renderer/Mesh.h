#pragma once
#include "Math/Structs.h"
#include "Texture.h"
#include "Resources/Resource.h"
#include <cassert>
#include <vector>


namespace STR_FALL
{
	struct Mesh2D;
	struct MultiMesh2D;
	struct Mesh3d;
	struct MultiMesh3D;

	struct Mesh3D
	{
		std::vector<VertexUV3D> m_points;
		std::vector<int> m_indices;
		Color m_color;
		res_t<Texture> m_texture;

		inline Mesh3D(const std::vector<VertexUV3D>& points = {}, const std::vector<int>& indices = {}, const Color& color = Color(), const res_t<Texture>& texture = nullptr) :
			m_points(points), m_indices(indices), m_color(color), m_texture(texture) {}
		inline Mesh3D(const std::vector<VertexUV3D>& newPoints, const Mesh3D& mesh) :
			m_points(newPoints), m_indices(mesh.m_indices), m_color(mesh.m_color), m_texture(mesh.m_texture) {}
		inline Mesh3D(const MultiMesh3D& meshs);

		Mesh3D operator+(const Vector3& rhs) const
		{
			std::vector<VertexUV3D> newPoints;
			for (const VertexUV3D& point : m_points) { newPoints.push_back(VertexUV3D(point.m_pos + rhs, point.m_uv)); }
			return Mesh3D(newPoints, *this);
		}
		Mesh3D operator-(const Vector3& rhs) const
		{
			std::vector<VertexUV3D> newPoints;
			for (const VertexUV3D& point : m_points) { newPoints.push_back(VertexUV3D(point.m_pos - rhs, point.m_uv)); }
			return Mesh3D(newPoints, *this);
		}
		Mesh3D operator*(const Vector3& rhs) const
		{
			std::vector<VertexUV3D> newPoints;
			for (const VertexUV3D& point : m_points) { newPoints.push_back(VertexUV3D(point.m_pos * rhs, point.m_uv)); }
			return Mesh3D(newPoints, *this);
		}
		Mesh3D operator/(const Vector3& rhs) const
		{
			std::vector<VertexUV3D> newPoints;
			for (const VertexUV3D& point : m_points) { newPoints.push_back(VertexUV3D(point.m_pos / rhs, point.m_uv)); }
			return Mesh3D(newPoints, *this);
		}
		Mesh3D operator+=(const Vector3& rhs)
		{
			for (VertexUV3D& point : m_points) { point.m_pos += rhs; }
			return *this;
		}
		Mesh3D operator-=(const Vector3& rhs)
		{
			for (VertexUV3D& point : m_points) { point.m_pos -= rhs; }
			return *this;
		}
		Mesh3D operator*=(const Vector3& rhs)
		{
			for (VertexUV3D& point : m_points) { point.m_pos *= rhs; }
			return *this;
		}
		Mesh3D operator/=(const Vector3& rhs)
		{
			for (VertexUV3D& point : m_points) { point.m_pos /= rhs; }
			return *this;
		}

		Mesh3D operator*(const Matrix3& rhs) const
		{
			std::vector<VertexUV3D> newPoints;
			for (const VertexUV3D& point : m_points) { newPoints.push_back(VertexUV3D(point.m_pos * rhs, point.m_uv)); }
			return Mesh3D(newPoints, *this);
		}
		Mesh3D operator*=(const Matrix3& rhs)
		{
			for (VertexUV3D& point : m_points) { point.m_pos *= rhs; }
			return *this;
		}

		VertexUV3D operator[](const unsigned int element) const { assert(element < m_points.size()); return m_points[element]; }
		VertexUV3D& operator[](const unsigned int element) { assert(element < m_points.size()); return m_points[element]; }

		float GetRadius(Vector3 translation = Vector3())
		{
			float dist = -1.0f;
			for (VertexUV3D vec : m_points)
			{
				vec.m_pos -= translation;
				dist = (vec.m_pos.Magnitude() > dist) ? vec.m_pos.Magnitude() : dist;
			}
			return dist;
		}
		std::vector<Vector3> GetPoints() 
		{
			std::vector<Vector3> temp;
			for (VertexUV3D& point : m_points) { temp.push_back(point.m_pos); }
			return temp;
		}
		std::vector<Vector2> GetUVs()
		{
			std::vector<Vector2> temp;
			for (VertexUV3D& point : m_points) { temp.push_back(point.m_uv); }
			return temp;
		}
	};

	struct MultiMesh3D
	{
		std::vector<Mesh3D> m_meshes;

		inline MultiMesh3D(const std::vector<Mesh3D>& meshes = {}) : m_meshes(meshes) {}
		inline MultiMesh3D(const Mesh3D& mesh) : m_meshes({ mesh }) {}

		MultiMesh3D operator+(const Vector3& rhs) const
		{
			std::vector<Mesh3D> newMeshes;
			std::vector<VertexUV3D> newPoints;
			for (const Mesh3D& mesh : m_meshes)
			{
				for (const VertexUV3D& point : mesh.m_points) { newPoints.push_back(VertexUV3D(point.m_pos + rhs, point.m_uv)); }
				newMeshes.push_back(Mesh3D(newPoints, mesh));
				newPoints.clear();
			}
			return MultiMesh3D(newMeshes);
		}
		MultiMesh3D operator-(const Vector3& rhs) const
		{
			std::vector<Mesh3D> newMeshes;
			std::vector<VertexUV3D> newPoints;
			for (const Mesh3D& mesh : m_meshes)
			{
				for (const VertexUV3D& point : mesh.m_points) { newPoints.push_back(VertexUV3D(point.m_pos - rhs, point.m_uv)); }
				newMeshes.push_back(Mesh3D(newPoints, mesh));
				newPoints.clear();
			}
			return MultiMesh3D(newMeshes);
		}
		MultiMesh3D operator*(const Vector3& rhs) const
		{
			std::vector<Mesh3D> newMeshes;
			std::vector<VertexUV3D> newPoints;
			for (const Mesh3D& mesh : m_meshes)
			{
				for (const VertexUV3D& point : mesh.m_points) { newPoints.push_back(VertexUV3D(point.m_pos * rhs, point.m_uv)); }
				newMeshes.push_back(Mesh3D(newPoints, mesh));
				newPoints.clear();
			}
			return MultiMesh3D(newMeshes);
		}
		MultiMesh3D operator/(const Vector3& rhs) const
		{
			std::vector<Mesh3D> newMeshes;
			std::vector<VertexUV3D> newPoints;
			for (const Mesh3D& mesh : m_meshes)
			{
				for (const VertexUV3D& point : mesh.m_points) { newPoints.push_back(VertexUV3D(point.m_pos / rhs, point.m_uv)); }
				newMeshes.push_back(Mesh3D(newPoints, mesh));
				newPoints.clear();
			}
			return MultiMesh3D(newMeshes);
		}
		MultiMesh3D operator+=(const Vector3& rhs)
		{
			for (Mesh3D& mesh : m_meshes) { for (VertexUV3D& point : mesh.m_points) { point.m_pos += rhs; } }
			return *this;
		}
		MultiMesh3D operator-=(const Vector3& rhs)
		{
			for (Mesh3D& mesh : m_meshes) { for (VertexUV3D& point : mesh.m_points) { point.m_pos -= rhs; } }
			return *this;
		}
		MultiMesh3D operator*=(const Vector3& rhs)
		{
			for (Mesh3D& mesh : m_meshes) { for (VertexUV3D& point : mesh.m_points) { point.m_pos *= rhs; } }
			return *this;
		}
		MultiMesh3D operator/=(const Vector3& rhs)
		{
			for (Mesh3D& mesh : m_meshes) { for (VertexUV3D& point : mesh.m_points) { point.m_pos /= rhs; } }
			return *this;
		}

		MultiMesh3D operator*(const Matrix3& rhs) const
		{
			std::vector<Mesh3D> newMeshes;
			std::vector<VertexUV3D> newPoints;
			for (const Mesh3D& mesh : m_meshes)
			{
				for (const VertexUV3D& point : mesh.m_points) { newPoints.push_back(VertexUV3D(point.m_pos * rhs, point.m_uv)); }
				newMeshes.push_back(Mesh3D(newPoints, mesh));
				newPoints.clear();
			}
			return MultiMesh3D(newMeshes);
		}
		MultiMesh3D operator*=(const Matrix3& rhs)
		{
			for (Mesh3D& mesh : m_meshes) { for (VertexUV3D& point : mesh.m_points) { point.m_pos *= rhs; } }
			return *this;
		}

		Mesh3D operator[](const unsigned int element) const { assert(element < m_meshes.size()); return m_meshes[element]; }
		Mesh3D& operator[](const unsigned int element) { assert(element < m_meshes.size()); return m_meshes[element]; }

		float GetRadius(Vector3 translation = Vector3(), int meshIndex = 0)
		{
			float dist = -1.0f;
			for (VertexUV3D vec : m_meshes[0].m_points)
			{
				vec.m_pos -= translation;
				dist = (vec.m_pos.Magnitude() > dist) ? vec.m_pos.Magnitude() : dist;
			}
			return dist;
		}
	};

	inline Mesh3D::Mesh3D(const MultiMesh3D& meshs) : m_points(meshs[0].m_points), m_indices(meshs[0].m_indices), m_color(meshs[0].m_color), m_texture(meshs[0].m_texture) {}
}