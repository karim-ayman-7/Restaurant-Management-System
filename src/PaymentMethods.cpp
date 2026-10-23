#include "PaymentMethods.h"

#include <iostream>
#include "Utils.h"

using namespace std;

string CashPayment::GetName() const
{
    return "Cash";
}

bool CashPayment::Pay(int amount)
{
    while (true)
    {
        int received;

        cout << "Enter the cash amount you are paying (0 to cancel): ";

        if (!ReadInt(received) || received < 0)
        {
            cout << "Invalid amount." << endl;
            continue;
        }

        if (received == 0)
            return false;

        if (received < amount)
        {
            cout << "Not enough. You still need " << amount - received << "." << endl;
            continue;
        }

        if (received > amount)
            cout << "Change: " << received - amount << endl;

        return true;
    }
}

bool CardPayment::IsValidCardNumber(const string& number) const
{
    if (number.length() != 16)
        return false;

    for (char c : number)
    {
        if (c < '0' || c > '9')
            return false;
    }

    return true;
}

string CardPayment::GetName() const
{
    return "Card";
}

bool CardPayment::Pay(int amount)
{
    while (true)
    {
        cout << "Enter 16-digit card number (0 to cancel): ";
        string cardNumber = ReadLine();

        if (cardNumber == "0")
            return false;

        if (!IsValidCardNumber(cardNumber))
        {
            cout << "Invalid card number." << endl;
            continue;
        }

        cout << "Charged " << amount << " to card ending in "
            << cardNumber.substr(12) << endl;

        return true;
    }
}
