#include "CustomerMenu.h"

#include <iostream>
#include "Utils.h"

using namespace std;

CustomerMenu::CustomerMenu(Menu& menu)
    : orderScreen(menu, order), paymentScreen(order)
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
    cout << "3-Make Payment" << endl;
    cout << "4-Back" << endl;
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

    case enCustomerMenu::MakePayment:
    {
        paymentScreen.MakePayment();
        ClearScreen();
        break;
    }

    case enCustomerMenu::Back:
    {
        ClearScreen();
        break;
    }
    }
}

int CustomerMenu::GetLastChoice() const
{
    return static_cast<int>(enCustomerMenu::Back);
}