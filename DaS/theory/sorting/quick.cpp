/*



* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

void printArr(int arr[], int size){
   for (size_t i = 0; i < size; i++){
       std::cout << arr[i]<< " ";
   }
   cout<<endl;
}

bool isSorted(int arr[], int size){
    for (size_t i = 0; i < size-1; i++)
    {
        if (arr[i]>arr[i+1])
        {
            return false;
        }
        
    }
    return true;
    
}

void quickSort(int arr[],int size, int low, int high){

    if (isSorted(arr,size))
    {
        return;
    }
    

    // pick the last element as pivot
    // pick j as 0 i as -1
    // if arr[j] > pivot, move j ahead
    // if arr[j] < pivot, move i ahead, swap i and j, 
    // until both reach end

    int pivot = high, j = low, i = low-1;

    while (j!=pivot)
    {
        if (arr[j]>arr[pivot])
        {
        
            std::cout << "moving on..."<<endl;
        }
        else if (arr[j]< arr[pivot])
        {
            i++;
            swap(arr[i],arr[j]);
        }
        j++;
    
    }
    
    // when j reaches pivot the final resting place of pivot's val is i+1

    // now all val before pivot are less than pivot, and vice versa for greater values
    
    swap(arr[pivot],arr[i+1]);

    // updating the pivot position
    pivot = i+1;

    

    // now perform this eqn recursively on the arr to the left and to the right, exclude the pivot from the both the new partitions
    quickSort(arr,size,low,pivot-1);
    quickSort(arr,size,pivot+1,high);

}


int main(){


    int arr[10] = {5,8,2,45,1,78,7,20,9,44};
    int size = 10;

    // quickSort(arr,0,size-1);
    quickSort(arr,size-1,0,size-1);

    int a = 2;
    int b = 5;


    // swap(a,b);

    // std::cout <<a << b  << std::endl;

    printArr(arr,size);

    return 0;
}