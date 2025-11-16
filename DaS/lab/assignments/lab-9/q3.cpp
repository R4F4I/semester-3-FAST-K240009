/*

Suppose you have an AVL tree with the following nodes: 10, 5, 15, 3, and 7 (in this
order). Perform the following steps:
1. Insert the value 12 into the tree.
2. Calculate the balance factor for each node.
3. Check the height of the tree.
4. If the tree becomes unbalanced during insertion, implement the rotations required to
5. maintain balance.
6. Provide the final balanced AVL tree.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

int max(int n, int m){
return m>n?m:n;
}

// --- Node Class ---
// (Height is initialized to 1, as leaves have height 1)
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

class BST {
public:
    node *root;

    // Correct constructor
    BST() {
        root = nullptr;
    }

    // --- O(1) Height Getter ---
    // Gets the height from the stored property.
    // This is the key to an O(log n) insert.
    int height(node *n) {
        if (n == nullptr)
            return 0;
        return n->height;
    }

    // O(1) Balance Factor calculation
    int bf(node *n) {
        if (n == nullptr)
            return 0;
        return height(n->left) - height(n->right);
    }

    // --- Rotation Functions (Corrected) ---
    // They now update height in O(1) time
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

    // --- Public Insert Function ---
    // This is the "wrapper"
    void insert(int val) {
        root = insertRecursive(root, val);
    }


    // --- Recursive AVL Insert (Corrected) ---
    // This is the function that does all the work.
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
        if (balance > 1 && val > current->left->data) {
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

void printTreeStyle() {
        // Call the helper, starting at the root,
        // with an initial level of 0.
        printTreeRecursive(root, 0);
    }


    void printTreeRecursive(node* current, int level) {
        // 1. Base Case: If the node is null, just return.
        if (current == nullptr) {
            return;
        }

        // 2. Increase indentation level
        // (We add 5 spaces per level for clarity)
        int indent = 5;

        // 3. Recursive Step 1: Print the RIGHT child first
        //    (This will be at the "top" of the visual print)
        printTreeRecursive(current->right, level + 1);

        // 4. Process Root: Print the current node's data
        //    - Print indentation (level * indent spaces)
        for (int i = 0; i < level * indent; i++) {
            std::cout << " ";
        }
        //    - Print the node's data
        std::cout << current->data << "\n";

        // 5. Recursive Step 2: Print the LEFT child
        //    (This will be at the "bottom" of the visual print)
        printTreeRecursive(current->left, level + 1);
    }
};

// --- Main Function ---
int main() {
    BST tree;

    std::cout << "--- Building Initial Tree ---" << std::endl;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    std::cout << "Initial Tree Structure:" << std::endl;
    tree.printTreeStyle();
    
    std::cout << "\n-----------------------------------" << std::endl;
    std::cout << "--- Inserting 12 ---" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    tree.insert(12);

    std::cout << "Final Tree Structure:" << std::endl;
    tree.printTreeStyle();

    std::cout << "\n\nFinal Tree Height: " << tree.height(tree.root) << std::endl;

    return 0;
}