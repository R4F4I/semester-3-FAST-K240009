/*

Task#6: . Implement the array given in the heading of binary search topic, sort it and find the
value corresponding to to your last two digits of the roll number
(if its not in the array add a value somewhere in between the array) and find it via binary search.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;


int binSearch(int arr[],int target, int start,int end){
    int mid = (start+end)/2;

    if (arr[mid]==target)
        return mid;


    if (arr[mid]>target)
        return binSearch(arr,target,start,mid);
    if (arr[mid]<target)
        return binSearch(arr,target,mid,end);
    
    return -1;
}


int main(){

    //         0 1 2 3 4 5 6 7 8 9 10 11 12 13
    int arr[]={1,2,2,3,4,5,5,5,6,8,10,34,51,61};
    std::cout << binSearch(arr,34,0,13) << std::endl;


    return 0;
}