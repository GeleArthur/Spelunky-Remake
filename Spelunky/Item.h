#pragma once

class Item
{
public:
    virtual ~Item() = default;
    virtual void Draw() const = 0;
    virtual void Update(float elapsedTime) = 0;
};
