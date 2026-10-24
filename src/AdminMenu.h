#pragma once

#include "NavigationMenu.h"
#include "Enums.h"
#include "AdminFeatures.h"
#include "AdminScreen.h"
#include "Menu.h"
#include <vector>

class AdminMenu : public NavigationMenu
{
private:
    Menu& menu;
    AdminFeatures adminFeatures;
    AdminScreen adminScreen;

    std::string GetTitle() const override;
    void ShowOptions() override;
    void PerformChoice(int choice) override;
    int GetLastChoice() const override;

public:
    AdminMenu(Menu& menu, const std::vector<Order>& orderHistory);

    void Run() override;
};
