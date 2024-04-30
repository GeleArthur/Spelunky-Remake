#pragma once
#include <array>
#include <vector>

#include "Entity.h"

class PickupItem;
class WorldManager;

class EntityManager final
{
public:x
    explicit EntityManager(WorldManager* worldManager);
    virtual ~EntityManager();
    EntityManager(const EntityManager& other) = delete;
    EntityManager& operator=(const EntityManager& other) = delete;
    EntityManager(EntityManager && other) = delete;
    EntityManager& operator=(const EntityManager&& other) = delete;
    
    void AddEntity(Entity* item);
    void DrawEntities() const;
    void UpdateItems(float elapsedTime);
    std::vector<Entity*>& GetAllEntities();
    void ClearAllEntities();
    
private:
    std::vector<Entity*> m_Entities;
    // std::vector<PickupItem*> m_PickupItems;
};
