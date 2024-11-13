#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Struct to hold each sale record
struct SaleRecord {
    string date;
    string sku;
    double unitPrice;
    int quantity;
};

// Function to parse data from file
vector<SaleRecord> parseData(const string& filepath) {
    vector<SaleRecord> data;
    ifstream file(filepath);
    string line;

    // Skip header line
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string date, item, quantityStr, priceStr;
        int quantity;
        double price;

        // Read values up to each comma
        getline(ss, date, ',');
        getline(ss, item, ',');
        getline(ss, quantityStr, ',');
        getline(ss, priceStr, ',');

        quantity = stoi(quantityStr); // Convert quantity to int
        price = stod(priceStr); // Convert price to double

        data.push_back({date, item, price, quantity});
    }
    return data;
}

// Function to calculate sales statistics
void calculateSales(const vector<SaleRecord>& data) {
    double totalSales = 0;
    map<string, double> monthlySales;
    map<string, map<string, int>> monthlyPopularItems;
    map<string, map<string, double>> monthlyRevenueItems;
    map<string, map<string, vector<int>>> orderStats;

    for (const auto& record : data) {
        string month = record.date.substr(0, 7);
        double saleAmount = record.quantity * record.unitPrice;

        // Total and monthly sales
        totalSales += saleAmount;
        monthlySales[month] += saleAmount;

        // Track quantity for popular items
        monthlyPopularItems[month][record.sku] += record.quantity;

        // Track revenue for each item
        monthlyRevenueItems[month][record.sku] += saleAmount;

        // Track order quantities for stats
        orderStats[month][record.sku].push_back(record.quantity);
    }

    cout << "Total Sales of Store: " << totalSales << endl;

    cout << "\nMonth-wise Sales Totals:" << endl;
    for (const auto& month : monthlySales) {
        cout << month.first << ": " << month.second << endl;
    }

    cout << "\nMost Popular Item Each Month:" << endl;
    for (const auto& items : monthlyPopularItems) {
        string popularItem;
        int maxQuantity = 0;
        for (const auto& item_qty : items.second) {
            if (item_qty.second > maxQuantity) {
                maxQuantity = item_qty.second;
                popularItem = item_qty.first;
            }
        }
        cout << items.first << ": Item: " << popularItem << ", Quantity Sold: " << maxQuantity << endl;
    }

    cout << "\nItems Generating Most Revenue Each Month:" << endl;
    for (const auto& monthItems : monthlyRevenueItems) {
        string revenueItem;
        double maxRevenue = 0;
        for (const auto& item_revenue : monthItems.second) {
            if (item_revenue.second > maxRevenue) {
                maxRevenue = item_revenue.second;
                revenueItem = item_revenue.first;
            }
        }
        cout << monthItems.first << ": Item: " << revenueItem << ", Revenue: " << maxRevenue << endl;
    }

    cout << "\nOrder Statistics for Most Popular Item Each Month:" << endl;
    for (const auto& monthItem : orderStats) {
        string popularItem;
        int maxQuantity = 0;

        for (const auto& item_quantities : monthlyPopularItems[monthItem.first]) {
            if (item_quantities.second > maxQuantity) {
                maxQuantity = item_quantities.second;
                popularItem = item_quantities.first;
            }
        }

        const auto& quantities = orderStats[monthItem.first][popularItem];
        int minOrders = numeric_limits<int>::max();
        int maxOrders = 0;
        int totalOrders = 0;

        for (int qty : quantities) {
            if (qty < minOrders) minOrders = qty;
            if (qty > maxOrders) maxOrders = qty;
            totalOrders += qty;
        }

        double avgOrders = quantities.empty() ? 0 : static_cast<double>(totalOrders) / quantities.size();
        cout << monthItem.first << ": Item: " << popularItem
             << ", Min Orders: " << minOrders
             << ", Max Orders: " << maxOrders
             << ", Average Orders: " << fixed << setprecision(2) << avgOrders << endl;
    }
}

int main() {
    vector<SaleRecord> data = parseData("one.txt");
    calculateSales(data);

    return 0;
}
