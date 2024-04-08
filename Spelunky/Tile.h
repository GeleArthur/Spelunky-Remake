#pragma once
#include "RectCollider.h"
#include "SpriteSheetManager.h"
#include "TileTypes.h"

class Tile
{
public:
    explicit Tile(TileTypes tileType, Vector2i tileIndex, SpriteSheetManager* spriteSheet);
    void SetVariantIndex(int index);
    void Draw() const;
    Vector2i GetIndexPosition() const;
    const Vector2f& GetWorldPosition() const;
    TileTypes GetTileType() const;
    const RectCollider* GetCollider() const;

private:
    SpriteSheetManager* m_SpriteSheetManager;
    Vector2f m_Position;
    RectCollider m_Collider;
    TileTypes m_TileType;
    int m_VariantIndex;
};
