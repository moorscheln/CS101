#include <iostream>

using namespace std;

class MyDynamicArray
{
private:
    int size, capacity, error;
    int *a;

public:
    MyDynamicArray()
    {
        capacity = 2;
        size = 0;
        error = 0;
        a = new int[capacity];
    }
    MyDynamicArray(int s)
    {
        /* Your code goes here */
        capacity = s;
        size = s;
        a = new int[capacity];
        error = 0;
    }
    ~MyDynamicArray()
    {

        cout << "In the destructor" << endl;
    }
    int &operator[](int i)
    {
        /* Your code goes here */
        if ((i >= size) || (i < 0))
        {
            cout << "Out of bounds reference : " << i << endl;
            return error;
        }
        else
        {
            return a[i];
        }
    }
    void add(int v)
    {
        /* Your code goes here */
        if (size == capacity)
        {
            capacity *= 2;
            cout << "Doubling to : " << capacity << endl;
            int *temp = new int[capacity];
            for (int i = 0; i < size; i++)
            {
                temp[i] = a[i];
            }
            delete[] a;
            a = temp;
        }
        a[size] = v;
        size++;
    }
    void del()
    {
        /* Your code goes here */
        if (size > 0)
        {
            size--;
        }
        if (size <= capacity / 4)
        {
            capacity = capacity / 2;
            cout << "Reducing to : " << capacity << endl;
            int *temp = new int[capacity];

            for (int i = 0; i < size; i++)
            {
                temp[i] = a[i];
            }

            delete a;
            a = temp;
        }
    }
    int length()
    {
        return size;
    }
    void clear()
    {
        delete a;
        a = new int[capacity = 2];
        size = 0;
    }
    MyDynamicArray &operator=(const MyDynamicArray &src)
    {
        /* Your code goes here */
        cout << "In the copy assignment operator" << endl;
        delete a;
        a = new int[src.capacity];
        size = src.size;

        for (int i = 0; i < size; i++)
        {
            a[i] = src.a[i];
        }
        error = 0;

        return *this;
    }

    // void deepCopy(const MyString &src) {
    //     len = strlen(src.data);
    //     data = new char[len + 1];
    //     strcpy(data, src.data);
    // }

    MyDynamicArray(const MyDynamicArray &src)
    {
        /* Your code goes here */
        cout << "In the copy constructor" << endl;
        a = new int[src.capacity];
        size = src.size;

        for (int i = 0; i < size; i++)
        {
            a[i] = src.a[i];
        }
        error = 0;
    }
};
