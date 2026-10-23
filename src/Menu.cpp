#include "Menu.h"

#include <iostream>
#include <iomanip>
#include "Utils.h"

using namespace std;

Menu::Menu()
{
    MenuItems.push_back(MenuItem("Chicken Burger", 50, enCategory::Burger));
    MenuItems.push_back(MenuItem("Meat Burger", 60, enCategory::Burger));

    MenuItems.push_back(MenuItem("Pepperoni Pizza", 100, enCategory::Pizza));
    MenuItems.push_back(MenuItem("Vegetable Pizza", 90, enCategory::Pizza));

    MenuItems.push_back(MenuItem("Pepsi", 20, enCategory::Drinks));
    MenuItems.push_back(MenuItem("Seven Up", 20, enCategory::Drinks));
    MenuItems.push_back(MenuItem("Orange Juice", 30, enCategory::Drinks));

    MenuItems.push_back(MenuItem("Cake", 40, enCategory::Dessert));
    MenuItems.push_back(MenuItem("Chocolate", 35, enCategory::Dessert));
}

void Menu::MenuHeader() const
{
    ClearScreen();

    PrintLine();
    PrintCentered("Restaurant Menu");
    PrintLine();
}

void Menu::DisplayCategories() const
{
    cout << "Choose A Category" << endl << endl;

    cout << "1-Burger" << endl;
    cout << "2-Pizza" << endl;
    cout << "3-Drinks" << endl;
    cout << "4-Dessert" << endl;
    cout << "5-Back" << endl;
}

void Menu::DisplayCategoryItems(enCategory Category) const
{
    int choice = 1;

    for (const MenuItem& item : MenuItems)
    {
        if (item.GetCategory() == Category)
        {
            cout << choice++ << "-";
            cout << setw(25) << left << item.GetName() << "Price: ";
            cout << item.GetPrice() << endl;
        }
    }

    cout << choice << "-Back" << endl;
}

enCategory Menu::SelectCategoryChoice()
{
    int choice;

    while (true)
    {
        if (ReadInt(choice) && choice >= 1 && choice <= 5)
            return static_cast<enCategory>(choice);

        cout << "Invalid category. Choose a number from 1 to 5: ";
    }
}

vector<MenuItem> Menu::GetItemsByCategory(enCategory category) const
{
    vector<MenuItem> result;

    for (const MenuItem& item : MenuItems)
    {
        if (item.GetCategory() == category)
            result.push_back(item);
    }

    return result;
}