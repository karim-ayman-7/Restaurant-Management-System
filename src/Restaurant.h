#pragma once

#include "NavigationMenu.h"
#include "Menu.h"
#include "CustomerMenu.h"
#include "CashierMenu.h"
#include "AdminMenu.h"
#include <vector>

class Restaurant : public NavigationMenu
{
private:
    Menu menu;
    std::vector<Order> pendingOrders;
    std::vector<Order> orderHistory;
    CustomerMenu customerMenu;
    CashierMenu cashierMenu;
    AdminMenu adminMenu;

    std::string GetTitle() const override;
    void ShowOptions() override;
    void PerformChoice(int choice) override;
    int GetLastChoice() const override;

public:
    Restaurant();
};
