#ifndef _P3_H_
#define _P3_H_

#include <iostream>
#include <string>

class Info
{
public:
    std::string name;
    std::string value;
    Info *next;

    Info();
    Info(std::string name, std::string value, Info *next = nullptr);
};

class Contact
{
public:
    std::string first;
    std::string last;
    Contact *next;
    Info *headInfoList;

    Contact();
    Contact(std::string first, std::string last, Contact *next = nullptr);
};

class ContactList
{
private:
    Contact *headContactList;
    int count;

public:
    ContactList();

    int getCount();

    bool printContact(std::ostream &os, std::string first, std::string last);
    void print(std::ostream &os);

    bool addContact(std::string first, std::string last);
    bool addInfo(std::string first, std::string last, std::string infoName, std::string infoVal);

    bool addContactOrdered(std::string first, std::string last);
    bool addInfoOrdered(std::string first, std::string last, std::string infoName, std::string infoVal);

    bool removeContact(std::string first, std::string last);
    bool removeInfo(std::string first, std::string last, std::string infoName);

    ~ContactList();
    ContactList(const ContactList &src);
    const ContactList &operator=(const ContactList &src);
    // MY HELPER FUNCTIONS
    bool addContactFront(std::string firstPar, std::string lastPar);
    bool addInfoFront(std::string firstPar, std::string lastPar, std::string infoNamePar, std::string infoValPar);
    Contact *SearchContact(std::string firstPar, std::string lastPar);
    bool BoolFindContact(std::string firstPar, std::string lastPar);
    bool BoolFindInfo(std::string firstPar, std::string lastPar, std::string infoNamePar);
    Info *SearchInfo(std::string firstPar, std::string lastPar, std::string infoNamePar);
    bool compareContact(Contact *cur, Contact *next);
    bool compareInfo(Info *newCompareInfo, Info *curInfo);
    void deepCopy(const ContactList &src);
    void clear();
};

#endif