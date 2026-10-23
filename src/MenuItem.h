#pragma once

#include <string>
#include "Enums.h"

class MenuItem
{
private:
    static int NextId;
    int Id;
    std::string Name;
    int Price;
    std::string Category;

public:
    MenuItem(const std::string& name, int price, const std::string& category);
    MenuItem(int id, const std::string& name, int price, const std::string& category);

    const std::string& GetName() const;
    int GetPrice() const;
    int GetId() const;
    const std::string& GetCategory() const;
};
