#pragma once

class Entity;

class PickUp
{
public:
    virtual ~PickUp() = default;
    virtual void DrawPickedUp() const = 0;
    virtual  void Throw(const Vector2f& force) = 0;
    virtual bool TryToPickUp(Entity* pickedUpBy) = 0;
    virtual void SetTargetPosition(const Vector2f& position, const Vector2f& goingTo) = 0;
    virtual  bool GetIsPickedUp() const = 0;
    virtual bool CanBePickedUp() const = 0;
};
