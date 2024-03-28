#pragma once
#include "Collider.h"

class PhysicsObject;

class RectCollider : public Collider
{
public:
    explicit RectCollider(const Rectf& rect, PhysicsObject* owner = nullptr);
    virtual ColliderTypes GetColliderType() const override;
    virtual Vector2f GetCenterPosition() const override;
    virtual void DebugDraw() const override;
    virtual bool CheckCollision(Collider* other, CollisionHelpers::HitInfo& out) const override;

    
    Rectf GetRect() const;
    void SetRect(const Rectf& rect);

private:
    Rectf m_Rect;
    PhysicsObject* m_Owner;
};
