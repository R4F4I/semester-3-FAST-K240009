/*

Given an array with birth years of children born in 2022, 2023, and 2024, the task is to
sort the array so that all children born in 2022 come first, followed by those born in 2023, and
finally those born in 2024.
Input: {2022, 2023, 2024, 2022, 2023, 2024}
Output: {2022, 2022, 2023, 2023, 2024, 2024}
Explanation: {2022, 2022, 2023, 2023, 2024, 2024} shows that all the 2022 birth years come
first, followed by the 2023 , and then all the 2024 birth years at the end.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;



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

template <typename T>
void printArr(T arr[], int size){
   for (size_t i = 0; i < size; i++){
       std::cout << arr[i]<< " ";
   }
   cout<<endl;
}

int main(){

    int arr[]={2022, 2023, 2024, 2022, 2023, 2024};
    printArr(arr,6);
    sort(arr,6);
    printArr(arr,6);



    return 0;
}