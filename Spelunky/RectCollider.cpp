#include "pch.h"
#include "RectCollider.h"

#include "PhysicsObject.h"
#include "utils.h"

RectCollider::RectCollider(const Rectf& rect, PhysicsObject* owner):
    m_Rect(rect),
    m_Owner(owner)
{
    
}

ColliderTypes RectCollider::GetColliderType() const
{
    return ColliderTypes::rect;
}

Vector2f RectCollider::GetCenterPosition()
{
    Vector2f centerPos{m_Rect.top - m_Rect.width/2, m_Rect.left - m_Rect.height/2};
    if(m_Owner != nullptr)
    {
        centerPos += m_Owner->GetPosition();
    }
    
    return centerPos;
}

void RectCollider::DebugDraw()
{
    const Vector2f pos{ m_Owner != nullptr ? m_Owner->GetPosition() : Vector2f{0,0} };
    utils::DrawRect(Rectf{pos.x + m_Rect.left, pos.y + m_Rect.top, m_Rect.width, m_Rect.height});
}

Rectf RectCollider::GetRect()
{
    return m_Rect;
}

void RectCollider::SetRect(const Rectf& rect)
{
    m_Rect = rect;
}
