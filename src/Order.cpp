#include "Order.h"

using namespace std;

int Order::NextId = 1;

Order::Order()
    : Id(NextId++), Status(enOrderStatus::Open)
{
}


Order::Order(int id, enOrderStatus status, const string& paymentMethod)
    : Id(id), Status(status), PaymentMethod(paymentMethod)
{
    if (id >= NextId)
        NextId = id + 1;
}


bool Order::AddItem(const MenuItem& item, int quantity)
{
    if (quantity <= 0)
        return false;

    for (OrderItem& orderItem : OrderItems)
    {
        if (orderItem.GetItem().GetId() == item.GetId())
        {
            orderItem.IncreaseQuantity(quantity);
            return true;
        }
    }

    OrderItems.push_back(OrderItem(item, quantity));
    return true;
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


void Order::MarkWaitingForPayment()
{
    Status = enOrderStatus::WaitingForPayment;
}

void Order::MarkPaid(const string& paymentMethod)
{
    Status = enOrderStatus::Paid;
    PaymentMethod = paymentMethod;
}


void Order::Reset()
{
    OrderItems.clear();
    Id = NextId++;
    Status = enOrderStatus::Open;
    PaymentMethod.clear();
}


bool Order::IsEmpty() const
{
    return OrderItems.empty();
}


const vector<OrderItem>& Order::GetItems() const
{
    return OrderItems;
}


int Order::GetId() const
{
    return Id;
}


enOrderStatus Order::GetStatus() const
{
    return Status;
}


const string& Order::GetPaymentMethod() const
{
    return PaymentMethod;
}
