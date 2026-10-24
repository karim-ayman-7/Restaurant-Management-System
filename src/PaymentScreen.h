#pragma once

#include "Order.h"
#include "PaymentMethods.h"

class PaymentScreen
{
private:
    int ReadPaymentChoice();
    void PrintReceipt(const Order& order) const;

public:
    PaymentResult MakePayment(const Order& order);
    void ShowReceipt(const Order& order) const;
};
