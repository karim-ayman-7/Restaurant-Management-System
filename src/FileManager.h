#pragma once

#include <string>
#include <vector>
#include "MenuItem.h"
#include "Order.h"

class FileManager
{
public:
    static std::vector<MenuItem> LoadMenu(const std::string& filePath);
    static bool SaveMenu(const std::string& filePath, const std::vector<MenuItem>& items);
    static std::vector<Order> LoadOrders(const std::string& filePath);
    static bool SaveOrders(const std::string& filePath, const std::vector<Order>& orders);
};
