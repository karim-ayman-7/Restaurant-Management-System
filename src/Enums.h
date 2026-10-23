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
    Exit = 4
};

enum class enAdminMenu
{
    AddMenuItem = 1,
    RemoveMenuItem = 2,
    ViewOrders = 3,
    Back = 4
};
