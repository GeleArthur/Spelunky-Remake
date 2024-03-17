﻿#include "pch.h"
#include "Tile.h"

#include <iostream>

#include "TileTypes.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
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
	Texture* levelTexture = m_SpriteSheetManager->GetLevelTexture();

	switch (m_TileType)
	{
	case TileTypes::air:
		break;
	case TileTypes::ground:
		{
			const float variantX = float(m_VariantIndex % 4) *64.f;
			const float variantY = float(m_VariantIndex / 4) * 64.0f;
			levelTexture->Draw(m_Position, Rectf{variantX, 64.0f + variantY, 64.0f, 64.0f});
		}
		break;
	case TileTypes::ladder:
		levelTexture->Draw(m_Position, Rectf{0.0f, 192.0f, 64.0f, 64.0f});
		break;
	}

}

Vector2i Tile::GetIndexPosition() const
{
	return Vector2i{static_cast<int>(m_Position.x/64), static_cast<int>(m_Position.y/64)};
}

Vector2f Tile::GetWorldPosition() const
{
	return m_Position;
}

