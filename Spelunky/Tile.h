#pragma once
#include "SpriteSheetManager.h"

enum class TileType
{
    air,
    ground,
    ladder
};


class Tile
{
public:
    Tile(TileType tileType, SpriteSheetManager* spriteSheet);
    void SetVariantIndex(int index);
    void Draw();
private:
    TileType m_TileType;
    int m_VariantIndex;
    SpriteSheetManager* m_SpriteSheetManager;
    Vector2f m_Position;
    
};
