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
    static WorldManager* GetSingleton();

    void SetCave(Cave* cave);
    Cave* GetCave() const;
    
    void SetPlayer(PlayerObject* player);
    PlayerObject* GetPlayer() const;
    
    void SetSpriteSheetManager(SpriteSheetManager* spriteSheet);
    SpriteSheetManager* GetSpriteSheet() const;
    
    void SetItemManager(ItemManager* itemManager);
    ItemManager* GetItemManager() const;
    
private:
    static WorldManager* m_WorldManager;
    Cave* m_Cave;
    PlayerObject* m_Player;
    SpriteSheetManager* m_SpriteSheetManager;
    ItemManager* m_ItemManager;
};
