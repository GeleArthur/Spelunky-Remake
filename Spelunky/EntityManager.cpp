#include "pch.h"
#include "EntityManager.h"


#include "Bomb.h"
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

std::vector<EntityRectCollider*>* EntityManager::GetAllEntities()
{
    return &m_Entities;
}

void EntityManager::ClearAllEntities()
{
    for (int i{}; i < m_EntitiesWithoutPlayer.size(); ++i)
    {
        delete m_EntitiesWithoutPlayer[i];
    }
    m_EntitiesWithoutPlayer.clear();
    m_Entities.clear();
    m_BombObjectPool.clear();
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
    const EntityType type = entity->GetEntityType();

    if(type == EntityType::bomb)
    {
        m_BombObjectPool.push_back(dynamic_cast<Bomb*>(entity));
    }

    if(type != EntityType::player)
    {
        m_EntitiesWithoutPlayer.push_back(entity);
    }
    
    m_Entities.push_back(entity);
}

Bomb* EntityManager::CreateBomb()
{
    for (int i = 0; i < m_BombObjectPool.size(); ++i)
    {
        if(m_BombObjectPool[i]->IsDead())
        {
            return m_BombObjectPool[i];
        }
    }

    Bomb* bomb = new Bomb{WorldManager::GetSingleton()};
    AddEntity(bomb);

    return bomb;
}
