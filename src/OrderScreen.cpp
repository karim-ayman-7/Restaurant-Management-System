#include "OrderScreen.h"

#include <iostream>
#include <iomanip>
#include "Utils.h"

using namespace std;

OrderScreen::OrderScreen(Menu& menu, Order& order)
    : menu(menu), order(order), menuScreen(menu)
{
}


bool OrderScreen::SelectCategory(string& category)
{
    menuScreen.MenuHeader();
    menuScreen.DisplayCategories();

    category = menuScreen.SelectCategoryChoice();

    return !category.empty();
}


int OrderScreen::SelectItemNumber(string category, int itemsCount)
{
    while (true)
    {
        menuScreen.MenuHeader();
        menuScreen.DisplayCategoryItems(category);

        cout << "Enter item number: ";
        int choice = ReadItemChoice();

        int backChoice = itemsCount + 1;

        if (choice == backChoice)
            return 0;

        if (choice >= 1 && choice <= itemsCount)
            return choice;

        cout << "Invalid item number." << endl;
        PauseAndWaitForEnter();
    }
}


int OrderScreen::ReadItemChoice()
{
    int choice;

    while (!ReadInt(choice))
    {
        cout << "Invalid input. Enter a numeric item number: ";
    }

    return choice;
}


int OrderScreen::ReadQuantity()
{
    int quantity;

    while (true)
    {
        cout << "Enter quantity: ";

        if (ReadInt(quantity) && quantity > 0)
            return quantity;

        cout << "Invalid quantity. Enter a number greater than 0." << endl;
    }
}


bool OrderScreen::AddItemToOrder()
{
    while (true)
    {
        string category;

        if (!SelectCategory(category))
            return false;

        vector<MenuItem> items = menu.GetItemsByCategory(category);

        int choice = SelectItemNumber(category, static_cast<int>(items.size()));

        if (choice == 0)
            continue;

        int quantity = ReadQuantity();

        if (!order.AddItem(items[choice - 1], quantity))
        {
            cout << "Invalid quantity. Enter a number greater than 0." << endl;
            PauseAndWaitForEnter();
            return false;
        }

        cout << "Item added successfully!" << endl;
        return true;
    }
}


void OrderScreen::StartOrder()
{
    do
    {
        if (!AddItemToOrder())
            return;

        cout << endl << "Do you want to add another item? (y/n): ";

    } while (ReadYesNo());
}


void OrderScreen::PrintOrderDetails() const
{
    cout << left << setw(6) << "No."
        << setw(25) << "Item"
        << setw(12) << "Quantity"
        << setw(15) << "Unit Price"
        << "Subtotal" << endl;

    for (int i = 0; i < static_cast<int>(order.GetItems().size()); i++)
    {
        const OrderItem& orderItem = order.GetItems()[i];
        const MenuItem& item = orderItem.GetItem();

        cout << left << setw(6) << i + 1
            << setw(25) << item.GetName()
            << setw(12) << orderItem.GetQuantity()
            << setw(15) << item.GetPrice()
            << orderItem.GetSubTotal() << endl;
    }

    cout << endl << "Total: " << order.GetTotal() << endl;
}


int OrderScreen::ReadNewQuantity()
{
    int quantity;

    while (true)
    {
        cout << "Enter new quantity (0 to remove): ";

        if (ReadInt(quantity) && quantity >= 0)
            return quantity;

        cout << "Invalid quantity. Enter 0 or a number greater than 0." << endl;
    }
}


void OrderScreen::ViewAndEditOrder()
{
    while (true)
    {
        ClearScreen();

        PrintLine();
        PrintCentered("My Order");
        PrintLine();

        if (order.IsEmpty())
        {
            cout << "Your order is empty." << endl;
            PauseAndWaitForEnter();
            return;
        }

        cout << "Order ID: " << order.GetId() << "\n\n";

        PrintOrderDetails();

        int itemsCount = static_cast<int>(order.GetItems().size());
        int backChoice = itemsCount + 1;

        cout << endl << backChoice << "-Back\n\n";
        cout << "Enter an item number to edit it, or " << backChoice << " to go back: ";
        int choice = ReadItemChoice();

        if (choice == backChoice)
            return;

        if (choice < 1 || choice > itemsCount)
        {
            cout << "Invalid item number." << endl;
            PauseAndWaitForEnter();
            continue;
        }

        int newQuantity = ReadNewQuantity();

        order.SetItemQuantity(choice - 1, newQuantity);

        if (newQuantity == 0)
            cout << "Item removed." << endl;
        else
            cout << "Quantity updated." << endl;

        PauseAndWaitForEnter();
    }
}
