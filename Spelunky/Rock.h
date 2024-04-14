#pragma once
#include "Item.h"
#include "PhysicsObject.h"

class SpriteSheetManager;

class Rock final : public PhysicsObject, public Item
{
public:
    Rock(const Vector2f& position, const SpriteSheetManager* spriteSheetManager, const std::vector<std::vector<Tile>>* tiles);
    
    virtual void Update(float elapsedTime) override;
    virtual void Draw() const override;
    virtual bool CanPickUp(const Collider* collider) const override;
    virtual bool IsPickedUp() const override;
    virtual void Teleport(const Vector2f& position) override;
    virtual void Throw(const Vector2f& velocity) override;
    virtual void SetIsPickedUp(bool pickedUp) override;
    
private:
    const SpriteSheetManager* m_SpriteSheetManager;
    bool m_IsPickedUp{};
};


