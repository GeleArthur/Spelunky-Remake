#pragma once
#include <vector>


#include "EntityPickupRectCollider.h"
#include "RectPhysicsCollider.h"


class Tile;
class SpriteSheetManager;

class Rock final : public EntityPickupRectCollider
{
public:
    explicit Rock(const Vector2f& position, WorldManager* worldManager);
    
    virtual EntityType GetEntityType() const override;
    virtual void Draw() const override;

private:
    const SpriteSheetManager* m_SpriteSheetManager;
};
