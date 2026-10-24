#include "CashierMenu.h"

#include <iostream>
#include "Utils.h"

using namespace std;

CashierMenu::CashierMenu(
    vector<Order>& pendingOrders,
    vector<Order>& orderHistory)
    : cashierFeatures(pendingOrders, orderHistory)
{
}


string CashierMenu::GetTitle() const
{
    return "Cashier Menu";
}


void CashierMenu::ShowOptions()
{
    cout << "1-View Pending Orders / Process Payment" << endl;
    cout << "2-View Completed Orders" << endl;
    cout << "3-View Payment Summary" << endl;
    cout << "4-Back" << endl;
}


int CashierMenu::GetLastChoice() const
{
    return static_cast<int>(enCashierMenu::Back);
}

void CashierMenu::PerformChoice(int choice)
{
    switch (static_cast<enCashierMenu>(choice))
    {
    case enCashierMenu::ViewPendingOrders:
    {
        ClearScreen();
        int index = cashierScreen.SelectPendingOrder(
            cashierFeatures.GetPendingOrders());
        if (index < 0)
            break;

        Order* order = cashierFeatures.GetPendingOrder(index);
        if (order != nullptr)
        {
            PaymentResult result = cashierScreen.MakePayment(*order);
            if (result.status != enPaymentStatus::Success)
                break;

            if (cashierFeatures.CompletePayment(index, result.method))
            {
                const vector<Order>& completed = cashierFeatures.GetCompletedOrders();
                cashierScreen.ShowReceipt(completed.back());
                cashierScreen.ShowMessage(
                    "Order payment completed and saved in order history.");
            }
            else
                cashierScreen.ShowMessage(
                    "Could not save the completed payment. The order remains pending.");
        }
        break;
    }

    case enCashierMenu::ViewCompletedOrders:
    {
        ClearScreen();
        cashierScreen.ShowCompletedOrders(cashierFeatures.GetCompletedOrders());
        break;
    }

    case enCashierMenu::ViewPaymentSummary:
    {
        ClearScreen();
        cashierScreen.ShowPaymentSummary(cashierFeatures.GetPaymentSummary());
        break;
    }

    case enCashierMenu::Back:
    {
        ClearScreen();
        break;
    }
    }
}
