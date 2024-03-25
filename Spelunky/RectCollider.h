#pragma once
#include "Collider.h"

class PhysicsObject;

class RectCollider : public Collider
{
public:
    explicit RectCollider(const Rectf& rect, PhysicsObject* owner = nullptr);
    virtual ColliderTypes GetColliderType() const override;
    virtual Vector2f GetCenterPosition() override;
    void DebugDraw() override;
    Rectf GetRect();
    void SetRect(const Rectf& rect);

private:
    Rectf m_Rect;
    PhysicsObject* m_Owner;
};
