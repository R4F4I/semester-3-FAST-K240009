/*



* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

void swap(int& n, int& m){
    int temp;
    temp = n;
    n=m;
    m=temp;
}

bool RecurBSort(int arr[], int size){
    // base case , size is the scope to which we have to sort, in the efficient bsort, the inner loop, has the clause j<i, where the nest loop gets shorter after every upper loop gets completed, here we are using the same principle
    if (size<1) 
        return true;

    // the "nested loop" in the iterative bsort
    for (size_t i = 0; i < size; i++){
        if (arr[i]>arr[i+1])
            swap(arr[i],arr[i+1]);
    }
    return RecurBSort(arr,size-1);
}



int main(){

int arr[] = {9,8,7,6,5,4,3,2,1};

    // int a = 10;
    // int b= 5;
    // swap(a,b);

    // std::cout << a <<b <<std::endl;
    
    RecurBSort(arr, 9);
    for (size_t i = 0; i < 9; i++)
    {
        
        std::cout << arr[i] << " ";
    }
    

    return 0;
}