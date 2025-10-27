/*

Imagine you are working for a company that provides an online shopping platform. There are only 3
products listed on the platform, and customers often search for products based on their price. Write a
program in C++ that uses Quick sort to sort the products based on their price in ascending order.
Define a class for each product that will store its name, price, description, and availability?

Steps of Quick Sort:
 Pivot Selection: Choose a pivot element.
 Partitioning: Rearrange the array such that all elements smaller than the pivot are on the left,
and all greater elements are on the right.
 Recursion: Recursively apply the quick sort on the left and right halves of the array.
The efficiency of Quick Sort depends on the pivot selection strategy.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/


#include <iostream>
// #include <string> // Required for using the string data type

using namespace std;

class Product {
public:
    string name;
    int price;
    string description;
    bool availability;
};

void swap(Product& a, Product& b) {
    Product temp = a;
    a = b;
    b = temp;
}


void quickSort(Product arr[], int low, int high) {
    // Base case for the recursion:
    // If the subarray has 0 or 1 element, it's already sorted.
    if (low >= high) {
        return;
    }

    // --- Start of Integrated Partitioning Logic (Lomuto scheme) ---

    // 1. Pivot Selection: Choose the last element's price as the pivot.
    int pivotPrice = arr[high].price;
    
    // 'i' is the index for the last element found that was < pivot.
    // It starts one position *before* the low boundary.
    int i = (low - 1);

    // 2. Partitioning:
    // Loop 'j' from the start (low) to the element just before the pivot.
    for (int j = low; j <= high - 1; j++) {
        // If the current element is smaller than the pivot
        if (arr[j].price < pivotPrice) {
            i++; // Move the 'i' pointer forward
            swap(arr[i], arr[j]); // Swap the smaller element to the left part
        }
    }
    
    // At the end of the loop, all elements from [low...i] are < pivot.
    // The pivot's correct final position is [i + 1].
    int pivotIndex = i + 1;
    swap(arr[pivotIndex], arr[high]);

    // --- End of Integrated Partitioning Logic ---

    // 3. Recursion:
    // Recursively sort the two halves *around* the new pivotIndex.
    quickSort(arr, low, pivotIndex - 1);  // Left half (elements < pivot)
    quickSort(arr, pivotIndex + 1, high); // Right half (elements > pivot)
}


void printProducts(Product arr[], int size) {
    for(int i = 0; i < size; i++) {
        // Use index to refer to the value (price)
        cout << "Index " << i << ": Price " << arr[i].price << " (Name: " << arr[i].name << ")" << endl;
    }
}

int main() {
    const int NUM_PRODUCTS = 3;

    Product products[NUM_PRODUCTS];

    products[0].name = "Laptop";
    products[0].price = 800;
    products[0].description = "A fast laptop";
    products[0].availability = true;
    
    products[1].name = "Mouse";
    products[1].price = 50;
    products[1].description = "A gaming mouse";
    products[1].availability = true;

    products[2].name = "Keyboard";
    products[2].price = 150;
    products[2].description = "A mechanical keyboard";
    products[2].availability = false;

    cout << "--- Original Products ---" << endl;
    printProducts(products, NUM_PRODUCTS);

    // Sort the products based on price
    quickSort(products, 0, NUM_PRODUCTS - 1);

    cout << "\n--- Sorted Products (by Price) ---" << endl;
    printProducts(products, NUM_PRODUCTS);

    return 0;
}