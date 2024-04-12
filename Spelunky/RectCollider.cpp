#include "pch.h"
#include "RectCollider.h"

#include "CircleCollider.h"
#include "utils.h"

RectCollider::RectCollider(const Rectf& rect):
    m_Rect(rect)
{
}

ColliderTypes RectCollider::GetColliderType() const
{
    return ColliderTypes::rect;
}

void RectCollider::DebugDraw() const
{
    utils::DrawRect(m_Rect);
}

Vector2f RectCollider::GetOrigin() const
{
    return m_Rect.GetCenter();
}

void RectCollider::SetOrigin(const Vector2f newPosition)
{
    m_Rect.left = newPosition.x - m_Rect.width/2;
    m_Rect.top = newPosition.y - m_Rect.height/2;
}

const Rectf& RectCollider::GetRect() const
{
    return m_Rect;
}

void RectCollider::SetRect(const Rectf& rect)
{
    m_Rect = rect;
}

Vector2f RectCollider::GetTopLeft() const
{
    return Vector2f{m_Rect.left, m_Rect.top};
}
