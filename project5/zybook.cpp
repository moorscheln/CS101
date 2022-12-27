#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <list>
#include <queue>
#include <list>
#include <stack>

using namespace std;

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
        this->leftChild = nullptr;
        this->rightChild = nullptr;
        this->parent = nullptr;
    };
    Node(int keyVal)
    {
        this->data = keyVal;
        this->leftChild = nullptr;
        this->rightChild = nullptr;
        this->parent = nullptr;
        this->inIdx = 0;
        this->levelIdx = 0;
    };
    Node(int keyVal, int keyIn, int keyLevel)
    {
        this->data = keyVal;
        this->inIdx = keyIn;
        this->levelIdx = keyLevel;
        this->leftChild = nullptr;
        this->rightChild = nullptr;
        this->parent = nullptr;
    };
    Node(int keyVal, Node *left, Node *right)
    {
        this->data = keyVal;
        this->leftChild = left;
        this->rightChild = right;
        this->parent = nullptr;
    };
    Node(int keyVal, int keyIn, int keyLevel, Node *left, Node *right) // all except parent
    {
        this->data = keyVal;
        this->inIdx = keyIn;
        this->levelIdx = keyLevel;
        this->leftChild = left;
        this->rightChild = right;
        this->parent = nullptr;
    };
    ~Node() // Destroy
    {
        delete parent;
        delete leftChild;
        delete rightChild;
    }
    Node &operator=(const Node &parNode) // Assign
    {
        Node *newNode = new Node();
        newNode->parent = parNode.parent;
        newNode->leftChild = parNode.leftChild;
        newNode->rightChild = parNode.rightChild;
        newNode->data = parNode.data;

        delete parent;
        delete leftChild;
        delete rightChild;

        parent = newNode->parent;
        leftChild = newNode->leftChild;
        rightChild = newNode->rightChild;
        data = newNode->data;

        return *this;
    };
    Node(const Node &copyNode) // Copy
    {
        parent = copyNode.parent;
        leftChild = copyNode.leftChild;
        rightChild = copyNode.rightChild;
        data = copyNode.data;
    };

    // Not used
    // Node *getNode(int key, Node *left, Node *right)
    // {
    //     Node *node = new Node();
    //     node->data = key;
    //     node->leftChild = left;
    //     node->rightChild = right;
    //     return node;
    // };
};

// int searchIn(vector<int> vecIn, int inOrderIndex)
// {
//     for (int i = 0; i < vecIn.size(); i++)
//     {
//         if (vecIn[i] == inOrderIndex)
//         {
//             return i;
//         }
//     }
//     return -1;
// }

// int searchLevel(vector<int> vecLevel, int levelOrderIndex)
// {
//     int levelSize = vecLevel.size();
//     for (int i = 0; i < levelSize; i++)
//     {
//         if (vecLevel[i] == levelOrderIndex)
//         {
//             return i;
//         }
//     }
//     return -1;
// }

// bool compareFoo(Node *l, Node *r)
// {
//     return l->data > r->data;
// }

bool isLeaf(Node *node)
{
    if ((node->leftChild == nullptr) && (node->rightChild == nullptr) && (node->data < 128))
    {
        return true;
    }
    else
    {
        return false;
    }
}

class Tree
{
public:
    int size;
    Node *root;
    Tree()
    {
        this->size = 0;
    };
    Tree(vector<int> inOrderVec, vector<int> levelOrderVec)
    {
        this->size = inOrderVec.size();
        // this->root = new Node
    };
    Node *createTreeHuffman(vector<int> in, vector<int> level)
    {

        // Recursion

        if (in.size() > 1)
        {
            int inIndex = 0;
            // Index of Root in InOrder
            // int levelSize = level.size();
            // int inSize = in.size();
            // Leave sizes as unsigned longs to match vector size
            for (int i = 0; i < level.size(); i++)
            {
                if (in[i] == level[0])
                {
                    inIndex = i;
                }
            }

            vector<int> inLeft;
            for (int i = 0; i < inIndex; i++)
            {
                inLeft.push_back(in[i]);
            }
            vector<int> inRight;
            for (int i = inIndex + 1; i < in.size(); i++)
            {
                inRight.push_back(in[i]);
            }

            vector<int> levelLeft;
            for (int i = 0; i < level.size(); i++)
            {
                for (int j = 0; j < inLeft.size(); j++)
                {
                    if (level[i] == inLeft[j])
                        levelLeft.push_back(level[i]);
                }
            }

            vector<int> levelRight;
            for (int i = 0; i < level.size(); i++)
            {
                for (int j = 0; j < inRight.size(); j++)
                {
                    if (level[i] == inRight[j])
                        levelRight.push_back(level[i]);
                }
            }

            return new Node(level[0], inIndex, 0, createTreeHuffman(inLeft, levelLeft), createTreeHuffman(inRight, levelRight));
        }
        else if (in.size() == 1)
        {
            Node *one = new Node(in[0], nullptr, nullptr);
            return one;
        }
        else
        {
            return nullptr;
        }
    };
};

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

    // If this is a leaf node, then it contains one of the input characters, print the character and its code from arr[]
    if (isLeaf(root) == true)
    {

        cout << root->data << ": ";
        printArr(arr, top);
    }
}

