#pragma once
#include "Entity.h"

class EntityPickupRectCollider: public Entity
{
public:
    EntityPickupRectCollider(const Rectf& collider, int health, float mass, float bounciness, bool invisible, WorldManager* worldManager);
    
    virtual EntityType GetEntityType() const override = 0;
    virtual void Draw() const override = 0;
    virtual void Update(float elapsedTime) override;

    virtual void Throw(const Vector2f& force) override;
    virtual bool TryToPickUp(Entity* pickedUpBy) override;
    virtual void SetTargetPosition(const Vector2f& position, const Vector2f& goingTo) override;
    virtual bool IsPickedUp() const override;
    virtual bool CanBePickedUp() const override;
    bool IsOnGround() const;

private:
    void TilesWeHitCheck(const std::vector<std::pair<const Tile*, RayVsRectInfo>>& hitInfo);
    void EntitiesWeHitCheck(const std::vector<std::pair<RayVsRectInfo, Entity*>>& hitInfo);
    
    Vector2f m_GoingToPosition{};
    Vector2f m_CenterOfTarget{};
    bool m_IsOnGround{};
    Entity* m_PickedUpBy{};
    std::vector<Entity*> m_HitPrevFrame;
};
