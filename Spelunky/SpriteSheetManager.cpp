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
	
	worldManager->SetSpriteSheetManager(this);
}

SpriteSheetManager::~SpriteSheetManager()
{
	delete m_LevelTexture;
	delete m_CurrentPlayerTexture;
	delete m_BackGroundTexture;
	delete m_ExitDoorsTexture;
	delete m_ItemsTexture;
}

Texture* SpriteSheetManager::GetLevelTexture() const
{
	return m_LevelTexture;
}

Texture* SpriteSheetManager::GetBackGroundTexture() const
{
	return m_BackGroundTexture;
}

Texture* SpriteSheetManager::GetDoorsTexture() const
{
	return m_ExitDoorsTexture;
}

Texture* SpriteSheetManager::GetCurrentPlayerTexture() const
{
	return m_CurrentPlayerTexture;
}

Texture* SpriteSheetManager::GetItemsTexture() const
{
	return m_ItemsTexture;
}
