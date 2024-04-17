#pragma once
#include <vector>

class RectPhysicsCollider;
class Collider;
class CirclePhysicsCollider;

namespace collision_helpers
{
    struct HitInfo
    {
        float lambda;
        Vector2f intersectPoint;
        Vector2f normal;
    };

    struct RayVsRectInfo
    {
        Vector2f normal;
        Vector2f pointHit;
        float nearHit;
        float farHit;
    };

    bool CircleVsCircle(const CirclePhysicsCollider& circle1, const CirclePhysicsCollider& circle2, HitInfo& out);
    bool RectVsRectOverLab(const RectPhysicsCollider& rect1, const RectPhysicsCollider& rect2);
    bool CircleVsRect(const CirclePhysicsCollider& circle, const RectPhysicsCollider& rect1, HitInfo& out);

    bool RayVsRect(const Rectf& rect, const Vector2f& rayOrigin, const Vector2f& rayDir, RayVsRectInfo& out );
    bool RectRayVsRect(const Rectf& movingRect, const Vector2f& rayDirection, const Rectf& staticRect, RayVsRectInfo& out);
    bool CircleRayVsRect(const CirclePhysicsCollider& movingCircle, const Vector2f& rayDirection,  const Rectf& staticRect, RayVsRectInfo& out);
};
