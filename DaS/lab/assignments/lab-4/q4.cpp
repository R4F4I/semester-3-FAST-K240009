/*

Task#4: Given an unsorted array that may contain duplicates. Write a function that returns true
if the array contains duplicates.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

// template <typename T>
// void swap(T& a, T& b){
//     T temp = a;
//     a=b;
//     b=temp;
// }

void sort(int arr[],int size){
    bool swapped;
    for (int i = 0; i < size - 1; i++) {
        swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

bool hasDup(int arr[],int size){
    sort(arr,size);
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i]==arr[i+1])
        {
            return true;
        }
    }
    return false;
}

template <typename T>
void printArr(T arr[], int size){
   for (size_t i = 0; i < size; i++){
       std::cout << arr[i]<< " ";
   }
   cout<<endl;
}

int main(){

    // suppose an unsorted list that contains duplicates
    int arr[10] = {1,2,5,7,5,3,6,10,9,3};
    // one way to detect is to sort the array
    
    // bubble sort
    

    // now compare each element with the next, if same then duplicate
    bool duplicate = hasDup(arr,10);
    printArr(arr,10);
    std::cout << "duplicate present? " << duplicate << std::endl;



    return 0;
}