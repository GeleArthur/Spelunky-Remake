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
    ~ItemManager();
    
private:
    std::vector<Item*> m_Items;
};
