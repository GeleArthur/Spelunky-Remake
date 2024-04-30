#pragma once

class PickupItem
{
public:
    PickupItem() = default;
    virtual ~PickupItem() = default;
    PickupItem(const PickupItem& other) = default;
    PickupItem& operator=(const PickupItem& other) = default;
    PickupItem(PickupItem && other) = default;
    PickupItem& operator=(PickupItem&& other) = default;
    
    virtual bool Throw(Vector2f force) = 0;
    virtual bool CanBePickedUp() = 0;
    virtual void Draw() const = 0;
};
