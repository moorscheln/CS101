#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <list>

using namespace std;

uint64_t djb2(string str)
{
    const char *ptr = str.c_str();
    uint64_t hash = 5381;
    int c;
    while ((c = *ptr++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

class Person
{
public:
    string id;
    string first;
    string last;
    string email;
    string phone;
    string city;
    string state;
    string postalCode;
    string returnCorrectPersonInfo(string inputInfo)
    {
        if (inputInfo == "Id")
        {
            return this->id;
        }
        else if (inputInfo == "FirstName")
        {
            return this->first;
        }
        else if (inputInfo == "LastName")
        {
            return this->last;
        }
        else if (inputInfo == "Email")
        {
            return this->email;
        }
        else if (inputInfo == "Phone")
        {
            return this->phone;
        }
        else if (inputInfo == "City")
        {
            return this->city;
        }
        else if (inputInfo == "State")
        {
            return this->state;
        }
        else if (inputInfo == "PostalCode")
        {
            return this->postalCode;
        }
        else
        {
            return "wrongInputInfo";
        }
    }

    Person()
    {
        this->id = "no id";
        this->first = "no first";
        this->last = "no last";
        this->email = "no email";
        this->phone = "no phone";
        this->city = "no city";
        this->state = "no state";
        this->postalCode = "no postalCode";
    };
    Person(string id, string first, string last, string email, string phone, string city, string state, string postalCode)
    {
        this->id = id;
        this->first = first;
        this->last = last;
        this->email = email;
        this->phone = phone;
        this->city = city;
        this->state = state;
        this->postalCode = postalCode;
    }
    friend ostream &operator<<(ostream &os, Person &per)
    {
        os << per.id << "," << per.first << "," << per.last << "," << per.email << "," << per.phone << "," << per.city << "," << per.state << "," << per.postalCode << endl;
        return os;
    }
};

class Bucket
{
public:
    int bucketIndex;
    int bucketSize;
    int bucketIntKey;
    uint64_t realBucketKey;
    string bucketWord;
    vector<Person> list;
    Bucket()
    {
        bucketIndex = 0;
        bucketSize = 0;
        bucketIntKey = 0;
    }
};

class HashTable
{
private:
    int tableSize;
    int bucketsProbed;
    int numBuckets;
    string infoString; // id, first, last, ...
    vector<Bucket> table;

public:
    HashTable(int size, string input)
    {
        tableSize = size;
        table.resize(size);
        bucketsProbed = 0;
        infoString = input;
    }
    void HashInsert(Person inputPersonHash)
    {
        // KEEP TRACK OF: int BucketIndex, inputPersonIntKey,          // if first bucket probed is not empty
        int indexBucket = 0; // buckets integer value
        bucketsProbed = 0;
        string correctPersonInfo = inputPersonHash.returnCorrectPersonInfo(infoString);

        // Hash function determines initial bucket
        uint64_t realHashKey = djb2(correctPersonInfo);
        int originalHash = realHashKey % tableSize;
        indexBucket = realHashKey % tableSize;
        for (int j = 0; j < tableSize; j++)
        {
            if (table[indexBucket].bucketSize == 0)
            {
                table[indexBucket].list.push_back(inputPersonHash);
                table[indexBucket].bucketSize++;
                table[indexBucket].bucketIndex = indexBucket;
                table[indexBucket].bucketWord = correctPersonInfo;
                table[indexBucket].realBucketKey = realHashKey;
                numBuckets++;
                break;
            }
            if (table[indexBucket].realBucketKey == realHashKey)
            { // if key already exists in hash, add person to end of that buckets list of people and increment size of bucket
                table[indexBucket].list.push_back(inputPersonHash);
                table[indexBucket].bucketSize++;
                break;
            }
            // Insert item in next empty bucket
            // Increment j and recompute bucket index
            indexBucket = (originalHash + j + (j * j)) % tableSize;

            // Increment number of buckets probed
            bucketsProbed = bucketsProbed + 1;
        }
    }
    void printHash()
    {
        for (int i = 0; i < tableSize; i++)
        {
            // int a = 0;
            // while (a < table.at(i).list.size())
            // {
            //
            //     a++;
            // }
            if (table.at(i).bucketSize > 0)
            {
                cout << table.at(i).bucketIndex << ": " << table.at(i).bucketWord << " (" << table.at(i).bucketSize << "),";
                cout << endl;
            }
        }
    }
    void searchHash(string searchTerm)
    {
        int indexBucket = 0; // buckets integer value
        bucketsProbed = 0;

        // Hash function determines initial bucket
        uint64_t realHashKey = djb2(searchTerm);
        indexBucket = djb2(searchTerm) % tableSize;
        for (int j = 0; j < tableSize; j++)
        {
            if (table[indexBucket].realBucketKey == realHashKey)
            {
                // print the whole bucket
                cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                for (int a = 0; a < table[indexBucket].bucketSize; a++)
                {
                    cout << table[indexBucket].list.at(a);
                }
                return;
            }
            // Insert item in next empty bucket
            // Increment j and recompute bucket index
            indexBucket = (djb2(searchTerm) + j + (j * j)) % tableSize;

            // Increment number of buckets probed
            bucketsProbed = bucketsProbed + 1;
        }
        cout << "No results" << endl;
    }
};

void getVal(istream &is, string &str)
{
    char ch;
    string line;

    is >> ch;
    getline(is, line);

    str = ch + line;
}

bool isValidKey(const string &key)
{
    string validKeys[8] = {"Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode"};
    for (int i = 0; i < 8; i++)
    {
        if (key == validKeys[i])
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    int tableSize = stoi(argv[2]); // HashTable is array with tableSize
    string key = argv[3];

    ifstream file(filename);
    if (!file)
    {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    if (!isValidKey(key))
    {
        cout << "Invalid key: " << key << endl;
        return 3;
    }

    // int hashKey = djb2(key) % tableSize;
    // HashTable h(tableSize);
    // h.printHash();

    // This is an example of how to retreive the tokens from the input file
    // You will need to modify this to fit your needs to build the hash table
    vector<Person> vecPerson;
    Person inputPerson;
    string line, token;
    getline(file, line); // consume header line
    int a = 0;
    while (getline(file, line))
    {
        istringstream iss(line);
        while (getline(iss, token, '\t'))
        {
            switch (a)
            {
            case 0:
                inputPerson.id = token;
                break;
            case 1:
                inputPerson.first = token;
                break;
            case 2:
                inputPerson.last = token;
                break;
            case 3:
                inputPerson.email = token;
                break;
            case 4:
                inputPerson.phone = token;
                break;
            case 5:
                inputPerson.city = token;
                break;
            case 6:
                inputPerson.state = token;
                break;
            case 7:
                inputPerson.postalCode = token;
                break;
            }
            if (a < 7)
            {
                a++;
            }
            else
            {
                a = 0;
                vecPerson.push_back(inputPerson);
            }
        }
        // cout << endl;
    }

    HashTable h(tableSize, key);
    for (uint64_t i = 0; i < vecPerson.size(); i++)
    {
        h.HashInsert(vecPerson.at(i));
    }

    // for (int i = 0; i < vecPerson.size(); i++)
    // {
    //     cout << vecPerson.at(i).first << endl;
    // }

    cout << "Commands:" << endl
         << "\tprint" << endl
         << "\tlookup <key>" << endl
         << "\tquit" << endl;
    string cmd, val;
    while (1)
    {
        cout << endl
             << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit")
        {
            break;
        }
        else if (cmd == "print")
        {
            h.printHash();
        }
        else if (cmd == "lookup")
        {
            getVal(cin, val);
            h.searchHash(val);
        }
        else
        {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }
    return 0;
}
