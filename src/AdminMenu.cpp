#include "AdminMenu.h"

#include <iostream>
#include "FileManager.h"
#include "Utils.h"

using namespace std;

AdminMenu::AdminMenu(Menu& menu)
    : menu(menu), adminFeatures(menu)
{
}

string AdminMenu::GetTitle() const
{
    return "Admin Menu";
}

void AdminMenu::ShowOptions()
{
    cout << "1-Add Menu Item" << endl;
    cout << "2-Remove Menu Item" << endl;
    cout << "3-View Orders" << endl;
    cout << "4-Back" << endl;
}

void AdminMenu::PerformChoice(int choice)
{
    switch (static_cast<enAdminMenu>(choice))
    {
    case enAdminMenu::AddMenuItem:
    {
        ClearScreen();
        if (adminFeatures.AddMenuItem())
            FileManager::SaveMenu("data/menu.txt", menu.GetItems());
        break;
    }

    case enAdminMenu::RemoveMenuItem:
    {
        ClearScreen();
        if (adminFeatures.RemoveMenuItem())
            FileManager::SaveMenu("data/menu.txt", menu.GetItems());
        break;
    }

    case enAdminMenu::ViewOrders:
    {
        ClearScreen();
        adminFeatures.ViewOrders();
        break;
    }

    case enAdminMenu::Back:
    {
        ClearScreen();
        break;
    }
    }
}

int AdminMenu::GetLastChoice() const
{
    return static_cast<int>(enAdminMenu::Back);
}
