#include "CashierFeatures.h"

#include "FileManager.h"

using namespace std;

CashierFeatures::CashierFeatures(
    vector<Order>& pendingOrders,
    vector<Order>& orderHistory)
    : pendingOrders(pendingOrders), orderHistory(orderHistory)
{
}


const vector<Order>& CashierFeatures::GetPendingOrders() const
{
    return pendingOrders;
}


Order* CashierFeatures::GetPendingOrder(int index)
{
    if (index < 0 || index >= static_cast<int>(pendingOrders.size()))
        return nullptr;

    return &pendingOrders[index];
}


bool CashierFeatures::CompletePayment(int index, const string& paymentMethod)
{
    if (index < 0 || index >= static_cast<int>(pendingOrders.size())
        || pendingOrders[index].GetStatus() != enOrderStatus::WaitingForPayment
        || (paymentMethod != "Cash" && paymentMethod != "Card"))
        return false;

    vector<Order> oldPendingOrders = pendingOrders;
    vector<Order> oldOrderHistory = orderHistory;

    pendingOrders[index].MarkPaid(paymentMethod);
    orderHistory.push_back(pendingOrders[index]);
    pendingOrders.erase(pendingOrders.begin() + index);

    bool pendingSaved = FileManager::SaveOrders(
        "data/pending_orders.txt", pendingOrders);
    bool historySaved = FileManager::SaveOrders(
        "data/order_history.txt", orderHistory);

    if (!pendingSaved || !historySaved)
    {
        pendingOrders = oldPendingOrders;
        orderHistory = oldOrderHistory;
        FileManager::SaveOrders("data/pending_orders.txt", pendingOrders);
        FileManager::SaveOrders("data/order_history.txt", orderHistory);
        return false;
    }

    return true;
}


const vector<Order>& CashierFeatures::GetCompletedOrders() const
{
    return orderHistory;
}


PaymentSummary CashierFeatures::GetPaymentSummary() const
{
    PaymentSummary summary;

    for (const Order& order : orderHistory)
    {
        if (order.GetStatus() != enOrderStatus::Paid)
            continue;

        summary.paidOrderCount++;
        if (order.GetPaymentMethod() == "Cash")
            summary.cashTotal += order.GetTotal();
        else if (order.GetPaymentMethod() == "Card")
            summary.cardTotal += order.GetTotal();
        else
            summary.otherTotal += order.GetTotal();
    }

    return summary;
}
