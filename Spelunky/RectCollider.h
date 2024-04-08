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
    virtual bool CheckCollision(const Collider* other, collision_helpers::HitInfo& out) const override;
    
    
    const Rectf& GetRect() const;
    Rectf GetRectWorldSpace() const;
    void SetRect(const Rectf& rect);

private:
    Rectf m_Rect;
    PhysicsObject* m_Owner;
};
