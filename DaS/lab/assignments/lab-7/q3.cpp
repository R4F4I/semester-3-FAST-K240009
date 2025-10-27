/*

Task-3:
Suppose you are working for a company that organizes a marathon every year. There are 10
participants in the marathon, and their finish times are recorded in seconds.
Write a program in C++ that uses Merge sort to find the top 5 fastest runners. Create an array of
runner objects that will store the participant&#39;s name and finish time in seconds.
 Prompt the user to input the participant&#39;s names and finish times into the array.
 Implement a merge function that will merge two subarrays of runners based on their finish
time in ascending order.
 Use the Merge sort algorithm to sort the runners based on their finish time by calling the
merge function in step 3.
 Display the top 5 fastest runners to the console, along with their name and finish time in
seconds.
 Use the appropriate data types and size for the arrays and variables to ensure efficient
memory usage.

Steps of Merge Sort:
 Divide: Split the array into two halves until each sub-array contains a single element.

 Conquer (Sort): Recursively sort each half.
 Merge: Merge the two sorted halves into a single sorted array.


* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/
#include <iostream>


using namespace std;

/**
 * Merges two sorted subarrays into one sorted integer array.
 */
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1; // Size of the left subarray
    int n2 = right - mid;    // Size of the right subarray

    // Create temporary arrays dynamically
    int* L = new int[n1];
    int* R = new int[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left...right]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        // Sort in ascending order (fastest time first)
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // Free the dynamically allocated memory
    delete[] L;
    delete[] R;
}


void mergeSort(int arr[], int left, int right) {
    if (left >= right) {
        return; // Base case: array of 0 or 1 element is already sorted
    }
    
    // Find the middle point
    int mid = left + (right - left) / 2;
    
    // Conquer (Sort) each half
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    
    // Merge the sorted halves
    merge(arr, left, mid, right);
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {

    int arr[] = {340, 290, 305, 275, 310, 400, 280, 320, 330, 295}; // <-- finishTimes, lesser the time, faster the racer
    int size = sizeof(arr)/sizeof(arr[0]);

    cout << "Original Times: ";
    printArray(arr, size);
    
    
    mergeSort(arr, 0, size - 1);
    
    cout << "Top 5 Times: ";
    printArray(arr, 5);

    return 0;
}