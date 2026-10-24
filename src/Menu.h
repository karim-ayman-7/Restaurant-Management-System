#pragma once

#include <vector>
#include <string>
#include "MenuItem.h"

class Menu
{
private:
    std::vector<MenuItem> MenuItems;

public:
    explicit Menu(const std::vector<MenuItem>& items);

    bool AddItem(const std::string& name, int price, const std::string& category);
    bool UpdateItem(
        int id,
        const std::string& name,
        int price,
        const std::string& category);
    std::vector<MenuItem> GetItems() const;
    bool RemoveItem(int id);
    std::vector<std::string> GetCategories() const;
    std::vector<MenuItem> GetItemsByCategory(const std::string& category) const;
};
