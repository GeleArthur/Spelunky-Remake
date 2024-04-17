#pragma once
#include "Collider.h"

class CirclePhysicsCollider;

class RectPhysicsCollider final : public Collider
{
public:
    explicit RectPhysicsCollider(const Rectf& rect);
    virtual ColliderTypes GetColliderType() const override;
    
    void DebugDraw() const;
    const Rectf& GetRect() const;
    void SetRect(const Rectf& rect);
    
    Vector2f GetCenter() const;

    const Vector2f& GetVelocity() const;
    void SetVelocity(const Vector2f& newVelocity);
    void ApplyForce(const Vector2f& forceToApply);

    // Collision checks
    bool IsOverlapping(const RectPhysicsCollider& other);
    bool IsOverlapping(const CirclePhysicsCollider& other);
    bool IsOverlapping(const Collider& other);

    bool PredictCollision(const RectPhysicsCollider& other /*TODO: out needed */);
    bool PredictCollision(const CirclePhysicsCollider& other /*TODO: out needed */);
    // bool PredictCollision(const Collider& other);

private:
    Rectf m_Rect;
    Vector2f m_Velocity;
};
