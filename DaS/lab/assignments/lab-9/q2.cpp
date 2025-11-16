/*

Suppose you have an AVL tree with the following elements: 50, 30, 70, 20, 40, 60, 80.
You need to insert a new node with value 55 into the tree and then display the tree after
performing a left rotation on the root. Write a C++ code to accomplish this task using the
AVLTree class and its methods.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

// --- Node Class ---
class node {
public:
    int data, height;
    node *left, *right;

    node(int data) {
        this->data = data;
        height = 1; // A new leaf node has height 1
        left = nullptr;
        right = nullptr;
    }
};

// --- AVLTree Class ---
class AVLTree {
private:
    // --- O(1) Height Getter ---
    // Gets the height from the stored property.
    int height(node *n) {
        if (n == nullptr)
            return 0;
        return n->height;
    }

    // --- O(1) Balance Factor calculation ---
    int bf(node *n) {
        if (n == nullptr)
            return 0;
        return height(n->left) - height(n->right);
    }

    // --- Simple Max Function ---
    int max(int n, int m) {
        return m > n ? m : n;
    }

    // --- Right Rotation ---
    node* rightRotate(node *y) {
        node *x = y->left;
        node *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x; // Return new root
    }

    // --- Left Rotation ---
    node* leftRotate(node *x) {
        node *y = x->right;
        node *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y; // Return new root
    }

    // --- Recursive AVL Insert ---
    node* insertRecursive(node *current, int val) {
        
        // 1. Standard BST Insertion
        if (current == nullptr) {
            return new node(val);
        }

        if (val < current->data) {
            current->left = insertRecursive(current->left, val);
        } else {
            current->right = insertRecursive(current->right, val);
        }

        // 2. Update Height
        current->height = 1 + max(height(current->left), height(current->right));

        // 3. Get Balance Factor
        int balance = bf(current);

        // 4. Rebalance (The 4 cases)
        // Case 1: Left-Left (LL)
        if (balance > 1 && val < current->left->data) {
            return rightRotate(current);
        }

        // Case 2: Right-Right (RR)
        if (balance < -1 && val > current->right->data) {
            return leftRotate(current);
        }

        // Case 3: Left-Right (LR)
        if (balance > 1 && val > current->right->data) {
            current->left = leftRotate(current->left);
            return rightRotate(current);
        }

        // Case 4: Right-Left (RL)
        if (balance < -1 && val < current->right->data) {
            current->right = rightRotate(current->right);
            return leftRotate(current);
        }

        // Return the (unchanged) node pointer
        return current;
    }

    // --- Helper for 2D printing ---
    void printTreeRecursive(node* current, int level) {
        if (current == nullptr) {
            return;
        }
        int indent = 5;
        printTreeRecursive(current->right, level + 1);

        cout << endl;
        for (int i = 0; i < level * indent; i++) {
            cout << " "; // Use spaces for indentation
        }
        cout << current->data << "\n";
        
        printTreeRecursive(current->left, level + 1);
    }

public:
    node *root;

    AVLTree() {
        root = nullptr;
    }

    // --- Public Insert Wrapper ---
    void insert(int val) {
        root = insertRecursive(root, val);
    }

    // --- Public 2D Print Wrapper ---
    void printTreeStyle() {
        printTreeRecursive(root, 0);
        cout << "\n-----------------------------------\n";
    }

    // --- NEW: Method to force left rotation on root ---
    // This function performs the operation you requested.
    void forceLeftRotateRoot() {
        if (root == nullptr || root->right == nullptr) {
            cout << "Cannot perform left rotation on root." << endl;
            return;
        }
        cout << "--- Performing Left Rotation on Root (" << root->data << ") ---" << endl;
        root = leftRotate(root);
    }
};

// --- Main Function ---
int main() {
    AVLTree tree;

    // 1. Build the initial tree
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "--- Initial AVL Tree ---" << endl;
    tree.printTreeStyle();

    // 2. Insert the new node with value 55
    cout << "--- Inserting 55 ---" << endl;
    tree.insert(55);

    cout << "--- Tree After Inserting 55 ---" << endl;
    tree.printTreeStyle();

    // 3. Perform a left rotation on the root, as requested
    tree.forceLeftRotateRoot();

    // 4. Display the final tree
    cout << "--- Final Tree After Left Rotation ---" << endl;
    tree.printTreeStyle();

    return 0;
}