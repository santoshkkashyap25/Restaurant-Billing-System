#pragma once
#include "products.h"

class BillDesk : public Restaurant {
private:
    string selectedProducts[5];
    string selectedProdCodes[5];
    float billPriceList[5];
    float billAmount;
    int billProdCount;

public:
    BillDesk();

    int findBillIndex(string);
    void billAddProduct(string);
    void billDeleteProduct(string);
    void generateBill();
    void checkBill();
};
