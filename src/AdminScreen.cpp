#include "AdminScreen.h"

#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include "Utils.h"

using namespace std;

MenuItemInput AdminScreen::ReadNewMenuItem(
    const vector<string>& categories) const
{
    ClearScreen();
    PrintLine();
    PrintCentered("Add Menu Item");
    PrintLine();
    cout << endl;

    MenuItemInput input;

    cout << "Item name: ";

    while (true)
    {
        input.name = ReadLine();

        if (input.name.find('#') == string::npos)
            break;

        cout << "Name cannot contain '#'. Enter a different name." << endl;
    }

    while (true)
    {
        cout << "Item price: ";

        if (ReadInt(input.price))
            break;

        cout << "Invalid price. Enter a whole number." << endl;
    }

    int newCategoryChoice = static_cast<int>(categories.size()) + 1;

    cout << "Choose A Category" << endl << endl;

    for (int i = 0; i < static_cast<int>(categories.size()); i++)
        cout << i + 1 << "-" << categories[i] << endl;

    cout << "\n" << newCategoryChoice << "-New Category" << endl;
    cout << newCategoryChoice + 1 << "-Cancel" << endl;
    cout << "Choose a category: ";

    int choice;

    while (true)
    {
        if (ReadInt(choice)
            && choice >= 1
            && choice <= newCategoryChoice + 1)
            break;

        cout << "Invalid choice. Choose a number from 1 to "
            << newCategoryChoice + 1 << ": ";
    }

    if (choice == newCategoryChoice + 1)
    {
        input.cancelled = true;
        return input;
    }

    if (choice == newCategoryChoice)
    {
        while (true)
        {
            cout << "New category name: ";
            input.category = ReadLine();

            if (input.category.empty())
            {
                cout << "Category cannot be empty." << endl;
                continue;
            }

            if (input.category.find('#') != string::npos)
            {
                cout << "Category cannot contain '#'. Enter a different category."
                    << endl;
                continue;
            }

            break;
        }
    }
    else
        input.category = categories[choice - 1];

    return input;
}


string AdminScreen::ReadCategoryChoice(
    const vector<string>& categories,
    const string& title) const
{
    ClearScreen();
    PrintLine();
    PrintCentered(title);
    PrintLine();
    cout << endl << "Choose A Category" << endl << endl;

    for (int i = 0; i < static_cast<int>(categories.size()); i++)
        cout << i + 1 << "-" << categories[i] << endl;

    cout << endl << categories.size() + 1 << "-Back" << endl;
    cout << "Choose a category, or choose Back to cancel: ";

    int choice;
    int backChoice = static_cast<int>(categories.size()) + 1;

    while (true)
    {
        if (ReadInt(choice) && choice >= 1 && choice <= backChoice)
            return choice == backChoice ? string() : categories[choice - 1];

        cout << "Invalid choice. Choose a number from 1 to " << backChoice << ": ";
    }
}


int AdminScreen::ReadMenuItemChoice(
    const vector<MenuItem>& items,
    const string& title,
    const string& action) const
{
    ClearScreen();
    PrintLine();
    PrintCentered(title);
    PrintLine();
    cout << endl;

    cout << left << setw(6) << "No." << setw(25) << "Item" << "Price" << endl;
    for (int i = 0; i < static_cast<int>(items.size()); i++)
    {
        cout << left << setw(6) << i + 1
            << setw(25) << items[i].GetName()
            << items[i].GetPrice() << endl;
    }

    cout << "0-Cancel" << endl;
    cout << "Choose an item to " << action << ": ";

    int choice;
    while (true)
    {
        if (ReadInt(choice) && choice >= 0
            && choice <= static_cast<int>(items.size()))
            return choice - 1;

        cout << "Invalid choice. Enter 0 or a number from 1 to "
            << items.size() << ": ";
    }
}


