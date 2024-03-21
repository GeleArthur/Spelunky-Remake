#pragma once
#include <vector>

#include "PhysicsObject.h"

class Tile;
class SpriteSheetManager;

class PlayerObject final : PhysicsObject
{
public:
    explicit PlayerObject(Vector2f startPosition, SpriteSheetManager* spriteSheetManager, const std::vector<std::vector<Tile>>& tiles);
    void Draw() const;
    void Update(float elapsedTimes);

private:
    SpriteSheetManager* m_SpriteSheetManager;
};
