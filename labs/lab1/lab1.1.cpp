#include <iostream>
#include <string>      // Supports use of "string" data type
#include <iomanip>
using namespace std;

int main() {
   int    userInt;
   double userDouble;
   // FIXME: Define char and string variables
   
   cout << "Enter integer:" << endl;
   cin  >> userInt;
   
   // FIXME (1): Finish reading other items into variables, then output the four values on a single line separated by a space
   cout << "Enter double:" << endl;
   cin  >> userDouble;

   char userChar;
   cout << "Enter character:" << endl;
   cin  >> userChar;

   string userString;
   cout << "Enter string:" << endl;
   cin  >> userString;
   
   cout << userInt << " " << userDouble << " " << userChar << " " << userString << endl;
   // FIXME (2): Output the four values in reverse
   cout << userString << " " << userChar << " " << userDouble << " " << userInt << endl;
   
   // FIXME (3): Cast the double to an integer, and output that integer
   int cast = 0;
   cast = userDouble;
   cout << userDouble << " cast to an integer is " << setprecision(1) << cast << endl;

   return 0;
}