// Test printInOrder
void printInorder(Node *node)
{
    if (node->parent == nullptr)
    {
        cout << "   Level 0 (Root)" << node->data << " " << endl;
    }
    if (node == nullptr)
    {
        return;
    }
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
    // Check InOrder File
    ifstream inorder(argv[1]);
    if (!inorder)
    {
        cout << "Unable to open" << inorderFile << endl;
        return 2;
    }
    // Check levelOrder File
    ifstream levelorder(argv[2]);
    if (!levelorder)
    {
        cout << "Unable to open" << levelorderFile << endl;
        return 3;
    }
    // Check encoded File
    ifstream encoded(argv[3]);
    if (!encoded)
    {
        cout << "Unable to open" << encodedFile << endl;
        return 4;
    }

    vector<int> vecInorder;
    vector<int> vecLevelorder;
    vector<Node *> vecNode;

    /////// IN ORDER INPUT STREAM & TREE SIZE
    int input = 0;
    while (inorder >> input)
    {
        vecInorder.push_back(input);
    }
    // int treeSize = vecInorder.size();

    /////// LEVEL ORDER INPUT STREAM
    while (levelorder >> input)
    {
        vecLevelorder.push_back(input);
    }

    Tree h(vecInorder, vecLevelorder);
    Node *root = h.createTreeHuffman(vecInorder, vecLevelorder);

    /////////// ENCODED INPUT STREAM — Assign string to strEncoded
    char encodeChar;
    string strEncoded;
    // int encodeSize = 0;
    // while (getline(encoded, fileLine))
    // {
    //     istringstream issEncoded(fileLine);
    //     encodeSize = encodeSize + fileLine.length();
    //     strEncoded = strEncoded + fileLine;
    // }

    // assign level order index to node
    // for (int i = 0; i < treeSize; i++)
    // {
    //     vecNode.push_back(new Node(i, vecInorder[i], vecLevelorder[i]));
    // }

    Node *currentNode = root;
    // char dataChar = ' ';
    while (encoded >> encodeChar)
    {
        if (encodeChar == '1')
        {
            currentNode = currentNode->rightChild;
            if (isLeaf(currentNode) == true)
            {
                // dataChar = char(currentNode->data);
                strEncoded = strEncoded + char(currentNode->data); // integer to char
                // strEncoded = strEncoded + dataChar;

                currentNode = root; // back to top of tree
            }
        }
        else if (encodeChar == '0')
        {
            currentNode = currentNode->leftChild;
            if (isLeaf(currentNode) == true)
            {
                // dataChar = char(currentNode->data);
                strEncoded = strEncoded + char(currentNode->data); // integer to char
                // strEncoded = strEncoded + dataChar;

                currentNode = root; // back to top of tree
            }
        }
    }

    cout << strEncoded;
    // for (int i = 0; i < strEncoded.size(); i++)
    // {
    //     // cout << strEncoded[i] << endl;
    //     // cout << currentNode->data << endl;
    //     // cout << "   Right: " << currentNode->rightChild->data << endl;
    //     // cout << "   Left: " << currentNode->leftChild->data << endl;
    //     if (strEncoded[i] == '1')
    //     {
    //         currentNode = currentNode->rightChild;
    //         if (isLeaf(currentNode) == true)
    //         {
    //             cout << char(currentNode->data);
    //             currentNode = root;
    //         }
    //     }
    //     else if (strEncoded[i] == '0')
    //     {
    //         currentNode = currentNode->leftChild;
    //         if (isLeaf(currentNode) == true)
    //         {
    //             cout << char(currentNode->data);
    //             currentNode = root;
    //         }
    //     }
    // }

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