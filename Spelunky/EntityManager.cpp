#include "pch.h"
#include "EntityManager.h"

#include "CirclePhysicsCollider.h"
#include "Collider.h"
#include "WorldManager.h"

void EntityManager::DrawEntities() const
{
    for (const Entity* entity : m_Entities)
    {
        entity->Draw();
    }
}

void EntityManager::UpdateEntity(const float elapsedTime)
{
    for (Entity* entity : m_Entities)
    {
        entity->Update(elapsedTime);
    }
}

std::vector<Entity*>& EntityManager::GetAllEntities()
{
    return m_Entities;
}

void EntityManager::ClearAllEntities()
{
    for (int i{}; i < m_Entities.size(); ++i)
    {
        delete m_Entities[i];
    }
    m_Entities.clear();
}

EntityManager::EntityManager(WorldManager* worldManager)
{
    worldManager->SetEntityManager(this);
}

EntityManager::~EntityManager()
{
    ClearAllEntities();
}

void EntityManager::AddEntity(Entity* entity)
{
    switch (entity->GetColliderType())
    {
    case ColliderTypes::circle:
        m_EntitiesWithCircleCollider.push_back(dynamic_cast<CirclePhysicsCollider*>(entity));
        break;
    case ColliderTypes::rect:
        m_EntitiesWithRectCollider.push_back(dynamic_cast<RectPhysicsCollider*>(entity));
        break;
    }
    
    m_Entities.push_back(entity);
}
