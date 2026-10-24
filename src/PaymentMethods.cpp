#include "PaymentMethods.h"

using namespace std;

string CashPayment::GetName() const
{
    return "Cash";
}


PaymentResult CashPayment::Pay(int amount, const PaymentInput& input) const
{
    if (input.cashReceived == 0)
        return {enPaymentStatus::Cancelled, GetName(), 0};

    if (input.cashReceived < 0 || amount <= 0)
        return {enPaymentStatus::InvalidAmount, GetName(), 0};

    if (input.cashReceived < amount)
        return {enPaymentStatus::InsufficientAmount, GetName(), 0};

    return {enPaymentStatus::Success, GetName(), input.cashReceived - amount};
}


string CardPayment::GetName() const
{
    return "Card";
}


PaymentResult CardPayment::Pay(int amount, const PaymentInput& input) const
{
    if (amount <= 0)
        return {enPaymentStatus::InvalidAmount, GetName(), 0};

    return {
        input.cardApproved ? enPaymentStatus::Success : enPaymentStatus::Declined,
        GetName(),
        0
    };
}
