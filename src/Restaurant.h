#pragma once

#include "NavigationMenu.h"
#include "Menu.h"
#include "CustomerMenu.h"

class Restaurant : public NavigationMenu
{
private:
    Menu menu;
    CustomerMenu customerMenu;

    std::string GetTitle() const override;
    void ShowOptions() override;
    void PerformChoice(int choice) override;
    int GetLastChoice() const override;

public:
    Restaurant();
};