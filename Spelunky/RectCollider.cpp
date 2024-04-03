#include "pch.h"
#include "RectCollider.h"

#include "CircleCollider.h"
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

Vector2f RectCollider::GetCenterPosition() const
{
    Vector2f centerPos{m_Rect.top - m_Rect.width/2, m_Rect.left - m_Rect.height/2};
    if(m_Owner != nullptr)
    {
        centerPos += m_Owner->GetPosition();
    }
    
    return centerPos;
}

void RectCollider::DebugDraw() const
{
    const Vector2f pos{ m_Owner != nullptr ? m_Owner->GetPosition() : Vector2f{0,0} };
    utils::DrawRect(Rectf{pos.x + m_Rect.left, pos.y + m_Rect.top, m_Rect.width, m_Rect.height});
}

bool RectCollider::CheckCollision(Collider* other, collision_helpers::HitInfo& out) const
{
    switch (other->GetColliderType())
    {
    case ColliderTypes::circle:
        return CircleVsRect(dynamic_cast<const CircleCollider&>(*other), *this, out);
    case ColliderTypes::rect:
        return RectVsRect(*this, dynamic_cast<const RectCollider&>(*other), out);
    default:
        throw;
    }
}

Rectf RectCollider::GetRect() const
{
    return m_Rect;
}

void RectCollider::SetRect(const Rectf& rect)
{
    m_Rect = rect;
}
