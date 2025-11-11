/*  

Question#4: Search for the value defined by the user in the tree. If the value does not
exist insert it and print the new tree.

*/
#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST
{
public:
    Node *root;

    BST() : root(nullptr) {}

    // Combined Search and Conditional Insert - Recursive
    // 'inserted' flag is passed by reference to check if the new node was created.
    Node *searchOrInsert(Node *current, int val, bool &inserted)
    {
        if (current == nullptr)
        {
            inserted = true;
            return new Node(val);
        }

        if (val < current->data)
        {
            current->left = searchOrInsert(current->left, val, inserted);
        }
        else if (val > current->data)
        {
            current->right = searchOrInsert(current->right, val, inserted);
        }
        // If val == current->data, the node is found, and 'inserted' remains false.

        return current;
    }

    // In-Order Traversal - Recursive
    void inOrder(Node *current)
    {
        if (current != nullptr)
        {
            inOrder(current->left);
            cout << current->data << " ";
            inOrder(current->right);
        }
    }
};

void printTreeStatus(BST &tree, int key, bool inserted)
{
    cout << "\nOperation for value " << key << ":\n";
    if (inserted)
    {
        cout << " -> Value NOT found. Inserted successfully.\n";
    }
    else
    {
        cout << " -> Value found. Insertion skipped.\n";
    }
    cout << "Current Tree (In-Order): ";
    tree.inOrder(tree.root);
    cout << "\n";
}

int main()
{
    BST tree;
    bool insertedFlag = false;

    // Initial Tree Construction
    tree.root = tree.searchOrInsert(tree.root, 50, insertedFlag);
    tree.root = tree.searchOrInsert(tree.root, 30, insertedFlag);
    tree.root = tree.searchOrInsert(tree.root, 70, insertedFlag);

    // Initial Status
    cout << "Initial Tree:\n";
    tree.inOrder(tree.root);
    cout << "\n";

    // --- Test Case 1: Value does NOT exist (Insert 40) ---
    int val1 = 40;
    insertedFlag = false;
    tree.root = tree.searchOrInsert(tree.root, val1, insertedFlag);
    printTreeStatus(tree, val1, insertedFlag);

    // --- Test Case 2: Value DOES exist (Search 50) ---
    int val2 = 50;
    insertedFlag = false;
    tree.root = tree.searchOrInsert(tree.root, val2, insertedFlag);
    printTreeStatus(tree, val2, insertedFlag);

    // --- Test Case 3: Another value does NOT exist (Insert 10) ---
    int val3 = 10;
    insertedFlag = false;
    tree.root = tree.searchOrInsert(tree.root, val3, insertedFlag);
    printTreeStatus(tree, val3, insertedFlag);

    return 0;
}
