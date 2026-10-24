#pragma once

enum class enUserType
{
    Customer = 1,
    Cashier = 2,
    Admin = 3,
    Exit = 4
};

enum class enCustomerMenu
{
    StartOrder = 1,
    ViewAndEditOrder = 2,
    ConfirmOrder = 3,
    Exit = 4
};

enum class enCashierMenu
{
    ViewPendingOrders = 1,
    ViewCompletedOrders = 2,
    ViewPaymentSummary = 3,
    Back = 4
};

enum class enAdminMenu
{
    AddMenuItem = 1,
    RemoveMenuItem = 2,
    EditMenuItem = 3,
    ViewOrders = 4,
    ViewSalesReport = 5,
    Back = 6
};

enum class enOrderStatus
{
    Open,
    WaitingForPayment,
    Paid
};
