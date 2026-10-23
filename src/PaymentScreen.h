#pragma once

#include "Order.h"

class PaymentScreen
{
private:
    Order& order;

    int ReadPaymentChoice();
    void PrintReceipt(const std::string& methodName) const;

public:
    PaymentScreen(Order& order);

    void MakePayment();
};