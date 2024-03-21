#pragma once
#include "PhysicsObject.h"

class SpriteSheetManager;

class Rock : PhysicsObject
{
public:
    Rock(const Vector2f& position, const SpriteSheetManager* spriteSheetManager, const std::vector<std::vector<Tile>>& tiles);

    void Update(float elapsedTime);
    void Draw();
    
private:
    const SpriteSheetManager* m_SpriteSheetManager;
};
