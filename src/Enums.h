#pragma once

enum class enUserType
{
    Customer = 1,
    Admin = 2,
    Exit = 3
};

enum class enCustomerMenu
{
    StartOrder = 1,
    ViewAndEditOrder = 2,
    MakePayment = 3,
    Back = 4
};

enum class enAdminMenu
{
    AddMenuItem = 1,
    RemoveMenuItem = 2,
    ViewOrders = 3,
    Back = 4
};

enum class enCategory
{
    Burger = 1,
    Pizza = 2,
    Drinks = 3,
    Dessert = 4,
    Back = 5
};
