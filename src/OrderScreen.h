#pragma once

#include <vector>
#include "Enums.h"
#include "Menu.h"
#include "MenuScreen.h"
#include "Order.h"

class OrderScreen
{
private:
    Menu& menu;
    Order& order;
    MenuScreen menuScreen;

    void PrintOrderDetails() const;
    int ReadItemChoice();
    int ReadQuantity();
    int ReadNewQuantity();
    bool SelectCategory(std::string& category);
    int SelectItemNumber(std::string category, int itemsCount);
    bool AddItemToOrder();

public:
    OrderScreen(Menu& menu, Order& order);

    void StartOrder();
    void ViewAndEditOrder();
};
