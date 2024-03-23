#pragma once
#include "Collider.h"

class RectCollider : public Collider
{
public:
    ColliderTypes GetColliderType() const override;
    Vector2f GetCenterPosition() override;
};
