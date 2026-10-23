#include "FileManager.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

vector<MenuItem> FileManager::LoadMenu(const string& filePath)
{
    vector<MenuItem> items;
    ifstream file(filePath);

    if (!file.is_open())
        return items;

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        istringstream ss(line);
        string idStr, name, priceStr, category;

        if (!getline(ss, idStr, '|'))
            continue;
        if (!getline(ss, name, '|'))
            continue;
        if (!getline(ss, priceStr, '|'))
            continue;
        if (!getline(ss, category, '|'))
            continue;

        string extraField;

        if (getline(ss, extraField, '|'))
            continue;

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

    return items;
}

void FileManager::SaveMenu(const string& filePath, const vector<MenuItem>& items)
{
    ofstream file(filePath);

    for (const MenuItem& item : items)
    {
        file << item.GetId() << "|"
            << item.GetName() << "|"
            << item.GetPrice() << "|"
            << item.GetCategory() << "\n";
    }
}
