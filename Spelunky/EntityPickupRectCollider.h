#pragma once
#include "EntityRectCollider.h"

class EntityPickupRectCollider: public EntityRectCollider
{
public:
    EntityPickupRectCollider(const Rectf& collider, float mass, float bounciness, WorldManager* worldManager);
    
    virtual EntityType GetEntityType() const override = 0;
    virtual void Draw() const override = 0;
    virtual void DrawPickedUp() const = 0;
    virtual void Update(float elapsedTime) override;
    
    void Throw(const Vector2f& force);
    bool TryToPickUp(Entity* pickedUpBy);
    void SetTargetPosition(const Vector2f& position);
    bool GetIsPickedUp() const;
    virtual bool CanBePickedUp() const = 0;
    
    
private:
    bool m_IsPickedUp{};
    Vector2f m_TargetPosition{};
    Entity* m_PickedUpBy{};
};
