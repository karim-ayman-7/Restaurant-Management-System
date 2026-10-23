#pragma once

#include <vector>
#include "Enums.h"
#include "MenuItem.h"

class Menu
{
private:
    std::vector<MenuItem> MenuItems;

public:
    Menu();

    void MenuHeader() const;
    void DisplayCategories() const;
    void DisplayCategoryItems(enCategory Category) const;
    enCategory SelectCategoryChoice();
    std::vector<MenuItem> GetItemsByCategory(enCategory category) const;
};