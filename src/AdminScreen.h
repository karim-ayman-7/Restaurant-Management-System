#pragma once

#include <string>
#include <vector>
#include "AdminFeatures.h"
#include "MenuItem.h"
#include "Order.h"

struct MenuItemInput
{
    std::string name;
    int price = 0;
    std::string category;
    bool cancelled = false;
};

struct EditedMenuItemInput
{
    std::string name;
    int price = 0;
    std::string category;
};

class AdminScreen
{
public:
    MenuItemInput ReadNewMenuItem(
        const std::vector<std::string>& categories) const;

    void ShowAddMenuItemSuccess() const;
    void ShowInvalidMenuItemDetails() const;
    std::string ReadCategoryChoice(
        const std::vector<std::string>& categories,
        const std::string& title) const;
    int ReadMenuItemChoice(
        const std::vector<MenuItem>& items,
        const std::string& title,
        const std::string& action) const;
    EditedMenuItemInput ReadEditedMenuItem(
        const MenuItem& current,
        const std::vector<std::string>& categories) const;
    void ShowOrders(const std::vector<Order>& orders) const;
    void ShowSalesReport(const SalesReport& report) const;
    void ShowMessage(const std::string& message) const;
    bool ConfirmRemove(const MenuItem& item) const;
};
