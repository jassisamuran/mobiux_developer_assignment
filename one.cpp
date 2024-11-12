#include<iostream>
using namespace std;
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
// struct for sales how data is added 
struct SaleRecord{
    string date;
    string sku;
    double unitPrice;
    double quality;
    
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
int main(){
    std::ifstream file("one.txt");
    if(!file.is_open()){
        // if there is error opening in file then then close file()
        cout<<"error opening of file";
        return 0;
    }else{
        cout<<"file is opened";
    }
    
    vector<SaleRecord> data=parseData("one.txt");
    
    return 0;
}