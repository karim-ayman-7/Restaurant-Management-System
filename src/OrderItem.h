#pragma once

#include "MenuItem.h"

class OrderItem
{
private:
    friend class Order;

    MenuItem Item;
    int Quantity;

    OrderItem(const MenuItem& item, int quantity);
    void IncreaseQuantity(int amount);
    void SetQuantity(int quantity);

public:
    const MenuItem& GetItem() const;
    int GetQuantity() const;
    int GetSubTotal() const;
};
