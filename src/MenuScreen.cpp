#include "MenuScreen.h"

#include <iomanip>
#include <iostream>
#include "Utils.h"

using namespace std;

MenuScreen::MenuScreen(const Menu& menu)
    : menu(menu)
{
}


void MenuScreen::MenuHeader() const
{
    ClearScreen();
    PrintLine();
    PrintCentered("Restaurant Menu");
    PrintLine();
}


void MenuScreen::DisplayCategories() const
{
    cout << "Choose A Category" << endl << endl;

    vector<string> categories = menu.GetCategories();

    for (int i = 0; i < static_cast<int>(categories.size()); i++)
        cout << i + 1 << "-" << categories[i] << endl;

    cout << endl;
    cout << categories.size() + 1 << "-Back" << endl;
}


string MenuScreen::SelectCategoryChoice() const
{
    vector<string> categories = menu.GetCategories();
    int backChoice = static_cast<int>(categories.size()) + 1;
    int choice;

    while (true)
    {
        if (ReadInt(choice) && choice >= 1 && choice <= backChoice)
        {
            if (choice == backChoice)
                return "";

            return categories[choice - 1];
        }

        cout << "Invalid category. Choose a number from 1 to " << backChoice << ": ";
    }
}

void MenuScreen::DisplayCategoryItems(const string& category) const
{
    vector<MenuItem> items = menu.GetItemsByCategory(category);

    cout << left << setw(6) << "No."
        << setw(25) << "Item"
        << "Price" << endl;

    for (int i = 0; i < static_cast<int>(items.size()); i++)
    {
        const MenuItem& item = items[i];

        cout << left << setw(6) << i + 1
            << setw(25) << item.GetName()
            << item.GetPrice() << endl;
    }

    cout << endl << items.size() + 1 << "-Back" << endl;
}
