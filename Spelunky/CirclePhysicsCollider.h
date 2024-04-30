#pragma once
#include "Collider.h"

class CirclePhysicsCollider : public Collider
{
public:
    explicit CirclePhysicsCollider(const Vector2f& position, float size);
    
    virtual ~CirclePhysicsCollider() override = default;
    CirclePhysicsCollider(const CirclePhysicsCollider& other) = default;
    CirclePhysicsCollider& operator=(const CirclePhysicsCollider& other) = default;
    CirclePhysicsCollider(CirclePhysicsCollider && other) = default;
    CirclePhysicsCollider& operator=(CirclePhysicsCollider&& other) = default;

    virtual ColliderTypes GetColliderType() const override;

    void DebugDraw() const;
    float GetSize() const;
    void SetSize(float newSize);
    
private:
    Vector2f m_Position;
    float m_Size;

    
};
