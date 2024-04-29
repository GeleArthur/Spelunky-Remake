#include "pch.h"
#include "EntityManager.h"
#include "Collider.h"
#include "WorldManager.h"

void EntityManager::DrawEntities() const
{
    for (const Entity* entity : m_Entities)
    {
        entity->Draw();
    }
}

void EntityManager::UpdateItems(const float elapsedTime)
{
    for (Entity* item : m_Entities)
    {
        item->Update(elapsedTime);
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

void EntityManager::AddEntity(Entity* item)
{
    m_Entities.push_back(item);
}
