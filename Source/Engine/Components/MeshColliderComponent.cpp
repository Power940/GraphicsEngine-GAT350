#include "pch.h"
#include "MeshColliderComponent.h"

namespace STR_FALL
{
    bool MeshColliderComponent::CheckCollision(const ColliderComponent& other)
    {
        const MeshColliderComponent* meshCollider = dynamic_cast<const MeshColliderComponent*>(&other);
        if (meshCollider)
        {
            // I hate SAT!!!

            const std::vector<VertexUV3D>& points1 = m_mesh.m_points;
            const std::vector<VertexUV3D>& points2 = meshCollider->m_mesh.m_points;
            const std::vector<int>& indices1 = m_mesh.m_indices;
            const std::vector<int>& indices2 = meshCollider->m_mesh.m_indices;

            if (points1.size() <= 0 || points2.size() <= 0 || indices1.size() <= 0 || indices2.size() <= 0)
            {
                return false;
            }

            // just so I don't redeclare the same stuff 70 times, maybe saves a little time
            Vector3 a, b, c, axis, edge1, edge2;
            float min1, max1, min2, max2, p;

            std::vector<Vector3> axes;

            for (int i = 0; i < indices1.size(); i += 3)
            {
                a = points1[indices1[i]];
                b = points1[indices1[i + 1]];
                c = points1[indices1[i + 2]];

                axis = (b - a).Cross(c - a);

                if (axis.Magnitude() > 0.00001f) { axes.push_back(axis); }
            }

            for (int i = 0; i < indices2.size(); i += 3)
            {
                a = points2[indices2[i]];
                b = points2[indices2[i + 1]];
                c = points2[indices2[i + 2]];

                axis = (b - a).Cross(c - a);

                if (axis.Magnitude() > 0.00001f) { axes.push_back(axis); }
            }

            for (int index1 = 0; index1 < indices1.size(); index1 += 3)
            {
                for (int i1 = index1; i1 < index1 + 3; i1++)
                {
                    edge1 = Vector3(points1[indices1[(i1 + 1 >= index1 + 3) ? index1 : i1 + 1]], points1[indices1[i1]]);

                    for (int index2 = 0; index2 < indices2.size(); index2 += 3)
                    {
                        for (int i2 = index2; i2 < index2 + 3; i2++)
                        {
                            edge2 = Vector3(points2[indices2[(i2 + 1 >= index2 + 3) ? index2 : i2 + 1]], points2[indices2[i2]]);

                            axis = edge1.Cross(edge2);

                            if (axis.Magnitude() > 0.00001f) { axes.push_back(axis); }
                        }
                    }
                }
            }

            for (Vector3 axis : axes)
            {
                min1 = axis.Dot(points1[0]);
                max1 = min1;
                min2 = axis.Dot(points2[0]);
                max2 = min2;

                for (Vector3 point : points1)
                {
                    p = axis.Dot(point);
                    if (p < min1) { min1 = p; }
                    else if (p > max1) { max1 = p; }
                }
                for (Vector3 point : points2)
                {
                    p = axis.Dot(point);
                    if (p < min2) { min2 = p; }
                    else if (p > max2) { max2 = p; }
                }

                if ((min1 > max2) || (min2 > max1)) { return false; }
            }

            return true;
        }
    }
}