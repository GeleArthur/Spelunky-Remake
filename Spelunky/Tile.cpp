#include "pch.h"
#include "Tile.h"

#include "GlobalValues.h"
#include "TileTypes.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Vector2i.h"
#include "WorldManager.h"
#include <limits>

using namespace spelucky_settings;

Tile::Tile(const TileTypes tileType, const Vector2i tileIndex, WorldManager* worldManager):
    RectPhysicsCollider{
        Rectf{
            static_cast<float>((tileIndex.x * g_TileSize)), static_cast<float>((tileIndex.y * g_TileSize)),
            g_TileSize, g_TileSize
        },
        0,
        0,
        worldManager
    },
    m_SpriteSheetManager(worldManager->GetSpriteSheet()),
    m_IndexPosition(tileIndex),
    m_TileType(tileType)
{
}

void Tile::SetVariantIndex(const int index)
{
    m_VariantIndex = index;
}

void Tile::Draw() const
{
    // if(m_TileType != TileTypes::air) GetCollider()->DebugDraw();

    Texture* levelTexture = m_SpriteSheetManager->GetLevelTexture();
    Texture* doorsTexture = m_SpriteSheetManager->GetDoorsTexture();

    const Rectf rect = GetRect();
    const Vector2f position = Vector2f{rect.left, rect.top};

    switch (m_TileType)
    {
    case TileTypes::air:
        break;
    case TileTypes::ground:
        {
            const float variantX = float(m_VariantIndex % 4) * g_TileSize;
            const float variantY = float(m_VariantIndex / 4) * g_TileSize;
            levelTexture->Draw(position, Rectf{variantX, g_TileSize + variantY, g_TileSize, g_TileSize});
        }
        break;
    case TileTypes::border:
        {
            const float variantX = float(m_VariantIndex % 2) * g_TileSize;
            const float variantY = float(m_VariantIndex / 2) * g_TileSize;
            levelTexture->Draw(position, Rectf{1536 + variantX, 512 + variantY, g_TileSize, g_TileSize});
        }
        break;
    case TileTypes::ladderTop:
        levelTexture->Draw(position, Rectf{192.0f, 0.0f, g_TileSize, g_TileSize});
        break;
    case TileTypes::ladder:
        levelTexture->Draw(position, Rectf{128.0f, 0.0f, g_TileSize, g_TileSize});
        break;
    case TileTypes::spikes:
        {
            const float variantX = float(m_VariantIndex) * g_TileSize;
            levelTexture->Draw(position, Rectf{256 + variantX, 384, g_TileSize, g_TileSize});
        }
        break;
    case TileTypes::pushBlock:
        // TODO: Replace with object
        levelTexture->Draw(position, Rectf{0.0f, 0.0f, g_TileSize, g_TileSize});
        break;
    case TileTypes::entrance:
    case TileTypes::exit:
        break;
    case TileTypes::unknown:
        levelTexture->Draw(position, Rectf{15 * g_TileSize, 26 * g_TileSize, g_TileSize, g_TileSize});
        break;
    default:
        throw;
    }
}

const Vector2i& Tile::GetIndexPosition() const
{
    return m_IndexPosition;
}

void Tile::SetTileType(const TileTypes newTileType)
{
    m_TileType = newTileType;
}

TileTypes Tile::GetTileType() const
{
    return m_TileType;
}
