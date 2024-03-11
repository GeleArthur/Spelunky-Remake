#include "pch.h"
#include "SpriteSheetManager.h"
#include "Texture.h"

SpriteSheetManager* SpriteSheetManager::m_pSpriteSheetManager{nullptr};

SpriteSheetManager::SpriteSheetManager()
{
	m_CurrentPlayerTexture = new Texture{"PLAYERS/char_orange.png"};

	// 512x512 for each tile stack
	// 64x64 for each tile
	m_LevelTexture = new Texture{"ALLTILES/alltiles.png"};
	m_pSpriteSheetManager = this;
}

SpriteSheetManager::~SpriteSheetManager()
{
	delete m_CurrentPlayerTexture;
	delete m_LevelTexture;
}

SpriteSheetManager* SpriteSheetManager::GetSingleton()
{
	if(m_pSpriteSheetManager == nullptr) throw;
	return m_pSpriteSheetManager;
}

void SpriteSheetManager::DrawTile(const Vector2f position, const int x, const int y) const
{
	m_LevelTexture->Draw(position, Rectf{float(0), float(0), 128, 128});
}
