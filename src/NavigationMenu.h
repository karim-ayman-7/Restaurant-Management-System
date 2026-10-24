#pragma once

#include <string>

class NavigationMenu
{
private:
    void ShowHeader() const;
    int ReadChoice() const;

    virtual std::string GetTitle() const = 0;
    virtual void ShowOptions() = 0;
    virtual void PerformChoice(int choice) = 0;
    virtual int GetLastChoice() const = 0;

public:
    virtual ~NavigationMenu() = default;

    virtual void Run();
};
