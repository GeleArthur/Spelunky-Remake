#pragma once
#include "Item.h"
#include "PhysicsObject.h"

class SpriteSheetManager;

class Rock : public PhysicsObject, public Item
{
public:
    Rock(const Vector2f& position, const SpriteSheetManager* spriteSheetManager, const std::vector<std::vector<Tile>>* tiles);

    void Update(float elapsedTime) override;
    void Draw() const override;
    
private:
    const SpriteSheetManager* m_SpriteSheetManager;
};
