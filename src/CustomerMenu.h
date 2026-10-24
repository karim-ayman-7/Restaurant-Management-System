#pragma once

#include "NavigationMenu.h"
#include "Enums.h"
#include "Menu.h"
#include "Order.h"
#include "OrderScreen.h"
#include <vector>

class CustomerMenu : public NavigationMenu
{
private:
    Order order;
    std::vector<Order>& pendingOrders;
    OrderScreen orderScreen;

    void ConfirmOrder();

    std::string GetTitle() const override;
    void ShowOptions() override;
    void PerformChoice(int choice) override;
    int GetLastChoice() const override;

public:
    CustomerMenu(Menu& menu, std::vector<Order>& pendingOrders);
};
