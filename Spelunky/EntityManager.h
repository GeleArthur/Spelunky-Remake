#pragma once
#include <array>
#include <vector>


class Bomb;
class EntityRectCollider;
class PickUp;
class RectPhysicsCollider;
class WorldManager;

class EntityManager final
{
public:
    explicit EntityManager(WorldManager* worldManager);
    virtual ~EntityManager();
    EntityManager(const EntityManager& other) = delete;
    EntityManager& operator=(const EntityManager& other) = delete;
    EntityManager(EntityManager && other) = delete;
    EntityManager& operator=(const EntityManager&& other) = delete;
    
    void AddEntity(EntityRectCollider* entity);
    Bomb* CreateBomb();
    
    void DrawEntities() const;
    void UpdateEntity(float elapsedTime) const;
    std::vector<EntityRectCollider*>* GetAllEntities();
    void ClearAllEntities();
    
private:
    std::vector<EntityRectCollider*> m_Entities;
    std::vector<EntityRectCollider*> m_EntitiesWithoutPlayer;
    std::vector<PickUp*> m_EntitiesWithPickUp;
    std::vector<Bomb*> m_BombObjectPool;
    // std::vector<PickupItem*> m_PickupItems;
};
