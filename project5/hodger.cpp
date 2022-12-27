#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

class binaryTreeNode
{
private:
public:
    binaryTreeNode *left;
    binaryTreeNode *right;
    int value;

    // Default Constructot
    binaryTreeNode()
    {
        left = nullptr;
        right = nullptr;
        value = 0;
    }
    // Constructor with only value as parameter
    binaryTreeNode(int x)
    {
        left = nullptr;
        right = nullptr;
        value = x;
    }
    // Constructor with full parameters
    binaryTreeNode(int x, binaryTreeNode *leftNew, binaryTreeNode *rightNew)
    {
        value = x;
        this->left = leftNew;
        this->right = rightNew;
    }
    // Destructor
    ~binaryTreeNode()
    {
        delete left;
        delete right;
    }
    // Assignment operator
    binaryTreeNode &operator=(const binaryTreeNode &node1)
    {
        binaryTreeNode *newNode = new binaryTreeNode();

        newNode->left = node1.left;
        newNode->right = node1.right;
        newNode->value = node1.value;

        delete left;
        delete right;

        left = newNode->left;
        right = newNode->right;
        value = newNode->value;

        return *this;
    }
    // Deep Copy Constructor
    binaryTreeNode(const binaryTreeNode &node1)
    {
        left = node1.left;
        right = node1.right;
        value = node1.value;
    }
};
// Function to return index of the first item in level order
int findIndex(vector<int> array, int val)
{
    for (int i = 0; i < array.size(); i++)
    {
        if (array.at(i) == val)
        {
            return i;
        }
    }
}
// Function to Create the sub level order traversal. It just iterates through the level order checking if the value is in that sub in order traversal
vector<int> createSubLevelOrder(vector<int> subInOrder, vector<int> levelOrder)
{
    vector<int> subLevelOrder;
    for (int i = 0; i < levelOrder.size(); i++)
    {
        for (int j = 0; j < subInOrder.size(); j++)
        {
            if (levelOrder[i] == subInOrder[j])
                subLevelOrder.push_back(levelOrder[i]);
        }
    }
    return subLevelOrder;
}
// This was used for testing.
void printArray(vector<int> array)
{
    for (int i = 0; i < array.size(); i++)
    {
        cout << array[i] << ", ";
    }
    cout << endl;
}
// This function recursively builds a binary tree from an inorder and level order traversal vector
binaryTreeNode *treeFromTraversals(vector<int> inOrder, vector<int> levelOrder)
{
    // Base Case 1: if the Traversals or empty return a null pointer
    if (levelOrder.size() == 0)
    {
        return nullptr;
    }
    // Base Case 2: If the size of the traversal is one return a binary tree node with left and right pointers both null
    else if (levelOrder.size() == 1)
    {
        return new binaryTreeNode(levelOrder.at(0));
    }
    // Recursive Case: Recurse through the traversals to create the tree.
    else
    {
        // Find the index of the first item in the level order in the in order
        int ind = findIndex(inOrder, levelOrder.at(0));
        // create left and right subarrays;
        vector<int> leftSubIn;
        vector<int> rightSubIn;

        for (int i = 0; i < ind; i++)
        {
            leftSubIn.push_back(inOrder[i]);
        }
        for (int j = ind + 1; j < inOrder.size(); j++)
        {
            rightSubIn.push_back(inOrder[j]);
        }

        vector<int> leftSubLevel;
        vector<int> rightSubLevel;

        leftSubLevel = createSubLevelOrder(leftSubIn, levelOrder);
        rightSubLevel = createSubLevelOrder(rightSubIn, levelOrder);

        // cout << "LeftSubIn: ";
        // printArray(leftSubIn);

        // cout << "RightSubIn: ";
        // printArray(rightSubIn);

        // cout << "LeftSubLevel: ";
        // printArray(leftSubLevel);

        // cout << "RightSubLevel: ";
        // printArray(rightSubLevel);

        // Create a binary tree node pointer with the value of the current level ordr zero index that points to a tree created by the same function with the left
        // and right subarrays. Will recurse until a base case is reached
        binaryTreeNode *root = new binaryTreeNode(levelOrder[0], treeFromTraversals(leftSubIn, leftSubLevel), treeFromTraversals(rightSubIn, rightSubLevel));

        return root;
    }
}

int main(int argc, char *argv[])
{
    // create all file streams to input from the three input files
    ifstream inOrderInput(argv[1]);
    ifstream levelOrderInput(argv[2]);
    ifstream encodedInput(argv[3]);

    // create the data structures to which I will store the traversals and encoded message
    vector<int> inOrder, encode, levelOrder;

    // make an integer to input to and then push to each vector
    int inputInt;
    // read in each file to the respective data structure.
    while (1)
    {
        inOrderInput >> inputInt;
        if (inOrderInput.eof())
            break;
        inOrder.push_back(inputInt);
    }

    while (1)
    {
        levelOrderInput >> inputInt;
        if (levelOrderInput.eof())
            break;
        levelOrder.push_back(inputInt);
    }

    // Create the tree
    binaryTreeNode *root = treeFromTraversals(inOrder, levelOrder);

    // Create the string to which we will add the decoding
    string decoded = "";
    // This character will allow me to read a string of 1s and 0s one by one
    char currEncoded;

    // This is my iterator tree
    binaryTreeNode *temp = root;

    // According to Huffman Coding walk through the tree. According to the project instructions and the ASCI character table, the internal nodes of the tree will be
    // less than 128, therefore if the value of the current node according to Huffman Code Traversal is less than 128, it is a leaf node and therefore the character
    // corresponding to that ASCII character should be added to the decoded string.

    // According to Huffman Coding, 1 means move right and 0 means move left
    while (1)
    {
        encodedInput >> currEncoded;
        if (encodedInput.eof())
            break;
        if (currEncoded == '1')
        {
            temp = temp->right;
        }
        else if (currEncoded == '0')
        {
            temp = temp->left;
        }
        if (temp->value < 128)
        {
            decoded = decoded + char(temp->value);
            temp = root;
        }
    }

    cout << decoded;

    return 0;
}
