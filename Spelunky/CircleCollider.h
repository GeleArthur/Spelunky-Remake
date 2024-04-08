#pragma once
#include "Collider.h"

class PhysicsObject;

class CircleCollider final : public Collider
{
public:
    explicit CircleCollider(const Vector2f& position, float size);
    virtual ColliderTypes GetColliderType() const override;
    virtual void DebugDraw() const override;

    float GetSize() const;
    void SetSize(float newSize);

    const Vector2f& GetCenterPosition() const;
    void SetCenterPosition(const Vector2f& newPosition);
    
private:
    Vector2f m_CenterPosition;
    float m_Size;
};
