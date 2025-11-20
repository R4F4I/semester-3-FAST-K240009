/*

Task#2: Look at above tree and write a function to check if a given array represents
a Binary Heap? Also that sort the array in ascending order.

*/


#include <iostream>

using namespace std;

// --- General Utility Function ---
// Helper to swap two elements. Used by both MinMaxHeap and HeapSort.
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// --- Task 2: Check if a given array represents a Binary Max Heap ---
// Checks if the array satisfies the Max Heap property (parent >= children)
bool isBinaryMaxHeap(int arr[], int size) {
    // We only need to check nodes from index 0 up to the last internal node: (size / 2) - 1
    for (int i = 0; i <= (size / 2) - 1; ++i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // Check left child
        if (left < size && arr[i] < arr[left]) {
            cout << "Failure at index " << i << " (Parent: " << arr[i] << ") < Left Child: " << arr[left] << endl;
            return false;
        }

        // Check right child
        if (right < size && arr[i] < arr[right]) {
            cout << "Failure at index " << i << " (Parent: " << arr[i] << ") < Right Child: " << arr[right] << endl;
            return false;
        }
    }
    return true;
}

// --- Utility for Task 2: Heap Sort (Max Heapify) ---
// Standard Max Heapify function used for building/restoring a Max Heap
void max_heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1; // left child index
    int r = 2 * i + 2; // right child index

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        // Recursively heapify the affected sub-tree
        max_heapify(arr, n, largest);
    }
}

// --- Task 2: Sort the array in ascending order (using Heap Sort) ---
void heapSort(int arr[], int size) {
    // 1. Build a Max Heap (rearrange array)
    // Start from the last non-leaf node: (size / 2) - 1
    for (int i = size / 2 - 1; i >= 0; i--) {
        max_heapify(arr, size, i);
    }

    // 2. One by one extract an element from the heap
    for (int i = size - 1; i > 0; i--) {
        // Move current root (largest element) to the end of the unsorted part
        swap(arr[0], arr[i]);

        // Call max_heapify on the reduced heap (i is the new size)
        max_heapify(arr, i, 0);
    }
}



const int MAX_SIZE = 100; 

class MinMaxHeap {
public:
    int heap[MAX_SIZE]; // C-style array for the heap data
    int size;

    // NOTE: swap is now a global utility function

    // --- Index and Level Helpers ---

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    int grandParent(int i) { return (parent(i) - 1) / 2; }

    // Determines if the index i is on a Min-Level (Level 0, 2, 4, ...)
    bool isMinLevel(int i) {
        // Calculates level: floor(log2(i + 1))
        if (i == 0) return true; 
        int index = i + 1;
        int level = 0;
        while (index > 1) {
            index /= 2;
            level++;
        }
        return level % 2 == 0;
    }

    // --- Min-Max Sift Up Logic (Handles Max and Min violations upwards) ---

    // Sift up when current node is on a Min-Level (violates Max parent/Min grandparent)
    void sift_up_min_level(int i) {
        if (i > 2) { // Only check grandparent if index allows
            int gp = grandParent(i);
            if (heap[i] < heap[gp]) { // Compare with Min-Level Grandparent
                swap(heap[i], heap[gp]);
                sift_up_min_level(gp);
            }
        }
    }

    // Sift up when current node is on a Max-Level (violates Min parent/Max grandparent)
    void sift_up_max_level(int i) {
        if (i > 2) { // Only check grandparent if index allows
            int gp = grandParent(i);
            if (heap[i] > heap[gp]) { // Compare with Max-Level Grandparent
                swap(heap[i], heap[gp]);
                sift_up_max_level(gp);
            }
        }
    }

