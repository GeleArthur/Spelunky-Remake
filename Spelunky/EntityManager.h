#pragma once
#include <array>
#include <vector>


class EntityPickupRectCollider;
class Bomb;
class Entity;
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
    
    
    void AddEntity(Entity* entity);
    Bomb* CreateBomb();
    
    void DrawEntities() const;
    void UpdateEntity(float elapsedTime) const;
    const std::vector<Entity*>& GetAllEntities();
    void ClearAllEntities();
    void GenerateEntities();
    
private:
    std::vector<Entity*> m_Entities;
    std::vector<Entity*> m_EntitiesWithoutPlayer;
    std::vector<EntityPickupRectCollider*> m_EntitiesWithPickUp;
    std::vector<Bomb*> m_BombObjectPool;

    WorldManager* m_WorldManager;
};
