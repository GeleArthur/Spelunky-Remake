#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:
    CircleCollider(const Vector2f& position, float size);
    virtual ColliderTypes GetColliderType() const override;
    virtual Vector2f GetCenterPosition() override;
    // bool CollisionCheck(const Collider& other, HitInfo& hitInfo) override;

private:
    Vector2f m_CenterPosition;
    float m_Size;
};
