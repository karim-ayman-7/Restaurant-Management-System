#pragma once

#include <vector>
#include <string>
#include "Order.h"

struct PaymentSummary
{
    int paidOrderCount = 0;
    int cashTotal = 0;
    int cardTotal = 0;
    int otherTotal = 0;
};

class CashierFeatures
{
private:
    std::vector<Order>& pendingOrders;
    std::vector<Order>& orderHistory;

public:
    CashierFeatures(
        std::vector<Order>& pendingOrders,
        std::vector<Order>& orderHistory);

    const std::vector<Order>& GetPendingOrders() const;
    const std::vector<Order>& GetCompletedOrders() const;
    Order* GetPendingOrder(int index);
    bool CompletePayment(int index, const std::string& paymentMethod);
    PaymentSummary GetPaymentSummary() const;
};
