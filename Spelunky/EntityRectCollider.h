#pragma once
#include "Entity.h"
#include "RectPhysicsCollider.h"

class EntityRectCollider : public RectPhysicsCollider, public Entity
{
public:
    explicit EntityRectCollider(const Rectf& collider, float mass, float bounciness, WorldManager* worldManager);
    
    virtual EntityType GetEntityType() const override = 0;
    virtual ColliderTypes GetColliderType() const override;

    virtual void Draw() const override = 0;
    virtual void Update(float elapsedTime) override;
    virtual void YouGotHit(int damage, Vector2f force, HitType hitType) override;

private:
};
