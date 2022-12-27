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

int search(int arr[], int start, int end, int value)
{
    for (int i = start; i <= end; i++)
        if (arr[i] == value)
            return i;
    return -1;
}

int *extrackKeys(int in[], int level[], int m, int n)
{
    int *newlevel = new int[m];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (search(in, 0, m - 1, level[i]) != -1)
            newlevel[j] = level[i], j++;
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
        this->inIdx == NULL;
        this->levelIdx == NULL;
    };
};

class Tree
{
public:
    int size;

    vector<Node *> tree;
    Tree()
    {
        this->size = 0;
    };
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
        int inIndex = search(in, inStrt, inEnd, root->data);

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
};

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
    int inIndex = search(in, inStrt, inEnd, root->data);

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
    Node inputNode;
    vector<Node *> vecNode;

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
            inputNode.data = inputToken;
            inputNode.inIdx = count;
            // huff.tree.push_back(new Node(inputNode));
            vecNode.push_back(new Node(inputNode));
            count++;
        }
    }
    int sizeTree = vecInorder.size();

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

    /////////// ENCODED INPUT STREAM — Assign string to strEncoded
    string strEncoded;
    while (getline(encoded, line))
    {
        istringstream issEncoded(line);
        strEncoded = strEncoded + line;
    }

    // assign level order index to node
    for (int i = 0; i < sizeTree; i++)
    {
        for (int j = 0; j < vecLevelorder.size(); j++)
        {
            if (vecNode[i]->data == vecLevelorder[j])
            {
                vecNode[i]->levelIdx = j;
                // huff.tree[i]->levelIdx = j;
            }
        }
    }

    ///////// Turn vectors into regular integer arrays
    int inArray[sizeTree];
    int levelArray[sizeTree];
    for (int i = 0; i < sizeTree; i++)
    {
        inArray[i] = vecInorder[i];
        levelArray[i] = vecLevelorder[i];
    }

    int n = vecInorder.size(); // same as treeSize
    Node *root = buildTree(inArray, levelArray, 0, n - 1, n);
    Node *currentNode = root;
    for (int i = 0; i < strEncoded.size(); i++)
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

// https://www.geeksforgeeks.org/construct-tree-inorder-level-order-traversals/?ref=rp

Node *buildTree(int in[], int level[], int inStrt, int inEnd, int n)
{
    if (inStrt > inEnd)
        return NULL;

    /* The first node in level order traversal is root */
    Node *root = new Node(level[0]);
    root->parent = NULL;

    /* If this node has no children then return */
    if ((root->leftChild == NULL) && (root->rightChild == NULL))
    {
        return root;
    }

    /* Else find the index of this node in Inorder traversal
     */
    // int inIndex = search(in, inStrt, inEnd, root->data);
    int inIndex = root->inIdx;
    cout << inIndex << endl;
    // Extract left subtree keys from level order traversal
    int *llevel = extrackKeys(in, level, inIndex, n);
    // int llevel[inIndex];
    // // int *llevel = new int[inIndex];

    // // llevel = extrackKeys(in, level, inIndex, n);
    // int j = 0;
    // for (int i = 0; i < n; i++)
    // {
    //     if (search(in, 0, inIndex - 1, level[i]) != -1)
    //     {
    //         llevel[j] = level[i];
    //         j++;
    //     }
    // }

    // // Extract right subtree keys from level order traversal
    int *rlevel = extrackKeys(in + inIndex + 1, level, n - 1, n);
    // // int rlevel[n - 1] = extrackKeys(in + inIndex + 1, level, n - 1, n);

    // int rlevel[n - 1];
    // // vector <int> rightsub;
    // // int *rlevel = new int[n - 1];
    // // llevel = extrackKeys(in, level, inIndex, n);
    // int h = 0;
    // for (int i = 0; i < n; i++)
    // {
    //     if (search(in + inIndex + 1, 0, inIndex - 1, level[i]) != -1)
    //     {
    //         rlevel[h] = level[i];
    //         h++;
    //     }
    // }

    /* construct left and right subtrees */
    root->leftChild = buildTree(in, llevel, inStrt, inIndex - 1, inIndex - inStrt);
    root->rightChild = buildTree(in, rlevel, inIndex + 1, inEnd, inEnd - inIndex);

    // Free memory to avoid memory leak
    delete[] llevel;
    delete[] rlevel;

    return root;
}