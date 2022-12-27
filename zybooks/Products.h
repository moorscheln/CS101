#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <vector>
#include "Product.h"

class Products
{
public:
    void InputProducts();
    void PrintAfterDiscount(int discountPrice);

private:
    std::vector<Product> productList;
};
#endif