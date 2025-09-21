/*



* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;



//::METHOD 1:://

int ZerosInNum(int n){
    if (n==0)
    {
        return 0;
    }
    int lastDig = n%10;
    if (lastDig==0)
    {
        return 1+ZerosInNum(n/10);
    }
    return ZerosInNum(n/10);
    
}

// this func simply performs some "func" on each element receives it output and 
// sums it with all the other elements of the array
int ZerosInArr(int arr[], int i, int size){
    
    // reached end of arr
    if (i==size)
    {
        return ZerosInNum(arr[i]);
    }
    
    // sum and then move on
    return ZerosInNum(arr[i]) + ZerosInArr(arr,i+1,size);
    
}


//::METHOD 2:://
// suppose an array of integers, get their total amount of 0s present
// the iterative version is also a 
int func(int arr[],int i,int size, int numOfZeros){
    int digit=0;
    if (i == size){
        return numOfZeros;
    }
    while (arr[i]>0){
        digit = arr[i]%10; // get last digit of the number
        arr[i]/=10; 
        if (digit==0){
            numOfZeros++;
        }
    }
    return func(arr,i+1,size,numOfZeros);
}

int main(){

    int arr[]={
        102,500,2040,70007
    };
    
    int arr2[]={
        102,500,2040,70007
    };
    
    
    
    std::cout << func(arr,0,4,0) << std::endl;
    // std::cout << arr[2] << std::endl;
    std::cout << ZerosInArr(arr2,0,4) << std::endl;


    return 0;
}