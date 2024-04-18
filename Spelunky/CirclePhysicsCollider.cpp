#include "pch.h"
#include "CirclePhysicsCollider.h"

#include "GizmosDrawer.h"

#include "utils.h"

CirclePhysicsCollider::CirclePhysicsCollider(const Vector2f& position, const float size):
    m_Position(position),
    m_Size(size)
{
}

ColliderTypes CirclePhysicsCollider::GetColliderType() const
{
    return ColliderTypes::circle;
}

void CirclePhysicsCollider::DebugDraw() const
{
    GizmosDrawer::DrawCircle(m_Position, m_Size);
}

float CirclePhysicsCollider::GetSize() const
{
    return m_Size;
}

void CirclePhysicsCollider::SetSize(const float newSize)
{
    m_Size = newSize;
}
