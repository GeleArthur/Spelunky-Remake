#include "pch.h"
#include "WorldManager.h"


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

EntityManager* WorldManager::GetEntityManager() const
{
    return m_EntityManager;
}

void WorldManager::SetInputManager(InputManager* inputManager)
{
    m_InputManager = inputManager;
}

InputManager* WorldManager::GetInputManager() const
{
    return m_InputManager;
}

void WorldManager::SetCave(Cave* cave)
{
    m_Cave = cave;
}

void WorldManager::SetPlayer(PlayerObject* player)
{
    m_Player = player;
}

void WorldManager::SetSpriteSheetManager(SpriteSheetManager* spriteSheet)
{
    m_SpriteSheetManager = spriteSheet;
}

void WorldManager::SetEntityManager(EntityManager* entityManager)
{
    m_EntityManager = entityManager;
}
