﻿#include "pch.h"
#include "ItemManager.h"
#include "Item.h"

void ItemManager::AddItem(Item* item)
{
    m_Items.push_back(item);
}

void ItemManager::DrawItems() const
{
    for (const Item* item : m_Items)
    {
        item->Draw();
    }
}

void ItemManager::UpdateItems(const float elapsedTime)
{
    for (Item* item : m_Items)
    {
        item->Update(elapsedTime);
    }
}
