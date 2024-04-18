#pragma once
struct Vector2f;

enum class ColliderTypes
{
    circle,
    rect,
};

class Collider
{
public:
    virtual ~Collider() = default;
    Collider() = default;
    Collider(const Collider&) = default;
    Collider& operator=(const Collider& c) = default;
    
    virtual ColliderTypes GetColliderType() const = 0;
};
