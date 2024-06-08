#pragma once
#include "RectPhysicsCollider.h"
#include "SpriteSheetManager.h"
#include "TileTypes.h"
#include "Vector2i.h"

class Tile final
{
public:
    explicit Tile(TileTypes tileType, const Vector2i& tileIndex, WorldManager* worldManager);
    
    void Draw() const;
    const Vector2i& GetIndexPosition() const;
    
    void SetTileType(TileTypes newTileType);
    void SetVariantIndex(int index);
    TileTypes GetTileType() const;
    const Vector2f& GetCenter() const;
    const Rectf& GetRect() const;
    const RectPhysicsCollider& GetCollider() const;

private:
    SpriteSheetManager* m_SpriteSheetManager;
    RectPhysicsCollider m_PhysicsCollider;
    Vector2i m_IndexPosition;
    TileTypes m_TileType;
    int m_VariantIndex{0};
};
