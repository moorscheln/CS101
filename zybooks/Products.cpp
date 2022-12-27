#include <iostream>
#include "Products.h"
using namespace std;

void Products::InputProducts()
{
    Product currProduct;
    int currPrice;
    string currName;

    cin >> currPrice;
    while (currPrice > 0)
    {
        cin >> currName;
        currProduct.SetPriceAndName(currPrice, currName);
        productList.push_back(currProduct);
        cin >> currPrice;
    }
}

void Products::PrintAfterDiscount(int discountPrice)
{
    unsigned int i;
    int currDiscountPrice;

    for (i = 0; i < productList.size(); ++i)
    {
        currDiscountPrice = productList.at(i).GetPrice() - discountPrice;
        cout << "$" << currDiscountPrice << " " << productList.at(i).GetName() << endl;
    }
}