#include <iostream>
using namespace std;

string RemoveNonAlpha(string userString) {
    string newString;
    for (int i = 0; i < userString.length(); i++) {
        if (isalpha(userString.at(i))) {
            newString.push_back(userString.at(i));
        }
    }
    return newString;
}

int main() {
   string input;
   getline(cin, input);
   /* Type your code here. Your code must call the function.  */

   cout << RemoveNonAlpha(input);
   cout << endl;

   return 0;
}
