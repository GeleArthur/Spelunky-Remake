#include "pch.h"
#include "SpriteSheetManager.h"

#include "Texture.h"

SpriteSheetManager::SpriteSheetManager()
{
	m_CurruntPlayerTexture = new Texture{"PLAYERS/char_orange.png"};

	// 512x512 for each tile stack
	// 64x64 for each tile
	m_LevelTexture = new Texture{"ALLTILES/alltiles.png"};
}

SpriteSheetManager::~SpriteSheetManager()
{
	delete m_CurruntPlayerTexture;
	delete m_LevelTexture;
}
