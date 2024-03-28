#pragma once
#include <vector>

#include "Tile.h"

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

    bool CheckCollision(const Collider& collider1, const Collider& collider2, HitInfo& out);
    bool CircleVsCircle(const CircleCollider& circle1, const CircleCollider& circle2, HitInfo& out);
    bool RectVsRect(const RectCollider& rect1, const RectCollider& rect2, HitInfo& out);
    bool RectVsCircle(const RectCollider& rect1, const CircleCollider& circle, HitInfo& out);
    bool CheckAgainstWorld(const Collider* collider, const std::vector<std::vector<Tile>>* worldTiles, HitInfo& out);
};
