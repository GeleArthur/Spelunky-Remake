#pragma once


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
    virtual void Update(float elapsedTime) override;

private:
    const SpriteSheetManager* m_SpriteSheetManager;
    float m_FrictionOnFloor{0.3f};
};
