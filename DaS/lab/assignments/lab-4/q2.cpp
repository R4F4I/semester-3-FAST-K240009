/*

Let arr[9] = { 20, 12, 15, 2, 10, 1, 13, 9, 5} now sort the array in such a way that
maximum element must be at middle of the array and rest of array must be sorted in ascending
order do this using insertion sort.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

/* 

acending half -> Largest -> ascending half
for this first sort asc
then sort the greater half desc, which move the largest in the middle
then sort the greater half w/o the largest val in asc,

*/

#include <iostream>

using namespace std;



void printArr(int arr[], int size){

    
    for (size_t i = 0; i < size; i++)
    {
        std::cout << arr[i]<< " ";
    }
    cout<<endl;

}




// 1. all val of left are sorted
// 2. pick the first val from right 'key'
// 3. compare key with all val at the left
// 4. when key<val, shift all the val in arr to the right side
// 5. insert the key


void insertionSort(int arr[], int dir, int S,int E){ // 1 for asc, -1 for desc, S=starting point E = ending point
    // 1. all val of left are sorted
    for (size_t i = S; i < E; i++){
        // 2. pick the first val from right ('key')
        int key = arr[i];
        // 3. compare key with all val at the left
        // 4. until key<val, shift all the val in arr to the right side
        int j = i-1;
        if (dir==1)
        {
            while (j>=S && arr[j]>key)
            {
                // shift
                arr[j+1]=arr[j];
                j--;
                // printArr(arr,size);
            }
            // 5. insert the key
            arr[j+1]=key;
        }
        if (dir==-1)
        {
            while (j>=S && arr[j]<key)
            {
                // shift
                arr[j+1]=arr[j];
                j--;
                // printArr(arr,size);
            }
            // 5. insert the key
            arr[j+1]=key;
        }
        
    }
}


int main(){

    int arr[9] = { 20, 12, 15, 2, 10, 1, 13, 9, 5};
    printArr(arr,9);

    insertionSort(arr,1,0,9);
    printArr(arr,9);

    insertionSort(arr,-1,4,9);
    printArr(arr,9);

    insertionSort(arr,1,5,9);
    printArr(arr,9);


    return 0;
}