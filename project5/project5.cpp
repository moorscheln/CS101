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
        a = new int[src.capacity];
        size = src.size;

        for (int i = 0; i < size; i++)
        {
            a[i] = src.a[i];
        }
        error = 0;
    }
};

int search(int arr[], int start, int end, int value)
{
    for (int i = 0; i < end; i++)
        if (arr[i] == value)
        {
            return i;
        }
    return 0;
}

int *extrackKeys(int in[], int level[], int m, int n)
{
    int *newlevel = new int[m];
    for (int i = 0; i < m; i++)
    {
        newlevel[i] = 0;
    }
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (search(in, 0, m - 1, level[i]) == 0)
        {
            newlevel[j] = level[i];
            j++;
        }
    }
    return newlevel;
}

class Node
{
public:
    int data;
    int inIdx;
    int levelIdx;
    Node *leftChild, *rightChild, *parent;
    Node()
    {
        this->data = 0;
        this->inIdx = 0;
        this->levelIdx = 0;
        this->leftChild = NULL;
        this->rightChild = NULL;
        this->parent = NULL;
    };
    Node(int keyVal)
    {
        this->data = keyVal;
        this->leftChild = NULL;
        this->rightChild = NULL;
        this->parent = NULL;
    };
};

// class Tree
// {
// public:
//     int size;

//     vector<Node *> tree;
//     Tree()
//     {
//         this->size = 0;
//     };
//     Node *buildTree(int in[], int level[], int inStrt, int inEnd, int n)
//     {

//         if (inStrt > inEnd)
//             return NULL;

//         /* The first node in level order traversal is root */
//         Node *root = new Node(level[0]);
//         root->parent = NULL;

//         /* If this node has no children then return */
//         if (inStrt == inEnd)
//             return root;

//         /* Else find the index of this node in Inorder traversal
//          */
//         int inIndex = search(in, inStrt, inEnd, root->data);

//         // Extract left subtree keys from level order traversal
//         int *llevel = extrackKeys(in, level, inIndex, n);

//         // Extract right subtree keys from level order traversal
//         int *rlevel = extrackKeys(in + inIndex + 1, level, n - 1, n);

//         /* construct left and right subtrees */
//         root->leftChild = buildTree(in, llevel, inStrt, inIndex - 1, inIndex - inStrt);
//         root->rightChild = buildTree(in, rlevel, inIndex + 1, inEnd, inEnd - inIndex);

//         // Free memory to avoid memory leak
//         delete[] llevel;
//         delete[] rlevel;

//         return root;
//     };
// };

bool isLeaf(Node *root)
{
    if ((root->leftChild == NULL) && (root->rightChild == NULL))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        cout << arr[i];

    cout << "\n";
}

