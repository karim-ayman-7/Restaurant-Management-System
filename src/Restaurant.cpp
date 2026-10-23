#include "Restaurant.h"

#include <iostream>
#include "Enums.h"
#include "Utils.h"

using namespace std;

Restaurant::Restaurant()
    : customerMenu(menu)
{
}

string Restaurant::GetTitle() const
{
    return "Restaurant Management System";
}

void Restaurant::ShowOptions()
{
    cout << "1-Customer" << endl;
    cout << "2-Admin" << endl;
    cout << "3-Exit" << endl;
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

    case enUserType::Admin:
    {
        cout << "Will be implemented in the future" << endl;
        PauseAndWaitForEnter();
        break;
    }

    case enUserType::Exit:
    {
        break;
    }
    }
}

int Restaurant::GetLastChoice() const
{
    return static_cast<int>(enUserType::Exit);
}