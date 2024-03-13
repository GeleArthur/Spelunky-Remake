#include "pch.h"
#include "Tile.h"
#include "TileTypes.h"
#include "SpriteSheetManager.h"
#include "Vector2i.h"

Tile::Tile(const TileTypes tileType, const Vector2i tileIndex, SpriteSheetManager* spriteSheet):
	m_SpriteSheetManager(spriteSheet),
	m_Position(tileIndex * 64),
	m_TileType(tileType),
	m_VariantIndex(0)
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

Vector2i Tile::GetIndexPosition() const
{
	return Vector2i{static_cast<int>(m_Position.x/64), static_cast<int>(m_Position.y/64)};
}

Vector2f Tile::GetWorldPosition() const
{
	return m_Position;
}

