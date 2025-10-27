/*

Given an array in the figure of integers, sort the array in ascending as well as descending order and
return it using radix sort

Steps of Radix Sort:
 Find the maximum number in the array to know the number of digits.
 Sort based on each digit, starting from the least significant digit (LSD) to the most significant
digit (MSD), using a stable sorting algorithm (such as counting sort).
 Repeat the sorting process for each digit position until all digits are processed.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/
#include <iostream>

using namespace std;

/**
 * Utility function to get the maximum value in an array.
 * This is needed to know the number of digits in the largest number.
 * arr The array to search.
 * n The size of the array.
 * @return The largest integer in the array.
 */
int getMax(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

/**
 * A utility function to print an array.
 * arr The array to print.
 * n The size of the array.
 */
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

/**
 * Performs a stable counting sort on an array based on a specific digit.
 * This version sorts in ASCENDING order.
 * arr The array to sort.
 * n The size of the array.
 * exp The current digit's place (1 for units, 10 for tens, etc.).
 */
void countingSortAscending(int arr[], int n, int exp) {
    // We can't use vector, so we declare arrays on the stack
    // Note: Variable Length Arrays (VLAs) like output[n] are not standard C++
    // but are supported by many compilers (like g++).
    // A more standard C++ approach without <vector> would be dynamic allocation.
    // For this problem, we'll assume a VLA-supporting compiler or a fixed max size.
    // Let's use dynamic allocation for standard-compliance.
    
    int* output = new int[n]; // Output array
    int count[10] = {0}; // Count array for digits 0-9

    // 1. Store count of occurrences in count[]
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // 2. Change count[i] so that count[i] now contains the
    //    actual position of this digit in output[]
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 3. Build the output array (stably)
    //    We iterate from the end to maintain stability
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // 4. Copy the output array to arr[], so that arr[] now
    //    contains sorted numbers according to the current digit
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    
    delete[] output; // Clean up the dynamically allocated memory
}

/**
 * Performs a stable counting sort on an array based on a specific digit.
 * This version sorts in DESCENDING order.
 * arr The array to sort.
 * n The size of the array.
 * exp The current digit's place (1 for units, 10 for tens, etc.).
 */
void countingSortDescending(int arr[], int n, int exp) {
    int* output = new int[n];
    int count[10] = {0};

    // 1. Store count of occurrences
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // 2. Modify the count array for descending order.
    //    We create a cumulative sum from the right (digit 9 to 0).
    for (int i = 8; i >= 0; i--) {
        count[i] += count[i + 1];
    }

    // 3. Build the output array (stably)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // 4. Copy the output array to arr[]
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    
    delete[] output;
}

/**
 * The main function to implement Radix Sort in ASCENDING order.
 * arr The array to be sorted.
 * n The size of the array.
 */
void radixSort(int arr[], int n, bool ascending) {
    // Find the maximum number to know the number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing the digit number, exp is passed. exp is 10^i
    // where i is the current digit number (0, 1, 2...)
    for (int exp = 1; m / exp > 0; exp *= 10) {
        if (ascending) {
            countingSortAscending(arr, n, exp);
        } else {
            countingSortDescending(arr, n, exp);
        }
    }
}


int main() {
    

    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Create a copy for the descending sort
    int* arrDesc = new int[n];
    for(int i = 0; i < n; i++) {
        arrDesc[i] = arr[i];
    }

    cout << "Original array: ";
    printArray(arr, n);
    
    // --- Sort Ascending ---
    radixSort(arr, n, true);
    cout << "Sorted array (Ascending): ";
    printArray(arr, n);

    // --- Sort Descending ---
    radixSort(arrDesc, n, false);
    cout << "Sorted array (Descending): ";
    printArray(arrDesc, n);

    // Clean up dynamic memory
    delete[] arrDesc;

    return 0;
}