#include<iostream>
using namespace std;
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
#include<string>
// struct for sales how data is added 
struct SaleRecord{
    string date;
    string sku;
    double unitPrice;
    double quantity;
    
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
        double quantity;
        double price;
        //getline is used to read value up to ','
        getline(ss,date,',');
        getline(ss,item,',');
        getline(ss,quantityStr,',');
        getline(ss,priceStr,',');
        
        quantity=stoi(quantityStr);
        price=stod(priceStr);
        data.push_back({date,item,quantity,price});
        

    }
    return data;
}
void calculatesSales(const vector<SaleRecord>& data){
    double totalSales=0;
    map<string,double>monthlySales;//used string for storing month as string 
    map<string,map<string, int>> monthlyPopularItems;// used map with string for months popularitems 

    for(const auto& record:data){
        string month=record.date.substr(0,7);
        double saleAmount=record.quantity*record.unitPrice;
        // Total sales
        totalSales+=saleAmount;
        // Monthly sales
        monthlySales[month]+=saleAmount;

        // Track quantity for popular items
        monthlyPopularItems[month][record.sku] += record.quantity;
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

}
int main(){
    std::ifstream file("one.txt");
    if(!file.is_open()){
        // if there is error opening in file then then close file()
        cout<<"error opening of file";
        return 0;
    }
    else
    {
        // cout<<"file is opened"<<endl;
    }
    
    vector<SaleRecord> data=parseData("one.txt");
    calculatesSales(data);

    return 0;
}