/*



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


// the algo is simple,
// a loop will be used to cycle through the unsorted half of the arr
// in each ith iteration the smallest val from unsorted half(range is "i to size") 
// will be chosen and placed into the ith position
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


    int arr[] = {29,10,14,37,9};
    printArr(arr,5);
    
    // int a=10;
    // int b=5;
    // swap(a,b);
    // std::cout << a <<b<< std::endl;
    
    selectionSort(arr,5);
    
    printArr(arr,5);


    return 0;
}