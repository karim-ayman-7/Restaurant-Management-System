#pragma once

#include "NavigationMenu.h"
#include "Enums.h"
#include "CashierFeatures.h"
#include "CashierScreen.h"

class CashierMenu : public NavigationMenu
{
private:
    CashierFeatures cashierFeatures;
    CashierScreen cashierScreen;

    std::string GetTitle() const override;
    void ShowOptions() override;
    void PerformChoice(int choice) override;
    int GetLastChoice() const override;

public:
    CashierMenu(
        std::vector<Order>& pendingOrders,
        std::vector<Order>& orderHistory);
};
