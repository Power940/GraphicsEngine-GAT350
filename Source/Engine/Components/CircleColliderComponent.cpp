#include "pch.h"
#include "CircleColliderComponent.h"
#include "Component.h"

namespace STR_FALL
{
    bool CircleColliderComponent::CheckCollision(const ColliderComponent& other)
    {
        const CircleColliderComponent* circleCollider = dynamic_cast<const CircleColliderComponent*>(&other);
        if (circleCollider)
        {
            return (m_owner->m_transform.m_pos - circleCollider->m_owner->m_transform.m_pos).Magnitude() <= (m_radius + circleCollider->m_radius);
        }
    }
}