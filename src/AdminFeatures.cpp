#include "AdminFeatures.h"
#include "Menu.h"

#include <iostream>
#include <vector>
#include "Utils.h"

using namespace std;

AdminFeatures::AdminFeatures(Menu& menu)
    : menu(menu), menuScreen(menu)
{
}

bool AdminFeatures::AddMenuItem()
{
    while (true)
    {
        ClearScreen();
        PrintLine();
        PrintCentered("Add Menu Item");
        PrintLine();
        cout << endl;

        string name;
        cout << "Item name: ";
        name = ReadLine();

        int price;

        while (true)
        {
            cout << "Item price: ";

            if (ReadInt(price))
                break;

            cout << "Invalid price. Enter a whole number." << endl;
        }

        vector<string> categories = menu.GetCategories();
        int newCategoryChoice = static_cast<int>(categories.size()) + 1;

        cout << "Choose A Category" << endl << endl;

        for (int i = 0; i < static_cast<int>(categories.size()); i++)
            cout << i + 1 << "-" << categories[i] << endl;

        cout <<"\n"<< newCategoryChoice << "-New Category" << endl;
        cout << newCategoryChoice + 1 << "-Cancel" << endl;
        cout << "Choose a category: ";

        int choice;

        while (true)
        {
            if (ReadInt(choice) && choice >= 1 && choice <= newCategoryChoice + 1)
                break;

            cout << "Invalid choice. Choose a number from 1 to "
                << newCategoryChoice + 1 << ": ";
        }

        if (choice == newCategoryChoice + 1)
            return false;

        string category;

        if (choice == newCategoryChoice)
        {
            cout << "New category name: ";
            category = ReadLine();
        }
        else
            category = categories[choice - 1];

        if (!menu.AddItem(name, price, category))
        {
            cout << "Invalid item details. Please enter the item again." << endl;
            PauseAndWaitForEnter();
            continue;
        }

        cout << endl;
        PrintCentered("Menu item added successfully.");
        PauseAndWaitForEnter();
        return true;
    }
}
bool AdminFeatures::RemoveMenuItem()
{
    vector<string> categories = menu.GetCategories();

    PrintLine();
    PrintCentered("Remove Menu Item");
    PrintLine();
    cout << endl;

    if (categories.empty())
    {
        cout << "There are no menu items to remove." << endl;
        PauseAndWaitForEnter();
        return false;
    }

    menuScreen.DisplayCategories();
    cout << "Choose a category, or choose Back to cancel: ";

    string category = menuScreen.SelectCategoryChoice();

    if (category.empty())
        return false;

    vector<MenuItem> items = menu.GetItemsByCategory(category);

    cout << endl << "Items in " << category << ":" << endl << endl;

    for (int i = 0; i < static_cast<int>(items.size()); i++)
    {
        const MenuItem& item = items[i];

        cout << i + 1 << "- " << item.GetName()
            << " | Price: " << item.GetPrice() << endl;
    }

    cout << "0-Cancel" << endl;
    cout << "Choose an item to remove: ";

    int choice;

    while (true)
    {
        if (ReadInt(choice) && choice >= 0 && choice <= static_cast<int>(items.size()))
            break;

        cout << "Invalid choice. Enter 0 or a number from 1 to "
            << items.size() << ": ";
    }

    if (choice == 0)
        return false;

    int itemId = items[choice - 1].GetId();

    bool removed = menu.RemoveItem(itemId);

    if (removed)
        cout << "Menu item removed successfully." << endl;
    else
        cout << "Menu item was not found." << endl;

    PauseAndWaitForEnter();
    return removed;
}

void AdminFeatures::ViewOrders()
{
}
