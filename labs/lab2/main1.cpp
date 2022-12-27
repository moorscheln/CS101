#include <iostream>
#include "Triangle.h"
using namespace std;

int main()
{
    Triangle triangle1;
    Triangle triangle2;

    double base1 = 0;
    double height1 = 0;
    double base2 = 0;
    double height2 = 0; // declaring values to read in for triangles
    // cout << base1 << height1 << base2 << height2;
    // TODO: Read and set base and height for triangle1 (use SetBase() and SetHeight())

    cin >> base1 >> height1 >> base2 >> height2;
    triangle1.SetBase(base1);
    triangle1.SetHeight(height1);

    // TODO: Read and set base and height for triangle2 (use SetBase() and SetHeight())

    triangle2.SetBase(base2);
    triangle2.SetHeight(height2);

    cout << "Triangle with smaller area:" << endl;

    // TODO: Determine smaller triangle (use GetArea())
    //       and output smaller triangle's info (use PrintInfo())

    if (triangle1.GetArea() < triangle2.GetArea())
    {
        triangle1.PrintInfo();
    }
    else if (triangle2.GetArea() < triangle1.GetArea())
    {
        triangle2.PrintInfo();
    }
    else
    {
        cout << "They are equal" << endl;
    }

    return 0;
}