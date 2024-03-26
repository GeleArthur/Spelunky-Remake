#pragma once
#include <array>
#include <vector>

#include "Item.h"

class ItemManager final
{
public:
    void AddItem(Item* item);
    void DrawItems() const;
    void UpdateItems(float elapsedTime);
    
private:
    std::vector<Item*> m_Items;
};
