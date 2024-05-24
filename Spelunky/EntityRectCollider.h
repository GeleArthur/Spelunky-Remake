#pragma once
#include "EntityTypes.h"
#include "HitType.h"
#include "RectPhysicsCollider.h"

class EntityRectCollider : public RectPhysicsCollider
{
public:
    explicit EntityRectCollider(const Rectf& collider, const int health, float mass, float bounciness, WorldManager* worldManager);
    
    virtual EntityType GetEntityType() const = 0;
    virtual void Draw() const = 0;
    virtual void Update(float elapsedTime);
    virtual void YouGotHit(int damage, const Vector2f& force);
    bool IsDead() const;
    
protected:
    int m_Health;
};
