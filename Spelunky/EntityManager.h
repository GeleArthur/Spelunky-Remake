﻿#pragma once
#include <array>
#include <vector>

#include "Entity.h"

class PickUp;
class CirclePhysicsCollider;
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
    
    void AddEntity(Entity* entity);
    void DrawEntities() const;
    void UpdateEntity(float elapsedTime);
    std::vector<Entity*>& GetAllEntities();
    void ClearAllEntities();
    
private:
    std::vector<Entity*> m_Entities;
    std::vector<RectPhysicsCollider*> m_EntitiesWithRectCollider;
    std::vector<CirclePhysicsCollider*> m_EntitiesWithCircleCollider;

    std::vector<PickUp*> m_EntitiesWithPickUp;
    // std::vector<PickupItem*> m_PickupItems;
};
