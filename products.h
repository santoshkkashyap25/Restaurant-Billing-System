#pragma once
#include <iostream>
using namespace std;

class Restaurant {
protected:
    string productCodes[10] = { };
    string productList[10] = { };
    float priceList[10] = { };
    int productCount ;

public:
    int findIndex(string);
    void showProducts();
    void readProductsFromFile();
    bool searchOne(string);
};