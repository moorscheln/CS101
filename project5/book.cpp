#include <iostream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <list>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// This constant can be avoided by explicitly
// calculating height of Huffman Tree
#define MAX_TREE_HT 256

// A Huffman tree node
struct MinHeapNode
{

    // One of the input characters
    // int data;
    // Frequency of the character
    int freq;

    // Left and right child of this node
    struct MinHeapNode *left, *right;

    // char printFreq()
    // {
    //     char c = (char)freq;
    //     return c;
    // }
};

// A Min Heap: Collection of
// min-heap (or Huffman tree) nodes
struct MinHeap
{

    // Current size of min heap
    int size;

    // capacity of min heap
    int capacity;

    // Array of minheap node pointers
    struct MinHeapNode **array;
};

// A utility function allocate a new
// min heap node with given character
// and frequency of the character
struct MinHeapNode *newNode(int silly)
{
    struct MinHeapNode *temp = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));

    temp->left = temp->right = NULL;
    temp->freq = silly;
    // temp->data = data;

    return temp;
}

// A utility function to create
// a min heap of given capacity
struct MinHeap *createMinHeap(int capacity)

{

    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));

    // current size is 0
    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array = (struct MinHeapNode **)malloc(minHeap->capacity * sizeof(struct MinHeapNode *));
    return minHeap;
}

// A utility function to
// swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode **a,
                     struct MinHeapNode **b)

{

    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

// The standard minHeapify function.
void minHeapify(struct MinHeap *minHeap, int idx)

{

    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
    {

        smallest = left;
    }

    if ((right < minHeap->size) && (minHeap->array[right]->freq < minHeap->array[smallest]->freq))
    {
        smallest = right;
    }

    if (smallest != idx)
    {

        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// A utility function to check
// if size of heap is 1 or not
int isSizeOne(struct MinHeap *minHeap)
{

    return (minHeap->size == 1);
}

// A standard function to extract
// minimum value node from heap
struct MinHeapNode *extractMin(struct MinHeap *minHeap)

{

    struct MinHeapNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

// A utility function to insert
// a new node to Min Heap
void insertMinHeap(struct MinHeap *minHeap,
                   struct MinHeapNode *minHeapNode)

{

    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
    {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

// A standard function to build min heap
void buildMinHeap(struct MinHeap *minHeap)

{

    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

int tree_height(MinHeapNode *root)
{
    // Get the height of the tree
    if (!root)
        return 0;
    else
    {
        // Find the height of both subtrees
        // and use the larger one
        int left_height = tree_height(root->left);
        int right_height = tree_height(root->right);
        if (left_height >= right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}

void print_level(MinHeapNode *root, int level_no)
{
    // Prints the nodes in the tree
    // having a level = level_no

    // We have a auxiliary root node
    // for printing the root of every
    // subtree
    if (!root)
        return;
    if (level_no == 0)
    {
        // We are at the top of a subtree
        // So print the auxiliary root node
        cout << root->freq;
    }
    else
    {
        // Make the auxiliary root node to
        // be the left and right nodes for
        // the subtrees and decrease level by 1, since
        // you are moving from top to bottom
        print_level(root->left, level_no - 1);
        print_level(root->right, level_no - 1);
    }
}

void print_tree_level_order(MinHeapNode *root)
{
    if (!root)
        return;
    int height = tree_height(root);
    for (int i = 0; i < height; i++)
    {
        cout << "Level " << i << ":";
        print_level(root, i);
        cout << endl;
    }
    cout << endl
         << "-----Complete Level Order Traversal:-----" << endl;
    for (int i = 0; i < height; i++)
    {
        print_level(root, i);
    }
    cout << endl;
}

// A utility function to print an array of size n
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        cout << arr[i];

    cout << "\n";
}

// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode *root)

{

    return !(root->left) && !(root->right);
}

// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
struct MinHeap *createAndBuildMinHeap(int freq[], int size)

{
    // for (int i = 0; i < 5; i++) {
    //     if (freq[i] > 0) {

    //     }
    // }
    struct MinHeap *minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
    {
        minHeap->array[i] = newNode(i);
    }

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

// The main function that builds Huffman tree
struct MinHeapNode *buildHuffmanTree(int freq[], int size)

{
    struct MinHeapNode *left, *right, *top;

    // Step 1: Create a min heap of capacity
    // equal to size. Initially, there are
    // modes equal to size.

    struct MinHeap *minHeap = createAndBuildMinHeap(freq, size);

    // Iterate while size of heap doesn't become 1
    while (!isSizeOne(minHeap))
    {

        // Step 2: Extract the two minimum
        // freq items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Step 3: Create a new internal
        // node with frequency equal to the
        // sum of the two nodes frequencies.
        // Make the two extracted node as
        // left and right children of this new node.
        // Add this node to the min heap
        // '$' is a special value for internal nodes, not used
        top = newNode(left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    // Step 4: The remaining node is the
    // root node and the tree is complete.
    return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void printCodes(struct MinHeapNode *root, int arr[], int top)

{

    // Assign 0 to left edge and recur
    if (root->left)
    {

        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (root->right)
    {

        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // If this is a leaf node, then
    // it contains one of the input
    // characters, print the character
    // and its code from arr[]
    if (isLeaf(root))
    {
        cout << char(root->freq) << ": ";
        printArr(arr, top);
    }
}
void printInorder(MinHeapNode *node)
{

    if (node == NULL)
    {
        return;
    }
    printInorder(node->left);
    cout << node->freq << " ";
    printInorder(node->right);
}

// The main function that builds a
// Huffman Tree and print codes by traversing
// the built Huffman Tree
void HuffmanCodes(int freq[], int size)
{
    // Construct Huffman Tree
    struct MinHeapNode *root = buildHuffmanTree(freq, size);

    // Print Huffman codes using
    // the Huffman tree built above
    int arr[MAX_TREE_HT], top = 0;

    printCodes(root, arr, top);
    cout << endl;
    cout << "InOrder" << endl;
    printInorder(root);
    cout << endl
         << endl;
    print_tree_level_order(root);
}

// Driver code
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

    char arr[128];
    int arrFreq[128];
    for (int i = 0; i < 128; i++)
    {
        arr[i] = char(i);
        arrFreq[i] = 0;
    }
    int b = 0;
    int g = 0;
    int count = 0;
    string line, token;
    int inputToken = 0;
    while (getline(levelorder, line))
    {
        istringstream issLevelorder(line);
        cout << line << endl;
        for (g = 0; g < line.size(); g++)
        {
            // cout << line[g] << endl;
            arrFreq[int(line[g])]++;
        }
    }
    for (int i = 0; i < 128; i++)
    {

        if (arrFreq[i] > 0)
        {
            cout << arr[i] << " | " << arrFreq[i] << endl;
            count++;
        }
    }
    // int freq[511];

    int size = sizeof(arr) / sizeof(arr[0]);
    cout << size << endl;

    HuffmanCodes(arrFreq, size);
    int fileS;

    // for (int i = 0; i < fileS; i++)
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

    return 0;
}