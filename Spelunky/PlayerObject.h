#pragma once
#include "PhysicsObject.h"

class SpriteSheetManager;

class PlayerObject final : PhysicsObject
{
public:
    explicit PlayerObject(Vector2f startPosition, SpriteSheetManager* spriteSheetManager);
    void Draw() const;
    void Update(float elapsedTimes);

private:
    SpriteSheetManager* m_SpriteSheetManager;
};
