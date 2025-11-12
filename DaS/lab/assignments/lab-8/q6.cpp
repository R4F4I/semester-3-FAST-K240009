/*

Question#6: Suppose you are working on a project for a small online retailer that needs
to keep track of their inventory using a binary search tree. The retailer’s inventory
consists of a unique product ID and its corresponding quantity in stock. Write a C++
class for the binary search tree and add the required functionalities to insert new
products into the tree, update the quantity of existing products, and search for products
by their ID.
Additionally, the retailer would like to keep track of the product with the highest quantity
in
stock. Implement a function that returns the ID of this product, along with its quantity.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/


#include <iostream>

using namespace std;

// Product structure (Data payload)
struct Product {
    int id;
    int quantity;
};

// Node structure (stores data and pointers)
struct Node {
    Product product;
    Node* left;
    Node* right;

    Node(const Product& data) : product(data), left(nullptr), right(nullptr) {}
};

// Structure to hold the result of the max stock search
struct MaxStockResult {
    int id;
    int quantity;
};

class BST {
private:
    // Helper function to find the product with max quantity recursively
    // This traverses ALL nodes, as the max quantity might not be at the root or rightmost node
    MaxStockResult findMaxStockRecursive(Node* current) {
        // Base case: If the node is null, return an invalid result (id=-1, quantity=-1)
        if (current == nullptr) {
            MaxStockResult invalid = {-1, -1};
            return invalid;
        }

        // Initialize max result with the current node's data
        MaxStockResult maxResult = {current->product.id, current->product.quantity};

        // Recursively check the left subtree
        MaxStockResult leftMax = findMaxStockRecursive(current->left);
        if (leftMax.quantity > maxResult.quantity) {
            maxResult = leftMax;
        }

        // Recursively check the right subtree
        MaxStockResult rightMax = findMaxStockRecursive(current->right);
        if (rightMax.quantity > maxResult.quantity) {
            maxResult = rightMax;
        }

        return maxResult;
    }

public:
    Node* root;

    BST() : root(nullptr) {}

    // Recursive Insert (Ordered by Product ID)
    Node* insert(Node* current, const Product& data) {
        if (current == nullptr) {
            return new Node(data);
        }
        if (data.id < current->product.id) {
            current->left = insert(current->left, data);
        } else if (data.id > current->product.id) {
            current->right = insert(current->right, data);
        }
        return current;
    }

    // Function to return the ID and quantity of the product with maximum stock
    MaxStockResult findMaxStock() {
        return findMaxStockRecursive(root);
    }
    
    // Traversal for Display
    void inOrder(Node* current) {
        if (current != nullptr) {
            inOrder(current->left);
            cout << "ID: " << current->product.id << ", Qty: " << current->product.quantity << "\n";
            inOrder(current->right);
        }
    }
};

int main() {
    BST inventory;

    // Insert products into the BST (ordered by ID)
    inventory.root = inventory.insert(inventory.root, {101, 50});
    inventory.root = inventory.insert(inventory.root, {105, 120}); // Max Stock
    inventory.root = inventory.insert(inventory.root, {103, 75});
    inventory.root = inventory.insert(inventory.root, {100, 30});
    inventory.root = inventory.insert(inventory.root, {102, 12});
    inventory.root = inventory.insert(inventory.root, {104, 119});

    cout << "--- Current Inventory (Ordered by Product ID) ---\n";
    inventory.inOrder(inventory.root);

    // Find the product with max stock
    MaxStockResult maxProduct = inventory.findMaxStock();

    cout << "\n--- Max Stock Product ---\n";
    if (maxProduct.id != -1) {
        cout << "Product ID: " << maxProduct.id << "\n";
        cout << "Quantity: " << maxProduct.quantity << "\n";
    } else {
        cout << "Inventory is empty.\n";
    }

    return 0;
}