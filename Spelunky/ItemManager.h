#pragma once
#include <array>
#include <vector>

#include "Item.h"

class ItemManager final
{
public:
    void AddItem(Item* item);
    void DrawItems() const;
    void DrawPickupItems() const;
    void UpdateItems(float elapsedTime);
    std::vector<Item*>& GetItems();
    void ClearItems();
    ~ItemManager();
    
private:
    std::vector<Item*> m_Items;
};
