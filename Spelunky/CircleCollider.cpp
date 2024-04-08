#include "pch.h"
#include "CircleCollider.h"

#include "PhysicsObject.h"
#include "utils.h"

CircleCollider::CircleCollider(const Vector2f& position, const float size):
    m_CenterPosition(position),
    m_Size(size)
{
}

ColliderTypes CircleCollider::GetColliderType() const
{
    return ColliderTypes::circle;
}

void CircleCollider::DebugDraw() const
{
    utils::DrawEllipse(GetCenterPosition(), m_Size, m_Size);
}

float CircleCollider::GetSize() const
{
    return m_Size;
}

void CircleCollider::SetSize(const float newSize)
{
    m_Size = newSize;
}

const Vector2f& CircleCollider::GetCenterPosition() const
{
    return m_CenterPosition;
}

void CircleCollider::SetCenterPosition(const Vector2f& newPosition)
{
    m_CenterPosition = newPosition;
}


