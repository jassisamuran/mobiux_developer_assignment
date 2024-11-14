#include<iostream>
using namespace std;
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
#include<string>
#include<iomanip>
#include<limits>

// struct for sales how data is added 
struct SaleRecord{
    string date;
    string sku;
    double Price;
    int quantity;
    
};

vector<SaleRecord> parseData(const string& filepath){
    // vector is used to read data of SaleRecord
    vector<SaleRecord> data;
    ifstream file(filepath);
    string line;
    // skip header line
    getline(file,line);
    while(getline(file,line)){
        stringstream ss(line);
        string date,item,quantityStr,priceStr;
        int quantity;
        double price;
        //getline is used to read value up to ','
        getline(ss,date,',');
        getline(ss,item,',');
        getline(ss,priceStr,',');
        getline(ss,quantityStr,',');
        
        
        quantity=stoi(quantityStr);
        price=stod(priceStr);
        data.push_back({date,item,price,quantity});
        

    }
    return data;
}
void calculatesSales(const vector<SaleRecord>& data){
    double totalSales=0;
    map<string,double>monthlySales;//used string for storing month as string 
    map<string,map<string, int>> monthlyPopularItems;// used map with string for months popularitems 
    map<string,map<string, double>>monthlyRevenueItems;
    map<string,map<string, vector<int>>> orderStats;

    for(const auto& record:data){
        string month=record.date.substr(0,7);
        double saleAmount=record.quantity*record.Price;
        // Total sales
        totalSales+=saleAmount;
        // Monthly sales
        monthlySales[month]+=saleAmount;

        // Track quantity for popular items
        monthlyPopularItems[month][record.sku] += record.quantity;

        // Track revenue for each item
        monthlyRevenueItems[month][record.sku] += saleAmount;

        // Track order quantities for stats
        orderStats[month][record.sku].push_back(record.quantity);

    }
    cout<<"Total Sales of Store: "<<totalSales<<endl;
    
    cout<<"Month-wise Sales Total"<<endl;
    
    for(const auto& month:monthlySales){
        cout<<month.first<<": "<<month.second<<endl;
    }

    cout<<"Most Popular Items for Each Months"<<endl;
    // used simple approach brute force approach 
    for(const auto& items:monthlyPopularItems){
        string popurItem;
        int maxQnty=0;
        for(const auto& item_qty:items.second){

            if(item_qty.second>maxQnty){
                maxQnty=item_qty.second;
                popurItem=item_qty.first;
            }

        }
        cout<<items.first<<": Item: "<<popurItem<<" Quantity Sold: "<<maxQnty<<endl;
    }

    cout<<"Items Generating Most Revenue Each Month"<<endl;
    for(const auto&month_Items:monthlyRevenueItems){
        string revenueItem;
        double maxRevenue=0;

        for(const auto& item_Revenue:month_Items.second){

            if(item_Revenue.second>maxRevenue){
                maxRevenue=item_Revenue.second;
                revenueItem=item_Revenue.first;
            }

        }
        cout<<month_Items.first<<": Item: "<<revenueItem<<" Revenue: "<<maxRevenue<<endl;
    }

    cout<<"Order statistics for Most popular Item Each Month"<<endl;

    for(const auto& month_item:orderStats){
        // Find the most popular item for this month
        string popularItem;
        int maxQuantity=0;

        for(const auto & item_quantities:monthlyPopularItems[month_item.first]){

            if(item_quantities.second>maxQuantity){
                maxQuantity=item_quantities.second;
                popularItem=item_quantities.first;
            }

        }
        
        // Get the order quantities for the most popular item
        const auto &quantities=orderStats[month_item.first][popularItem];
        int minOrders=numeric_limits<int>::max();
        int maxOrders=0;
        int totalOrders=0;
        
        for(int qty:quantities){
            if(qty<minOrders)minOrders=qty;
            if(qty>maxOrders)maxOrders=qty;
            totalOrders+=qty;
        }
        double avgOrders=quantities.empty()?0:static_cast<double>(totalOrders)/quantities.size();
        cout<<month_item.first<<" "<<popularItem<<
            ", Min Orders: "<<minOrders<<
            ", Max Orders: "<<maxOrders<<
            ", Average Orders: "<<fixed<< setprecision(2)<<avgOrders<<endl;
    }

}

int main(){
    // std::ifstream file("one.txt");
    // if(!file.is_open()){
    //     // if there is error opening in file then then close file()
    //     cout<<"error opening of file";
    //     return 0;
    // }
    // else
    // {
    //     // cout<<"file is opened"<<endl;
    // }
    
    vector<SaleRecord> data=parseData("one.txt");
    calculatesSales(data);

    return 0;
}