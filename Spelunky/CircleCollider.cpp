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

Vector2f CircleCollider::GetCenterPosition()
{
    Vector2f centerPos = m_CenterPosition;
    if(m_PhysicsOwner != nullptr)
        centerPos =+ m_PhysicsOwner->GetPosition();
    
    return centerPos;
}

void CircleCollider::DebugDraw()
{
    utils::DrawEllipse(GetCenterPosition(), m_Size, m_Size);
}

Vector2f CircleCollider::GetLocalCenterPosition() const
{
    return m_CenterPosition;
}

void CircleCollider::SetLocalCenterPosition(const Vector2f& newPos)
{
    m_CenterPosition = newPos;
}

// bool SphereCollider::CheckAgainstRect(const Rectf& other, HitInfo& out)
// {
//     Vector2f sidesToTest{m_CenterPosition};
//     if(m_CenterPosition.x < other.left) sidesToTest.x = other.left;
//     else if (m_CenterPosition.x > other.left + other.width) sidesToTest.x = other.left + other.width;
//
//     if(m_CenterPosition.y < other.bottom) sidesToTest.y = other.bottom;
//     else if (m_CenterPosition.y > other.bottom + other.height) sidesToTest.y = other.bottom + other.height;
//
//     if(sidesToTest.SquaredLength() < m_Size*m_Size)
//     {
//         out.normal;
//         
//         return true;
//     }
//     return false;
// }
