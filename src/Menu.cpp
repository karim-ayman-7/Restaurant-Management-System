#include "Menu.h"

using namespace std;

Menu::Menu(const vector<MenuItem>& items)
    : MenuItems(items)
{
}


vector<string> Menu::GetCategories() const
{
    vector<string> categories;

    for (const MenuItem& item : MenuItems)
    {
        bool found = false;

        for (const string& cat : categories)
        {
            if (cat == item.GetCategory())
            {
                found = true;
                break;
            }
        }

        if (!found)
            categories.push_back(item.GetCategory());
    }

    return categories;
}


vector<MenuItem> Menu::GetItemsByCategory(const string& category) const
{
    vector<MenuItem> result;

    for (const MenuItem& item : MenuItems)
    {
        if (item.GetCategory() == category)
            result.push_back(item);
    }

    return result;
}

bool Menu::AddItem(const string& name, int price, const string& category)
{
    if (name.empty() || price <= 0 || category.empty())
        return false;

    MenuItems.push_back(MenuItem(name, price, category));

    return true;
}


bool Menu::UpdateItem(
    int id,
    const string& name,
    int price,
    const string& category)
{
    for (MenuItem& item : MenuItems)
    {
        if (item.GetId() == id)
            return item.UpdateDetails(name, price, category);
    }

    return false;
}


bool Menu::RemoveItem(int id)
{
    for (int i = 0; i < static_cast<int>(MenuItems.size()); i++)
    {
        if (MenuItems[i].GetId() == id)
        {
            MenuItems.erase(MenuItems.begin() + i);
            return true;
        }
    }

    return false;
}


std::vector<MenuItem> Menu::GetItems() const
{
    return MenuItems;
}
