/*

Write a Program that ask user to enter 10 elements and finds the 4 minimum elements
from given array using selection Sort.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

void swap(int& a, int& b){
    int temp = a;
    a=b;
    b=temp;
}


void printArr(int arr[], int size){

    
    for (size_t i = 0; i < size; i++)
    {
        std::cout << arr[i]<< " ";
    }
    cout<<endl;

}


void selectionSort(int arr[],int size){
    for (size_t i = 0; i < size; i++){
        int least=i;    // least points to the smallest val instead

        for (size_t j = i; j < size; j++){
            if (arr[j]<arr[least]){
                least = j;
            }
        }
        // after finding the smallest value swap with the ith element
        swap(arr[i],arr[least]);
    }
}

int main(){


    int arr[10];

    for (size_t i = 0; i < 10; i++)
    {
        cout<<"enter num: ";cin>>arr[i];
    }
    

    printArr(arr,10);
    
    selectionSort(arr,10);
    
    cout<<" the 4 min \n";
    printArr(arr,4);


    return 0;
}