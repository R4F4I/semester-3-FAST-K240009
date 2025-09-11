
/*

// duplicate detecter


* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;





int main(){

    // suppose an unsorted list that contains duplicates
    int arr[10] = {1,2,5,7,5,3,6,10,9,3};
    // one way to detect is to sort the array
    
    // bubble sort
    bool swapped;
    for (int i = 0; i < 10 - 1; i++) {
        swapped = false;
        for (int j = 0; j < 10 - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
      
        // If no two elements were swapped, then break
        if (!swapped)
            break;
    }

    // now compare each element with the next, if same then duplicate
    bool duplicate = false;
    for (size_t i = 0; i < 10; i++)
    {
        if (arr[i]==arr[i+1])
        {
            duplicate = true;
            break;
        }
    }
    std::cout << "duplicate present? " << duplicate << std::endl;



    return 0;
}