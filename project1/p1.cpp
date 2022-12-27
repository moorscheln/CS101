#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>
// #include <vector>

using namespace std;

class Identifier
{
private:
    string name;
    int srcBandwidth;
    int destBandwidth;

public:
    Identifier()
    {
        name = "idName";
        srcBandwidth = 0;
        destBandwidth = 0;
    };

    // string idName;
    // int srcBand;
    // int destBand;
    // double rat;
    // Identifier(string idName, int srcBandwith, int destBandwith)
    // {
    //     this->name = idName;
    //     this->srcBandwidth = srcBandwith;
    //     this->destBandwidth = destBandwith;
    // }
    void setName(string inputName)
    {
        this->name = inputName;
    };
    // void setSrc(int inputSrc)
    // {
    //     this->srcBandwidth = inputSrc;
    // };
    // void setDest(int inputDest)
    // {
    //     this->destBandwidth = inputDest;
    // };
    void addSrc(int srcBand)
    {
        this->srcBandwidth += srcBand;
    };
    void addDest(int destBand)
    {
        this->destBandwidth += destBand;
    };
    int getDest()
    {
        return this->destBandwidth;
    };
    int getSrc()
    {
        return this->srcBandwidth;
    };
    string getName()
    {
        return this->name;
    };
    bool doesIdExist(string inputName)
    {
        if (this->name == inputName)
        {
            return true;
        }
        else
        {
            return false;
        }
    };
    void createDest(string inputName, int inputBand)
    {
        setName(inputName);
        addDest(inputBand);
    };
    void createSrc(string inputName, int inputBand)
    {
        setName(inputName);
        addSrc(inputBand);
    };

    friend ostream &operator<<(ostream &os, Identifier &id)
    {
        os << id.name << " " << id.srcBandwidth << " " << id.destBandwidth << endl;
        return os;
    }
};

// ostream &operator<<(ostream &os, Identifier &id)
// {
//     os << id.name << " " << id.srcBandwidth << " " << id.destBandwidth << " " << endl;
//     return os;
// }
// class Network
// {
// private:
//     Identifier arrID[1000];

// public:
//     // string srcIdentify[1000];
//     // string destIdentify[1000];
//     // int bandwithAvailable[1000];
//     int counter;
//     Identifier id[1000];
//     Network()
//     {
//         // Default Constructor
//         // string srcIdentify[1000];
//         // string destIdentify[1000];
//         // this->int bandwithAvailable[1000];
//         // this->srcIdentify[0] = "Hello";
//         // this->srcIdentify[1] = "World";
//         // this->bandwithInput = 0;
//         // srcInput = "";
//         // destInput = "";
//         Identifier arrID[1000];
//         counter = 0;
//     };
//     void printNetwork()
//     {
//         int i = 0;
//         int size;
//         for (i = 0; i < size; i++)
//         {
//             cout << arrID[i] << endl;
//         }
//     };
//     void assignID(string srcID, string destID, int band){
//         // check if srcID already exists
//         // if it does, add band
//         // else, ID to next position in arrID corresponding to counter #
//         // check if destID already exists
//         // if it does, add band
//         // else, ID to next position in arrID corresponding to counter #
//     };

//     // string toString()
//     // {
//     //     return to_string();
//     // };
// };

ifstream OpenFile(int argc, string argv)
{
    if (argc != 3)
    {
        cout << "Usage: ./a filename input.txt" << endl;
        exit(0);
    }

    string filename = argv;
    ifstream infile(filename);
    if (!infile)
    {
        cout << "Could not open file " << filename << endl;
        exit(0);
    }
    return infile;
}

// class File {
// public:
//     int getX() {
//         return x;
//     }
//     int getY() {
//         return y;
//     }
//     void setX(int val)  {
//         x = val;
//     }
//     void setY(int val) {
//         y = val;
// }
// File(char* argv) { //  default  constructor
//     ifstream fin;
//      fin.open(*argv);

// }
// Point(int x, int y) { // other constructor
//     this->x = x;
//     this->y = y;
// }
//     string toString()  {
//         return string("(") + to_string(x) + "," + to_string(getY()) + ")";
//     }
//     friend ostream &operator<<(ostream &os, Point &pt);
// private:
//     int x;
//     int y;
// };

// friend can access private members
// ostream &operator<<(ostream &os, Point &pt) {
//     os << pt.toString();
//     return os;
// }

// ostream &operator<<(ostream &os, Network var)
// {
//     os << var.toString();
//     return os;
// }

