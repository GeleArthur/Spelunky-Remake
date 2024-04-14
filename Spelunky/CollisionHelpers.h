#pragma once
#include <vector>

class RectCollider;
class Collider;
class CircleCollider;

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

    bool CircleVsCircle(const CircleCollider& circle1, const CircleCollider& circle2, HitInfo& out);
    bool RectVsRectOverLab(const RectCollider& rect1, const RectCollider& rect2);
    bool CircleVsRect(const CircleCollider& circle, const RectCollider& rect1, HitInfo& out);

    bool RayVsRect(const Rectf& rect, const Vector2f& rayOrigin, const Vector2f& rayDir, RayVsRectInfo& out );
    bool RectRayVsRect(const Rectf& movingRect, const Vector2f& rayDirection, const Rectf& staticRect, RayVsRectInfo& out);
    bool CircleRayVsRect(const CircleCollider& movingCircle, const Vector2f& rayDirection,  const Rectf& staticRect, RayVsRectInfo& out);
};
