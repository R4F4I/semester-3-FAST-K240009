/*

placing n queens on a n x n board, such that they are not in eac others way

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

bool isSafe(int** arr,int n,int m, int size){
    // check if horizontally, or vertically or diagonally if there is no queen find
    // for (size_t i = 0; i < size; i++)
    // {
    //     if (arr[n+i][m+i]==1)
    //     {
    //         return false;
    //     }
    //     if (arr[n-i][m+i]==1)
    //     {
    //         return false;
    //     }
    //     if (arr[n+i][m-i]==1)
    //     {
    //         return false;
    //     }
    //     if (arr[n-i][m-i]==1)
    //     {
    //         return false;
    //     }
        
    //     if (arr[n][i]==1)
    //     {
    //         return false;
    //     }
    //     if (arr[i][m]==1)
    //     {
    //         return false;
    //     }
        
    // }



    return true;

}



template <typename T>
void printArr(T **arr, int size){
    cout<<endl;
    for (size_t i = 0; i < size; i++){
        for (size_t j = 0; j < size; j++){
         std::cout << arr[i][j]<< " ";
        }
        cout<<endl;
    }
}


/* 
start from beginning 0 0
check if no queens, then place 1
move to next col ->  recursive call
start from 1 0, check if safe, if not move ahead
if n<size and m==size, then backtrack
do  this until last col, if placeQueens(or n) < size
then backtrack, and place the prev ahead
if cant then backtrack until placedQueen(or n) = 0 or n==size

- base case:
    - n== size
    - 

- call
    - after placing,

- backtrack
    - n<size and m==size

*/

bool placedQ(int** arr, int n, int m, int size){

    if (n==size){
        std::cout << "completed!" << std::endl;
        return true;
    }
    if (isSafe(arr,n,m,size)){
        arr[n][m]=1;
        std::cout << "placed at " <<n<<m<< std::endl;
        printArr(arr,size);
    }else{
        std::cout << "finding the correct spot" << std::endl;
        while (m!=size)
        {
            if (isSafe(arr,n,m,size)){
                arr[n][m]=1;
                std::cout << "  found!" << std::endl;
            }
            m++;
        }
        std::cout << "  failed" << std::endl;
        // could not find any valid row in n
        return false;
    }
    

    if (!placedQ(arr,n+1,0,size)) // start from starting of the nth col
    {
        // backtrack
        arr[n][m] = 0;
        std::cout << "backtracking" << std::endl;
    }
    
    return false;

}


int main(){

    // init 2d arr
    int** arr;
    int n;
    cout<<"choose size of arr: ";cin>>n;
    arr = new int*[n];
    for (size_t i = 0; i < n; i++)
    {
        arr[i] = new int[n];
    }
    
    // init 2d arr to 0
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            arr[i][j] = 0;
        }
        
    }
    arr[1][2]=1;

    printArr(arr,n);
    
    // bool t = placedQ(arr,0,0,n);
    // printArr(arr,n);

    std::cout << isSafe(arr,1,4,3) << std::endl;



        return 0;
}