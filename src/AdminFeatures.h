#pragma once

#include "Menu.h"
#include "MenuScreen.h"

class AdminFeatures
{
private:
    Menu& menu;
    MenuScreen menuScreen;

public:
    AdminFeatures(Menu& menu);

    bool AddMenuItem();
    bool RemoveMenuItem();
    void ViewOrders();
};
