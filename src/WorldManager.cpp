
#include "WorldManager.h"
#include <cassert>


Cave* WorldManager::GetCave() const
{
    assert(m_Cave != nullptr && "Cave doesn't exist yet but we are tring to access it");
    return m_Cave;
}

PlayerObject* WorldManager::GetPlayer() const
{
    assert(m_Player != nullptr && "Player doesn't exist yet but we are tring to access it");
    return m_Player;
}

SpriteSheetManager* WorldManager::GetSpriteSheet() const
{
    assert(m_SpriteSheetManager != nullptr && "SpriteSheet doesn't exist yet but we are tring to access it");
    return m_SpriteSheetManager;
}

EntityManager* WorldManager::GetEntityManager() const
{
    assert(m_EntityManager != nullptr && "EntityManager doesn't exist yet but we are tring to access it");
    return m_EntityManager;
}


InputManager* WorldManager::GetInputManager() const
{
    assert(m_InputManager != nullptr && "InputManager doesn't exist yet but we are tring to access it");
    return m_InputManager;
}

SoundManager* WorldManager::GetSoundManager() const
{
    assert(m_SoundManager != nullptr && "m_SoundManager doesn't exist yet but we are tring to access it");
    return m_SoundManager;
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

void WorldManager::SetInputManager(InputManager* inputManager)
{
    m_InputManager = inputManager;
}

void WorldManager::SetSoundManager(SoundManager* soundManager)
{
    m_SoundManager = soundManager;
}