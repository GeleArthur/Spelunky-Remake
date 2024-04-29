#pragma once

class PickupItem
{
public:
    virtual ~PickupItem() = default;
    
    virtual bool Throw(Vector2f force) = 0;
    virtual bool CanBePickedUp() = 0;
    virtual void Draw() const = 0;
};
