/*

Task 7:
In the quick sort algorithm, the selection of a pivot element is of utmost importance. There are
different ways to select the pivot element. Your task is to implement quick sort using the following
pivot selection techniques and count the number of comparisons of each approach:
Note: The implementation should be in-place.
 Select the first element as pivot.
 Select any random element as pivot
 Select middle element as pivot
 Use median approach for pivot selection
 Apply quick sort on list (Use any pivot selection approach)
After applying all the above approaches, evaluate the efficiency of each pivot selection technique,
we count the number of comparisons made during partitioning.
Note: Apply the quick sort on different input arrays (e.g., sorted, reverse-sorted, random) to see
how each pivot strategy performs.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/


#include <iostream>

using namespace std;


int randValues[] = {5, 8, 2, 10, 19, 0, 7, 3, 11, 15, 1, 4, 9, 6, 12, 18, 13, 17, 14, 16};

const int randSize = 20;

int randIndex = 0;


void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

/*
 * Finds the median of three elements (low, mid, high)
 * and returns the index of the median.
 * This implementation sorts the three elements in-place.
 */
int getMedianOfThreeIndex(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;

    // Sort the three elements arr[low], arr[mid], arr[high]
    if (arr[low] > arr[mid]) {
        swap(arr[low], arr[mid]);
    }
    if (arr[low] > arr[high]) {
        swap(arr[low], arr[high]);
    }
    if (arr[mid] > arr[high]) {
        swap(arr[mid], arr[high]);
    }

    // After sorting, the median value is at index 'mid'
    return mid;
}

/*
 * Partitions the array
 * It assumes the pivot is already at arr[high].
 */
int partition(int arr[], int low, int high, long long& comparisons) {
    int pivotValue = arr[high];
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // This is the main comparison
        comparisons++;
        if (arr[j] < pivotValue) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high, long long& comparisons, int strategy) {
    if (low >= high) {
        return; // Base case
    }

    // 1. Select Pivot Index based on strategy
    int pivotIndex;
    switch (strategy) {
        case 1: // First element
            pivotIndex = low;
            break;
        case 2: // "Random" element (using our hardcoded list)
        {
            // Get the next pseudo-random value
            int randVal = randValues[randIndex % randSize];
            randIndex++; // Move to the next "random" value for the next call
            
            // Map the value to the valid range [low, high]
            pivotIndex = low + (randVal % (high - low + 1));
            break;
        }
        case 3: // Middle element
            pivotIndex = low + (high - low) / 2;
            break;
        case 4: // Median-of-three
            pivotIndex = getMedianOfThreeIndex(arr, low, high);
            break;
        default:
            pivotIndex = low; // Default to first
    }

    // 2. Move pivot to the end (for Lomuto partition)
    swap(arr[pivotIndex], arr[high]);

    // 3. Partition the array
    int pi = partition(arr, low, high, comparisons);

    // 4. Recurse on the two halves
    quickSort(arr, low, pi - 1, comparisons, strategy);
    quickSort(arr, pi + 1, high, comparisons, strategy);
}

void copyArray(int src[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void resetRandIndex() {
    randIndex = 0;
}


int main() {
    long long comparisons;
    
    // --- Define the 3 input arrays ---
    int randomArr[] = {12, 8, 19, 3, 17, 1, 10, 14, 5, 9, 6, 11, 2, 20, 7, 16, 4, 18, 13, 15};
    int sortedArr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int reverseArr[] = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    const int SIZE = sizeof(randomArr)/sizeof(randomArr[0]);
    
    // A temporary array to hold copies for sorting
    int tempArr[SIZE];

    // --- Test 1: Random Array ---
    cout << "--- Testing on Random Array ---" << endl;
    
    comparisons = 0;
    resetRandIndex();
    copyArray(randomArr, tempArr, SIZE);
    quickSort(tempArr, 0, SIZE - 1, comparisons, 1);
    cout << "1. First Element: " << comparisons << " comparisons." << endl;

    comparisons = 0;
    resetRandIndex();
    copyArray(randomArr, tempArr, SIZE);
    quickSort(tempArr, 0, SIZE - 1, comparisons, 2);
    cout << "2. \"Random\" Element: " << comparisons << " comparisons." << endl;
    
    comparisons = 0;
    resetRandIndex();
    copyArray(randomArr, tempArr, SIZE);
    quickSort(tempArr, 0, SIZE - 1, comparisons, 3);
    cout << "3. Middle Element: " << comparisons << " comparisons." << endl;

    comparisons = 0;
    resetRandIndex();
    copyArray(randomArr, tempArr, SIZE);
    quickSort(tempArr, 0, SIZE - 1, comparisons, 4);
    cout << "4. Median-of-Three: " << comparisons << " comparisons." << endl;

    // --- Test 2: Sorted Array ---
    cout << "\n--- Testing on Sorted Array ---" << endl;
    
    comparisons = 0;
    resetRandIndex();
    copyArray(sortedArr, tempArr, SIZE);
    quickSort(tempArr, 0, SIZE - 1, comparisons, 1);
    cout << "1. First Element: " << comparisons << " comparisons." << endl;

    comparisons = 0;
    resetRandIndex();
    copyArray(sortedArr, tempArr, SIZE);
    quickSort(tempArr, 0, SIZE - 1, comparisons, 2);
    cout << "2. \"Random\" Element: " << comparisons << " comparisons." << endl;
    
    comparisons = 0;
    resetRandIndex();
    copyArray(sortedArr, tempArr, SIZE);
    quickSort(tempArr, 0, SIZE - 1, comparisons, 3);
    cout << "3. Middle Element: " << comparisons << " comparisons." << endl;

    comparisons = 0;
    resetRandIndex();
    copyArray(sortedArr, tempArr, SIZE);
    quickSort(tempArr, 0, SIZE - 1, comparisons, 4);
    cout << "4. Median-of-Three: " << comparisons << " comparisons." << endl;

    // --- Test 3: Reverse-Sorted Array ---
    cout << "\n--- Testing on Reverse-Sorted Array ---" << endl;
    
    comparisons = 0;
    resetRandIndex();
    copyArray(reverseArr, tempArr, SIZE);
    quickSort(tempArr, 0, SIZE - 1, comparisons, 1);
    cout << "1. First Element: " << comparisons << " comparisons." << endl;

    comparisons = 0;
    resetRandIndex();
    copyArray(reverseArr, tempArr, SIZE);
    quickSort(tempArr, 0, SIZE - 1, comparisons, 2);
    cout << "2. \"Random\" Element: " << comparisons << " comparisons." << endl;
    
    comparisons = 0;
    resetRandIndex();
    copyArray(reverseArr, tempArr, SIZE);
    quickSort(tempArr, 0, SIZE - 1, comparisons, 3);
    cout << "3. Middle Element: " << comparisons << " comparisons." << endl;

    comparisons = 0;
    resetRandIndex();
    copyArray(reverseArr, tempArr, SIZE);
    quickSort(tempArr, 0, SIZE - 1, comparisons, 4);
    cout << "4. Median-of-Three: " << comparisons << " comparisons." << endl;


    return 0;
}