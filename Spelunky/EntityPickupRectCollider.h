#pragma once
#include "Entity.h"

class EntityPickupRectCollider: public Entity
{
public:
    EntityPickupRectCollider(const Rectf& collider, int health, float mass, float bounciness, float frictionOnGround, WorldManager* worldManager);
    
    virtual EntityType GetEntityType() const override = 0;
    virtual void Draw() const override = 0;
    virtual void DrawPickedUp() const = 0;
    virtual void Update(float elapsedTime) override;

    virtual void Throw(const Vector2f& force);
    virtual bool TryToPickUp(Entity* pickedUpBy);
    virtual void SetTargetPosition(const Vector2f& position, const Vector2f& goingTo);
    virtual bool IsPickedUp() const;
    virtual bool CanBePickedUp() const;
    bool IsOnGround() const;

protected:
    void EntitiesWeHitCheck(const std::vector<std::pair<const Tile*, RayVsRectInfo>>& hitInfo);
    void TilesWeHitCheck(const std::vector<std::pair<RayVsRectInfo, Entity*>>& hitInfo);
    
private:
    Vector2f m_GoingToPosition{};
    Vector2f m_CenterOfTarget{};
    float m_FrictionOnFloor;
    bool m_IsOnGround{};
    Entity* m_PickedUpBy{};
    std::vector<Entity*> m_HitPrevFrame;
};
