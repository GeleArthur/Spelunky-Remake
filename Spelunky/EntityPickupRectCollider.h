#pragma once
#include "EntityRectCollider.h"
#include "PickUp.h"

class EntityPickupRectCollider: public EntityRectCollider, public PickUp
{
public:
    EntityPickupRectCollider(const Rectf& collider, int health, float mass, float bounciness, float frictionOnGround, WorldManager* worldManager);
    
    virtual EntityType GetEntityType() const override = 0;
    virtual void Draw() const override = 0;
    virtual void DrawPickedUp() const override = 0;
    virtual void Update(float elapsedTime) override;

    virtual void Throw(const Vector2f& force) override;
    virtual bool TryToPickUp(EntityRectCollider* pickedUpBy) override;
    virtual void SetTargetPosition(const Vector2f& position, const Vector2f& goingTo) override;
    virtual bool IsPickedUp() const override;
    virtual bool CanBePickedUp() const override = 0;
    bool IsOnGround() const;


private:
    virtual void CallBackHitTile(std::vector<std::pair<const Tile*, RayVsRectInfo>>& hitInfo) override;
    
    Vector2f m_GoingToPosition{};
    Vector2f m_CenterOfTarget{};
    float m_FrictionOnFloor;
    bool m_IsOnGround{};
    EntityRectCollider* m_PickedUpBy{};
};
