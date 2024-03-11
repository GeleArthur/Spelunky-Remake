#include "pch.h"
#include "SpriteSheetManager.h"
#include "Texture.h"

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

void SpriteSheetManager::DrawTile(const Vector2f position, const int x, const int y) const
{
	m_LevelTexture->Draw(position, Rectf{float(x*64), float(y*64), 64, 64});
}
