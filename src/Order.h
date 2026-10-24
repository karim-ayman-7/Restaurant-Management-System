#pragma once

#include <string>
#include <vector>
#include "OrderItem.h"
#include "Enums.h"

class Order
{
private:
    std::vector<OrderItem> OrderItems;

    static int NextId;
    int Id;
    enOrderStatus Status;
    std::string PaymentMethod;

public:
    Order();
    Order(int id, enOrderStatus status, const std::string& paymentMethod);

    int GetId() const;
    enOrderStatus GetStatus() const;
    const std::string& GetPaymentMethod() const;
    int GetTotal() const;
    bool AddItem(const MenuItem& item, int quantity);
    bool IsEmpty() const;
    const std::vector<OrderItem>& GetItems() const;
    bool SetItemQuantity(int index, int quantity);
    void MarkWaitingForPayment();
    void MarkPaid(const std::string& paymentMethod);
    void Reset();
};
