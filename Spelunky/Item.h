#pragma once

class Collider;

class Item
{
public:
    virtual ~Item() = default;
    Item() = default;
    Item(const Item&) = default;
    Item& operator=(const Item& c) = default;
    
    virtual void Draw() const = 0;
    virtual bool CanPickUp(const Collider* collider) const = 0;
    virtual bool IsPickedUp() const = 0;
    virtual void Teleport(const Vector2f& position) = 0;
    virtual void Throw(const Vector2f& velocity) = 0;
    virtual void SetIsPickedUp(bool pickedUp) = 0;
    virtual void Update(float elapsedTime) = 0;
};
