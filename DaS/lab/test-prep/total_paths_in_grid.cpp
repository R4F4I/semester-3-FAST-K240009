/*

5 5 

0 0 0 0 0
1 1 0 0 0
0 1 1 0 0
1 1 1 0 0
0 0 0 1 0

output 7

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;


void printArr(int** arr, int size){
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++){
            std::cout << arr[i][j]<< " ";
        }
        cout<<endl;
    }
    
}

int count(int** arr,int i , int j, int m, int n){

    if (i == m && j==n)
    {
        return 1;
    }
    // we will have add a clause of invalid paths

    if (i>n ||j>m)
    {
        return 0;
    }
    // additional clause to ignore paths with 1s
    if (arr[i][j]==1)
    {
        return 0;
    }
    
    
    return count(arr,i+1,j,m,n) + count(arr,i,j+1,m,n);

}


int main(){

    int N = 5;

    int **arr = new int*[N];

    for (size_t i = 0; i < N; i++)
    {
        arr[i]=new int[N];
    }
    
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            arr[i][j] = 0;
        }
        
    }

    
    arr[1][0] =1 ;
    arr[1][1] =1 ;
    arr[2][1] =1 ;
    arr[2][2] =1 ;
    arr[3][1] =1 ;
    arr[3][0] =1 ;
    arr[3][2] =1 ;
    arr[4][3] =1 ;
    
    printArr(arr,5);

    std::cout << count(arr,0,0,4,4) << std::endl;

    return 0;
}