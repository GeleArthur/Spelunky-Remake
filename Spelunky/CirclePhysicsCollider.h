#pragma once
#include "Collider.h"

class CirclePhysicsCollider : public Collider
{
public:
    explicit CirclePhysicsCollider(const Vector2f& position, float size);

    virtual ColliderTypes GetColliderType() const override;

    void DebugDraw() const;
    float GetSize() const;
    void SetSize(float newSize);
    
private:
    Vector2f m_Position;
    float m_Size;

    
};
