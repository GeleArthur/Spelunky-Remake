#include "pch.h"
#include "CollisionHelpers.h"

#include "Collider.h"

void CollisionHelpers::CheckCollision(const Collider& collider1, const Collider& collider2, HitInfo& out)
{
    const char collider1Type = static_cast<char>(collider1.GetColliderType());
    const char collider2Type = static_cast<char>(collider2.GetColliderType());

    // Real 
    switch (collider1Type | collider2Type)
    {
    case 0b0000'0001:
        CircleVsCircle(reinterpret_cast<const CircleCollider&>(collider1),
                       reinterpret_cast<const CircleCollider&>(collider2), out);
        break;
    case 0b0000'0010:
        RectVsRect(reinterpret_cast<const RectCollider&>(collider1),
                       reinterpret_cast<const RectCollider&>(collider2), out);
        break;
    case 0b0000'0011:
        if(collider1Type == 0b0000'0001)
            RectVsCircle(reinterpret_cast<const RectCollider&>(collider2), reinterpret_cast<const CircleCollider&>(collider1),  out);
        else
            RectVsCircle(reinterpret_cast<const RectCollider&>(collider1), reinterpret_cast<const CircleCollider&>(collider2),  out);
    default:
        throw;
    }
}

void CollisionHelpers::CircleVsCircle(const CircleCollider& circle1, const CircleCollider& circle2, HitInfo& out)
{
}

void CollisionHelpers::RectVsRect(const RectCollider& rect1, const RectCollider& rect2, HitInfo& out)
{
    
}

void CollisionHelpers::RectVsCircle(const RectCollider& rect1, const CircleCollider& rect2, HitInfo& out)
{
}
