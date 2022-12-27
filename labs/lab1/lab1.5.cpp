#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

int main() {

    string filename;
    cin >> filename;

   ifstream infile;
   infile.open(filename);

   string input;
   while (infile >> input) {
    input.find("_photo.jpg");
    input.erase(input.find("_photo.jpg"), 10);
    input.append("_info.txt");
    cout << input << endl;
   }



   return 0;
}
