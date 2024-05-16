#pragma once

class EntityRectCollider;

class PickUp
{
public:
    virtual ~PickUp() = default;
    virtual void DrawPickedUp() const = 0;
    virtual  void Throw(const Vector2f& force) = 0;
    virtual bool TryToPickUp(EntityRectCollider* pickedUpBy) = 0;
    virtual void SetTargetPosition(const Vector2f& position, const Vector2f& goingTo) = 0;
    virtual  bool IsPickedUp() const = 0;
    virtual bool CanBePickedUp() const = 0;
};