void printCodes(Node *root, int arr[], int top)
{

    // Assign 0 to left edge and recur
    if (root->leftChild)
    {

        arr[top] = 0;
        printCodes(root->leftChild, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (root->rightChild)
    {

        arr[top] = 1;
        printCodes(root->rightChild, arr, top + 1);
    }

    // If this is a leaf node, then
    // it contains one of the input
    // characters, print the character
    // and its code from arr[]
    if (isLeaf(root) == true)
    {

        cout << root->data << ": ";
        printArr(arr, top);
    }
}

Node *buildTree(int in[], int level[], int inStrt, int inEnd, int n)
{

    if (inStrt > inEnd)
        return NULL;

    /* The first node in level order traversal is root */
    Node *root = new Node(level[0]);
    root->parent = NULL;

    /* If this node has no children then return */
    if (inStrt == inEnd)
        return root;

    /* Else find the index of this node in Inorder traversal
     */
    int inIndex = root->inIdx;

    // Extract left subtree keys from level order traversal
    int *llevel = extrackKeys(in, level, inIndex, n);

    // Extract right subtree keys from level order traversal
    int *rlevel = extrackKeys(in + inIndex + 1, level, n - 1, n);

    /* construct left and right subtrees */
    root->leftChild = buildTree(in, llevel, inStrt, inIndex - 1, inIndex - inStrt);
    root->rightChild = buildTree(in, rlevel, inIndex + 1, inEnd, inEnd - inIndex);

    // Free memory to avoid memory leak
    delete[] llevel;
    delete[] rlevel;

    return root;
}

void printInorder(Node *node)
{
    if (node == NULL)
        return;
    printInorder(node->leftChild);
    cout << node->data << " ";
    printInorder(node->rightChild);
}

// int **load(/*string imageFile,*/ int &length, int &height)
// {
//     //ifstream file(imageFile);
//     // if (file.is_open())
//     // {
//         //file >> length;
//         int *array = new int [length];
//         //file >> height;
//         for (int i = 0; i < length; i++)
//         {
//             array[i] = new int[height];
//             for (int j = 0; j < height; j++)
//             {
//                 // file >> array[i][j];
//             }
//         //}
//         return array;
//     }
//     else
//     {
//         cout << "Unable to open file." << endl;
//         return 0;
//     }
// }

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "Usage: ./a.out inorder.txt levelorder.txt encoded.txt" << endl;
        return 1;
    }

    string inorderFile = argv[1];
    string levelorderFile = argv[2];
    string encodedFile = argv[3];

    ifstream inorder(argv[1]);
    if (!inorder)
    {
        cout << "Unable to open" << inorderFile << endl;
        return 2;
    }

    ifstream levelorder(argv[2]);
    if (!levelorder)
    {
        cout << "Unable to open" << levelorderFile << endl;
        return 3;
    }

    ifstream encoded(argv[3]);
    if (!encoded)
    {
        cout << "Unable to open" << encodedFile << endl;
        return 4;
    }

    vector<int> vecInorder;
    vector<int> vecLevelorder;
    // Node inputNode;
    // vector<Node *> vecNode;

    string line, token;
    int inputToken = 0;
    int count = 0;
    /////// IN ORDER INPUT STREAM & CHECK SIZE
    while (getline(inorder, line))
    {
        istringstream issInorder(line);
        while (getline(issInorder, token, ' '))
        {
            inputToken = stoi(token);
            vecInorder.push_back(inputToken);
            // inputNode.data = inputToken;
            // inputNode.inIdx = count;
            // huff.tree.push_back(new Node(inputNode));
            // vecNode.push_back(new Node(inputNode));
            count++;
        }
    }
    int treeSize = vecInorder.size();

    /////// LEVEL ORDER INPUT STREAM
    while (getline(levelorder, line))
    {
        istringstream issLevelorder(line);
        while (getline(issLevelorder, token, ' '))
        {
            inputToken = stoi(token);
            vecLevelorder.push_back(inputToken);
        }
    }
    int levelOrderSize = vecLevelorder.size();
    /////////// ENCODED INPUT STREAM — Assign string to strEncoded
    string strEncoded;
    while (getline(encoded, line))
    {
        istringstream issEncoded(line);
        strEncoded = strEncoded + line;
    }
    int encodeSize = strEncoded.size();

    // assign level order index to node
    // for (int i = 0; i < treeSize; i++)
    // {
    //     for (int j = 0; j < treeSize; j++)
    //     {
    //         if (vecNode[i]->data == vecLevelorder[j])
    //         {
    //             vecNode[i]->levelIdx = j;

    //         }
    //     }
    // }

    ///////// Turn vectors into regular integer arrays
    int inArray[treeSize];
    int levelArray[treeSize];
    for (int i = 0; i < treeSize; i++)
    {
        inArray[i] = vecInorder[i];
        levelArray[i] = vecLevelorder[i];
    }

    int n = vecInorder.size(); // same as treeSize
    // Tree huff;
    // huff.buildTree(inArray, levelArray, 0, n - 1, n);
    Node *root = buildTree(inArray, levelArray, 0, n - 1, n);
    Node *currentNode = buildTree(inArray, levelArray, 0, n - 1, n);
    // Node *root = huff.buildTree(inArray, levelArray, 0, n - 1, n);
    // Node *currentNode = huff.buildTree(inArray, levelArray, 0, n - 1, n);
    for (int i = 0; i < encodeSize; i++)
    {
        // cout << strEncoded[i] << endl;
        // cout << currentNode->data << endl;
        // cout << "   Right: " << currentNode->rightChild->data << endl;
        // cout << "   Left: " << currentNode->leftChild->data << endl;
        if (strEncoded[i] == '1')
        {
            currentNode = currentNode->rightChild;
            if (isLeaf(currentNode) == true)
            {
                cout << char(currentNode->data);
                currentNode = root;
            }
        }
        else if (strEncoded[i] == '0')
        {
            currentNode = currentNode->leftChild;
            if (isLeaf(currentNode) == true)
            {
                cout << char(currentNode->data);
                currentNode = root;
            }
        }
    }

    // printInorder(root);
    // // huff.size = sizeTree;
    // for (int i = 0; i < sizeTree; i++)
    // {
    //     if (vecNode[i]->levelIdx == 0)
    //     {
    //         // huff.tree[0] = vecNode[i];
    //     }
    //     if (vecNode[i]->levelIdx == 1)
    //     {
    //         // huff.tree[1] = vecNode[i];
    //         huff.tree[0]->leftChild = vecNode[i];
    //     }
    // }

    // cout << "Inorder" << endl;
    // for (int i = 0; i < vecInorder.size(); i++)
    // {
    //     cout << vecInorder.at(i) << endl;
    // }
    // cout << "Levelorder" << endl;
    // for (int i = 0; i < vecLevelorder.size(); i++)
    // {
    //     cout << vecLevelorder.at(i) << endl;
    // }

    // cout << "vecNodes" << endl;
    /*
            for (int i = 0; i < vecLevelorder.size(); i++)
            {
                cout << "Data: " << vecNode[i]->data << " | " << vecNode[i]->inIdx << " | " << vecNode[i]->levelIdx << endl;
                cout << "Data: " << huff.tree[i]->data << " | " << huff.tree[i]->inIdx << " | " << huff.tree[i]->levelIdx << endl;
            }
            */

    return 0;
}