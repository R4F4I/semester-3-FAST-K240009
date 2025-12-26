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

// modified bubble sort, has the simple nested loop present in the code with a gap b/w comparisons

void combSort(int arr[], int size){

    // in each loop the gap val is set, if the two val are not sorted, then sort
    // the gap is shortened after every run by 1.3

    int gap = size;
    while (gap > 1)
    {
        for (size_t i = 0; i < size-gap; i++)
        {
            
            if (arr[i]>arr[i+gap])
            {
                swap(arr[i],arr[i+gap]);
            }
        }
        gap /= 1.3;
        
    }
    
    

}


int main(){

    

    int arr[] = {29,10,14,37,9,9};
    int size = sizeof(arr)/ sizeof(arr[0]);
    printArr(arr,size);
    
    combSort(arr,size);
    
    printArr(arr,size);



    return 0;
}