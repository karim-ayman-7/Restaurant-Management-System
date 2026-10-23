#pragma once

#include "MenuItem.h"

class OrderItem
{
private:
    MenuItem Item;
    int Quantity;

public:
    OrderItem(const MenuItem& item, int quantity);

    const MenuItem& GetItem() const;
    int GetQuantity() const;
    void IncreaseQuantity(int amount);
    void SetQuantity(int quantity);
    int GetSubTotal() const;
};