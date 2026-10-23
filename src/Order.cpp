#include "Order.h"

using namespace std;

int Order::NextId = 1;

Order::Order()
    : Id(NextId++)
{
}

int Order::GetId() const
{
    return Id;
}

int Order::GetTotal() const
{
    int total = 0;

    for (const OrderItem& orderItem : OrderItems)
    {
        total += orderItem.GetSubTotal();
    }

    return total;
}

void Order::AddItem(const MenuItem& item, int quantity)
{
    for (OrderItem& orderItem : OrderItems)
    {
        if (orderItem.GetItem().GetId() == item.GetId())
        {
            orderItem.IncreaseQuantity(quantity);
            return;
        }
    }

    OrderItems.push_back(OrderItem(item, quantity));
}

bool Order::IsEmpty() const
{
    return OrderItems.empty();
}

const vector<OrderItem>& Order::GetItems() const
{
    return OrderItems;
}

bool Order::SetItemQuantity(int index, int quantity)
{
    if (index < 0 || index >= static_cast<int>(OrderItems.size()))
        return false;

    if (quantity < 0)
        return false;

    if (quantity == 0)
    {
        OrderItems.erase(OrderItems.begin() + index);
        return true;
    }

    OrderItems[index].SetQuantity(quantity);
    return true;
}

void Order::Reset()
{
    OrderItems.clear();
    Id = NextId++;
}