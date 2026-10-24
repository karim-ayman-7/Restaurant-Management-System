#include "AdminFeatures.h"

#include <map>

using namespace std;

AdminFeatures::AdminFeatures(Menu& menu, const vector<Order>& orderHistory)
    : menu(menu), orderHistory(orderHistory)
{
}


vector<string> AdminFeatures::GetCategories() const
{
    return menu.GetCategories();
}


vector<MenuItem> AdminFeatures::GetItemsByCategory(const string& category) const
{
    return menu.GetItemsByCategory(category);
}


bool AdminFeatures::AddMenuItem(
    const string& name,
    int price,
    const string& category)
{
    if (name.empty() || name.find('#') != string::npos || price <= 0
        || category.empty() || category.find('#') != string::npos)
        return false;

    return menu.AddItem(name, price, category);
}


bool AdminFeatures::RemoveMenuItem(int itemId)
{
    return menu.RemoveItem(itemId);
}


bool AdminFeatures::EditMenuItem(
    int itemId,
    const string& name,
    int price,
    const string& category)
{
    if (name.empty() || name.find('#') != string::npos || price <= 0
        || category.empty() || category.find('#') != string::npos)
        return false;

    return menu.UpdateItem(itemId, name, price, category);
}


const vector<Order>& AdminFeatures::GetOrderHistory() const
{
    return orderHistory;
}


SalesReport AdminFeatures::GetSalesReport() const
{
    map<int, ItemSales> salesByItem;
    SalesReport report;

    for (const Order& order : orderHistory)
    {
        if (order.GetStatus() != enOrderStatus::Paid)
            continue;

        report.paidOrderCount++;
        report.totalRevenue += order.GetTotal();

        for (const OrderItem& orderItem : order.GetItems())
        {
            const MenuItem& item = orderItem.GetItem();
            ItemSales& sales = salesByItem[item.GetId()];

            if (sales.name.empty())
            {
                sales.name = item.GetName();
                sales.category = item.GetCategory();
            }

            sales.quantity += orderItem.GetQuantity();
            sales.revenue += orderItem.GetSubTotal();
        }
    }

    for (const auto& entry : salesByItem)
        report.itemSales.push_back(entry.second);

    return report;
}
