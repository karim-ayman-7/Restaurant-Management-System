#pragma once

#include <vector>
#include "CashierFeatures.h"
#include "PaymentScreen.h"

class CashierScreen
{
private:
    PaymentScreen paymentScreen;

public:
    int SelectPendingOrder(const std::vector<Order>& orders) const;
    PaymentResult MakePayment(const Order& order);
    void ShowReceipt(const Order& order) const;
    void ShowCompletedOrders(const std::vector<Order>& orders) const;
    void ShowPaymentSummary(const PaymentSummary& summary) const;
    void ShowMessage(const std::string& message) const;
};
