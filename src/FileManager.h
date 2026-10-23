#pragma once

#include <string>
#include <vector>
#include "MenuItem.h"

class FileManager
{
public:
    static std::vector<MenuItem> LoadMenu(const std::string& filePath);
    static void SaveMenu(const std::string& filePath, const std::vector<MenuItem>& items);
};
