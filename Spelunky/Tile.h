#pragma once
#include "RectPhysicsCollider.h"
#include "SpriteSheetManager.h"
#include "TileTypes.h"
#include "Vector2i.h"

class Tile final
{
public:
    explicit Tile(TileTypes tileType, Vector2i tileIndex, SpriteSheetManager* spriteSheet);
    void SetVariantIndex(int index);
    void Draw() const;
    const Vector2i& GetIndexPosition() const;
    TileTypes GetTileType() const;
    const RectPhysicsCollider* GetCollider() const;

private:
    SpriteSheetManager* m_SpriteSheetManager;
    Vector2i m_IndexPosition;
    RectPhysicsCollider m_Collider;
    TileTypes m_TileType;
    int m_VariantIndex;
};
