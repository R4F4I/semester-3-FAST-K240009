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


//1. in the ith iteration choose the find the smallest val from the unsorted half, 
//2. when the smallest is found run a new loop (in reverse) to compare the least with all the previous values
//3. if a val is greater than the smallest, swap

// void insertionSort(int arr[], int size){
//     int least;

//     //1. in the ith iteration choose the find the smallest val from the unsorted half, 
//     for (size_t i = 0; i < size; i++)
//     {
//         least = i;
//         // this loop will limit to the unsorted half
//         for (size_t j = i; j < size; j++)
//         {
//             if (arr[least]>arr[j])
//             {
//                 least=j;
//                 for (size_t k = i; k > 0; k--)
//                 {
//                     if (arr[least]>arr[k])
//                     {
//                         swap(arr[k],arr[least]);
//                     }
//                 }
//             }
//         }
//     }
// }

// 1. all val of left are sorted
// 2. pick the first val from right 'key'
// 3. compare key with all val at the left
// 4. when key<val, shift all the val in arr to the right side
// 5. insert the key


void insertionSort(int arr[], int size){
    // 1. all val of left are sorted
    for (size_t i = 0; i < size; i++){
        // 2. pick the first val from right ('key')
        int key = arr[i];
        // 3. compare key with all val at the left
        // 4. until key<val, shift all the val in arr to the right side
        int j = i-1;
        while (j>=0 && arr[j]>key)
        {
            // shift
            arr[j+1]=arr[j];
            j--;
            printArr(arr,size);
        }
        // 5. insert the key
        arr[j+1]=key;
    }
}


void insertionSortV2(int arr[], int size){
    int key;

    //1. in the ith iteration choose the find the smallest val from the unsorted half, 
    for (size_t i = 0; i < size; i++)
    {
        // key chosen from the right half
        key = arr[i];
        int j = i-1;
        // this loop will limit to the unsorted half
        // loop val < key
        for (;j >=0; j--)
        {
            // shift
            arr[j+1]=arr[j];
            // if val is lesser than key stop shifting
            if (arr[j]<key)
            {
                break;
            }
            
        }
        // insert
        arr[j+1]=key;
    }
}


void insertionSort(int arr[], int size, int dir){ // 1 for asc, -1 for desc
    // 1. all val of left are sorted
    for (size_t i = 0; i < size; i++){
        // 2. pick the first val from right ('key')
        int key = arr[i];
        // 3. compare key with all val at the left
        // 4. until key<val, shift all the val in arr to the right side
        int j = i-1;
        if (dir==1)
        {
            while (j>=0 && arr[j]>key)
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
            while (j>=0 && arr[j]<key)
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

void insertionSort(int arr[], int size){
    // 1. all val of left are sorted
    for (size_t i = 0; i < size; i++){
        // 2. pick the first val from right ('key')
        int key = arr[i];
        // 3. compare key with all val at the left
        // 4. until key<val, shift all the val in arr to the right side
        int j = i-1;
        while (j>=0 && arr[j]>key)
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


int main(){

    

    int arr[] = {29,10,14,37,9,9};
    printArr(arr,6);
    
    insertionSortV2(arr,6);
    
    printArr(arr,6);



    return 0;
}