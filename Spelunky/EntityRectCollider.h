#pragma once
#include "Entity.h"
#include "RectPhysicsCollider.h"

class EntityRectCollider : public Entity, public RectPhysicsCollider
{
public:
    explicit EntityRectCollider(const Rectf& collider, const float mass, const float bounciness, WorldManager* worldManager);
    
    virtual EntityType GetEntityType() const override = 0;
    virtual ColliderTypes GetColliderType() const override;

    virtual void Draw() const override = 0;
    virtual void Update(float elapsedTime) override;
    
    
    // virtual void YouCollidedWith(Entity* other) override;
    
    // virtual bool TryToPickup(Entity* beaningPickedUpBy) override;
    // virtual bool ThrowPickUp(const Vector2f& force) override;
    // virtual void SetTargetPositionPickUp(const Vector2f& position) override;

private:
    
};
