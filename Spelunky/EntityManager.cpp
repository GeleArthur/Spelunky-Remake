#include "pch.h"
#include "EntityManager.h"


#include "WorldManager.h"

void EntityManager::DrawEntities() const
{
    for (const EntityRectCollider* entity : m_EntitiesWithoutPlayer)
    {
        entity->Draw();
    }
}

void EntityManager::UpdateEntity(const float elapsedTime) const
{
    for (EntityRectCollider* entity : m_EntitiesWithoutPlayer)
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
    for (int i{}; i < m_EntitiesWithoutPlayer.size(); ++i)
    {
        delete m_EntitiesWithoutPlayer[i];
    }
    m_EntitiesWithoutPlayer.clear();
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
    switch (entity->GetEntityType())
    {
    case EntityType::player:
        break;
    case EntityType::rock:
    case EntityType::arrow:
    case EntityType::snake:
    case EntityType::bomb:
        m_EntitiesWithoutPlayer.push_back(entity);
        break;
    }
    m_Entities.push_back(entity);
}

Bomb* EntityManager::CreateBomb()
{
    return nullptr;
}
