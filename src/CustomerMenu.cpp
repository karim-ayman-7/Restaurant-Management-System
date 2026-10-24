#include "CustomerMenu.h"

#include <iomanip>
#include <iostream>
#include "FileManager.h"
#include "Utils.h"

using namespace std;

CustomerMenu::CustomerMenu(Menu& menu, vector<Order>& pendingOrders)
    : pendingOrders(pendingOrders),
      orderScreen(menu, order)
{
}


string CustomerMenu::GetTitle() const
{
    return "Customer Menu";
}


void CustomerMenu::ShowOptions()
{
    cout << "1-Start Order" << endl;
    cout << "2-View / Edit My Order" << endl;
    cout << "3-Confirm Order " << endl;
    cout << "4-Exit Customer" << endl;
}


int CustomerMenu::GetLastChoice() const
{
    return static_cast<int>(enCustomerMenu::Exit);
}

void CustomerMenu::PerformChoice(int choice)
{
    switch (static_cast<enCustomerMenu>(choice))
    {
    case enCustomerMenu::StartOrder:
    {
        orderScreen.StartOrder();
        ClearScreen();
        break;
    }

    case enCustomerMenu::ViewAndEditOrder:
    {
        orderScreen.ViewAndEditOrder();
        ClearScreen();
        break;
    }

    case enCustomerMenu::ConfirmOrder:
    {
        ConfirmOrder();
        ClearScreen();
        break;
    }

    case enCustomerMenu::Exit:
    {
        ClearScreen();
        break;
    }
    }
}


void CustomerMenu::ConfirmOrder()
{
    ClearScreen();
    PrintLine();
    PrintCentered("Confirm Order");
    PrintLine();

    if (order.IsEmpty())
    {
        cout << "Your cart is empty." << endl;
        PauseAndWaitForEnter();
        return;
    }

    cout << "Order ID: " << order.GetId() << "\n\n";
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

    cout << "\nTotal: " << order.GetTotal() << endl;
    cout << "Send this order to the cashier? (y/n): ";

    if (!ReadYesNo())
    {
        cout << "Your cart was not submitted." << endl;
        PauseAndWaitForEnter();
        return;
    }

    int submittedOrderId = order.GetId();
    Order submittedOrder = order;
    submittedOrder.MarkWaitingForPayment();
    pendingOrders.push_back(submittedOrder);

    if (!FileManager::SaveOrders("data/pending_orders.txt", pendingOrders))
    {
        pendingOrders.pop_back();
        cout << "Could not save your order. Your cart is still available." << endl;
        PauseAndWaitForEnter();
        return;
    }

    order.Reset();

    cout << "Order " << submittedOrderId << " was sent to the cashier." << endl;
    PauseAndWaitForEnter();
}
