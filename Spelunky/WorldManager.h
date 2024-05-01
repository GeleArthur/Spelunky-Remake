#pragma once
#include "PlayerObject.h"

class EntityManager;
class SpriteSheetManager;
class PlayerObject;
class Cave;

class WorldManager final
{
public:
    explicit WorldManager();
    virtual ~WorldManager() = default;
    WorldManager(const WorldManager& other) = delete;
    WorldManager& operator=(const WorldManager& other) = delete;
    WorldManager( WorldManager&& other) = delete;
    WorldManager& operator=(WorldManager&& other) = delete;
    
    static WorldManager* GetSingleton();

    void SetCave(Cave* cave);
    Cave* GetCave() const;
    
    void SetPlayer(PlayerObject* player);
    PlayerObject* GetPlayer() const;
    
    void SetSpriteSheetManager(SpriteSheetManager* spriteSheet);
    SpriteSheetManager* GetSpriteSheet() const;
    
    void SetEntityManager(EntityManager* entityManager);
    EntityManager* GetEntityManager() const;

    void SetInputManager(InputManager* inputManager);
    InputManager* GetInputManager() const;
    
private:
    static WorldManager* m_WorldManager;
    Cave* m_Cave;
    PlayerObject* m_Player;
    SpriteSheetManager* m_SpriteSheetManager;
    EntityManager* m_EntityManager;
    InputManager* m_InputManager;
};
