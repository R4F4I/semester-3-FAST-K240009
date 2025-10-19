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

void merge(int arr[], int low, int high){

    int mid = low + (high - low)/2;

    int sizeL = mid - low +1; // if low = 5 mid =7 high = 9, size of low-high is 2 and 3 not 7
    int sizeR = high - mid;


    // before actually merge, split the arr in 2 given their sizes
    int *leftSubArr = new int[sizeL]; 
    int *rightSubArr = new int[sizeR];
    

    // copy all left val of arr
    for (size_t i = 0; i <= sizeL; i++)
    {
        leftSubArr[i]=arr[low+i];
    }

    // copy all left val of arr
    for (size_t i = 0; i <= sizeR ; i++)
    {
        
        rightSubArr[i]=arr[i+mid+1];
    }

    // compare if the val in left arr is lesser than all the val in right arr, if larger val is found, move it first

    // size of mergedArr can be assumed to be right+left

    int i = 0, j =0; // two loops looping through the 2 sub arrays

    int k = low;   // CORRECT index for the target array arr

    // Main comparison and merge loop
    while (i < sizeL && j < sizeR) {
        if (leftSubArr[i] <= rightSubArr[j]) {
            arr[k++] = leftSubArr[i++];
        } else {
            arr[k++] = rightSubArr[j++];
        }
    }

    // CORRECTLY handle remaining elements
    while (i < sizeL) {
        arr[k++] = leftSubArr[i++];
    }
    while (j < sizeR) {
        arr[k++] = rightSubArr[j++];
    }


    delete[] leftSubArr;
    delete[] rightSubArr;
}

void mergeSort(int arr[], int low, int high){

    if (low>=high)
    {
        return;
    }
    int mid = low + (high-low) /2; 
    
    mergeSort(arr,low,mid);
    mergeSort(arr,mid+1,high);
    
    merge(arr,low,high);

}


int main(){

    int arr[10] = {5,8,2,45,1,78,7,20,9,44};
    int size = 10;

    mergeSort(arr,0,size-1);

    printArr(arr,size);

    return 0;
}