#include "pch.h"
#include "Tile.h"


#include "TileTypes.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Vector2i.h"
#include "WorldManager.h"
#include <limits>

#include "Game.h"

Tile::Tile(const TileTypes tileType, const Vector2i& tileIndex, WorldManager* worldManager):
    RectPhysicsCollider{
        Rectf{
            static_cast<float>((tileIndex.x * Game::TILE_SIZE)), static_cast<float>((tileIndex.y * Game::TILE_SIZE)),
            Game::TILE_SIZE, Game::TILE_SIZE
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

    const Texture* levelTexture = m_SpriteSheetManager->GetLevelTexture();
    const Texture* doorsTexture = m_SpriteSheetManager->GetDoorsTexture();

    const Rectf rect = GetRect();
    const Vector2f position = Vector2f{rect.left, rect.top};

    switch (m_TileType)
    {
    case TileTypes::air:
        break;
    case TileTypes::ground:
        {
            const float variantX = static_cast<float>(m_VariantIndex % 4) * Game::TILE_SIZE;
            const float variantY = static_cast<float>(m_VariantIndex / 4) * Game::TILE_SIZE;
            levelTexture->Draw(position, Rectf{variantX, Game::TILE_SIZE + variantY, Game::TILE_SIZE, Game::TILE_SIZE});
        }
        break;
    case TileTypes::border:
        {
            const float variantX = static_cast<float>(m_VariantIndex % 2) * Game::TILE_SIZE;
            const float variantY = static_cast<float>(m_VariantIndex / 2) * Game::TILE_SIZE;
            levelTexture->Draw(position, Rectf{1536 + variantX, 512 + variantY, Game::TILE_SIZE, Game::TILE_SIZE});
        }
        break;
    case TileTypes::ladderTop:
        levelTexture->Draw(position, Rectf{192.0f, 0.0f, Game::TILE_SIZE, Game::TILE_SIZE});
        break;
    case TileTypes::ladder:
        levelTexture->Draw(position, Rectf{128.0f, 0.0f, Game::TILE_SIZE, Game::TILE_SIZE});
        break;
    case TileTypes::spikes:
        {
            const float variantX = static_cast<float>(m_VariantIndex) * Game::TILE_SIZE;
            levelTexture->Draw(position, Rectf{256 + variantX, 384, Game::TILE_SIZE, Game::TILE_SIZE});
        }
        break;
    case TileTypes::pushBlock:
        // TODO: Replace with object
        levelTexture->Draw(position, Rectf{0.0f, 0.0f, Game::TILE_SIZE, Game::TILE_SIZE});
        break;
    case TileTypes::entrance:
    case TileTypes::exit:
        break;
    case TileTypes::unknown:
        levelTexture->Draw(position, Rectf{15 * Game::TILE_SIZE, 26 * Game::TILE_SIZE, Game::TILE_SIZE, Game::TILE_SIZE});
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
