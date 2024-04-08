﻿#include "pch.h"
#include "Tile.h"

#include <iostream>

#include "GlobalValues.h"
#include "TileTypes.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Vector2i.h"


Tile::Tile(const TileTypes tileType, const Vector2i tileIndex, SpriteSheetManager* spriteSheet):
	m_SpriteSheetManager(spriteSheet),
	m_Position(tileIndex * g_TileSize),
	m_Collider(RectCollider{Rectf{m_Position.x, m_Position.y, g_TileSize, g_TileSize}}),
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
	Texture* doorsTexture = m_SpriteSheetManager->GetDoorsTexture();

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
	case TileTypes::ladderTop:
		levelTexture->Draw(m_Position, Rectf{192.0f, 0.0f, 64.0f, 64.0f});
		break;
	case TileTypes::ladder:
		levelTexture->Draw(m_Position, Rectf{128.0f, 0.0f, 64.0f, 64.0f});
		break;
	case TileTypes::spikes:
		{
			const float variantX = float(m_VariantIndex) * 64.0f;
			levelTexture->Draw(m_Position, Rectf{256 + variantX, 384, 64.0f, 64.0f});
		}
		break;
	case TileTypes::pushBlock:
		// TODO: Replace with object
		levelTexture->Draw(m_Position, Rectf{0.0f, 0.0f, 64.0f, 64.0f});
		break;
	case TileTypes::entrance:
		break;
	case TileTypes::exit:
		break;
	case TileTypes::unknown:
		levelTexture->Draw(m_Position, Rectf{15*64,26*64,64,64});
		break;

	}

}

Vector2i Tile::GetIndexPosition() const
{
	return Vector2i{static_cast<int>(m_Position.x/g_TileSize), static_cast<int>(m_Position.y/g_TileSize)};
}

const Vector2f& Tile::GetWorldPosition() const
{
	return m_Position;
}

TileTypes Tile::GetTileType() const
{
	return m_TileType;
}

const RectCollider* Tile::GetCollider() const
{
	return &m_Collider;
}
