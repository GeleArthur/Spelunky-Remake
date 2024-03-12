#include "pch.h"
#include "Tile.h"

#include "SpriteSheetManager.h"

Tile::Tile(const TileType tileType, const Vector2f position, SpriteSheetManager* spriteSheet):
	m_TileType(tileType),
	m_VariantIndex(0),
	m_SpriteSheetManager(spriteSheet),
	m_Position(position)
{
    
}

void Tile::SetVariantIndex(const int index)
{
    m_VariantIndex = index;
}

void Tile::Draw() const
{
	m_SpriteSheetManager->DrawTile(m_Position, m_TileType, m_VariantIndex);
}


