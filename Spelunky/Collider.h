#pragma once
#include "CollisionHelpers.h"
struct Vector2f;

enum class ColliderTypes
{
    circle,
    rect
};

class Collider
{
public:
    virtual ~Collider() = default;
    virtual ColliderTypes GetColliderType() const = 0;
    virtual Vector2f GetCenterPosition() const = 0;
    virtual void DebugDraw() const = 0;
    virtual bool CheckCollision(Collider* other, CollisionHelpers::HitInfo& out) const = 0;
};
