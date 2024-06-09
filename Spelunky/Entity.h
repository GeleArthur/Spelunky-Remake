#pragma once
#include "EntityTypes.h"
#include "HitType.h"
#include "RectPhysicsCollider.h"

class Entity
{
public:
    explicit Entity(const Rectf& collider, const int health, float mass, float bounciness, WorldManager* worldManager);
    
    virtual ~Entity() = default;
    Entity(const Entity& other) = delete;
    Entity& operator=(const Entity& other) = delete;
    Entity(Entity && other) = delete;
    Entity& operator=(Entity&& other) = delete;
    
    virtual EntityType GetEntityType() const = 0;
    virtual void Draw() const = 0;
    virtual void Update(float elapsedTime);
    virtual void YouGotHit(int damage, const Vector2f& force);
    int GetHealth() const;
    bool IsDead() const;
    
    const Rectf& GetRect() const;
    Vector2f GetCenter() const;
    const RectPhysicsCollider& GetCollider() const;
    
protected:
    int m_Health;
    RectPhysicsCollider m_PhysicsCollider;
};
