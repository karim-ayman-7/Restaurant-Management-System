#pragma once

#include <string>
#include "Menu.h"

class MenuScreen
{
private:
    const Menu& menu;

public:
    MenuScreen(const Menu& menu);

    void MenuHeader() const;
    void DisplayCategories() const;
    void DisplayCategoryItems(const std::string& category) const;
    std::string SelectCategoryChoice() const;
};
