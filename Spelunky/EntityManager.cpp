#include "pch.h"
#include "EntityManager.h"


#include "WorldManager.h"

void EntityManager::DrawEntities() const
{
    for (const EntityRectCollider* entity : m_Entities)
    {
        entity->Draw();
    }
}

void EntityManager::UpdateEntity(const float elapsedTime)
{
    for (EntityRectCollider* entity : m_Entities)
    {
        entity->Update(elapsedTime);
    }
}

std::vector<EntityRectCollider*>& EntityManager::GetAllEntities()
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

void EntityManager::AddEntity(EntityRectCollider* entity)
{
    m_Entities.push_back(entity);
}
