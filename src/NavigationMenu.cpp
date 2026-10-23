#include "NavigationMenu.h"

#include <iostream>
#include "Utils.h"

using namespace std;

void NavigationMenu::ShowHeader() const
{
    ClearScreen();

    PrintLine();
    PrintCentered(GetTitle());
    PrintLine();
}

int NavigationMenu::ReadChoice() const
{
    int choice;
    int max = GetLastChoice();

    while (true)
    {
        if (ReadInt(choice) && choice >= 1 && choice <= max)
            return choice;

        cout << "Invalid choice. Choose a number from 1 to " << max << ": ";
    }
}

void NavigationMenu::Run()
{
    int choice;

    do
    {
        ShowHeader();
        ShowOptions();
        choice = ReadChoice();
        PerformChoice(choice);

    } while (choice != GetLastChoice());
}
