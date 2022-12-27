#include <iostream>
using namespace std;

void SwapValues(int &userVal1, int &userVal2, int& userVal3, int& userVal4) {
    int tempA = userVal1;
    userVal1 = userVal2;
    userVal2 = tempA;

    int tempB = userVal3;
    userVal3 = userVal4;
    userVal4 = tempB;
}

int main() {
   int input1, input2, input3, input4;

   cin >> input1 >> input2 >> input3 >> input4;

   SwapValues(input1, input2, input3, input4);

   cout << input1 << " " << input2 << " " << input3 << " " << input4;
    cout << endl;
   return 0;
}