#pragma once

#include <string>
#include "Enums.h"

class MenuItem
{
private:
    std::string Name;
    int Price;
    enCategory Category;

    static int NextId;
    int Id;

public:
    MenuItem(const std::string& name, int price, enCategory category);

    const std::string& GetName() const;
    int GetPrice() const;
    int GetId() const;
    enCategory GetCategory() const;
};