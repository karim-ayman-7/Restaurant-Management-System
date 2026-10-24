#pragma once

#include <string>

enum class enPaymentStatus
{
    Success,
    Cancelled,
    InvalidAmount,
    InsufficientAmount,
    Declined
};

struct PaymentInput
{
    int cashReceived = 0;
    bool cardApproved = false;
};

struct PaymentResult
{
    enPaymentStatus status = enPaymentStatus::Cancelled;
    std::string method;
    int change = 0;
};

class PaymentMethod
{
public:
    virtual ~PaymentMethod() = default;

    virtual std::string GetName() const = 0;
    virtual PaymentResult Pay(int amount, const PaymentInput& input) const = 0;
};

class CashPayment : public PaymentMethod
{
public:
    std::string GetName() const override;
    PaymentResult Pay(int amount, const PaymentInput& input) const override;
};

class CardPayment : public PaymentMethod
{
public:
    std::string GetName() const override;
    PaymentResult Pay(int amount, const PaymentInput& input) const override;
};
