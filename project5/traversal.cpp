/**
    Code for https://journaldev.com
    File Name: level_order.c
    Purpose: Find the Level Order Traversal of a Binary Tree

    @author Vijay Ramachandran
    @date 28/01/2020
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

// Define the Tree Node here
struct Node
{
    int value;
    // Pointers to the left and right children
    Node *left, *right;
};

Node *init_tree(int data)
{
    // Creates the tree and returns the
    // root node
    Node *root = (Node *)malloc(sizeof(Node));
    root->left = root->right = NULL;
    root->value = data;
    return root;
}

Node *create_node(int data)
{
    // Creates a new node
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = data;
    node->left = node->right = NULL;
    return node;
}

void free_tree(Node *root)
{
    // Deallocates memory corresponding
    // to every node in the tree.
    Node *temp = root;
    if (!temp)
        return;
    free_tree(temp->left);
    free_tree(temp->right);
    if (!temp->left && !temp->right)
    {
        free(temp);
        return;
    }
}

int tree_height(Node *root)
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

void print_level(Node *root, int level_no)
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
        printf("%d -> ", root->value);
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

void print_tree_level_order(Node *root)
{
    if (!root)
        return;
    int height = tree_height(root);
    for (int i = 0; i < height; i++)
    {
        printf("Level %d: ", i);
        print_level(root, i);
        printf("\n");
    }
    printf("\n\n-----Complete Level Order Traversal:-----\n");
    for (int i = 0; i < height; i++)
    {
        print_level(root, i);
    }
    printf("\n");
}

int main()
{
    // Program to demonstrate Level Order Traversal

    // Create the root node having a value of 10
    Node *root = init_tree(10);

    // Insert nodes onto the tree
    root->left = create_node(20);
    root->right = create_node(30);
    root->left->left = create_node(40);
    root->left->right = create_node(50);

    // Level Order Traversal
    print_tree_level_order(root);

    // Free the tree!
    free_tree(root);
    return 0;
}

/*
class CTest
{
public:
    int numberOfCases, successful, failed;
    string testname, alphabet, desiredOutputString, mutations, actualOutputString;
    int *failedNumbers;
    string failedTitles[];
    CTest()
    {
        numberOfCases = 0;
        successful = 0;
        failed = 0;
    }

    void InitializeTest()
    {
        numberOfCases++;
        cout << "Test " << numberOfCases << " Output:" << endl;
        Tree s;
        s.BuildTree(alphabet, mutations);
    }

    void RunTests()
    {
        // Test 1: Test InorderPrint for tree with no rotations
        testname = "InorderPrint on tree with no rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "";
        desiredOutputString = " 10  15  20  25  30  35  40  45  50  55  60  65  70  75  80  85  90  95  100  105  110  115  120  125  130  135  140  145  150  155  160  165  170  175  180  185  190  195  200  205  210  215  220  225  230  235  240  245  250  255  260  265  270  275  280  285  300  305  310 ";
        InitializeTest();
        actualOutputString = s.InorderPrint();
        ProcessResults();

        // Test 2: Test InorderPrintLeaves for tree with no rotations
        testname = "InorderPrintLeaves on tree with no rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "";
        desiredOutputString = " a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z     .  ,  ? ";
        InitializeTest();
        actualOutputString = s.InorderPrintLeafLetters();
        ProcessResults();

        // Test 3: Test InorderPrint for tree with non-root rotation
        testname = "InorderPrint on tree with non-root rotation";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "265L";
        desiredOutputString = " 10  15  20  25  30  35  40  45  50  55  60  65  70  75  80  85  90  95  100  105  110  115  120  125  130  135  140  145  150  155  160  165  170  175  180  185  190  195  200  205  210  215  220  225  230  235  240  245  250  255  260  265  270  275  280  285  300  305  310 ";
        InitializeTest();
        actualOutputString = s.InorderPrint();
        ProcessResults();

        // Test 4: Test InorderPrintLeaves for tree with non-root rotation
        testname = "InorderPrintLeaves on tree with non-root rotation";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "265L";
        desiredOutputString = " a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z     .  ,  ? ";
        InitializeTest();
        actualOutputString = s.InorderPrintLeafLetters();
        ProcessResults();

        // Test 5: Test InorderPrint for tree with root rotation
        testname = "InorderPrint on tree with root rotation";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "165R";
        desiredOutputString = " 10  15  20  25  30  35  40  45  50  55  60  65  70  75  80  85  90  95  100  105  110  115  120  125  130  135  140  145  150  155  160  165  170  175  180  185  190  195  200  205  210  215  220  225  230  235  240  245  250  255  260  265  270  275  280  285  300  305  310 ";
        InitializeTest();
        actualOutputString = s.InorderPrint();
        ProcessResults();

        // Test 6: Test InorderPrintLeaves for tree with root rotations
        testname = "InorderPrintLeaves on tree with root rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "165R";
        desiredOutputString = " a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z     .  ,  ? ";
        InitializeTest();
        actualOutputString = s.InorderPrintLeafLetters();
        ProcessResults();

        // Test 7: Test GetCode for tree without rotations
        testname = "GetCode on tree with root rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "";
        desiredOutputString = "11011";
        InitializeTest();
        actualOutputString = s.GetCode(".");
        cout << actualOutputString;
        ProcessResults();

        // Test 8: Test GetCode for tree with non-root rotation
        testname = "GetCode on tree with root rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "265L";
        desiredOutputString = "1101";
        InitializeTest();
        actualOutputString = s.GetCode(".");
        cout << actualOutputString;
        ProcessResults();

        // Test 9: Test GetCode for tree with root rotation
        testname = "GetCode on tree with root rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "165R";
        desiredOutputString = "111011";
        InitializeTest();
        actualOutputString = s.GetCode(".");
        cout << actualOutputString;
        ProcessResults();

        // Test 10: Encode enitre alphabet for tree with no rotations
        testname = "Encode alphabet on tree with no rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "";
        desiredOutputString = "0000000001000100001100100001010011000111010000100101010010110110001101011100111110000100011001010011101001010110110101111100011001110101101111101111";
        InitializeTest();
        actualOutputString = s.Encode(alphabet);
        cout << actualOutputString;
        ProcessResults();

        // Test 11: Decode enitre alphabet for tree with no rotations
        testname = "Decode alphabet on tree with no rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "";
        desiredOutputString = "abcdefghijklmnopqrstuvwxyz .,?";
        InitializeTest();
        actualOutputString = s.Decode("0000000001000100001100100001010011000111010000100101010010110110001101011100111110000100011001010011101001010110110101111100011001110101101111101111");
        cout << actualOutputString;
        ProcessResults();

        // Test 12: Encode and decode alphabet for tree with no rotations
        testname = "Encode and decode alphabet on tree with no rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "";
        desiredOutputString = "abcdefghijklmnopqrstuvwxyz .,?";
        InitializeTest();
        actualOutputString = s.Decode(s.Encode(alphabet));
        cout << actualOutputString;
        ProcessResults();

        // Test 13: Encode phrase with entire alphabet for tree with no rotations
        testname = "Encode phrase with entire alphabet on tree with no rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "";
        desiredOutputString = "0000001011010111101001011001001001110011001001000110010111111010100111000111000111011010100110011100100110101000010100010000001001010110100000110001011101011001101110100010101110101111101001001101000110001111100101101001110101010010010001110101001100111001001101001011000001100111000110100001101110001101101111010";
        InitializeTest();
        actualOutputString = s.Encode("all letters? try, the quick brown fox jumps over the lazy dog. ");
        cout << actualOutputString;
        ProcessResults();

        // Test 14: Decode enitre phrase with entire alphabet for tree with no rotations
        testname = "Decode phrase with entire alphabet on tree with no rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "";
        desiredOutputString = "all letters? try, the quick brown fox jumps over the lazy dog. ";
        InitializeTest();
        actualOutputString = s.Decode("0000001011010111101001011001001001110011001001000110010111111010100111000111000111011010100110011100100110101000010100010000001001010110100000110001011101011001101110100010101110101111101001001101000110001111100101101001110101010010010001110101001100111001001101001011000001100111000110100001101110001101101111010");
        cout << actualOutputString;
        ProcessResults();

        // Test 15: Encode and decode phrase with entire alphabet for tree with no rotations
        testname = "Encode and decode phrase with entire alphabet on tree with no rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "";
        desiredOutputString = "all letters? try, the quick brown fox jumps over the lazy dog. ";
        InitializeTest();
        actualOutputString = s.Decode(s.Encode("all letters? try, the quick brown fox jumps over the lazy dog. "));
        cout << actualOutputString;
        ProcessResults();

        // Test 16: Encode enitre alphabet for tree with rotation
        testname = "Encode alphabet on tree with rotation";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "265L";
        desiredOutputString = "00000000010001000011001000010100110001110100001001010100101101100011010111001111100001000110010100111010010101101101011111000011000111001110111101111";
        InitializeTest();
        actualOutputString = s.Encode(alphabet);
        cout << actualOutputString;
        ProcessResults();

        // Test 17: Decode enitre alphabet for tree with rotation
        testname = "Decode alphabet on tree with rotation";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "265L";
        desiredOutputString = "abcdefghijklmnopqrstuvwxyz .,?";
        InitializeTest();
        actualOutputString = s.Decode("00000000010001000011001000010100110001110100001001010100101101100011010111001111100001000110010100111010010101101101011111000011000111001110111101111");
        cout << actualOutputString;
        ProcessResults();

        // Test 18: Encode and decode alphabet for tree with rotation
        testname = "Encode and decode alphabet on tree with rotation";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "265L";
        desiredOutputString = "abcdefghijklmnopqrstuvwxyz .,?";
        InitializeTest();
        actualOutputString = s.Decode(s.Encode(alphabet));
        cout << actualOutputString;
        ProcessResults();

        // Test 19: Encode phrase with entire alphabet for tree with rotation
        testname = "Encode phrase with entire alphabet on tree with rotation";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "265L";
        desiredOutputString = "000000101101011110010101100100100111001100100100011001011111100110011100011100001110110011001100111001001100110000101000100000010010101100100001100010111010110011011100100101011101011111001010011010001100011111001011001011101010100100100011100110011001110010011001010110000011000111000011001000110111000110110111001";
        InitializeTest();
        actualOutputString = s.Encode("all letters? try, the quick brown fox jumps over the lazy dog. ");
        cout << actualOutputString;
        ProcessResults();

        // Test 20: Decode enitre phrase with entire alphabet for tree with rotation
        testname = "Decode phrase with entire alphabet on tree with rotation";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "265L";
        desiredOutputString = "all letters? try, the quick brown fox jumps over the lazy dog. ";
        InitializeTest();
        actualOutputString = s.Decode("000000101101011110010101100100100111001100100100011001011111100110011100011100001110110011001100111001001100110000101000100000010010101100100001100010111010110011011100100101011101011111001010011010001100011111001011001011101010100100100011100110011001110010011001010110000011000111000011001000110111000110110111001");
        cout << actualOutputString;
        ProcessResults();

        // Test 21: Encode and decode phrase with entire alphabet for tree with rotation
        testname = "Encode and decode phrase with entire alphabet on tree with rotation";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "265L";
        desiredOutputString = "all letters? try, the quick brown fox jumps over the lazy dog. ";
        InitializeTest();
        actualOutputString = s.Decode(s.Encode("all letters? try, the quick brown fox jumps over the lazy dog. "));
        cout << actualOutputString;
        ProcessResults();

        // Test 22: Encode enitre alphabet for tree with rotations on non-existent nodes
        testname = "Encode alphabet on tree with rotations on non-existent nodes";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "064R";
        desiredOutputString = "0000000001000100001100100001010011000111010000100101010010110110001101011100111110000100011001010011101001010110110101111100011001110101101111101111";
        InitializeTest();
        actualOutputString = s.Encode(alphabet);
        cout << actualOutputString;
        ProcessResults();

        // Test 23: Decode enitre alphabet for tree with rotations on non-existent nodes
        testname = "Decode alphabet on tree with rotations on non-existent nodes";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "064R";
        desiredOutputString = "abcdefghijklmnopqrstuvwxyz .,?";
        InitializeTest();
        actualOutputString = s.Decode("0000000001000100001100100001010011000111010000100101010010110110001101011100111110000100011001010011101001010110110101111100011001110101101111101111");
        cout << actualOutputString;
        ProcessResults();

        // Test 24: Encode and decode alphabet for tree with rotations on non-existent nodes
        testname = "Encode and decode alphabet on tree with rotations on non-existent nodes";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "064R";
        desiredOutputString = "abcdefghijklmnopqrstuvwxyz .,?";
        InitializeTest();
        actualOutputString = s.Decode(s.Encode(alphabet));
        cout << actualOutputString;
        ProcessResults();

        // Test 25: Encode phrase with entire alphabet for tree with rotations on non-existent nodes
        testname = "Encode phrase with entire alphabet on tree with rotations on non-existent nodes";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "064R";
        desiredOutputString = "0000001011010111101001011001001001110011001001000110010111111010100111000111000111011010100110011100100110101000010100010000001001010110100000110001011101011001101110100010101110101111101001001101000110001111100101101001110101010010010001110101001100111001001101001011000001100111000110100001101110001101101111010";
        InitializeTest();
        actualOutputString = s.Encode("all letters? try, the quick brown fox jumps over the lazy dog. ");
        cout << actualOutputString;
        ProcessResults();

        // Test 26: Decode enitre phrase with entire alphabet for tree with rotations on non-existent nodes
        testname = "Decode phrase with entire alphabet on tree with rotations on non-existent nodes";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "064R";
        desiredOutputString = "all letters? try, the quick brown fox jumps over the lazy dog. ";
        InitializeTest();
        actualOutputString = s.Decode("0000001011010111101001011001001001110011001001000110010111111010100111000111000111011010100110011100100110101000010100010000001001010110100000110001011101011001101110100010101110101111101001001101000110001111100101101001110101010010010001110101001100111001001101001011000001100111000110100001101110001101101111010");
        cout << actualOutputString;
        ProcessResults();

        // Test 27: Encode and decode phrase with entire alphabet for tree with rotations on non-existent nodes
        testname = "Encode and decode phrase with entire alphabet on tree with rotations on non-existent nodes";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "064R";
        desiredOutputString = "all letters? try, the quick brown fox jumps over the lazy dog. ";
        InitializeTest();
        actualOutputString = s.Decode(s.Encode("all letters? try, the quick brown fox jumps over the lazy dog. "));
        cout << actualOutputString;
        ProcessResults();

        // Test 28: Encode enitre alphabet for tree with rotation on leaf node
        testname = "Encode alphabet on tree with rotation on leaf node";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "010R";
        desiredOutputString = "0000000001000100001100100001010011000111010000100101010010110110001101011100111110000100011001010011101001010110110101111100011001110101101111101111";
        InitializeTest();
        actualOutputString = s.Encode(alphabet);
        cout << actualOutputString;
        ProcessResults();

        // Test 29: Decode enitre alphabet for tree with rotation on leaf node
        testname = "Decode alphabet on tree with rotation on leaf node";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "010R";
        desiredOutputString = "abcdefghijklmnopqrstuvwxyz .,?";
        InitializeTest();
        actualOutputString = s.Decode("0000000001000100001100100001010011000111010000100101010010110110001101011100111110000100011001010011101001010110110101111100011001110101101111101111");
        cout << actualOutputString;
        ProcessResults();

        // Test 30: Encode and decode alphabet for tree with rotation on leaf node
        testname = "Encode and decode alphabet on tree with rotation on leaf node";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "010R";
        desiredOutputString = "abcdefghijklmnopqrstuvwxyz .,?";
        InitializeTest();
        actualOutputString = s.Decode(s.Encode(alphabet));
        cout << actualOutputString;
        ProcessResults();

        // Test 31: Encode phrase with entire alphabet for tree with rotation on leaf node
        testname = "Encode phrase with entire alphabet on tree with rotation on leaf node";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "010R";
        desiredOutputString = "0000001011010111101001011001001001110011001001000110010111111010100111000111000111011010100110011100100110101000010100010000001001010110100000110001011101011001101110100010101110101111101001001101000110001111100101101001110101010010010001110101001100111001001101001011000001100111000110100001101110001101101111010";
        InitializeTest();
        actualOutputString = s.Encode("all letters? try, the quick brown fox jumps over the lazy dog. ");
        cout << actualOutputString;
        ProcessResults();

        // Test 32: Decode enitre phrase with entire alphabet for tree with rotation on leaf node
        testname = "Decode phrase with entire alphabet on tree with rotation on leaf node";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "010R";
        desiredOutputString = "all letters? try, the quick brown fox jumps over the lazy dog. ";
        InitializeTest();
        actualOutputString = s.Decode("0000001011010111101001011001001001110011001001000110010111111010100111000111000111011010100110011100100110101000010100010000001001010110100000110001011101011001101110100010101110101111101001001101000110001111100101101001110101010010010001110101001100111001001101001011000001100111000110100001101110001101101111010");
        cout << actualOutputString;
        ProcessResults();

        // Test 33: Encode and decode phrase with entire alphabet for tree with rotation on leaf node
        testname = "Encode and decode phrase with entire alphabet on tree with rotation on leaf node";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "010R";
        desiredOutputString = "all letters? try, the quick brown fox jumps over the lazy dog. ";
        InitializeTest();
        actualOutputString = s.Decode(s.Encode("all letters? try, the quick brown fox jumps over the lazy dog. "));
        cout << actualOutputString;
        ProcessResults();

        // Test 34: Encode enitre alphabet for tree with rotation on root node
        testname = "Encode alphabet on tree with rotation on root node";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "165R";
        desiredOutputString = "0000000100100011010001010110011110000100011001010011101001010110110101111100001100011100101100111101001101011101101101111110001110011110101110111111011111";
        InitializeTest();
        actualOutputString = s.Encode(alphabet);
        cout << actualOutputString;
        ProcessResults();

        // Test 35: Decode enitre alphabet for tree with rotation on root node
        testname = "Decode alphabet on tree with rotation on root node";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "165R";
        desiredOutputString = "abcdefghijklmnopqrstuvwxyz .,?";
        InitializeTest();
        actualOutputString = s.Decode("0000000100100011010001010110011110000100011001010011101001010110110101111100001100011100101100111101001101011101101101111110001110011110101110111111011111");
        cout << actualOutputString;
        ProcessResults();

        // Test 36: Encode and decode alphabet for tree with rotation on root node
        testname = "Encode and decode alphabet on tree with rotation on root node";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "165R";
        desiredOutputString = "abcdefghijklmnopqrstuvwxyz .,?";
        InitializeTest();
        actualOutputString = s.Decode(s.Encode(alphabet));
        cout << actualOutputString;
        ProcessResults();

        // Test 37: Encode phrase with entire alphabet for tree with rotation on root node
        testname = "Encode phrase with entire alphabet on tree with rotation on root node";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "165R";
        desiredOutputString = "0000100111001111101010011010011001111001101001100011100101111111101011001111000111100011110111010110011011101001110101100001101001000000101001011101000011100011011011011010101111010010110110110111111010100011101001010010111110010111010101101101010100110001111010110011011101001110101001100001110011110001110100011101100110111011111010";
        InitializeTest();
        actualOutputString = s.Encode("all letters? try, the quick brown fox jumps over the lazy dog. ");
        cout << actualOutputString;
        ProcessResults();

        // Test 38: Decode enitre phrase with entire alphabet for tree with rotation on root node
        testname = "Decode phrase with entire alphabet on tree with rotation on root node";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "165R";
        desiredOutputString = "all letters? try, the quick brown fox jumps over the lazy dog. ";
        InitializeTest();
        actualOutputString = s.Decode("0000100111001111101010011010011001111001101001100011100101111111101011001111000111100011110111010110011011101001110101100001101001000000101001011101000011100011011011011010101111010010110110110111111010100011101001010010111110010111010101101101010100110001111010110011011101001110101001100001110011110001110100011101100110111011111010");
        cout << actualOutputString;
        ProcessResults();

        // Test 39: Encode and decode phrase with entire alphabet for tree with rotation on root node
        testname = "Encode and decode phrase with entire alphabet on tree with rotation on root node";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "165R";
        desiredOutputString = "all letters? try, the quick brown fox jumps over the lazy dog. ";
        InitializeTest();
        actualOutputString = s.Decode(s.Encode("all letters? try, the quick brown fox jumps over the lazy dog. "));
        cout << actualOutputString;
        ProcessResults();

        // Test 40: Encode enitre alphabet for tree with all types of rotations
        testname = "Encode alphabet on tree with all types of rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "065R023L310R025L165R";
        desiredOutputString = "000000000100010010100110011100111110000100011001010011101001010110110101111100001100011100101100111101001101011101101101111110001110011110101110111111011111";
        InitializeTest();
        actualOutputString = s.Encode(alphabet);
        cout << actualOutputString;
        ProcessResults();

        // Test 41: Decode enitre alphabet for tree with all types of rotations
        testname = "Decode alphabet on tree with all types of rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "065R023L310R025L165R";
        desiredOutputString = "abcdefghijklmnopqrstuvwxyz .,?";
        InitializeTest();
        actualOutputString = s.Decode("000000000100010010100110011100111110000100011001010011101001010110110101111100001100011100101100111101001101011101101101111110001110011110101110111111011111");
        cout << actualOutputString;
        ProcessResults();

        // Test 42: Encode and decode alphabet for tree with all types of rotations
        testname = "Encode and decode alphabet on tree with all types of rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "065R023L310R025L165R";
        desiredOutputString = "abcdefghijklmnopqrstuvwxyz .,?";
        InitializeTest();
        actualOutputString = s.Decode(s.Encode(alphabet));
        cout << actualOutputString;
        ProcessResults();

        // Test 43: Encode phrase with entire alphabet for tree with all types of rotations
        testname = "Encode phrase with entire alphabet on tree with all types of rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "065R023L310R025L165R";
        desiredOutputString = "0000010011100111110101001101011001111001101011000111001011111111010110011110001111000111101110101100110111101011101011000011010010000000110010111010000011100011011011011010101111010011010110110111111010100011101001010010111110010111010101101101010101100011110101100110111101011101010011000001110011110001110100011011001110111011111010";
        InitializeTest();
        actualOutputString = s.Encode("all letters? try, the quick brown fox jumps over the lazy dog. ");
        cout << actualOutputString;
        ProcessResults();

        // Test 44: Decode enitre phrase with entire alphabet for tree with all types of rotations
        testname = "Decode phrase with entire alphabet on tree with all types of rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "065R023L310R025L165R";
        desiredOutputString = "all letters? try, the quick brown fox jumps over the lazy dog. ";
        InitializeTest();
        actualOutputString = s.Decode("0000010011100111110101001101011001111001101011000111001011111111010110011110001111000111101110101100110111101011101011000011010010000000110010111010000011100011011011011010101111010011010110110111111010100011101001010010111110010111010101101101010101100011110101100110111101011101010011000001110011110001110100011011001110111011111010");
        cout << actualOutputString;
        ProcessResults();

        // Test 45: Encode and decode phrase with entire alphabet for tree with all types of rotations
        testname = "Encode and decode phrase with entire alphabet on tree with all types of rotations";
        alphabet = "abcdefghijklmnopqrstuvwxyz .,?";
        mutations = "065R023L310R025L165R";
        desiredOutputString = "all letters? try, the quick brown fox jumps over the lazy dog. ";
        InitializeTest();
        actualOutputString = s.Decode(s.Encode("all letters? try, the quick brown fox jumps over the lazy dog. "));
        cout << actualOutputString;
        ProcessResults();

        GetTestResults();
    }

    // Takes care of test statistics bookkeeping and prints results of individual test
    void ProcessResults()
    {
        cout << endl;
        if (desiredOutputString.compare(actualOutputString) == 0)
        {
            cout << "Test ";
            cout << numberOfCases;
            cout << ": \"";
            cout << testname;
            cout << "\" passed.\n\n";
            successful++;
        }
        else
        {
            cout << "Test ";
            cout << numberOfCases;
            cout << ": \"";
            cout << testname;
            cout << "\" failed.\n\n";
            failedNumbers[failed] = numberOfCases;
            failedTitles[failed] = testname;
            failed++;
        }
    }

    // Prints summary of test statistics and if applicable a list of failed tests.
    void GetTestResults()
    {
        cout << "Out of " << numberOfCases << " cases: " << successful << " passed and " << failed << " failed." << endl;
        if (failed > 0)
        {
            cout << endl;
            cout << "Failed Cases:\n";
            for (int i = 0; i < failed; i++)
            {
                cout << failedNumbers[i] << ": " << failedTitles[i] << endl;
            }
        }
        cout << endl;
    }
};

*/