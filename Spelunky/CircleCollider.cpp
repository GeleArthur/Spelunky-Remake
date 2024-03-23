#include "pch.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(const Vector2f& position, const float size):
    m_CenterPosition(position),
    m_Size(size)
{
}

ColliderTypes CircleCollider::GetColliderType() const
{
    return ColliderTypes::circle;
}

Vector2f CircleCollider::GetCenterPosition()
{
    return m_CenterPosition;
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