bool isNonLeaf(Identifier id)
{
    if ((id.getDest() != 0) && (id.getSrc() != 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

string Uppercase(string inputString)
{
    for (int i = 0; i < inputString.length(); i++)
    {
        if (isalpha(inputString[i]) && (islower(inputString[i])))
            inputString[i] = inputString[i] - 32;
    }
    return inputString;
}

double RatioFunction(int inputSource, int inputDest)
{
    double dest = inputDest;
    double src = inputSource;
    double ratio = dest / src;
    return ratio;
}

int main(int argc, char *argv[])
{
    // File fileIn;
    string filename = argv[1];
    ifstream infile = OpenFile(argc, filename);
    ofstream outfile;
    outfile.open(argv[2]);

    string input;
    string currSource;
    string currDest;

    Identifier id[1000];
    // id[2].addSrc(30);
    // for (int i = 0; i < 1000; i++)
    // {
    // }
    // cout << id[2].getSrc() << endl;
    // cout << id[3].doesIdExist("idName");

    int count = 0; // count of how many IDs have been made
    string inputSource = "";
    string inputDest = "";
    int inputBand = 0;
    bool srcFound;
    bool destFound;
    while (1)
    {
        srcFound = false;
        destFound = false;
        infile >> inputSource >> inputDest >> inputBand;
        if (infile.eof())
        {
            break;
        }
        inputSource = Uppercase(inputSource);
        inputDest = Uppercase(inputDest);
        // cout << "Line " << x << ": " << endl;
        // cout << "Input Source: " << inputSource << endl;
        // cout << "Input Dest: " << inputDest << endl;
        // cout << "Input Band: " << inputBand << endl;

        if (count == 0)
        {

            id[0].createSrc(inputSource, inputBand);
            count = 1; // count == 0
            // if inputDest == inputSource, addband to existing id
            // else, create new ID, and increase count
            if (id[0].getName() == inputDest)
            {
                id[0].addDest(inputBand);
                // if inputDest exists, add inputBand to existing ID as dest
            }
            else
            {
                // create new ID, add inputBand to destBand;
                id[count].createDest(inputDest, inputBand);
                count++;
            }
        }
        else
        {
            for (int i = 0; i < count; i++)
            {
                // cout << id[i];
                if (id[i].getName() == inputSource)
                {
                    id[i].addSrc(inputBand);
                    srcFound = true;
                    // cout << "srcFound" << endl;
                    // if inputSource + inputDest exist
                    //  inputDest exist
                    // add inputBand to BOTH existing IDs
                }
            }
            if (srcFound == false)
            {
                // cout << "No source found" << endl;
                id[count].createSrc(inputSource, inputBand);
                // cout << count << " " << id[count];
                count++;
            }
            // cout << "sources finished" << endl;
            for (int i = 0; i < count; i++)
            {
                // cout << i << endl;
                if (id[i].getName() == inputDest)
                {
                    id[i].addDest(inputBand);
                    destFound = true;
                    // if inputSource + inputDest exist
                    //  inputDest exist
                    // add inputBand to BOTH existing IDs
                }
            }
            if (destFound == false)
            {
                id[count].createDest(inputDest, inputBand);
                count++;
            }
        }
        // cout << "While Loops: " << x << endl;
    }
    for (int i = 0; i < count; i++)
    {
        // if (isLeaf(id[i]))
        // {
        // cout << count << endl;
        outfile << id[i].getName() << endl;

        // }
    }
    outfile << endl;
    for (int i = 0; i < count; i++)
    {
        if (isNonLeaf(id[i]))
        {
            // cout << count << endl;
            outfile << id[i].getName() << " ";
            outfile << id[i].getSrc() << " ";
            outfile << id[i].getDest() << " ";
            outfile << fixed << setprecision(2) << RatioFunction(id[i].getSrc(), id[i].getDest()) << endl;
        }
    }

    // Identifier id2;
    // cout << id2 << endl;
    // // Identifier id2("nameofID", 10, 10);
    // id2.addSrc(10);
    // id2.addSrc(10);
    // cout << id2 << endl;

    infile.close();
    outfile.close();

    return 0;
}

// else if ((id[i].doesIdExist(inputSource)) && (!(id[i].doesIdExist(inputDest))))
// {
//     id[i].addSrc(inputBand);

//     break;
// }
// else
// {
//     // create new ID, add inputBand to srcBand;
//     id[i].setName(inputSource);
//     id[count].addSrc(inputBand);
//     count++;
// }
// if (id[i].doesIdExist(inputDest))
// {
//     id[i].addDest(inputBand);
//     // if inputDest exists, add inputBand to existing ID as dest
// }
// else
// {
//     // create new ID, add inputBand to destBand;
//     id[i].setName(inputDest);
//     id[count].addDest(inputBand);
//     count++;
// }