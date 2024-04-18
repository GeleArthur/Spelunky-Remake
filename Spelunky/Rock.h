#pragma once
#include <vector>

#include "Item.h"
#include "PhysicsComponent.h"
#include "RectPhysicsCollider.h"


class Tile;
class SpriteSheetManager;

class Rock final : public RectPhysicsCollider, public Item
{
public:
    Rock(const Vector2f& position, const SpriteSheetManager* spriteSheetManager,
         const std::vector<std::vector<Tile>>* tiles);

    virtual void Update(float elapsedTime) override;
    virtual void Draw() const override;
    virtual bool IsPickedUp() const override;
    virtual void SetIsPickedUp(bool pickedUp) override;

    virtual bool CanPickUp(const Collider* collider) const override;
    virtual void Teleport(const Vector2f& position) override;
    virtual void Throw(const Vector2f& velocity) override;

private:
    const SpriteSheetManager* m_SpriteSheetManager;
    bool m_IsPickedUp{};
};
