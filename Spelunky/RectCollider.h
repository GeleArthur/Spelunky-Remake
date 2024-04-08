#pragma once
#include "Collider.h"

class PhysicsObject;

class RectCollider : public Collider
{
public:
    explicit RectCollider(const Rectf& rect);
    virtual ColliderTypes GetColliderType() const override;
    virtual void DebugDraw() const override;
    virtual Vector2f GetOrigin() const override;
    virtual void SetOrigin(Vector2f newPosition) override;
    
    const Rectf& GetRect() const;
    void SetRect(const Rectf& rect);

private:
    Rectf m_Rect;
};
