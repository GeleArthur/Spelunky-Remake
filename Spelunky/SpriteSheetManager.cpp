#include "pch.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "TileTypes.h"
#include "WorldManager.h"

SpriteSheetManager::SpriteSheetManager(WorldManager* worldManager)
{
	// 512x512 for each tile stack
	// 64x64 for each tile
	m_LevelTexture = new Texture{"ALLTILES/alltiles.png"};
	m_CurrentPlayerTexture = new Texture{"PLAYERS/char_orange.png"};
	m_BackGroundTexture = new Texture{"MINE/minebg.jpg"};
	m_ExitDoorsTexture = new Texture{"ANYLEVEL/TU_exitdoors.png"};
	m_ItemsTexture = new Texture{"ITEMS/items.png"};
	m_MonsterTexture = new Texture{"MONSTERS/monsters.png"};
	m_MonsterTexture3 = new Texture{"MONSTERS/monsters3.png"};
	
	worldManager->SetSpriteSheetManager(this);
}

SpriteSheetManager::~SpriteSheetManager()
{
	delete m_LevelTexture;
	delete m_CurrentPlayerTexture;
	delete m_BackGroundTexture;
	delete m_ExitDoorsTexture;
	delete m_ItemsTexture;
	delete m_MonsterTexture;
	delete m_MonsterTexture3;
}

const Texture* SpriteSheetManager::GetLevelTexture() const
{
	return m_LevelTexture;
}

const Texture* SpriteSheetManager::GetBackGroundTexture() const
{
	return m_BackGroundTexture;
}

const Texture* SpriteSheetManager::GetDoorsTexture() const
{
	return m_ExitDoorsTexture;
}

const Texture* SpriteSheetManager::GetCurrentPlayerTexture() const
{
	return m_CurrentPlayerTexture;
}

const Texture* SpriteSheetManager::GetItemsTexture() const
{
	return m_ItemsTexture;
}

const Texture* SpriteSheetManager::GetMonsterTexture() const
{
	return m_MonsterTexture;
}
const Texture* SpriteSheetManager::GetMonsterTexture3() const
{
	return m_MonsterTexture3;
}
