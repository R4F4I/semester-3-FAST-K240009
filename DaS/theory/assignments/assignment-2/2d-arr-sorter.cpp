/*

create an NxN array and sort row wise and column wise

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;


void printArr(int** arr, int n){
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            std::cout << arr[i][j] <<" ";
        }
        std::cout << std::endl;
    }
    
}


void arrSorter(int** arr, int n){
    bool swapped;
    int temp;
    for (size_t i = 0; i < n; i++)
    {
        // first sort all the rows
        for (size_t j = 0; j < n; j++)
        {
            swapped = false;
            for (size_t k = 0; k < n-j-1; k++)
            {
                if (arr[i][k]> arr[i][k+1])
                {
                    temp = arr[i][k+1];
                    arr[i][k+1] = arr[i][k];
                    arr[i][k] = temp;
                }
            }
        }
    }


    for (size_t i = 0; i < n; i++)
    {
        // first sort all the columns
        for (size_t j = 0; j < n; j++)
        {
            swapped = false;
            for (size_t k = 0; k < n-j-1; k++)
            {
                if (arr[k][i]> arr[k+1][i])
                {
                    temp = arr[k+1][i];
                    arr[k+1][i] = arr[k][i];
                    arr[k][i] = temp;
                }
            }
        }
    }
}


int main(){
    int size = 5;

    
    int sourceArr[5][5] = {
        {23, 5, 89, 11, 42},
        {7, 65, 33, 91, 19},
        {54, 8, 77, 2, 60},
        {30, 99, 15, 48, 73},
        {1, 82, 36, 68, 25}
    };

    // done due cpp pointer limitations
    int** squareArray = new int*[size];

    for (size_t i = 0; i < size; i++)
    {
        squareArray[i] = new int[size];
    }
    

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            squareArray[i][j] = sourceArr[i][j];
        }
        
    }
    
    std::cout << "before sorting: \n===================" << std::endl;
    printArr(squareArray, 5);
    
    arrSorter(squareArray, size);
    std::cout << "\n\nafter sorting: \n===================" << std::endl;
    printArr(squareArray, 5);




    return 0;
}