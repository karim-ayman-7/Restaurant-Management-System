#include "PaymentScreen.h"

#include <iostream>
#include <iomanip>
#include "PaymentMethods.h"
#include "Utils.h"

using namespace std;

PaymentResult PaymentScreen::MakePayment(const Order& order)
{
    ClearScreen();

    PrintLine();
    PrintCentered("Process Payment");
    PrintLine();

    cout << "Order ID: " << order.GetId() << endl;
    cout << "Total to pay: " << order.GetTotal() << "\n\n";

    cout << "Choose payment method:" << endl;
    cout << "1-Cash" << endl;
    cout << "2-Card" << endl;
    cout << "3-Back\n\n";
    cout << "Enter choice: ";

    int choice = ReadPaymentChoice();

    if (choice == 3)
        return {enPaymentStatus::Cancelled, "", 0};

    CashPayment cash;
    CardPayment card;

    const PaymentMethod& method = (choice == 1)
        ? static_cast<const PaymentMethod&>(cash)
        : static_cast<const PaymentMethod&>(card);

    PaymentInput input;
    if (choice == 1)
    {
        while (true)
        {
            cout << "Enter cash received from the customer (0 to cancel): ";
            if (!ReadInt(input.cashReceived))
            {
                cout << "Invalid amount." << endl;
                continue;
            }

            PaymentResult result = method.Pay(order.GetTotal(), input);
            if (result.status == enPaymentStatus::Cancelled)
                return result;
            if (result.status == enPaymentStatus::InvalidAmount)
            {
                cout << "Invalid amount." << endl;
                continue;
            }
            if (result.status == enPaymentStatus::InsufficientAmount)
            {
                cout << "Not enough. You still need "
                    << order.GetTotal() - input.cashReceived << "." << endl;
                continue;
            }

            if (result.change > 0)
            {
                cout << "Change: " << result.change << endl;
                PauseAndWaitForEnter();
            }
            return result;
        }
    }

    cout << "Process " << order.GetTotal() << " on the card terminal." << endl;
    cout << "Was the card payment approved by the terminal? (y/n): ";
    input.cardApproved = ReadYesNo();
    PaymentResult result = method.Pay(order.GetTotal(), input);
    if (result.status != enPaymentStatus::Success)
    {
        cout << "Payment was not completed. The order is still waiting for payment." << endl;
        PauseAndWaitForEnter();
    }
    return result;
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


void PaymentScreen::PrintReceipt(const Order& order) const
{
    cout << endl;
    PrintLine('=');
    PrintCentered("Receipt");
    PrintLine('=');

    cout << "Order ID: " << order.GetId() << endl << endl;
    cout << left << setw(25) << "Item"
        << setw(12) << "Quantity"
        << setw(15) << "Unit Price"
        << "Subtotal" << endl;

    for (const OrderItem& orderItem : order.GetItems())
    {
        const MenuItem& item = orderItem.GetItem();

        cout << left << setw(25) << item.GetName()
            << setw(12) << orderItem.GetQuantity()
            << setw(15) << item.GetPrice()
            << orderItem.GetSubTotal() << endl;
    }

    cout << endl << "Total: " << order.GetTotal() << endl;
    cout << "Paid by: " << order.GetPaymentMethod() << endl;
    cout << endl << "Thank you!" << endl;
}


void PaymentScreen::ShowReceipt(const Order& order) const
{
    ClearScreen();
    PrintReceipt(order);
    PauseAndWaitForEnter();
}
