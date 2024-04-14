#pragma once
#include <array>
#include <vector>

#include "Item.h"

class ItemManager final
{
public:
    ItemManager() = default;
    ~ItemManager();
    ItemManager(const ItemManager& other);
    ItemManager& operator=(const ItemManager& other);
    
    void AddItem(Item* item);
    void DrawItems() const;
    void DrawPickupItems() const;
    void UpdateItems(float elapsedTime);
    std::vector<Item*>& GetItems();
    void ClearItems();

    
private:
    std::vector<Item*> m_Items;
};
