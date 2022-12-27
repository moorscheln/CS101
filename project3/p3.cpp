#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Info::Info()
{
    this->name = "No Name Set";
    this->value = "No Value Set";
    this->next = nullptr;
}

Info::Info(std::string name, std::string value, Info *next)
{
    this->name = name;
    this->value = value;
    this->next = next;
}

Contact::Contact()
{
    this->first = "No First Set";
    this->last = "No Last Set";
    this->next = nullptr;
    this->headInfoList = nullptr;
}

Contact::Contact(std::string first, std::string last, Contact *next)
{
    this->first = first;
    this->last = last;
    this->next = next;
    this->headInfoList = nullptr;
}

ContactList::ContactList()
{
    this->headContactList = nullptr;
    this->count = 0;
}

int ContactList::getCount()
{
    return this->count;
}

// print the specified contact and its information
// 1. return false and print nothing if the contact is not in the list
// 2. otherwise return true and print the contact
bool ContactList::printContact(std::ostream &os, std::string firstPar, std::string lastPar)
{
    // if findContact == true, print contact
    if (BoolFindContact(firstPar, lastPar) == false)
    {
        return false;
    }
    else
    {
        Contact *curContact = SearchContact(firstPar, lastPar);
        os << "Contact Name: " << curContact->first << " " << curContact->last << endl;
        if (curContact->headInfoList != nullptr)
        {
            Info *curInfo = curContact->headInfoList;
            while (curInfo != nullptr)
            {
                os << "   " << curInfo->name << " | " << curInfo->value << endl;
                curInfo = curInfo->next;
            }
        }
    }
    // else return false,
    return true;
}

// print all contacts and their information
// print nothing if the list is empty
void ContactList::print(std::ostream &os) // WORKS
{
    // os << headContactList->first << " " << headContactList->last << endl;
    if (headContactList == nullptr)
    {
    }
    else
    {
        for (Contact *cur = headContactList; cur != nullptr; cur = cur->next)
        {
            os << "Contact Name: " << cur->first << " " << cur->last << endl;

            if (cur->headInfoList != nullptr)
            {
                Info *curInfo = cur->headInfoList;
                while (curInfo != nullptr)
                {
                    if ((curInfo->next == nullptr) && (cur->next == nullptr))
                    {
                        os << "   " << curInfo->name << " | " << curInfo->value;
                        break;
                        // curInfo = curInfo->next;
                    }
                    else
                    {
                        os << "   " << curInfo->name << " | " << curInfo->value << endl;
                        curInfo = curInfo->next;
                    }
                }
            }
        }
    }
}

// ADD CONTACT FRONT
bool ContactList::addContactFront(std::string firstPar, std::string lastPar) // WORKS
{
    // Contact *next = nullptr;
    // ContactList *newList = new ContactList();
    Contact *n = new Contact(firstPar, lastPar);
    headContactList = n;

    return true;
    // headContactList = n;
}

// add a contact to the back of the list
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the back of the list
// - do not forget to update count
bool ContactList::addContact(std::string firstPar, std::string lastPar) // WORKS
{
    if (headContactList == nullptr)
    {
        addContactFront(firstPar, lastPar);
        count++;
        return true;
    }
    else
    {
        if (BoolFindContact(firstPar, lastPar) == true)
        {
            return false;
        }
        else
        {
            Contact *cur = headContactList;
            while (cur->next != nullptr)
            {
                cur = cur->next;
            }
            cur->next = new Contact(firstPar, lastPar);
            count++;
            return true;
        }
    }
}

// ADD INFO FRONT
bool ContactList::addInfoFront(std::string firstPar, std::string lastPar, std::string infoNamePar, std::string infoValPar) // WORKS
{
    Contact *curContact = SearchContact(firstPar, lastPar);
    Info *n = new Info(infoNamePar, infoValPar);
    curContact->headInfoList = n;
    return true;
}

// add info to the back of a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the back of the contact's list and return true
bool ContactList::addInfo(std::string firstPar, std::string lastPar, std::string infoNamePar, std::string infoValPar) // WORKS
{
    if (headContactList == nullptr)
    {
        return false;
    }
    else
    {
        if (BoolFindContact(firstPar, lastPar) == false)
        {
            return false;
        }
        else
        {
            Contact *currentContact = SearchContact(firstPar, lastPar);
            if (currentContact->headInfoList == nullptr)
            {
                addInfoFront(firstPar, lastPar, infoNamePar, infoValPar);
                return true;
            }
            else if (BoolFindInfo(firstPar, lastPar, infoNamePar) == true) // if infoName exists (searchInfoName), update that and return true;
            {
                Info *currentInfo = SearchInfo(firstPar, lastPar, infoNamePar);
                currentInfo->value = infoValPar;
                return true;
            }
            else
            // else, addInfoBack
            {
                Info *currentInfo = currentContact->headInfoList;
                while (currentInfo->next != nullptr)
                {
                    currentInfo = currentInfo->next;
                }
                currentInfo->next = new Info(infoNamePar, infoValPar);
                return true;
            }
        }
    }
}

