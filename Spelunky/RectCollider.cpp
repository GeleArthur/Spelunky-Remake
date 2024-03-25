#include "pch.h"
#include "RectCollider.h"

ColliderTypes RectCollider::GetColliderType() const
{
    return ColliderTypes::rect;
}

Vector2f RectCollider::GetCenterPosition()
{
    return Vector2f{0,0};
}

void RectCollider::DebugDraw()
{
}
