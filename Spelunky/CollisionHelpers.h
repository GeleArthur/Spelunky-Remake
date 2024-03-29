#pragma once
#include <vector>

#include "Tile.h"

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

    bool CheckCollision(const Collider& collider1, const Collider& collider2, HitInfo& out);
    bool CircleVsCircle(const CircleCollider& circle1, const CircleCollider& circle2, HitInfo& out);
    bool RectVsRect(const RectCollider& rect1, const RectCollider& rect2, HitInfo& out);
    bool RectVsCircle(const RectCollider& rect1, const CircleCollider& circle, HitInfo& out);
    bool CheckAgainstWorld(const Collider* collider, const std::vector<std::vector<Tile>>* worldTiles, HitInfo& out);
    bool RayVsRect(const Rectf& rect, const Vector2f& rayOrigin, const Vector2f& rayDir, RayVsRectInfo& out );
    bool DynamicRectVsRect(const Rectf& movingRect, const Vector2f& velocity, const Rectf& staticRect, RayVsRectInfo& out);
};