EditedMenuItemInput AdminScreen::ReadEditedMenuItem(
    const MenuItem& current,
    const vector<string>& categories) const
{
    ClearScreen();
    PrintLine();
    PrintCentered("Edit Menu Item Details");
    PrintLine();
    cout << endl;
    cout << "Current name: " << current.GetName() << endl;
    cout << "Current price: " << current.GetPrice() << endl;
    cout << "Current category: " << current.GetCategory() << endl << endl;

    EditedMenuItemInput input;
    cout << "New name (press Enter to keep current): ";
    while (true)
    {
        input.name = ReadLine();
        if (input.name.find('#') == string::npos)
            break;
        cout << "Name cannot contain '#'. Enter a different name." << endl;
    }
    if (input.name.empty())
        input.name = current.GetName();

    input.price = current.GetPrice();
    while (true)
    {
        cout << "New price (press Enter to keep current): ";
        string priceInput = ReadLine();
        if (priceInput.empty())
            break;

        istringstream priceStream(priceInput);
        char extraCharacter;
        if (priceStream >> input.price && !(priceStream >> extraCharacter)
            && input.price > 0)
            break;

        input.price = current.GetPrice();
        cout << "Invalid price. Enter a whole number greater than 0, or press Enter to keep the current price." << endl;
    }

    const int newCategoryChoice = static_cast<int>(categories.size()) + 1;
    const int keepCategoryChoice = newCategoryChoice + 1;
    cout << endl << "Choose a category:" << endl << endl;
    for (int i = 0; i < static_cast<int>(categories.size()); i++)
        cout << i + 1 << "-" << categories[i] << endl;
    cout << newCategoryChoice << "-New Category" << endl;
    cout << keepCategoryChoice << "-Keep Current Category" << endl;
    cout << "Choose a category: ";

    int choice;
    while (true)
    {
        if (ReadInt(choice) && choice >= 1 && choice <= keepCategoryChoice)
            break;
        cout << "Invalid choice. Choose a number from 1 to "
            << keepCategoryChoice << ": ";
    }

    if (choice == newCategoryChoice)
    {
        while (true)
        {
            cout << "New category name: ";
            input.category = ReadLine();
            if (input.category.empty())
                cout << "Category cannot be empty." << endl;
            else if (input.category.find('#') != string::npos)
                cout << "Category cannot contain '#'. Enter a different category." << endl;
            else
                break;
        }
    }
    else if (choice == keepCategoryChoice)
        input.category = current.GetCategory();
    else
        input.category = categories[choice - 1];

    return input;
}


bool AdminScreen::ConfirmRemove(const MenuItem& item) const
{
    ClearScreen();
    PrintLine();
    PrintCentered("Confirm Remove Menu Item");
    PrintLine();
    cout << endl << "Item: " << item.GetName() << endl;
    cout << "Category: " << item.GetCategory() << endl;
    cout << "Price: " << item.GetPrice() << endl << endl;
    cout << "Are you sure you want to remove this item? (y/n): ";
    return ReadYesNo();
}

void AdminScreen::ShowOrders(const vector<Order>& orders) const
{
    PrintLine();
    PrintCentered("Order History");
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
        cout << "Status: "
            << (order.GetStatus() == enOrderStatus::Paid ? "Paid" : "Open")
            << endl;
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


void AdminScreen::ShowSalesReport(const SalesReport& report) const
{
    PrintLine();
    PrintCentered("Sales Report");
    PrintLine();
    cout << endl;

    if (report.paidOrderCount == 0)
    {
        cout << "There are no completed sales yet." << endl;
        PauseAndWaitForEnter();
        return;
    }

    cout << "Paid orders: " << report.paidOrderCount << endl;
    cout << "Total sales revenue: " << report.totalRevenue << endl << endl;
    cout << left << setw(15) << "Category" << setw(27) << "Item"
        << setw(12) << "Qty Sold" << "Sales" << endl;
    for (const ItemSales& sales : report.itemSales)
    {
        cout << left << setw(15) << sales.category << setw(27) << sales.name
            << setw(12) << sales.quantity << sales.revenue << endl;
    }
    cout << endl;
    cout << "Note: This report includes all saved completed orders." << endl;
    cout << "Sales revenue is not net profit; item costs and expenses are not recorded." << endl;
    PauseAndWaitForEnter();
}


void AdminScreen::ShowMessage(const string& message) const
{
    cout << message << endl;
    PauseAndWaitForEnter();
}


void AdminScreen::ShowAddMenuItemSuccess() const
{
    cout << endl;
    PrintCentered("Menu item added successfully.");
    PauseAndWaitForEnter();
}


void AdminScreen::ShowInvalidMenuItemDetails() const
{
    cout << "Invalid item details. Please enter the item again." << endl;
    PauseAndWaitForEnter();
}
