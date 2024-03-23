#pragma once
#include "Collider.h"

class RectCollider : public Collider
{
public:
    virtual ColliderTypes GetColliderType() const override;
    virtual Vector2f GetCenterPosition() override;
private:
    
};
