#pragma once
#include <vector>

#include "Entity.h"
#include "PickupPickupItem.h"
#include "RectPhysicsCollider.h"


class Tile;
class SpriteSheetManager;

class Rock final : public Entity, public PickupItem, public RectPhysicsCollider
{
public:
    explicit Rock(const Vector2f& position, WorldManager* worldManager);
    virtual ~Rock() override = default;
    Rock(const Rock& other) = default;
    Rock& operator=(const Rock& other) = default;
    Rock(Rock && other) = default;
    Rock& operator=(Rock&& other) = default;
    
    virtual EntityType GetEntityType() const override;
    virtual bool Throw(Vector2f force) override;
    virtual void Update(float elapsedTime) override;
    virtual void Draw() const override;
    virtual bool CanBePickedUp() override;

private:
    const SpriteSheetManager* m_SpriteSheetManager;
    // bool m_IsPickedUp{};
};
