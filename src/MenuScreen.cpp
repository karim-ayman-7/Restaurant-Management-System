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

void MenuScreen::DisplayCategoryItems(const string& category) const
{
    int choice = 1;
    vector<MenuItem> items = menu.GetItemsByCategory(category);

    for (const MenuItem& item : items)
    {
        cout << choice++ << "-";
        cout << setw(25) << left << item.GetName() << "Price: ";
        cout << item.GetPrice() << endl;
    }

    cout << choice << "-Back" << endl;
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
