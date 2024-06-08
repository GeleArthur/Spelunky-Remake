#include "pch.h"
#include "EntityManager.h"


#include "Bat.h"
#include "Bomb.h"
#include "Cave.h"
#include "Game.h"
#include "GizmosDrawer.h"
#include "Rock.h"
#include "Snake.h"
#include "WorldManager.h"

void EntityManager::DrawEntities() const
{
    for (const Entity* entity : m_EntitiesWithoutPlayer)
    {
        entity->Draw();
    }
}

void EntityManager::UpdateEntity(const float elapsedTime) const
{
    for (Entity* entity : m_EntitiesWithoutPlayer)
    {
        entity->Update(elapsedTime);
    }
}

const std::vector<Entity*>& EntityManager::GetAllEntities()
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
    m_BombObjectPool.clear();
}

void EntityManager::GenerateEntities()
{
    const std::vector<std::vector<Tile*>>& tiles = m_WorldManager->GetCave()->GetTiles();
    for (int x = 0; x < tiles.size(); ++x)
    {
        for (int y = 0; y < tiles[x].size(); ++y)
        {
            if(tiles[x][y]->GetTileType() != TileTypes::air) continue;

            if(tiles[x][y-1]->GetTileType() == TileTypes::ground && tiles[x][y+1]->GetTileType() == TileTypes::air)
            {
                if(rand() % 15 == 0)
                {
                    AddEntity(new Bat{tiles[x][y-1], m_WorldManager});

                }
            }

            if(
                tiles[x][y+1]->GetTileType() == TileTypes::ground &&
                tiles[x-1][y+1]->GetTileType() == TileTypes::ground &&
                tiles[x+1][y+1]->GetTileType() == TileTypes::ground &&
                tiles[x+1][y]->GetTileType() == TileTypes::air &&
                tiles[x-1][y]->GetTileType() == TileTypes::air
                )
            {
                if(rand() % 10 == 0)
                {
                    AddEntity(new Snake{Vector2f{static_cast<float>(x*Game::TILE_SIZE), static_cast<float>(y * Game::TILE_SIZE)}, m_WorldManager});
                }
                else if(rand() % 15 == 0)
                {
                    AddEntity(new Rock{Vector2f{static_cast<float>(x*Game::TILE_SIZE), static_cast<float>(y * Game::TILE_SIZE)}, m_WorldManager});
                }
            }

        }
    }

    
}

EntityManager::EntityManager(WorldManager* worldManager):
    m_WorldManager(worldManager)
{
    worldManager->SetEntityManager(this);
}

EntityManager::~EntityManager()
{
    ClearAllEntities();
}

void EntityManager::AddEntity(Entity* entity)
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

    Bomb* bomb = new Bomb{m_WorldManager};
    AddEntity(bomb);

    return bomb;
}
