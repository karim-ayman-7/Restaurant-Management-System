#include "MenuItem.h"

using namespace std;

int MenuItem::NextId = 1;

MenuItem::MenuItem(const string& name, int price, const string& category)
    : MenuItem(NextId, name, price, category)
{
}


MenuItem::MenuItem(int id, const string& name, int price, const string& category)
    : Id(id), Name(name), Price(price), Category(category)
{
    if (id >= NextId)
        NextId = id + 1;
}


int MenuItem::GetNextId()
{
    return NextId;
}


void MenuItem::RestoreNextId(int nextId)
{
    if (nextId > NextId)
        NextId = nextId;
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


const string& MenuItem::GetCategory() const
{
    return Category;
}


bool MenuItem::UpdateDetails(const string& name, int price, const string& category)
{
    if (name.empty() || price <= 0 || category.empty())
        return false;

    Name = name;
    Price = price;
    Category = category;
    return true;
}
