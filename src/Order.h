#pragma once

#include <vector>
#include "OrderItem.h"

class Order
{
private:
    std::vector<OrderItem> OrderItems;

    static int NextId;
    int Id;

public:
    Order();

    int GetId() const;
    int GetTotal() const;
    void AddItem(const MenuItem& item, int quantity);
    bool IsEmpty() const;
    const std::vector<OrderItem>& GetItems() const;
    bool SetItemQuantity(int index, int quantity);
    void Reset();
};