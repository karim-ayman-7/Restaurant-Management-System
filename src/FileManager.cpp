#include "FileManager.h"

#include <fstream>
#include <stdexcept>

using namespace std;

namespace
{
    vector<string> SplitFields(const string& line, const string& delimiter)
    {
        vector<string> fields;
        size_t start = 0;

        while (true)
        {
            size_t delimiterPosition = line.find(delimiter, start);

            if (delimiterPosition == string::npos)
            {
                fields.push_back(line.substr(start));
                break;
            }

            fields.push_back(line.substr(start, delimiterPosition - start));
            start = delimiterPosition + delimiter.size();
        }

        return fields;
    }

    vector<string> ParseFields(const string& line)
    {
        return SplitFields(line, "#");
    }

    bool ParseInt(const string& text, int& value)
    {
        size_t parsed = 0;

        try
        {
            value = stoi(text, &parsed);
        }
        catch (const invalid_argument&)
        {
            return false;
        }
        catch (const out_of_range&)
        {
            return false;
        }

        return parsed == text.size();
    }

    string GetOrderStatusName(enOrderStatus status)
    {
        if (status == enOrderStatus::WaitingForPayment)
            return "WaitingForPayment";

        if (status == enOrderStatus::Paid)
            return "Paid";

        return "Open";
    }
}


vector<MenuItem> FileManager::LoadMenu(const string& filePath)
{
    vector<MenuItem> items;
    ifstream file(filePath);
    string line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line.empty())
                continue;

            vector<string> fields = ParseFields(line);

            if (fields.size() != 4)
                continue;

            const string& idStr = fields[0];
            const string& name = fields[1];
            const string& priceStr = fields[2];
            const string& category = fields[3];

            if (name.empty() || category.empty())
                continue;

            int id;
            int price;
            size_t idParsed = 0;
            size_t priceParsed = 0;

            try
            {
                id = stoi(idStr, &idParsed);
                price = stoi(priceStr, &priceParsed);
            }
            catch (const invalid_argument&)
            {
                continue;
            }
            catch (const out_of_range&)
            {
                continue;
            }

            if (idParsed != idStr.size() || priceParsed != priceStr.size())
                continue;

            if (id <= 0 || price <= 0)
                continue;

            items.push_back(MenuItem(id, name, price, category));
        }
    }

    ifstream idFile(filePath + ".nextid");
    int nextId;
    if (idFile >> nextId && nextId > 0)
        MenuItem::RestoreNextId(nextId);

    return items;
}


bool FileManager::SaveMenu(const string& filePath, const vector<MenuItem>& items)
{
    ofstream file(filePath);
    if (!file.is_open())
        return false;

    for (const MenuItem& item : items)
    {
        file << item.GetId() << "#"
            << item.GetName() << "#"
            << item.GetPrice() << "#"
            << item.GetCategory() << "\n";
    }

    file.flush();
    if (!file)
        return false;
    file.close();
    if (file.fail())
        return false;

    ofstream idFile(filePath + ".nextid");
    if (!idFile.is_open())
        return false;

    idFile << MenuItem::GetNextId() << "\n";
    idFile.flush();
    if (!idFile)
        return false;
    idFile.close();
    return !idFile.fail();
}


vector<Order> FileManager::LoadOrders(const string& filePath)
{
    vector<Order> orders;
    ifstream file(filePath);

    if (!file.is_open())
        return orders;

    string line;
    int currentOrderId = -1;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        vector<string> fields = ParseFields(line);

        if (fields.size() != 8)
            continue;

        const string& orderIdStr = fields[0];
        const string& statusStr = fields[1];
        const string& paymentMethod = fields[2];
        const string& itemIdStr = fields[3];
        const string& itemName = fields[4];
        const string& priceStr = fields[5];
        const string& quantityStr = fields[6];
        const string& category = fields[7];

        int orderId;
        int itemId;
        int price;
        int quantity;

        if (!ParseInt(orderIdStr, orderId)
            || !ParseInt(itemIdStr, itemId)
            || !ParseInt(priceStr, price)
            || !ParseInt(quantityStr, quantity))
            continue;

        if (orderId <= 0 || itemId <= 0 || price <= 0 || quantity <= 0
            || itemName.empty() || category.empty())
            continue;

        enOrderStatus status;

        if (statusStr == "Open")
            status = enOrderStatus::Open;
        else if (statusStr == "WaitingForPayment")
            status = enOrderStatus::WaitingForPayment;
        else if (statusStr == "Paid")
            status = enOrderStatus::Paid;
        else
            continue;

        if (orderId != currentOrderId)
        {
            orders.push_back(Order(orderId, status, paymentMethod));
            currentOrderId = orderId;
        }

        orders.back().AddItem(
            MenuItem(itemId, itemName, price, category), quantity);
    }

    return orders;
}


bool FileManager::SaveOrders(const string& filePath, const vector<Order>& orders)
{
    ofstream file(filePath);
    if (!file.is_open())
        return false;

    for (const Order& order : orders)
    {
        string status = GetOrderStatusName(order.GetStatus());

        for (const OrderItem& orderItem : order.GetItems())
        {
            const MenuItem& item = orderItem.GetItem();

            file << order.GetId() << "#"
                << status << "#"
                << order.GetPaymentMethod() << "#"
                << item.GetId() << "#"
                << item.GetName() << "#"
                << item.GetPrice() << "#"
                << orderItem.GetQuantity() << "#"
                << item.GetCategory() << "\n";
        }
    }

    file.flush();
    if (!file)
        return false;
    file.close();
    return !file.fail();
}
