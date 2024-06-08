#pragma once
#include <array>
#include <vector>


class EntityPickupRectCollider;
class Bomb;
class EntityRectCollider;
class PickUp;
class RectPhysicsCollider;
class WorldManager;

class EntityManager final
{
public:
    explicit EntityManager(WorldManager* worldManager);
    ~EntityManager();
    EntityManager(const EntityManager& other) = delete;
    EntityManager& operator=(const EntityManager& other) = delete;
    EntityManager(EntityManager && other) = delete;
    EntityManager& operator=(EntityManager&& other) = delete;
    
    
    void AddEntity(EntityRectCollider* entity);
    Bomb* CreateBomb();
    
    void DrawEntities() const;
    void UpdateEntity(float elapsedTime) const;
    std::vector<EntityRectCollider*>* GetAllEntities();
    void ClearAllEntities();
    void GenerateEntities();
    
private:
    std::vector<EntityRectCollider*> m_Entities;
    std::vector<EntityRectCollider*> m_EntitiesWithoutPlayer;
    std::vector<EntityPickupRectCollider*> m_EntitiesWithPickUp;
    std::vector<Bomb*> m_BombObjectPool;

    WorldManager* m_WorldManager;
    // std::vector<PickupItem*> m_PickupItems;
};
