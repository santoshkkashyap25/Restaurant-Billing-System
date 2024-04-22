#pragma once
#include "products.h"
class RestAdmin : public Restaurant {
public:
    void addProduct(string, string, float);
    void deleteProduct(string);
    void updateProduct(string, string, float);
};
