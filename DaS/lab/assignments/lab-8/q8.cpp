/*

Given a Binary Search Tree (BST) and a range [a, b], the task is to count the number of
nodes in the BST that lie in the given range.
Examples:
Input: a= 5, b = 45



    10
   /  \
  5   50
 /   /  \
1   40  100


Output: 3
Explanation: There are three nodes in range [5, 45] = 5, 10 and 40.

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

// Structure to hold the result of the median search
struct MedianResult {
    double median;
    bool valid;
};


class BST {
public:
    // --- Max Stock Logic (Kept as per original file) ---
    MaxStockResult findMaxStockRecursive(Node* current) {
        if (current == nullptr) {
            MaxStockResult invalid = {-1, -1};
            return invalid;
        }
        MaxStockResult maxResult = {current->product.id, current->product.quantity};
        MaxStockResult leftMax = findMaxStockRecursive(current->left);
        if (leftMax.quantity > maxResult.quantity) {
            maxResult = leftMax;
        }
        MaxStockResult rightMax = findMaxStockRecursive(current->right);
        if (rightMax.quantity > maxResult.quantity) {
            maxResult = rightMax;
        }
        return maxResult;
    }

    // --- Median Logic Helpers ---

    // 1. Recursive Node Counter
    int countNodesRecursive(Node* current) {
        if (current == nullptr) {
            return 0;
        }
        return 1 + countNodesRecursive(current->left) + countNodesRecursive(current->right);
    }

    // 2. Recursive In-Order Traversal to find the k-th element
    // Uses references to track the counter and the found result value.
    void findKthRecursive(Node* current, int k, int& count, int& result, bool& found) {
        if (current == nullptr || found) {
            return;
        }

        // 1. Traverse Left (L)
        findKthRecursive(current->left, k, count, result, found);

        // 2. Visit Root (N) - Only if we haven't found the result yet
        if (!found) {
            count++;
            if (count == k) {
                result = current->product.id; // Median is calculated based on the sorted IDs
                found = true;
                return;
            }
        }

        // 3. Traverse Right (R) - Only if we haven't found the result yet
        if (!found) {
            findKthRecursive(current->right, k, count, result, found);
        }
    }

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

    // Public Median Finder
    MedianResult findMedian() {
        int n = countNodesRecursive(root);
        
        if (n == 0) {
            MedianResult invalid = {0.0, false};
            return invalid;
        }

        int count = 0;
        int result1 = 0;
        int result2 = 0;
        bool found = false;
        
        // Odd number of nodes: Median is the element at position (n+1)/2
        if (n % 2 != 0) {
            int k = (n + 1) / 2;
            findKthRecursive(root, k, count, result1, found);
            
            MedianResult r = {(double)result1, true};
            return r;

        // Even number of nodes: Median is the average of elements at positions n/2 and (n/2)+1
        } else {
            int k1 = n / 2;
            int k2 = (n / 2) + 1;

            // Find K1-th element
            findKthRecursive(root, k1, count, result1, found);

            // Reset counter and flag to find the K2-th element
            count = 0;
            found = false; 

            // Find K2-th element
            findKthRecursive(root, k2, count, result2, found);

            double median = (result1 + result2) / 2.0;
            
            MedianResult r = {median, true};
            return r;
        }
    }

    int countNodesRecursive(Node* current) {
        if (current == nullptr) {
            return 0;
        }
        return 1 + countNodesRecursive(current->left) + countNodesRecursive(current->right);
    }
};

int main() {
    BST inventory;

    // Example 1: Odd number of nodes (n=7). Sorted IDs: 100, 101, 102, [103], 104, 105, 106. Median is 103.
    inventory.root = inventory.insert(inventory.root, {101, 50});
    inventory.root = inventory.insert(inventory.root, {105, 120});
    inventory.root = inventory.insert(inventory.root, {103, 75});
    inventory.root = inventory.insert(inventory.root, {100, 30});
    inventory.root = inventory.insert(inventory.root, {102, 12});
    inventory.root = inventory.insert(inventory.root, {104, 119});
    inventory.root = inventory.insert(inventory.root, {106, 80}); 

    cout << "--- Current Inventory (Ordered by Product ID) ---\n";
    inventory.inOrder(inventory.root);
    cout << "\n";

    // Find the product with max stock (from Q5)
    MaxStockResult maxProduct = inventory.findMaxStock();
    cout << "Max Stock Product ID: " << maxProduct.id << ", Quantity: " << maxProduct.quantity << "\n";

    // Find the median (Odd case)
    MedianResult medianResult = inventory.findMedian();
    
    cout << "\n--- Median Product ID (Odd Case) ---\n";
    if (medianResult.valid) {
        cout << "Total Nodes (n): " << inventory.countNodesRecursive(inventory.root) << "\n";
        cout << "Median ID: " << medianResult.median << "\n";
    } else {
        cout << "Inventory is empty, cannot calculate median.\n";
    }
    
    // Example 2: Even number of nodes (n=6). Sorted IDs: 100, 101, [102], [103], 104, 105. Median is (102 + 103) / 2 = 102.5.
    
    BST inventory_even;
    inventory_even.root = inventory_even.insert(inventory_even.root, {101, 50});
    inventory_even.root = inventory_even.insert(inventory_even.root, {105, 120}); 
    inventory_even.root = inventory_even.insert(inventory_even.root, {103, 75});
    inventory_even.root = inventory_even.insert(inventory_even.root, {100, 30});
    inventory_even.root = inventory_even.insert(inventory_even.root, {102, 12});
    inventory_even.root = inventory_even.insert(inventory_even.root, {104, 119});

    cout << "\n--- Even-Sized Inventory ---\n";
    inventory_even.inOrder(inventory_even.root);
    
    MedianResult medianResultEven = inventory_even.findMedian();

    cout << "\n--- Median Product ID (Even Case) ---\n";
    if (medianResultEven.valid) {
        cout << "Total Nodes (n): " << inventory_even.countNodesRecursive(inventory_even.root) << "\n";
        cout << "Median ID: " << medianResultEven.median << "\n"; // Should be 102.5
    }

    return 0;
}