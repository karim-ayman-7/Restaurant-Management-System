#include "CashierScreen.h"

#include <iomanip>
#include <iostream>
#include "Utils.h"

using namespace std;

int CashierScreen::SelectPendingOrder(const vector<Order>& orders) const
{
    PrintLine();
    PrintCentered("Orders Waiting for Payment");
    PrintLine();
    cout << endl;

    if (orders.empty())
    {
        cout << "There are no orders waiting for payment." << endl;
        PauseAndWaitForEnter();
        return -1;
    }

    for (int i = 0; i < static_cast<int>(orders.size()); i++)
    {
        const Order& order = orders[i];
        cout << left << setw(12) << ("Order " + to_string(i + 1))
            << setw(15) << "Order ID:" << order.GetId() << endl << endl;
        cout << left << setw(25) << "Item" << setw(12) << "Quantity"
            << setw(15) << "Unit Price" << "Subtotal" << endl;
        for (const OrderItem& orderItem : order.GetItems())
        {
            const MenuItem& item = orderItem.GetItem();
            cout << left << setw(25) << item.GetName()
                << setw(12) << orderItem.GetQuantity()
                << setw(15) << item.GetPrice()
                << orderItem.GetSubTotal() << endl;
        }
        cout << endl << "Total: " << order.GetTotal() << endl << endl;
    }

    cout << "0-Back" << endl;
    cout << "Choose an order to process: ";
    int choice;
    while (true)
    {
        if (ReadInt(choice) && choice >= 0
            && choice <= static_cast<int>(orders.size()))
            return choice - 1;
        cout << "Invalid choice. Enter 0 or a number from 1 to "
            << orders.size() << ": ";
    }
}


PaymentResult CashierScreen::MakePayment(const Order& order)
{
    return paymentScreen.MakePayment(order);
}


void CashierScreen::ShowReceipt(const Order& order) const
{
    paymentScreen.ShowReceipt(order);
}


void CashierScreen::ShowCompletedOrders(const vector<Order>& orders) const
{
    PrintLine();
    PrintCentered("Completed Orders");
    PrintLine();
    cout << endl;

    if (orders.empty())
    {
        cout << "There are no completed orders yet." << endl;
        PauseAndWaitForEnter();
        return;
    }

    for (const Order& order : orders)
    {
        cout << "Order ID: " << order.GetId() << endl;
        cout << "Status: Paid" << endl;
        cout << left << setw(25) << "Item" << setw(12) << "Quantity"
            << setw(15) << "Unit Price" << "Subtotal" << endl;
        for (const OrderItem& orderItem : order.GetItems())
        {
            const MenuItem& item = orderItem.GetItem();
            cout << left << setw(25) << item.GetName()
                << setw(12) << orderItem.GetQuantity()
                << setw(15) << item.GetPrice()
                << orderItem.GetSubTotal() << endl;
        }
        cout << endl << "Total: " << order.GetTotal() << endl;
        cout << "Paid by: " << order.GetPaymentMethod() << endl << endl;
    }
    PauseAndWaitForEnter();
}


void CashierScreen::ShowPaymentSummary(const PaymentSummary& summary) const
{
    PrintLine();
    PrintCentered("Payment Summary");
    PrintLine();
    cout << endl;

    if (summary.paidOrderCount == 0)
    {
        cout << "There are no completed payments yet." << endl;
        PauseAndWaitForEnter();
        return;
    }

    cout << "Paid orders: " << summary.paidOrderCount << endl;
    cout << "Cash collected: " << summary.cashTotal << endl;
    cout << "Card collected: " << summary.cardTotal << endl;
    if (summary.otherTotal > 0)
        cout << "Other payments: " << summary.otherTotal << endl;
    cout << "Total collected: "
        << summary.cashTotal + summary.cardTotal + summary.otherTotal << endl;
    cout << endl << "Note: This summary includes all saved completed orders." << endl;
    PauseAndWaitForEnter();
}


void CashierScreen::ShowMessage(const string& message) const
{
    cout << message << endl;
    PauseAndWaitForEnter();
}
