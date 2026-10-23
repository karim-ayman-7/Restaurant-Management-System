#include "PaymentScreen.h"

#include <iostream>
#include <iomanip>
#include "Utils.h"
#include "PaymentMethods.h"

using namespace std;

PaymentScreen::PaymentScreen(Order& order)
    : order(order)
{
}

int PaymentScreen::ReadPaymentChoice()
{
    int choice;

    while (true)
    {
        if (ReadInt(choice) && choice >= 1 && choice <= 3)
            return choice;

        cout << "Invalid choice. Choose a number from 1 to 3: ";
    }
}

void PaymentScreen::PrintReceipt(const string& methodName) const
{
    cout << endl;
    PrintLine('=');
    PrintCentered("Receipt");
    PrintLine('=');

    cout << "Order ID: " << order.GetId() << "\n\n";

    for (const OrderItem& orderItem : order.GetItems())
    {
        const MenuItem& item = orderItem.GetItem();

        cout << "- " << left << setw(20) << item.GetName()
            << setw(10) << ("x" + to_string(orderItem.GetQuantity()))
            << "Subtotal: " << orderItem.GetSubTotal() << endl;
    }

    cout << endl << "Total: " << order.GetTotal() << endl;
    cout << "Paid by: " << methodName << endl;
    cout << endl << "Thank you!" << endl;
}

void PaymentScreen::MakePayment()
{
    ClearScreen();

    PrintLine();
    PrintCentered("Payment");
    PrintLine();

    if (order.IsEmpty())
    {
        cout << "Your order is empty." << endl;
        PauseAndWaitForEnter();
        return;
    }

    cout << "Order ID: " << order.GetId() << endl;
    cout << "Total to pay: " << order.GetTotal() << "\n\n";

    cout << "Choose payment method:" << endl;
    cout << "1-Cash" << endl;
    cout << "2-Card" << endl;
    cout << "3-Back\n\n";
    cout << "Enter choice: ";

    int choice = ReadPaymentChoice();

    if (choice == 3)
        return;

    CashPayment cash;
    CardPayment card;

    PaymentMethod& method = (choice == 1)
        ? static_cast<PaymentMethod&>(cash)
        : static_cast<PaymentMethod&>(card);

    if (!method.Pay(order.GetTotal()))
    {
        cout << "Payment cancelled." << endl;
        PauseAndWaitForEnter();
        return;
    }

    PauseAndWaitForEnter();
    ClearScreen();
    PrintReceipt(method.GetName());
    order.Reset();

    PauseAndWaitForEnter();
}