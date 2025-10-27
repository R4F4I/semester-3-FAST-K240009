/*

You have been given two unsorted arrays, arr1 and arr2, each containing 10 integers. You need to
combine the two arrays into a single sorted array using either Radix Sort or Merge Sort.
 Write a C++ program to combine arr1 and arr2 using Radix Sort and print the sorted array.
 Write a C++ program to combine arr1 and arr2 using Merge Sort and print the sorted array.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/


#include <iostream>

using namespace std;

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int getMax(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

void countingSort(int arr[], int n, int exp) {
    int* output = new int[n]; // Output array
    int count[10] = {0}; // Count array for digits 0-9

    // Store count of occurrences in count[]
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // Change count[i] to store the actual position
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array (stably)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy the output array to arr[]
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    
    delete[] output; // Clean up memory
}


void radixSort(int arr[], int n) {
    int m = getMax(arr, n);

    // Do counting sort for every digit
    for (int exp = 1; m / exp > 0; exp *= 10) {
        countingSort(arr, n, exp);
    }
}

// ////////////////////////////////////

/**
 * @brief Merges two sorted subarrays into one sorted subarray.
 */
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0; 
    int j = 0; 
    int k = left; 

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    delete[] L;
    delete[] R;
}

/**
 * @brief Sorts an array of integers using the Merge Sort algorithm.
 */
void mergeSort(int arr[], int left, int right) {
    if (left >= right) {
        return; 
    }
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

/**
 * @brief Merges two already-sorted arrays into a third destination array.
 */
void mergeArrays(int arr1[], int size1, int arr2[], int size2, int dest[]) {
    int i = 0; // index for arr1
    int j = 0; // index for arr2
    int k = 0; // index for dest
    
    // Compare elements and place the smaller one in the dest array
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            dest[k] = arr1[i];
            i++;
        } else {
            dest[k] = arr2[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements from arr1
    while (i < size1) {
        dest[k] = arr1[i];
        i++;
        k++;
    }

    // Copy any remaining elements from arr2
    while (j < size2) {
        dest[k] = arr2[j];
        j++;
        k++;
    }
}


int main() {
    const int SIZE = 10;
    const int COMBINED_SIZE = 20;

    int arr1[SIZE] = {170, 45, 75, 90, 802, 24, 2, 66, 50, 320};
    int arr2[SIZE] = {30, 99, 1, 430, 2, 88, 19, 5, 230, 77};
    
    int combinedArr[COMBINED_SIZE];

    
    // 1. Combine the two arrays
    for(int i = 0; i < SIZE; i++) {
        combinedArr[i] = arr1[i];
    }
    for(int i = 0; i < SIZE; i++) {
        combinedArr[i + SIZE] = arr2[i];
    }
    int diffArr[COMBINED_SIZE];
    
    for(int i = 0; i < 2*SIZE; i++) {
        diffArr[i] = combinedArr[i];
    }

    
    cout << "--- Radix Sort ---" << endl;
    cout << "Combined Unsorted: ";
    printArray(combinedArr, COMBINED_SIZE);

    // 2. Sort the combined array
    radixSort(combinedArr, COMBINED_SIZE);

    cout << "Combined   Sorted: ";
    printArray(combinedArr, COMBINED_SIZE);
    
    
    
    cout << "--- Merge Sort ---" << endl;
    cout << "Combined Unsorted: ";
    printArray(diffArr, COMBINED_SIZE);

    // 2. Sort the combined array
    radixSort(diffArr, COMBINED_SIZE);

    cout << "Combined   Sorted: ";
    printArray(diffArr, COMBINED_SIZE);

    return 0;
}