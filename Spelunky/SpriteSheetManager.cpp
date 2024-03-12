#include "pch.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Tile.h"

SpriteSheetManager* SpriteSheetManager::m_pSpriteSheetManager{nullptr};

SpriteSheetManager::SpriteSheetManager()
{
	m_pSpriteSheetManager = this;


	// 512x512 for each tile stack
	// 64x64 for each tile
	m_LevelTexture = new Texture{"ALLTILES/alltiles.png"};
	m_CurrentPlayerTexture = new Texture{"PLAYERS/char_orange.png"};
	m_BackGroundImage = new Texture{"MINE/minebg.jpg"};
}

SpriteSheetManager::~SpriteSheetManager()
{
	delete m_CurrentPlayerTexture;
	delete m_LevelTexture;
	delete m_BackGroundImage;
}

SpriteSheetManager* SpriteSheetManager::GetSingleton()
{
	if(m_pSpriteSheetManager == nullptr) throw;
	return m_pSpriteSheetManager;
}

void SpriteSheetManager::DrawTile(const Vector2f position, const TileType type, int variant = 0) const
{
	switch (type)
	{
	case TileType::air:
		break;
	case TileType::ground:
		//TODO: Add variant
		m_LevelTexture->Draw(position, Rectf{64.0f, 64.0f, 64.0f, 64.0f});
		break;
	case TileType::ladder:
		m_LevelTexture->Draw(position, Rectf{0.0f, 192.0f, 64.0f, 64.0f});
		break;
	}

}
