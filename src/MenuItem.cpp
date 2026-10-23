#include "MenuItem.h"

using namespace std;

int MenuItem::NextId = 1;

MenuItem::MenuItem(const string& name, int price, enCategory category)
    : Name(name), Price(price), Category(category), Id(NextId++)
{
}

const string& MenuItem::GetName() const
{
    return Name;
}

int MenuItem::GetPrice() const
{
    return Price;
}

int MenuItem::GetId() const
{
    return Id;
}

enCategory MenuItem::GetCategory() const
{
    return Category;
}