/*

Find the kth smallest and largest value in the AVL tree and print its key also print both
the left side and right side height of the tree starting from root.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/


#include <iostream>

using namespace std;

class node {
public:
    int data, height;
    node *left, *right;

    node(int data) {
        this->data = data;
        height = 1; // Leaf nodes have height 1
        left = nullptr;
        right = nullptr;
    }
};

class BST {
public:
    node *root;

    BST() {
        root = nullptr;
    }

private:
    // --- O(1) Height Getter ---
    int height(node *n) {
        if (n == nullptr)
            return 0;
        return n->height;
    }

    // --- O(1) Balance Factor ---
    int bf(node *n) {
        if (n == nullptr)
            return 0;
        return height(n->left) - height(n->right);
    }

    // --- User-specified max function ---
    int max(int n, int m) {
        return m > n ? m : n;
    }

    // --- Rotation Functions (using your max) ---
    node* rightRotate(node *y) {
        node *x = y->left;
        node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }

    node* leftRotate(node *x) {
        node *y = x->right;
        node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    // --- Recursive AVL Insert (using your max) ---
    node* insertRecursive(node *current, int val) {
        if (current == nullptr) {
            return new node(val);
        }

        if (val < current->data) {
            current->left = insertRecursive(current->left, val);
        } else {
            current->right = insertRecursive(current->right, val);
        }

        current->height = 1 + max(height(current->left), height(current->right));
        int balance = bf(current);

        if (balance > 1 && val < current->left->data)
            return rightRotate(current);
        if (balance < -1 && val > current->right->data)
            return leftRotate(current);
        if (balance > 1 && val > current->left->data) {
            current->left = leftRotate(current->left);
            return rightRotate(current);
        }
        if (balance < -1 && val < current->right->data) {
            current->right = rightRotate(current->right);
            return leftRotate(current);
        }
        return current;
    }

    // --- Helper for 2D print (no setw) ---
    void printTreeRecursive(node* current, int level) {
        if (current == nullptr) {
            return;
        }
        int indent = 5;
        printTreeRecursive(current->right, level + 1);

        std::cout << std::endl;
        for (int i = 0; i < level * indent; i++) {
            std::cout << " "; // Use spaces for indentation
        }
        std::cout << current->data << "(BF:" << bf(current) << ")" << "\n";
        
        printTreeRecursive(current->left, level + 1);
    }

    // --- NEW: Helper for Kth Smallest ---
    // (Uses in-order traversal)
    node* kthSmallestRecursive(node* current, int& k) {
        if (current == nullptr) {
            return nullptr;
        }

        // 1. Go Left
        node* leftResult = kthSmallestRecursive(current->left, k);
        if (leftResult != nullptr) {
            return leftResult; // Found in left subtree
        }

        // 2. Process Root
        k--; // Decrement k
        if (k == 0) {
            return current; // This is the k-th node
        }

        // 3. Go Right
        return kthSmallestRecursive(current->right, k);
    }

    // --- NEW: Helper for Kth Largest ---
    // (Uses reverse in-order traversal)
    node* kthLargestRecursive(node* current, int& k) {
        if (current == nullptr) {
            return nullptr;
        }

        // 1. Go Right
        node* rightResult = kthLargestRecursive(current->right, k);
        if (rightResult != nullptr) {
            return rightResult; // Found in right subtree
        }

        // 2. Process Root
        k--; // Decrement k
        if (k == 0) {
            return current; // This is the k-th node
        }

        // 3. Go Left
        return kthLargestRecursive(current->left, k);
    }

public:
    // --- Public Insert ---
    void insert(int val) {
        root = insertRecursive(root, val);
    }

    // --- Public 2D Print ---
    void printTreeStyle() {
        printTreeRecursive(root, 0);
    }

    // --- NEW: Function to print root's subtree heights ---
    void printRootSubtreeHeights() {
        if (root == nullptr) {
            std::cout << "Tree is empty." << std::endl;
            return;
        }
        std::cout << "Left Subtree Height: " << height(root->left) << std::endl;
        std::cout << "Right Subtree Height: " << height(root->right) << std::endl;
    }

    // --- NEW: Public wrapper for Kth Smallest ---
    void findKthSmallest(int k) {
        if (k <= 0 || root == nullptr) {
            std::cout << "Invalid k or empty tree." << std::endl;
            return;
        }
        int tempK = k; // Use a temp variable since k is passed by reference
        node* result = kthSmallestRecursive(root, tempK);
        if (result == nullptr) {
            std::cout << "k is larger than the number of nodes." << std::endl;
        } else {
            std::cout << "The " << k << "-th smallest key is: " << result->data << std::endl;
        }
    }

    // --- NEW: Public wrapper for Kth Largest ---
    void findKthLargest(int k) {
        if (k <= 0 || root == nullptr) {
            std::cout << "Invalid k or empty tree." << std::endl;
            return;
        }
        int tempK = k;
        node* result = kthLargestRecursive(root, tempK);
        if (result == nullptr) {
            std::cout << "k is larger than the number of nodes." << std::endl;
        } else {
            std::cout << "The " << k << "-th largest key is: " << result->data << std::endl;
        }
    }
};

// --- Main Function ---
int main() {
    BST tree;
    
    // Build the tree from your problem
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);

    std::cout << "--- Final Tree Structure ---" << std::endl;
    tree.printTreeStyle();
    
    std::cout << "\n-----------------------------------" << std::endl;
    std::cout << "--- Root Subtree Heights ---" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    tree.printRootSubtreeHeights(); // Prints left and right heights

    std::cout << "\n-----------------------------------" << std::endl;
    std::cout << "--- Kth Smallest/Largest ---" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    
    // Tree nodes are: 3, 5, 7, 10, 12, 15
    tree.findKthSmallest(1); // 3
    tree.findKthSmallest(3); // 7
    tree.findKthSmallest(6); // 15
    
    std::cout << std::endl;

    tree.findKthLargest(1); // 15
    tree.findKthLargest(2); // 12
    tree.findKthLargest(4); // 7

    return 0;
}