bool ContactList::compareContact(Contact *newCompare, Contact *cur)
{
    if (newCompare->last < cur->last) // next last name > cur last name, return true
    {
        return true;
    }
    else if (newCompare->last > cur->last)
    {
        return false;
    }
    else
    {
        // order by first names
        if (newCompare->first <= cur->first)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

// add a contact to the list in ascending order by last name
//     if last names are equal, then order by first name ascending
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the list
// - do not forget to update count
// - compare strings with the built-in comparison operators: <, >, ==, etc.
// - a compare method/function is recommended
bool ContactList::addContactOrdered(std::string firstPar, std::string lastPar)
{
    // 1) Empty List
    Contact *n = new Contact(firstPar, lastPar);
    if (headContactList == nullptr)
    {
        addContactFront(firstPar, lastPar);
        count++;
        return true;
    }
    else if (BoolFindContact(firstPar, lastPar) == true) // contact already exists, do nothing & return false
    {
        return false;
    }
    else if (compareContact(n, headContactList) == true) // new Contact is < headContact
    {
        n->next = headContactList;
        headContactList = n;
        count++;
        return true;
    }
    else
    {
        Contact *prev = headContactList;
        Contact *cur = headContactList->next;
        while (cur != nullptr)
        {
            if (compareContact(n, cur) == true)
            {
                break;
            }
            prev = prev->next;
            cur = cur->next;
        }
        prev->next = n;
        n->next = cur;
        count++;
        return true;
    }
    // 2) Nonempty list
    // 2.1 addFront() when new->degree > head->degree
    // 2.2 addMiddle() & addBack()
    //  - traverse with prev & cur
    //  - prev->next = new
    //  - new->next = cur
}

bool ContactList::compareInfo(Info *newCompareInfo, Info *curInfo)
{
    if (newCompareInfo->name < curInfo->name) // next last name < curInfo last name, return true
    {
        return true;
    }
    else
    {
        return false;
    }
}

// add info to a contact's info list in ascending order by infoName
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the contact's list and return true
bool ContactList::addInfoOrdered(std::string firstPar, std::string lastPar, std::string infoNamePar, std::string infoValPar)
{
    Info *nInfo = new Info(infoNamePar, infoValPar);
    if (headContactList == nullptr) // Contact list is empty, return false
    {
        return false;
    }
    else if (BoolFindContact(firstPar, lastPar) == false) // contact doesnt exists, do nothing & return false
    {
        return false;
    }
    else // contact exists
    {
        Contact *currentContact = SearchContact(firstPar, lastPar);
        if (currentContact->headInfoList == nullptr)
        {
            addInfoFront(firstPar, lastPar, infoNamePar, infoValPar);
            return true;
        }
        else if (BoolFindInfo(firstPar, lastPar, infoNamePar) == true) // if infoName exists (searchInfoName), update that and return true;
        {
            Info *currentInfo = SearchInfo(firstPar, lastPar, infoNamePar);
            currentInfo->value = infoValPar;
            return true;
        }
        else if (compareInfo(nInfo, currentContact->headInfoList) == true) // new Contact is < headContact
        {
            nInfo->next = currentContact->headInfoList;
            currentContact->headInfoList = nInfo;
            return true;
        }
        else
        {

            Info *prevInfo = currentContact->headInfoList;
            Info *curInfo = currentContact->headInfoList->next;
            while (curInfo != nullptr)
            {
                if (compareInfo(nInfo, curInfo) == true)
                {
                    break;
                }
                prevInfo = prevInfo->next;
                curInfo = curInfo->next;
            }
            prevInfo->next = nInfo;
            nInfo->next = curInfo;
            return true;
        }
    }
}

// remove the contact and its info from the list
// 1. return false and do nothing if the contact is not in the list
// 2. otherwise return true and remove the contact and its info
// - do not forget to update count
bool ContactList::removeContact(std::string firstPar, std::string lastPar)
{
    if (BoolFindContact(firstPar, lastPar) == false)
    {
        return false;
    }
    else if ((headContactList->first == firstPar) && (headContactList->last == lastPar))
    {
        Contact *oldHead = headContactList;
        headContactList = headContactList->next;
        delete oldHead;
        count--;
        return true;
    }
    else
    {
        Contact *prev = headContactList;
        Contact *cur = headContactList->next;
        while (cur != nullptr)
        {
            if ((cur->first == firstPar) && (cur->last == lastPar))
            {
                break;
            }
            prev = prev->next;
            cur = cur->next;
        }
        prev->next = cur->next;
        delete cur;
        count--;
        return true;
    }
}

// remove the info from a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. return false and do nothing if the info is not in the contact's info list
// 3. otherwise return true and remove the info from the contact's list
bool ContactList::removeInfo(std::string firstPar, std::string lastPar, std::string infoNamePar)
{

    if (BoolFindContact(firstPar, lastPar) == false)
    {
        return false;
    }
    Contact *nContact = SearchContact(firstPar, lastPar);
    if (BoolFindInfo(firstPar, lastPar, infoNamePar) == false)
    {
        return false;
    }
    // Info *nHeadInfo = nContact->headInfoList;
    if (nContact->headInfoList->name == infoNamePar)
    {

        Info *oldHeadInfo = nContact->headInfoList;
        nContact->headInfoList = nContact->headInfoList->next;
        delete oldHeadInfo;
        return true;
    }
    else
    {
        Info *prevInfo = nContact->headInfoList;
        Info *curInfo = nContact->headInfoList->next;
        while (curInfo != nullptr)
        {
            if (curInfo->name == infoNamePar)
            {
                break;
            }
            prevInfo = prevInfo->next;
            curInfo = curInfo->next;
        }
        prevInfo->next = curInfo->next;
        delete curInfo;
        return true;
    }
}

void ContactList::clear() // WORKS
{
    while (headContactList != nullptr)
    {
        while (headContactList->headInfoList != nullptr)
        {
            removeInfo(headContactList->first, headContactList->last, headContactList->headInfoList->name);
        }
        removeContact(headContactList->first, headContactList->last);
    }
    count = 0;
}

// destroy the list by removing all contacts and their infos
ContactList::~ContactList() // WORKS
{
    clear();
}

void ContactList::deepCopy(const ContactList &src)
{
    for (Contact *cur = src.headContactList; cur != nullptr; cur = cur->next)
    {
        addContact(cur->first, cur->last);
        for (Info *curInfo = cur->headInfoList; curInfo != nullptr; curInfo = curInfo->next)
        {
            addInfo(cur->first, cur->last, curInfo->name, curInfo->value);
        }
    }
    count = src.count;
}

// deep copy the source list
// - do not forget to update count
ContactList::ContactList(const ContactList &src)
{
    headContactList = nullptr;
    deepCopy(src);
}

// remove all contacts and their info then deep copy the source list
// - do not forget to update count
const ContactList &ContactList::operator=(const ContactList &src)
{
    if (this != &src)
    {
        clear();
        deepCopy(src);
    }
    return *this;
}

Contact *ContactList::SearchContact(std::string firstPar, std::string lastPar)
{
    for (Contact *cur = headContactList; cur != nullptr; cur = cur->next)
    {
        if ((firstPar == cur->first) && (lastPar == cur->last))
        {
            return cur;
        }
    }
    return nullptr;
}

Info *ContactList::SearchInfo(std::string firstPar, std::string lastPar, std::string infoNamePar)
{
    Contact *curContact = SearchContact(firstPar, lastPar);
    for (Info *curInfo = curContact->headInfoList; curInfo != nullptr; curInfo = curInfo->next)
    {

        if (infoNamePar == curInfo->name)
        {
            return curInfo;
        }
    }
    return nullptr;
}

bool ContactList::BoolFindContact(std::string firstPar, std::string lastPar)
{
    for (Contact *cur = headContactList; cur != nullptr; cur = cur->next)
    {
        if ((firstPar == cur->first) && (lastPar == cur->last))
        {
            return true;
        }
    }
    return false;
}

bool ContactList::BoolFindInfo(std::string firstPar, std::string lastPar, std::string infoNamePar)
{
    Contact *curContact = SearchContact(firstPar, lastPar);
    for (Info *curInfo = curContact->headInfoList; curInfo != nullptr; curInfo = curInfo->next)
    {

        if (infoNamePar == curInfo->name)
        {
            return true;
        }
    }
    return false;
}