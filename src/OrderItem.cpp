#include "OrderItem.h"

OrderItem::OrderItem(const MenuItem& item, int quantity)
    : Item(item), Quantity(quantity)
{
}


const MenuItem& OrderItem::GetItem() const
{
    return Item;
}


int OrderItem::GetQuantity() const
{
    return Quantity;
}


int OrderItem::GetSubTotal() const
{
    return Item.GetPrice() * Quantity;
}

void OrderItem::IncreaseQuantity(int amount)
{
    Quantity += amount;
}


void OrderItem::SetQuantity(int quantity)
{
    Quantity = quantity;
}
