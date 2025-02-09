﻿#pragma once
#include "EntityTypes.h"
#include "RectPhysicsCollider.h"

class SoundManager;
class Entity
{
public:
    explicit Entity(const Rectf& collider, int health, float mass, float bounciness, bool invisible, WorldManager* worldManager);
    
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

    virtual void Throw(const Vector2f& force);
    virtual bool TryToPickUp(Entity* pickedUpBy);
    virtual void SetTargetPosition(const Vector2f& position, const Vector2f& goingTo);
    virtual bool IsPickedUp() const;
    virtual bool CanBePickedUp() const;
    
    
protected:
    int m_Health;
    RectPhysicsCollider m_PhysicsCollider;
    SoundManager* m_SoundManager;
    bool m_Invisable{false};
};
