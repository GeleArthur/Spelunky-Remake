#pragma once
#include "PlayerObject.h"

class EntityManager;
class SpriteSheetManager;
class PlayerObject;
class Cave;

class WorldManager final
{
public:
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
    Cave* m_Cave{};
    PlayerObject* m_Player{};
    SpriteSheetManager* m_SpriteSheetManager{};
    EntityManager* m_EntityManager{};
    InputManager* m_InputManager{};
};
