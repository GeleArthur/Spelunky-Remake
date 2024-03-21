#pragma once
#include "Collider.h"

class SphereCollider : Collider
{
public:
    SphereCollider(const Vector2f& position, float size);
    virtual bool CheckAgainstRect(const Rectf& other, HitInfo& out) override;

private:
    float m_Size;
};
