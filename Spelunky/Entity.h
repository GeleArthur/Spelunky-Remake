#pragma once
#include "Collider.h"

enum class EntityType
{
    player,
    
    rock,
    arrow,
    
    snake
};

class Entity
{
public:
    Entity() = default;
    virtual ~Entity() = default;
    Entity(const Entity&) = default;
    Entity& operator=(const Entity& c) = default;
    Entity(Entity&& other) = default;
    Entity& operator=(Entity&& c) = default;
    
    virtual EntityType GetEntityType() const = 0;
    virtual ColliderTypes GetColliderType() const = 0;
    virtual void Update(float elapsedTime) = 0;
    virtual void Draw() const = 0;
    
    // virtual bool TryToPickup(Entity* beaningPickedUpBy) = 0;
    // virtual bool ThrowPickUp(const Vector2f& force) = 0;
    // virtual void DrawPickedUp() const override;
    // virtual void SetTargetPositionPickUp(const Vector2f& position) = 0;
    
    // virtual void YouCollidedWith(Entity* other) = 0;
    
private:
    
};
