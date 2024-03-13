#pragma once
#include "SpriteSheetManager.h"
#include "TileTypes.h"

class Tile
{
public:
    Tile(TileTypes tileType, Vector2i tileIndex, SpriteSheetManager* spriteSheet);
    void SetVariantIndex(int index);
    void Draw() const;
    Vector2i GetIndexPosition() const;
    Vector2f GetWorldPosition() const;
private:
    SpriteSheetManager* m_SpriteSheetManager;
    Vector2f m_Position;
    TileTypes m_TileType;
    int m_VariantIndex;
};
