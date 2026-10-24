#pragma once

#include "Menu.h"
#include "Order.h"
#include <string>
#include <vector>

struct ItemSales
{
    std::string name;
    std::string category;
    int quantity = 0;
    int revenue = 0;
};

struct SalesReport
{
    int paidOrderCount = 0;
    int totalRevenue = 0;
    std::vector<ItemSales> itemSales;
};

class AdminFeatures
{
private:
    Menu& menu;
    const std::vector<Order>& orderHistory;

public:
    AdminFeatures(Menu& menu, const std::vector<Order>& orderHistory);

    bool AddMenuItem(const std::string& name, int price, const std::string& category);
    bool RemoveMenuItem(int itemId);
    bool EditMenuItem(int itemId, const std::string& name, int price, const std::string& category);
    std::vector<std::string> GetCategories() const;
    std::vector<MenuItem> GetItemsByCategory(const std::string& category) const;
    const std::vector<Order>& GetOrderHistory() const;
    SalesReport GetSalesReport() const;
};
