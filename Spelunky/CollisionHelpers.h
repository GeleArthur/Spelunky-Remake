#pragma once

class RectCollider;
class Collider;
class CircleCollider;

namespace CollisionHelpers
{
    struct HitInfo
    {
        float lambda;
        Vector2f intersectPoint;
        Vector2f normal;
    };
    
    void CheckCollision(const Collider& collider1,  const Collider& collider2, HitInfo& out);
    void CircleVsCircle(const CircleCollider& circle1, const CircleCollider& circle2, HitInfo& out);
    void RectVsRect(const RectCollider& rect1, const RectCollider& rect2, HitInfo& out);
    void RectVsCircle(const RectCollider& rect1, const CircleCollider& rect2, HitInfo& out);
};
