#include "pch.h"
#include "WorldManager.h"

WorldManager* WorldManager::m_WorldManager{nullptr};

WorldManager::WorldManager()
{
    m_WorldManager = this;
}

Cave* WorldManager::GetCave() const
{
    return m_Cave;
}

PlayerObject* WorldManager::GetPlayer() const
{
    return m_Player;
}

SpriteSheetManager* WorldManager::GetSpriteSheet() const
{
    return m_SpriteSheetManager;
}

ItemManager* WorldManager::GetItemManager() const
{
    return m_ItemManager;
}

void WorldManager::Init(Cave* cave, PlayerObject* player, SpriteSheetManager* spriteSheet, ItemManager* itemManager)
{
    m_Cave = cave;
    m_Player = player;
    m_SpriteSheetManager = spriteSheet;
    m_ItemManager = itemManager;
}

WorldManager* WorldManager::GetSingleton()
{
    if(m_WorldManager == nullptr) throw;
    return m_WorldManager;
}