    void sift_up(int i) {
        if (i == 0) return; 
        int p = parent(i);
        
        if (isMinLevel(i)) { // Node i is on a Min-Level
            if (heap[i] > heap[p]) {
                // Min-Level node is greater than its Max-Level parent: Violation 1
                swap(heap[i], heap[p]);
                sift_up_max_level(p); // Parent is now the node, bubble up as Max-element
            } else {
                // Check Grandparent (Min-Level)
                sift_up_min_level(i);
            }
        } else { // Node i is on a Max-Level
            if (heap[i] < heap[p]) {
                // Max-Level node is smaller than its Min-Level parent: Violation 1
                swap(heap[i], heap[p]);
                sift_up_min_level(p); // Parent is now the node, bubble up as Min-element
            } else {
                // Check Grandparent (Max-Level)
                sift_up_max_level(i);
            }
        }
    }

    // --- Min-Max Sift Down Logic (Handles Min and Max violations downwards) ---

    // Finds the index of the best (smallest/largest) descendant (children or grandchildren)
    int findBestDescendant(int i, bool find_min) {
        int best_index = -1;
        int best_val = find_min ? 2000000000 : -2000000000; // Large/Small sentinel value

        // Helper to check and update best descendant
        auto check_and_update = [&](int j) {
            if (j < size) {
                if (find_min ? (heap[j] < best_val) : (heap[j] > best_val)) {
                    best_val = heap[j];
                    best_index = j;
                }
            }
        };

        // Check Children and Grandchildren
        for (int j = leftChild(i); j <= rightChild(i) && j < size; ++j) {
            check_and_update(j); // Child 1/2
            check_and_update(leftChild(j)); // Grandchild 1/2
            check_and_update(rightChild(j)); // Grandchild 3/4
        }
        return best_index;
    }

    void sift_down(int i) {
        bool min_level = isMinLevel(i);
        int best_descendant_index = findBestDescendant(i, min_level);
        
        if (best_descendant_index == -1) return;

        int j = best_descendant_index; // Index of the best descendant
        int p_j = parent(j); // Parent of the best descendant

        // Check if the best descendant is a grandchild
        bool is_grandchild = (parent(p_j) != i); 

        if ((min_level && heap[i] > heap[j]) || (!min_level && heap[i] < heap[j])) {
            // Violation found: heap[i] is greater than a smaller descendant (Min-Level) 
            // OR heap[i] is smaller than a larger descendant (Max-Level)
            
            swap(heap[i], heap[j]);

            if (is_grandchild) {
                // Check Max/Min Level property correction on the parent of the swapped node (p_j)
                if ((min_level && heap[j] > heap[p_j]) || (!min_level && heap[j] < heap[p_j])) {
                    swap(heap[j], heap[p_j]); // Correct Max/Min property violation with parent
                }
                sift_down(j); // Continue sifting down from the new position
            }
        }
    }


    // Constructor to initialize the heap with the given values
    MinMaxHeap(int values[], int count) : size(count) {
        for (int i = 0; i < count; ++i) {
            heap[i] = values[i];
        }
        // Build the heap properties by starting from the last internal node
        for (int i = (size / 2) - 1; i >= 0; --i) {
             sift_down(i);
        }
    }

    // Task 1: Update Key (from previous task)
    void update_key(int i, int new_val) {
        if (i < 0 || i >= size) {
            cout << "Error: Invalid index for update." << endl;
            return;
        }

        int old_val = heap[i];
        heap[i] = new_val;

        cout << "\n--- Update Key ---" << endl;
        cout << "Index " << i << " updated from " << old_val << " to " << new_val << endl;

        if (new_val > old_val) {
            sift_up(i); 
        } else if (new_val < old_val) {
            sift_down(i);
        }
        cout << "------------------" << endl;
    }

    // Task 1: Delete element from heap (Implementing Delete Min) (from previous task)
    void delete_min() {
        if (size == 0) {
            cout << "Error: Heap is empty." << endl;
            return;
        }

        // The minimum element is at the root (0), or its children (1 or 2)
        int min_index = 0;
        if (size > 1 && heap[1] < heap[min_index]) {
            min_index = 1;
        }
        if (size > 2 && heap[2] < heap[min_index]) {
            min_index = 2;
        }

        cout << "\n--- Delete Min ---" << endl;
        cout << "Removing minimum value " << heap[min_index] << " at index " << min_index << endl;

        // Replace the minimum element with the last element
        heap[min_index] = heap[size - 1];
        size--;

        if (size > 0) {
            // Sift down the new element at the deleted position
            sift_down(min_index);
        }
        cout << "------------------" << endl;
    }


