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
    Collider() = default;
    virtual ~Collider() = default;
    Collider(const Collider&) = default;
    Collider& operator=(const Collider& c) = default;
    Collider(Collider&& other) = default;
    Collider& operator=(Collider&& c) = default;
    
    virtual ColliderTypes GetColliderType() const = 0;
};
