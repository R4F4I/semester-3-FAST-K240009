

/*  
Question#5: Given the root of a binary tree. Check whether these are Binary Search
Tree or not.

      0002
     /	  \
   0001  0003
	    \
	   0005


	      10
       /  \
      5   20
         /  \
        9   25
    

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
private:
    // Helper 1: Checks if ALL nodes in a subtree are LESS than 'rootData'
    // (Ensures all nodes in the left subtree are smaller than the local root)
    bool checkAllLeft(Node *current, int rootData)
    {
        if (current == nullptr)
        {
            return true;
        }
        // Check current node against the higher root limit
        if (current->data >= rootData)
        {
            return false;
        }
        // Recursively check all descendants against the same root limit
        return checkAllLeft(current->left, rootData) && checkAllLeft(current->right, rootData);
    }

    // Helper 2: Checks if ALL nodes in a subtree are GREATER than 'rootData'
    // (Ensures all nodes in the right subtree are larger than the local root)
    bool checkAllRight(Node *current, int rootData)
    {
        if (current == nullptr)
        {
            return true;
        }
        // Check current node against the lower root limit
        if (current->data <= rootData)
        {
            return false;
        }
        // Recursively check all descendants against the same root limit
        return checkAllRight(current->left, rootData) && checkAllRight(current->right, rootData);
    }

public:
    Node *root;

    BST() : root(nullptr) {}

    // Public BST check function using the requested recursive descendant checks
    bool isBST(Node *current)
    {
        if (current == nullptr)
        {
            return true;
        }

        // 1. Check if the entire left subtree (all descendants) adheres to the current root's data
        if (!checkAllLeft(current->left, current->data))
        {
            return false;
        }

        // 2. Check if the entire right subtree (all descendants) adheres to the current root's data
        if (!checkAllRight(current->right, current->data))
        {
            return false;
        }

        // 3. Recursively call isBST on the subtrees themselves to enforce structure at lower levels
        return isBST(current->left) && isBST(current->right);
    }

    // Traversal for Display
    void inOrder(Node *current)
    {
        if (current != nullptr)
        {
            inOrder(current->left);
            cout << current->data << " ";
            inOrder(current->right);
        }
    }

    // Simple recursive insert for demonstration purposes only
    Node *insert(Node *current, int val)
    {
        if (current == nullptr)
        {
            return new Node(val);
        }
        if (val < current->data)
        {
            current->left = insert(current->left, val);
        }
        else if (val > current->data)
        {
            current->right = insert(current->right, val);
        }
        return current;
    }
};

void checkAndPrint(const char *name, BST &tree)
{
    cout << "\n--- Checking Tree: " << name << " ---\n";
    cout << "In-Order Traversal: ";
    tree.inOrder(tree.root);
    cout << "\n";
    if (tree.isBST(tree.root))
    {
        cout << "Result: YES, the tree is a Binary Search Tree.\n";
    }
    else
    {
        cout << "Result: NO, the tree is NOT a Binary Search Tree.\n";
    }
}

int main()
{
    // --- Tree 1 Structure: 2 -> (1, 3 -> 5) ---
    // This structure follows the BST property.
    BST tree1;
    tree1.root = new Node(2);
    tree1.root->left = new Node(1);
    tree1.root->right = new Node(3);
    tree1.root->right->right = new Node(5);
    checkAndPrint("Tree 1: [2, 1, 3, 5]", tree1); // Output: YES

    // --- Tree 2 Structure: 10 -> (5, 20 -> (9, 25)) ---
    // VIOLATION: Node 9 is in the right subtree of 10, but 9 is less than 10.
    // The checkAllRight helper correctly detects this violation against the root 10.
    BST tree2;
    tree2.root = new Node(10);
    tree2.root->left = new Node(5);
    tree2.root->right = new Node(20);
    tree2.root->right->left = new Node(9); // VIOLATION HERE: Must be > 10
    tree2.root->right->right = new Node(25);
    checkAndPrint("Tree 2: [10, 5, 20, 9, 25]", tree2); // Output: NO (correctly detected)

    return 0;
}
