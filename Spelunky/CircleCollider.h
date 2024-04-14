#pragma once
#include "Collider.h"

class PhysicsObject;

class CircleCollider : public Collider
{
public:
    explicit CircleCollider(const Vector2f& position, float size);

    virtual ColliderTypes GetColliderType() const override;
    virtual void DebugDraw() const override;
    virtual Vector2f GetOrigin() const override;
    virtual void SetOrigin(Vector2f newPosition) override;

    float GetSize() const;
    void SetSize(float newSize);
    
private:
    Vector2f m_CenterPosition;
    float m_Size;
};
