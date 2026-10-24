#include "AdminMenu.h"

#include <iostream>
#include "FileManager.h"
#include "Utils.h"

using namespace std;

namespace
{
    bool SaveMenuChanges(Menu& menu, const vector<MenuItem>& previousItems)
    {
        if (FileManager::SaveMenu("data/menu.txt", menu.GetItems()))
            return true;

        menu = Menu(previousItems);
        FileManager::SaveMenu("data/menu.txt", previousItems);
        return false;
    }
}

AdminMenu::AdminMenu(Menu& menu, const vector<Order>& orderHistory)
    : menu(menu), adminFeatures(menu, orderHistory)
{
}


void AdminMenu::Run()
{
    ClearScreen();
    PrintLine();
    PrintCentered("Admin Login");
    PrintLine();
    cout << endl;

    cout << "Enter password (admin123): ";
    string input = ReadLine();

    if (input != "admin123")
    {
        cout << "Wrong password." << endl;
        PauseAndWaitForEnter();
        return;
    }

    NavigationMenu::Run();
}



string AdminMenu::GetTitle() const
{
    return "Admin Menu";
}


void AdminMenu::ShowOptions()
{
    cout << "1-Add Menu Item" << endl;
    cout << "2-Remove Menu Item" << endl;
    cout << "3-Edit Menu Item" << endl;
    cout << "4-View Orders" << endl;
    cout << "5-View Sales Report" << endl;
    cout << "6-Back" << endl;
}


int AdminMenu::GetLastChoice() const
{
    return static_cast<int>(enAdminMenu::Back);
}

void AdminMenu::PerformChoice(int choice)
{
    switch (static_cast<enAdminMenu>(choice))
    {
    case enAdminMenu::AddMenuItem:
    {
        while (true)
        {
            MenuItemInput input = adminScreen.ReadNewMenuItem(menu.GetCategories());

            if (input.cancelled)
                break;

            vector<MenuItem> previousItems = menu.GetItems();
            if (!adminFeatures.AddMenuItem(
                input.name, input.price, input.category))
            {
                adminScreen.ShowInvalidMenuItemDetails();
                continue;
            }

            if (!SaveMenuChanges(menu, previousItems))
            {
                adminScreen.ShowMessage(
                    "Could not save the menu item. The menu was restored.");
                break;
            }
            adminScreen.ShowAddMenuItemSuccess();
            break;
        }
        break;
    }

    case enAdminMenu::RemoveMenuItem:
    {
        vector<string> categories = adminFeatures.GetCategories();
        if (categories.empty())
        {
            adminScreen.ShowMessage("There are no menu items to remove.");
            break;
        }

        string category = adminScreen.ReadCategoryChoice(categories, "Remove Menu Item");
        if (category.empty())
            break;

        vector<MenuItem> items = adminFeatures.GetItemsByCategory(category);
        int itemIndex = adminScreen.ReadMenuItemChoice(items, "Remove Menu Item", "remove");
        if (itemIndex < 0)
            break;

        if (!adminScreen.ConfirmRemove(items[itemIndex]))
        {
            adminScreen.ShowMessage("Removal cancelled.");
            break;
        }

        vector<MenuItem> previousItems = menu.GetItems();
        if (adminFeatures.RemoveMenuItem(items[itemIndex].GetId()))
        {
            if (SaveMenuChanges(menu, previousItems))
                adminScreen.ShowMessage("Menu item removed successfully.");
            else
                adminScreen.ShowMessage(
                    "Could not save the removal. The menu was restored.");
        }
        else
            adminScreen.ShowMessage("Menu item was not found.");
        break;
    }

    case enAdminMenu::EditMenuItem:
    {
        vector<string> categories = adminFeatures.GetCategories();
        if (categories.empty())
        {
            adminScreen.ShowMessage("There are no menu items to edit.");
            break;
        }

        string category = adminScreen.ReadCategoryChoice(categories, "Edit Menu Item");
        if (category.empty())
            break;

        vector<MenuItem> items = adminFeatures.GetItemsByCategory(category);
        int itemIndex = adminScreen.ReadMenuItemChoice(items, "Edit Menu Item", "edit");
        if (itemIndex < 0)
            break;

        EditedMenuItemInput input = adminScreen.ReadEditedMenuItem(
            items[itemIndex], adminFeatures.GetCategories());
        if (input.name == items[itemIndex].GetName()
            && input.price == items[itemIndex].GetPrice()
            && input.category == items[itemIndex].GetCategory())
        {
            adminScreen.ShowMessage("No changes were made.");
            break;
        }

        vector<MenuItem> previousItems = menu.GetItems();
        if (adminFeatures.EditMenuItem(items[itemIndex].GetId(),
            input.name, input.price, input.category))
        {
            if (SaveMenuChanges(menu, previousItems))
                adminScreen.ShowMessage("Menu item updated successfully.");
            else
                adminScreen.ShowMessage(
                    "Could not save the changes. The menu was restored.");
        }
        else
            adminScreen.ShowMessage("Could not update the menu item.");
        break;
    }

    case enAdminMenu::ViewOrders:
    {
        ClearScreen();
        adminScreen.ShowOrders(adminFeatures.GetOrderHistory());
        break;
    }

    case enAdminMenu::ViewSalesReport:
    {
        ClearScreen();
        adminScreen.ShowSalesReport(adminFeatures.GetSalesReport());
        break;
    }

    case enAdminMenu::Back:
    {
        ClearScreen();
        break;
    }
    }
}
