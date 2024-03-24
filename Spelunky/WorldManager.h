#pragma once
#include "ItemManager.h"
#include "PlayerObject.h"
#include "SpriteSheetManager.h"

class ItemManager;
class SpriteSheetManager;
class PlayerObject;
class Cave;

class WorldManager final
{
public:
    explicit WorldManager();
    
    Cave* GetCave() const;
    PlayerObject* GetPlayer() const;
    SpriteSheetManager* GetSpriteSheet() const;
    ItemManager* GetItemManager() const;
    void Init(Cave* cave, PlayerObject* player, SpriteSheetManager* spriteSheet, ItemManager* itemManager);
    static WorldManager* GetSingleton();
    
private:

    static WorldManager* m_WorldManager;
    Cave* m_Cave;
    PlayerObject* m_Player;
    SpriteSheetManager* m_SpriteSheetManager;
    ItemManager* m_ItemManager;
};
