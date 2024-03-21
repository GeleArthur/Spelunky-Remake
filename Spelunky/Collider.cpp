#include "pch.h"
#include "Collider.h"

Collider::Collider(const Vector2f& centerPosition):
    m_CenterPosition(centerPosition)
{
}

Collider::~Collider()
{
}

bool Collider::CheckAgainstRect(const Rectf& other, HitInfo& out)
{
}

Vector2f& Collider::GetCenterPosition()
{
    return m_CenterPosition;
}
