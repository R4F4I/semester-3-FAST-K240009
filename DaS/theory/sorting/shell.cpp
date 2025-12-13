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

void shellSort(int arr[],int size){

    // modifed insertion sort
    
    
    int gap = size/2;
    while (gap>0){
        for (size_t i = gap; i < size; i++){
            int key = arr[i];
            int j=i;
            while (j>=gap && arr[j-gap]>key){
                
                arr[j] = arr[j-gap];
                
                j-=gap;
            }
            arr[j] = key;
        }
        gap /= 2;
    }

}


int main(){

    

    int arr[] = {29,10,14,37,9,9};
    int size = sizeof(arr)/sizeof(arr[0]);
    
    printArr(arr,size);

    shellSort(arr,size);
    
    printArr(arr,size);



    return 0;
}