#include "Restaurant.h"

#include <iostream>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif
#include "Enums.h"
#include "FileManager.h"
#include "Utils.h"

using namespace std;

namespace
{
    vector<MenuItem> LoadMenuAfterCreatingDataDirectory()
    {
    #ifdef _WIN32
        _mkdir("data");
    #else
        mkdir("data", 0755);
    #endif
        return FileManager::LoadMenu("data/menu.txt");
    }
}


Restaurant::Restaurant()
    : menu(LoadMenuAfterCreatingDataDirectory()),
      pendingOrders(FileManager::LoadOrders("data/pending_orders.txt")),
      orderHistory(FileManager::LoadOrders("data/order_history.txt")),
      customerMenu(menu, pendingOrders),
      cashierMenu(pendingOrders, orderHistory),
      adminMenu(menu, orderHistory)
{
}


string Restaurant::GetTitle() const
{
    return "Restaurant Management System";
}


void Restaurant::ShowOptions()
{
    cout << "1-Customer" << endl;
    cout << "2-Cashier" << endl;
    cout << "3-Admin" << endl;
    cout << "4-Exit" << endl;
}


int Restaurant::GetLastChoice() const
{
    return static_cast<int>(enUserType::Exit);
}

void Restaurant::PerformChoice(int choice)
{
    switch (static_cast<enUserType>(choice))
    {
    case enUserType::Customer:
    {
        customerMenu.Run();
        break;
    }

    case enUserType::Cashier:
    {
        cashierMenu.Run();
        break;
    }

    case enUserType::Admin:
    {
        adminMenu.Run();
        break;
    }

    case enUserType::Exit:
    {
        break;
    }
    }
}
