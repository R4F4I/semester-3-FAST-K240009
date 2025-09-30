/*

Task#3: Given an array of strings arr[]. Sort given strings using Bubble Sort and display the
sorted array.
Input: string arr[] = {"banana", "apple", "cherry", "date", "grape"};
Output: apple banana cherry date grape

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;


template <typename T>
void printArr(T arr[], int size){
   for (size_t i = 0; i < size; i++){
       std::cout << arr[i]<< " ";
   }
   cout<<endl;
}

void BubbleSort(string arr[], int size){
    string temp;
    for (size_t i = 0; i < size; i++){
        for (size_t j = 0; j < size; j++){
            if (arr[j-1]>arr[j]){
                //swap
                temp = arr[j-1];
                arr[j-1]=arr[j];
                arr[j]=temp;
            }
        }
    }
}


int main(){

    string arr[] = {"banana", "apple", "cherry", "date", "grape"};

    printArr(arr,5);
    BubbleSort(arr,5);
    printArr(arr,5);



    return 0;
}