    void print_heap_array() const {
        cout << "\nHeap Array (Size: " << size << "): [";
        for (int i = 0; i < size; ++i) {
            cout << heap[i] << (i == size - 1 ? "" : ", ");
        }
        cout << "]" << endl;
    }
    
    // Simple tree visualization for the first few levels
    void print_heap_visualization() const {
        cout << "\n--- Current Heap Structure ---" << endl;
        if (size == 0) {
            cout << "Empty." << endl;
            return;
        }

        cout << "      " << heap[0] << " (L0 Min)" << endl;
        if (size > 1) {
            cout << "     / \\" << endl;
            cout << "   " << heap[1] << " (L1 Max)";
            if (size > 2) {
                cout << "  " << heap[2] << " (L1 Max)";
            }
            cout << endl;
        }
        if (size > 3) {
            cout << "   / \\";
            if (size > 2) {
                cout << " / \\";
            }
            cout << endl;
            cout << " " << heap[3] << " (L2 Min)";
            if (size > 4) {
                cout << " " << heap[4] << " (L2 Min)";
            }
            if (size > 5) {
                cout << " " << heap[5] << " (L2 Min)";
            }
            if (size > 6) {
                cout << " " << heap[6] << " (L2 Min)";
            }
            cout << endl;
        }
        cout << "------------------------------" << endl;
    }
};


int main() {
    // Initial values for Min-Max Heap: 8, 7, 6, 5, 4
    int initial_values[] = {8, 7, 6, 5, 4};
    int initial_count = sizeof(initial_values) / sizeof(initial_values[0]);

    cout << "--- Demonstration of Min-Max Heap Operations ---" << endl;
    MinMaxHeap mmHeap(initial_values, initial_count);
    mmHeap.print_heap_array();
    
    // Demonstration of MinMaxHeap updates (from Task 1)
    mmHeap.update_key(3, 15); 
    mmHeap.update_key(0, 2);
    mmHeap.delete_min();
    mmHeap.print_heap_array();
    
    cout << "\n=======================================================" << endl;

    // --- Task 2: Demonstration of Binary Heap Check and Sort ---

    // Test Array 1 (Initial values, which also form a Max Heap)
    int test_arr_1[] = {8, 7, 6, 5, 4};
    int size_1 = sizeof(test_arr_1) / sizeof(test_arr_1[0]);
    
    cout << "\n--- Task 2: Binary Heap Check ---" << endl;
    cout << "Array: [8, 7, 6, 5, 4]" << endl;
    if (isBinaryMaxHeap(test_arr_1, size_1)) {
        cout << "Result: The array IS a Binary Max Heap." << endl;
    } else {
        cout << "Result: The array IS NOT a Binary Max Heap." << endl;
    }

    // Test Array 2 (Not a heap)
    int test_arr_2[] = {4, 10, 5, 1, 20};
    int size_2 = sizeof(test_arr_2) / sizeof(test_arr_2[0]);
    
    cout << "\nArray: [4, 10, 5, 1, 20]" << endl;
    if (isBinaryMaxHeap(test_arr_2, size_2)) {
        cout << "Result: The array IS a Binary Max Heap." << endl;
    } else {
        cout << "Result: The array IS NOT a Binary Max Heap." << endl;
    }

    // --- Task 2: Ascending Sort using Heap Sort ---
    cout << "\n--- Task 2: Ascending Sort (Heap Sort) ---" << endl;
    
    int sort_arr[] = {15, 5, 8, 2, 10};
    int sort_size = sizeof(sort_arr) / sizeof(sort_arr[0]);
    
    cout << "Original Array: [15, 5, 8, 2, 10]" << endl;
    
    heapSort(sort_arr, sort_size);
    
    cout << "Sorted Array (Ascending): [";
    for (int i = 0; i < sort_size; ++i) {
        cout << sort_arr[i] << (i == sort_size - 1 ? "" : ", ");
    }
    cout << "]" << endl;


    return 0;
}