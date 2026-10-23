#pragma once

#include <string>

class PaymentMethod
{
public:
    virtual ~PaymentMethod() = default;

    virtual std::string GetName() const = 0;
    virtual bool Pay(int amount) = 0;
};

class CashPayment : public PaymentMethod
{
public:
    std::string GetName() const override;
    bool Pay(int amount) override;
};

class CardPayment : public PaymentMethod
{
private:
    bool IsValidCardNumber(const std::string& number) const;

public:
    std::string GetName() const override;
    bool Pay(int amount) override;
};