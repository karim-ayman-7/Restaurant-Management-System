#pragma once

#include "NavigationMenu.h"
#include "Enums.h"
#include "Menu.h"
#include "Order.h"
#include "OrderScreen.h"
#include "PaymentScreen.h"

class CustomerMenu : public NavigationMenu
{
private:
    Order order;
    OrderScreen orderScreen;
    PaymentScreen paymentScreen;

    std::string GetTitle() const override;
    void ShowOptions() override;
    void PerformChoice(int choice) override;
    int GetLastChoice() const override;

public:
    CustomerMenu(Menu& menu);
};