#include <iostream>
#include <vector>
using namespace std;

int main() {

   vector<int> intList;
   int numOfInt = 0;

   cin >> numOfInt;
   int input = 0;
   for (int i = 0; i < numOfInt; i++) {
    cin >> input;
    intList.push_back(input);
   }

    int threshold = 0;
    cin >> threshold;
   for (int i = 0; i < numOfInt; i++) {
     if (intList.at(i) <= threshold) {
    cout << intList.at(i) << ",";
     }
   }

   cout << endl;
   return 0;
}
