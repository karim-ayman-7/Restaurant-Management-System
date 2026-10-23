#pragma once

#include "NavigationMenu.h"
#include "Enums.h"
#include "AdminFeatures.h"
#include "Menu.h"

class AdminMenu : public NavigationMenu
{
private:
    Menu& menu;
    AdminFeatures adminFeatures;

    std::string GetTitle() const override;
    void ShowOptions() override;
    void PerformChoice(int choice) override;
    int GetLastChoice() const override;

public:
    AdminMenu(Menu& menu);
};
