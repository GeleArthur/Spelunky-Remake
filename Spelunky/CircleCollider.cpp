#include "pch.h"
#include "CircleCollider.h"

#include "PhysicsObject.h"
#include "utils.h"

CircleCollider::CircleCollider(const Vector2f& position, const float size, PhysicsObject* owner):
    m_CenterPosition(position),
    m_Size(size),
    m_PhysicsOwner(owner)
{
}

ColliderTypes CircleCollider::GetColliderType() const
{
    return ColliderTypes::circle;
}

Vector2f CircleCollider::GetCenterPosition() const
{
    Vector2f centerPos = m_CenterPosition;
    if(m_PhysicsOwner != nullptr)
        centerPos =+ m_PhysicsOwner->GetPosition();
    
    return centerPos;
}

void CircleCollider::DebugDraw() const
{
    utils::DrawEllipse(GetCenterPosition(), m_Size, m_Size);
}

bool CircleCollider::CheckCollision(const Collider* other, collision_helpers::HitInfo& out) const
{
    switch (other->GetColliderType())
    {
    case ColliderTypes::circle:
        return collision_helpers::CircleVsCircle(*this, dynamic_cast<const CircleCollider&>(*other), out);
        break;
    case ColliderTypes::rect:
        break;
    }
    return false;
}

Vector2f CircleCollider::GetLocalCenterPosition() const
{
    return m_CenterPosition;
}

void CircleCollider::SetLocalCenterPosition(const Vector2f& newPos)
{
    m_CenterPosition = newPos;
}

float CircleCollider::GetSize() const
{
    return m_Size;
}

void CircleCollider::SetSize(float newSize)
{
    m_Size = newSize;
}


