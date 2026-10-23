#pragma once

#include <vector>
#include "Enums.h"
#include "Menu.h"
#include "Order.h"

class OrderScreen
{
private:
    Menu& menu;
    Order& order;

    void PrintOrderDetails() const;
    int ReadItemChoice();
    int ReadQuantity();
    int ReadNewQuantity();
    bool SelectCategory(enCategory& category);
    int SelectItemNumber(enCategory category, int itemsCount);
    bool AddItemToOrder();

public:
    OrderScreen(Menu& menu, Order& order);

    void StartOrder();
    void ViewAndEditOrder();
};