#pragma once
#include <functional>

#include "Collider.h"
#include "PhysicsComponent.h"

class CirclePhysicsCollider;

class RectPhysicsCollider : public Collider
{
public:
    explicit RectPhysicsCollider(const Rectf& rect);
    virtual ColliderTypes GetColliderType() const override;
    
    void DebugDraw() const;
    const Rectf& GetRect() const;
    void SetRect(const Rectf& rect);
    
    Vector2f GetCenter() const;
    void SetCenter(const Vector2f& position);

    const Vector2f& GetVelocity() const;
    void SetVelocity(const Vector2f& newVelocity);
    void SetVelocity(float x, float y);
    void ApplyForce(const Vector2f& forceToApply);

    // Collision checks
    bool IsOverlapping(const RectPhysicsCollider& other) const;
    bool IsOverlapping(const CirclePhysicsCollider& other) const;
    bool IsOverlapping(const Collider& other) const;

    bool PredictCollision(const RectPhysicsCollider& other /*TODO: out needed */);
    bool PredictCollision(const CirclePhysicsCollider& other /*TODO: out needed */);
    // bool PredictCollision(const Collider& other);

    void UpdatePhysics();
    // void SetOnCollisionStay(std::function<void()> function);
    // void RemoveOnCollisionStay();
    

    /// Update
    ///
    /// Predict if we are going to hit world
    /// World tiles. Grid Collider???
    /// Need to know what tile we hit and where
    ///
    /// Predict if we hit creatures
    /// List of all creatures
    /// Tell player what enemy we hit
    ///
    /// So we are going to have collider type pass through or solid
    /// We have a callback function that gets called when we hit any other collider.
    /// If its solid the physics engine will apply normal opposite force.
    /// Otherwise it will do nothing but tell the subscriber we hit that object.
    /// 
    /// We might want onEnter, onStay, onExit. For now lets do onStay
    

private:
    Rectf m_Rect;
    Vector2f m_Velocity;
};
