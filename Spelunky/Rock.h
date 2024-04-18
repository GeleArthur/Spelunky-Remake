#pragma once
#include <vector>

#include "Entity.h"
#include "PickupPickupItem.h"
#include "RectPhysicsCollider.h"


class Tile;
class SpriteSheetManager;

class Rock final : public Entity, public RectPhysicsCollider, public PickupItem
{
public:
    Rock(const Vector2f& position, const SpriteSheetManager* spriteSheetManager,
         const std::vector<std::vector<Tile>>* tiles);

    
    virtual EntityType GetEntityType() const override;
    virtual bool Throw(Vector2f force) override;
    virtual void Update(float elapsedTime) override;
    virtual void Draw() const override;
    virtual bool CanBePickedUp() override;

private:
    const SpriteSheetManager* m_SpriteSheetManager;
    // bool m_IsPickedUp{};
};
